import ast.*;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class ASTConstructorVisitor extends CBaseVisitor<ASTNode> {

    private static class Flags {
        public boolean hasError;
        public boolean inFunctionCall;
        public boolean inFunctionCallParameterList;
        public boolean inFunctionDeclarator;
        public boolean inIteration;
        public boolean hasReturned;
        public boolean notNeedPush;
        public boolean inArrayDeclarator;
        public boolean inAssignExpression;

        public Flags() {
            hasError = false;
            inFunctionCall = false;
            inFunctionCallParameterList = false;
            inFunctionDeclarator = false;
            inIteration = false;
            hasReturned = false;
            notNeedPush = false;
            inArrayDeclarator = false;
            inAssignExpression = false;
        }
    }

    private final Flags flags = new Flags();

    public static class IdentifierSymbol {
        public String type;
        public String name;
        public Integer size;

        public IdentifierSymbol(String type, String name, Integer size) {
            this.type = type;
            this.name = name;
            this.size = size;
        }
    }

    public final List<List<IdentifierSymbol>> identifierSymbolTable = new ArrayList<>();

    public final List<IdentifierSymbol> identifierSymbolRoughTable = new ArrayList<>();

    public static class FunctionDeclarationSymbol {
        public String type;
        public String name;
        public List<IdentifierSymbol> parameter;

        public FunctionDeclarationSymbol(String type, String name) {
            this.type = type;
            this.name = name;
            this.parameter = new ArrayList<>();
        }
    }

    public final List<FunctionDeclarationSymbol> functionDeclarationSymbolTable = new ArrayList<>();

    public Integer tableIndex = 0;

    private final Stack<Integer> tableStack = new Stack<>();

    public static class IntermediateCode {
        public String op;
        public String arg_a;
        public String arg_b;
        public String dst;
        public String code;

        public IntermediateCode(String op, String arg_a, String arg_b, String dst) {
            this.op = op;
            this.arg_a = arg_a;
            this.arg_b = arg_b;
            this.dst = dst;
            this.code = this.toString();
            // this.saveToFile("test/ic_test/1.out");
        }

        @Override
        public String toString() {
            // System.out.println("[ " + op + " , " + arg_a + " , " + arg_b + " , " + dst + " ]");
            return "[ " + op + " , " + arg_a + " , " + arg_b + " , " + dst + " ]";
        }

        public void saveToFile(String filepath) {
            try {
                File file = new File(filepath);
                FileWriter fileWriter = new FileWriter(file.getName(), true);
                fileWriter.write(this.toString() + "\n");
                fileWriter.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private static class IntermediateSymbol {
        public Integer index;

        public IntermediateSymbol() {
            this.index = 0;
        }

        public void inc() {
            index++;
        }

        @Override
        public String toString() {
            return "_" + index;
        }
    }

    private static final IntermediateSymbol intermediateSymbol = new IntermediateSymbol();

    private final Stack<String> intermediateSymbolTable = new Stack<>();

    private final Stack<String> loopSymbolTable = new Stack<>();

    private final Stack<String> functionSymbolTable = new Stack<>();

    private Integer arraySize = 0;

    private final List<String> stringLiteralList = new ArrayList<>();

    public final List<String> targetCode = new ArrayList<>();

    public static void printJsonString(ASTNode astNode) {
        ObjectMapper mapper = new ObjectMapper();
        try {
            String jsonString = mapper.writeValueAsString(astNode);
            System.out.println(jsonString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public ASTNode visitPrimaryExpression(CParser.PrimaryExpressionContext ctx) {
        ASTNode astNode;
        if (ctx.Identifier() != null) {
            astNode = new ASTIdentifier(ctx.Identifier().getSymbol().getText(),
                    ctx.Identifier().getSymbol().getTokenIndex());
            if (!flags.inFunctionCall) {
                ((ASTIdentifier) astNode).value = "_" + ((ASTIdentifier) astNode).value;
            }
            // Get symbol for IC
            intermediateSymbolTable.push(((ASTIdentifier) astNode).value);
            // Generate target code
            if (!flags.notNeedPush) {
                targetCode.add("\tPUSH\t" + ((ASTIdentifier) astNode).value + "\n");
            }
            if (flags.inAssignExpression) {
                targetCode.add("\tLEA\tEAX, " + ((ASTIdentifier) astNode).value + "\n");
                targetCode.add("\tPUSH\tEAX\n");
            }
        } else if (ctx.IntegerConstant() != null) {
            astNode = new ASTIntegerConstant(Integer.parseInt(ctx.IntegerConstant().getSymbol().getText()),
                    ctx.IntegerConstant().getSymbol().getTokenIndex());
            // Get symbol for IC
            intermediateSymbolTable.push(((ASTIntegerConstant) astNode).value.toString());
            if (flags.inArrayDeclarator) {
                arraySize = ((ASTIntegerConstant) astNode).value;
            } else {
                if (!flags.notNeedPush) {
                    // Generate target code
                    targetCode.add("\tMOV\tEAX, " + ((ASTIntegerConstant) astNode).value.toString() + "\n");
                    targetCode.add("\tPUSH\tEAX\n");
                }
            }
        } else if (ctx.FloatingConstant() != null) {
            astNode = new ASTFloatConstant(Double.parseDouble(ctx.FloatingConstant().getSymbol().getText()),
                    ctx.FloatingConstant().getSymbol().getTokenIndex());
            // Get symbol for IC
            intermediateSymbolTable.push(((ASTFloatConstant) astNode).value.toString());
        } else if (ctx.CharacterConstant() != null) {
            astNode = new ASTCharConstant(ctx.CharacterConstant().getSymbol().getText(),
                    ctx.CharacterConstant().getSymbol().getTokenIndex());
            // Get symbol for IC
            intermediateSymbolTable.push(((ASTCharConstant) astNode).value);
        } else if (ctx.StringLiteral() != null) {
            astNode = new ASTStringConstant(ctx.StringLiteral().getSymbol().getText(),
                    ctx.StringLiteral().getSymbol().getTokenIndex());
            stringLiteralList.add(((ASTStringConstant) astNode).value);
            // Get symbol for IC
            intermediateSymbolTable.push("OFFSET _string_" + stringLiteralList.size());
            if (!flags.notNeedPush) {
                // Generate target code
                targetCode.add("\tMOV\tEAX, " + "OFFSET _string_" + stringLiteralList.size() + "\n");
                targetCode.add("\tPUSH\tEAX\n");
            }
        } else {
            astNode = visitExpression(ctx.expression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitPostfixExpression(CParser.PostfixExpressionContext ctx) {
        ASTNode astNode;
        if (ctx.expression() != null) {
            ASTExpression postfixExpression = (ASTExpression) visitPostfixExpression(ctx.postfixExpression());
            List<ASTExpression> astNodeList = new LinkedList<>();
            for (int i = 0; i < ctx.expression().assignmentExpression().size(); i++)
                astNodeList.add((ASTExpression) visitAssignmentExpression(ctx.expression().assignmentExpression(i)));
            astNode = new ASTArrayAccess(postfixExpression, astNodeList);
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            String tempDestSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("[]", tempDestSymbol, tempSymbol,
                    intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
            // Generate target code
            if (flags.inAssignExpression) {
                targetCode.add("\tPOP\tESI\n");
                targetCode.add("\tLEA\tEAX, " + tempDestSymbol + "[ESI]\n");
                targetCode.add("\tPUSH\tEAX\n");
            } else {
                targetCode.add("\tPOP\tESI\n");
                targetCode.add("\tPUSH\t" + tempDestSymbol + "[ESI]\n");
            }
        } else if (ctx.RightParen() != null && ctx.LeftParen() != null) {
            flags.inFunctionCallParameterList = true;
            List<ASTExpression> astNodeList = new LinkedList<>();
            List<String> argList = new ArrayList<>();
            if (ctx.argumentExpressionList() != null) {
                for (int i = 0; i < ctx.argumentExpressionList().assignmentExpression().size(); i++) {
                    astNodeList.add((ASTExpression) visitAssignmentExpression(ctx.argumentExpressionList().assignmentExpression(i)));
                    // Discard arguments for intermediate code
                    argList.add(intermediateSymbolTable.pop());
                }
            }
            flags.inFunctionCallParameterList = false;
            flags.notNeedPush = true;
            flags.inFunctionCall = true;
            astNode = new ASTFunctionCall((ASTExpression) visitPostfixExpression(ctx.postfixExpression()), astNodeList);
            flags.inFunctionCall = false;
            flags.notNeedPush = false;
            // Generate intermediate code
            String funSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("FunCall", funSymbol, "",
                    intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
            // Generate target code
            targetCode.add("\tCALL\t" + funSymbol + "\n");
            targetCode.add("\tPUSH\tEAX\n");
        } else if (ctx.PlusPlus() != null || ctx.MinusMinus() != null) {
            ASTToken astToken;
            if (ctx.PlusPlus() != null) {
                astToken = new ASTToken(ctx.PlusPlus().getSymbol().getText(),
                        ctx.PlusPlus().getSymbol().getTokenIndex());
            } else {
                astToken = new ASTToken(ctx.MinusMinus().getSymbol().getText(),
                        ctx.MinusMinus().getSymbol().getTokenIndex());
            }
            flags.notNeedPush = true;
            astNode = new ASTPostfixExpression((ASTExpression) visitPostfixExpression(ctx.postfixExpression()),
                    astToken);
            flags.notNeedPush = false;
            // Generate intermediate code
            String symbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Postfix " + astToken.value,
                    symbol, "", intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
            // Generate target code
            targetCode.add("\tMOV\tEAX, " + symbol + "\n");
            targetCode.add("\tINC\tEAX\n");
            targetCode.add("\tPUSH\tEAX\n");
            targetCode.add("\tMOV\t" + symbol + ", EAX\n");
        } else {
            astNode = visitPrimaryExpression(ctx.primaryExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitUnaryExpression(CParser.UnaryExpressionContext ctx) {
        ASTNode astNode;
        if (ctx.PlusPlus() != null || ctx.MinusMinus() != null) {
            ASTToken astToken = new ASTToken(ctx.PlusPlus() != null ? ctx.PlusPlus().getSymbol().getText() :
                    ctx.MinusMinus().getSymbol().getText(),
                    ctx.PlusPlus() != null ? ctx.PlusPlus().getSymbol().getTokenIndex() :
                            ctx.MinusMinus().getSymbol().getTokenIndex());
            astNode = new ASTUnaryExpression(astToken, (ASTExpression) visitUnaryExpression(ctx.unaryExpression()));
            // Generate intermediate code
            IntermediateCode intermediateCode = new IntermediateCode("Unary " + astToken.value,
                    intermediateSymbolTable.pop(), "", intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
        } else if (ctx.unaryOperator() != null) {
            ASTToken astToken;
            if (ctx.unaryOperator().And() != null) {
                astToken = new ASTToken(ctx.unaryOperator().And().getSymbol().getText(),
                        ctx.unaryOperator().And().getSymbol().getTokenIndex());
            } else if (ctx.unaryOperator().Star() != null) {
                astToken = new ASTToken(ctx.unaryOperator().Star().getSymbol().getText(),
                        ctx.unaryOperator().Star().getSymbol().getTokenIndex());
            } else if (ctx.unaryOperator().Plus() != null) {
                astToken = new ASTToken(ctx.unaryOperator().Plus().getSymbol().getText(),
                        ctx.unaryOperator().Plus().getSymbol().getTokenIndex());
            } else if (ctx.unaryOperator().Minus() != null) {
                astToken = new ASTToken(ctx.unaryOperator().Minus().getSymbol().getText(),
                        ctx.unaryOperator().Minus().getSymbol().getTokenIndex());
            } else if (ctx.unaryOperator().Tilde() != null) {
                astToken = new ASTToken(ctx.unaryOperator().Tilde().getSymbol().getText(),
                        ctx.unaryOperator().Tilde().getSymbol().getTokenIndex());
            } else {
                astToken = new ASTToken(ctx.unaryOperator().Not().getSymbol().getText(),
                        ctx.unaryOperator().Not().getSymbol().getTokenIndex());
            }
            astNode = new ASTUnaryExpression(astToken, (ASTExpression) visitCastExpression(ctx.castExpression()));
            // Generate intermediate code
            IntermediateCode intermediateCode = new IntermediateCode("Unary " + astToken.value,
                    intermediateSymbolTable.pop(), "", intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
        } else if (ctx.Sizeof() != null && ctx.unaryExpression() != null) {
            ASTToken astToken = new ASTToken(ctx.Sizeof().getSymbol().getText(),
                    ctx.Sizeof().getSymbol().getTokenIndex());
            astNode = new ASTUnaryExpression(astToken, (ASTExpression) visitUnaryExpression(ctx.unaryExpression()));
            // Generate intermediate code
            IntermediateCode intermediateCode = new IntermediateCode("Unary " + astToken.value,
                    intermediateSymbolTable.pop(), "", intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
        } else if (ctx.Sizeof() != null && ctx.typeName() != null) {
            ASTToken astToken = new ASTToken(ctx.Sizeof().getSymbol().getText(),
                    ctx.Sizeof().getSymbol().getTokenIndex());
            astNode = new ASTUnaryExpression(astToken, (ASTExpression) visitTypeName(ctx.typeName()));
            // Generate intermediate code
            IntermediateCode intermediateCode = new IntermediateCode("Unary " + astToken.value,
                    intermediateSymbolTable.pop(), "", intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
        } else {
            astNode = visitPostfixExpression(ctx.postfixExpression());
        }
        return astNode;
    }

    @Override

    public ASTNode visitCastExpression(CParser.CastExpressionContext ctx) {
        ASTNode astNode;
        if (ctx.typeName() != null) {
            astNode = new ASTCastExpression((ASTTypename) visitTypeName(ctx.typeName()),
                    (ASTExpression) visitCastExpression(ctx.castExpression()));
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Cast",
                    intermediateSymbolTable.pop(), tempSymbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
        } else {
            astNode = visitUnaryExpression(ctx.unaryExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitMultiplicativeExpression(CParser.MultiplicativeExpressionContext ctx) {
        ASTNode astNode;
        ASTToken astToken;
        if (ctx.Star() != null || ctx.Div() != null || ctx.Mod() != null) {
            if (ctx.Star() != null) {
                astToken = new ASTToken(ctx.Star().getSymbol().getText(), ctx.Star().getSymbol().getTokenIndex());
            } else if (ctx.Div() != null) {
                astToken = new ASTToken(ctx.Div().getSymbol().getText(), ctx.Div().getSymbol().getTokenIndex());
            } else {
                astToken = new ASTToken(ctx.Mod().getSymbol().getText(), ctx.Mod().getSymbol().getTokenIndex());
            }
            astNode = new ASTBinaryExpression(astToken,
                    (ASTExpression) visitMultiplicativeExpression(ctx.multiplicativeExpression()),
                    (ASTExpression) visitCastExpression(ctx.castExpression()));
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Binary " + astToken.value,
                    intermediateSymbolTable.pop(), tempSymbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
            // Generate target code
            if (ctx.Star() != null) {
                targetCode.add("\tPOP\tEBX\n");
                targetCode.add("\tPOP\tEAX\n");
                targetCode.add("\tMUL\tEBX\n");
                targetCode.add("\tPUSH\tEAX\n");
            } else if (ctx.Div() != null) {
                targetCode.add("\tPOP\tEBX\n");
                targetCode.add("\tPOP\tEAX\n");
                targetCode.add("\tXOR\tEDX, EDX\n");
                targetCode.add("\tDIV\tEBX\n");
                targetCode.add("\tPUSH\tEAX\n");
            } else {
                targetCode.add("\tPOP\tEBX\n");
                targetCode.add("\tPOP\tEAX\n");
                targetCode.add("\tDIV\tEBX\n");
                targetCode.add("\tPUSH\tEDX\n");
            }
        } else {
            astNode = visitCastExpression(ctx.castExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitAdditiveExpression(CParser.AdditiveExpressionContext ctx) {
        ASTNode astNode;
        ASTToken astToken;
        if (ctx.Plus() != null || ctx.Minus() != null) {
            if (ctx.Plus() != null) {
                astToken = new ASTToken(ctx.Plus().getSymbol().getText(), ctx.Plus().getSymbol().getTokenIndex());
            } else {
                astToken = new ASTToken(ctx.Minus().getSymbol().getText(), ctx.Minus().getSymbol().getTokenIndex());
            }
            astNode = new ASTBinaryExpression(astToken,
                    (ASTExpression) visitAdditiveExpression(ctx.additiveExpression()),
                    (ASTExpression) visitMultiplicativeExpression(ctx.multiplicativeExpression()));
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Binary " + astToken.value,
                    intermediateSymbolTable.pop(), tempSymbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
            // Generate target code
            if (ctx.Plus() != null) {
                targetCode.add("\tPOP\tEBX\n");
                targetCode.add("\tPOP\tEAX\n");
                targetCode.add("\tADD\tEAX, EBX\n");
                targetCode.add("\tPUSH\tEAX\n");
            } else {
                targetCode.add("\tPOP\tEBX\n");
                targetCode.add("\tPOP\tEAX\n");
                targetCode.add("\tSUB\tEAX, EBX\n");
                targetCode.add("\tPUSH\tEAX\n");
            }
        } else {
            astNode = visitMultiplicativeExpression(ctx.multiplicativeExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitRelationalExpression(CParser.RelationalExpressionContext ctx) {
        ASTNode astNode;
        ASTToken astToken;
        if (ctx.Less() != null || ctx.Greater() != null || ctx.LessEqual() != null || ctx.GreaterEqual() != null) {
            if (ctx.Less() != null) {
                astToken = new ASTToken(ctx.Less().getSymbol().getText(), ctx.Less().getSymbol().getTokenIndex());
            } else if (ctx.Greater() != null) {
                astToken = new ASTToken(ctx.Greater().getSymbol().getText(), ctx.Greater().getSymbol().getTokenIndex());
            } else if (ctx.LessEqual() != null) {
                astToken = new ASTToken(ctx.LessEqual().getSymbol().getText(),
                        ctx.LessEqual().getSymbol().getTokenIndex());
            } else {
                astToken = new ASTToken(ctx.GreaterEqual().getSymbol().getText(),
                        ctx.GreaterEqual().getSymbol().getTokenIndex());
            }
            astNode = new ASTBinaryExpression(astToken,
                    (ASTExpression) visitRelationalExpression(ctx.relationalExpression()),
                    (ASTExpression) visitAdditiveExpression(ctx.additiveExpression()));
            String jFLabel = "L" + intermediateSymbol + "F";
            String jNLabel = "L" + intermediateSymbol + "N";
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Binary " + astToken.value,
                    intermediateSymbolTable.pop(), tempSymbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
            // Generate target code
            targetCode.add("\tPOP\tEBX\n");
            targetCode.add("\tPOP\tEAX\n");
            targetCode.add("\tCMP\tEAX, EBX\n");
            if (ctx.Less() != null) {
                targetCode.add("\tJGE\t" + jFLabel + "\n");
                targetCode.add("\tMOV\tEAX, 1\n");
                targetCode.add("\tPUSH\tEAX\n");
                targetCode.add("\tJMP\t" + jNLabel + "\n");
            } else if (ctx.Greater() != null) {
                targetCode.add("\tJLE\t" + jFLabel + "\n");
                targetCode.add("\tMOV\tEAX, 1\n");
                targetCode.add("\tPUSH\tEAX\n");
                targetCode.add("\tJMP\t" + jNLabel + "\n");
            } else if (ctx.LessEqual() != null) {
                targetCode.add("\tJG\t" + jFLabel + "\n");
                targetCode.add("\tMOV\tEAX, 1\n");
                targetCode.add("\tPUSH\tEAX\n");
                targetCode.add("\tJMP\t" + jNLabel + "\n");
            } else {
                targetCode.add("\tJL\t" + jFLabel + "\n");
                targetCode.add("\tMOV\tEAX, 1\n");
                targetCode.add("\tPUSH\tEAX\n");
                targetCode.add("\tJMP\t" + jNLabel + "\n");
            }
            targetCode.add(jFLabel + ":\n");
            targetCode.add("\tMOV\tEAX, 0\n");
            targetCode.add("\tPUSH\tEAX\n");
            targetCode.add(jNLabel + ":\n");
        } else {
            astNode = visitAdditiveExpression(ctx.additiveExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitEqualityExpression(CParser.EqualityExpressionContext ctx) {
        ASTNode astNode;
        ASTToken astToken;
        if (ctx.Equal() != null || ctx.NotEqual() != null) {
            if (ctx.Equal() != null) {
                astToken = new ASTToken(ctx.Equal().getSymbol().getText(), ctx.Equal().getSymbol().getTokenIndex());
            } else {
                astToken = new ASTToken(ctx.NotEqual().getSymbol().getText(),
                        ctx.NotEqual().getSymbol().getTokenIndex());
            }
            astNode = new ASTBinaryExpression(astToken,
                    (ASTExpression) visitEqualityExpression(ctx.equalityExpression()),
                    (ASTExpression) visitRelationalExpression(ctx.relationalExpression()));
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Binary " + astToken.value,
                    intermediateSymbolTable.pop(), tempSymbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
            // Generate target code
            targetCode.add("\tPOP\tEBX\n");
            targetCode.add("\tPOP\tEAX\n");
            targetCode.add("\tCMP\tEAX, EBX\n");
            String jFLabel = "L" + intermediateSymbolTable.peek() + "F";
            String jNLabel = "L" + intermediateSymbolTable.peek() + "N";
            if (ctx.Equal() != null) {
                targetCode.add("\tJNE\t" + jFLabel + "\n");
                targetCode.add("\tMOV\tEAX, 1\n");
                targetCode.add("\tPUSH\tEAX\n");
                targetCode.add("\tJMP\t" + jNLabel + "\n");
            } else {
                targetCode.add("\tJE\t" + jFLabel + "\n");
                targetCode.add("\tMOV\tEAX, 1\n");
                targetCode.add("\tPUSH\tEAX\n");
                targetCode.add("\tJMP\t" + jNLabel + "\n");
            }
            targetCode.add(jFLabel + ":\n");
            targetCode.add("\tMOV\tEAX, 0\n");
            targetCode.add("\tPUSH\tEAX\n");
            targetCode.add(jNLabel + ":\n");
        } else {
            astNode = visitRelationalExpression(ctx.relationalExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitAndExpression(CParser.AndExpressionContext ctx) {
        ASTNode astNode;
        ASTToken astToken;
        if (ctx.And() != null) {
            astToken = new ASTToken(ctx.And().getSymbol().getText(), ctx.And().getSymbol().getTokenIndex());
            astNode = new ASTBinaryExpression(astToken,
                    (ASTExpression) visitAndExpression(ctx.andExpression()),
                    (ASTExpression) visitEqualityExpression(ctx.equalityExpression()));
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Binary " + astToken.value,
                    intermediateSymbolTable.pop(), tempSymbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
        } else {
            astNode = visitEqualityExpression(ctx.equalityExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitExclusiveOrExpression(CParser.ExclusiveOrExpressionContext ctx) {
        ASTNode astNode;
        ASTToken astToken;
        if (ctx.Caret() != null) {
            astToken = new ASTToken(ctx.Caret().getSymbol().getText(), ctx.Caret().getSymbol().getTokenIndex());
            astNode = new ASTBinaryExpression(astToken,
                    (ASTExpression) visitExclusiveOrExpression(ctx.exclusiveOrExpression()),
                    (ASTExpression) visitAndExpression(ctx.andExpression()));
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Binary " + astToken.value,
                    intermediateSymbolTable.pop(), tempSymbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
        } else {
            astNode = visitAndExpression(ctx.andExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitInclusiveOrExpression(CParser.InclusiveOrExpressionContext ctx) {
        ASTNode astNode;
        ASTToken astToken;
        if (ctx.Or() != null) {
            astToken = new ASTToken(ctx.Or().getSymbol().getText(), ctx.Or().getSymbol().getTokenIndex());
            astNode = new ASTBinaryExpression(astToken,
                    (ASTExpression) visitInclusiveOrExpression(ctx.inclusiveOrExpression()),
                    (ASTExpression) visitExclusiveOrExpression(ctx.exclusiveOrExpression()));
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Binary " + astToken.value,
                    intermediateSymbolTable.pop(), tempSymbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
        } else {
            astNode = visitExclusiveOrExpression(ctx.exclusiveOrExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitLogicalAndExpression(CParser.LogicalAndExpressionContext ctx) {
        ASTNode astNode;
        ASTToken astToken;
        if (ctx.AndAnd() != null) {
            astToken = new ASTToken(ctx.AndAnd().getSymbol().getText(), ctx.AndAnd().getSymbol().getTokenIndex());
            astNode = new ASTBinaryExpression(astToken,
                    (ASTExpression) visitLogicalAndExpression(ctx.logicalAndExpression()),
                    (ASTExpression) visitInclusiveOrExpression(ctx.inclusiveOrExpression()));
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Binary " + astToken.value,
                    intermediateSymbolTable.pop(), tempSymbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
        } else {
            astNode = visitInclusiveOrExpression(ctx.inclusiveOrExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitLogicalOrExpression(CParser.LogicalOrExpressionContext ctx) {
        ASTNode astNode;
        ASTToken astToken;
        if (ctx.OrOr() != null) {
            astToken = new ASTToken(ctx.OrOr().getSymbol().getText(), ctx.OrOr().getSymbol().getTokenIndex());
            astNode = new ASTBinaryExpression(astToken,
                    (ASTExpression) visitLogicalOrExpression(ctx.logicalOrExpression()),
                    (ASTExpression) visitLogicalAndExpression(ctx.logicalAndExpression()));
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Binary " + astToken.value,
                    intermediateSymbolTable.pop(), tempSymbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
        } else {
            astNode = visitLogicalAndExpression(ctx.logicalAndExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitConditionalExpression(CParser.ConditionalExpressionContext ctx) {
        ASTNode astNode;
        if (ctx.logicalOrExpression() != null && ctx.expression() != null && ctx.conditionalExpression() != null) {
            ASTExpression logicalOrExpression = (ASTExpression) visitLogicalOrExpression(ctx.logicalOrExpression());
            // TODO: Need to take the return value of this expression into consideration
            // Generate intermediate code
            IntermediateCode intermediateCodeCond = new IntermediateCode("?:",
                    intermediateSymbolTable.pop(), "", intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            String jFLabel = "L" + intermediateSymbol + "F";
            String jNLabel = "L" + intermediateSymbol + "N";
            IntermediateCode intermediateCodeJF = new IntermediateCode("JF", intermediateSymbol.toString(), "",
                    jFLabel);
            intermediateSymbol.inc();
            LinkedList<ASTExpression> astNodeList = new LinkedList<>();
            for (int i = 0; i < ctx.expression().assignmentExpression().size(); i++) {
                astNodeList.add((ASTExpression) visitAssignmentExpression(ctx.expression().assignmentExpression(i)));
                // Discard expression for intermediate code
                intermediateSymbolTable.pop();
            }
            // Generate intermediate code
            IntermediateCode intermediateCodeJN = new IntermediateCode("Jmp", "", "", jNLabel);
            IntermediateCode intermediateCodeJFLabel = new IntermediateCode("Label", jFLabel, "", "");
            astNode = new ASTConditionExpression(logicalOrExpression, astNodeList,
                    (ASTExpression) visitConditionalExpression(ctx.conditionalExpression()));
            IntermediateCode intermediateCodeJNLabel = new IntermediateCode("Label", jNLabel, "", "");
        } else {
            astNode = visitLogicalOrExpression(ctx.logicalOrExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitAssignmentExpression(CParser.AssignmentExpressionContext ctx) {
        ASTNode astNode;
        ASTToken astToken;
        if (ctx.unaryExpression() != null && ctx.assignmentOperator() != null && ctx.assignmentExpression() != null) {
            if (ctx.assignmentOperator().Assign() != null) {
                astToken = new ASTToken(ctx.assignmentOperator().Assign().getSymbol().getText(),
                        ctx.assignmentOperator().Assign().getSymbol().getTokenIndex());
            } else if (ctx.assignmentOperator().StarAssign() != null) {
                astToken = new ASTToken(ctx.assignmentOperator().StarAssign().getSymbol().getText(),
                        ctx.assignmentOperator().StarAssign().getSymbol().getTokenIndex());
            } else if (ctx.assignmentOperator().DivAssign() != null) {
                astToken = new ASTToken(ctx.assignmentOperator().DivAssign().getSymbol().getText(),
                        ctx.assignmentOperator().DivAssign().getSymbol().getTokenIndex());
            } else if (ctx.assignmentOperator().ModAssign() != null) {
                astToken = new ASTToken(ctx.assignmentOperator().ModAssign().getSymbol().getText(),
                        ctx.assignmentOperator().ModAssign().getSymbol().getTokenIndex());
            } else if (ctx.assignmentOperator().PlusAssign() != null) {
                astToken = new ASTToken(ctx.assignmentOperator().PlusAssign().getSymbol().getText(),
                        ctx.assignmentOperator().PlusAssign().getSymbol().getTokenIndex());
            } else if (ctx.assignmentOperator().MinusAssign() != null) {
                astToken = new ASTToken(ctx.assignmentOperator().MinusAssign().getSymbol().getText(),
                        ctx.assignmentOperator().MinusAssign().getSymbol().getTokenIndex());
            } else if (ctx.assignmentOperator().AndAssign() != null) {
                astToken = new ASTToken(ctx.assignmentOperator().AndAssign().getSymbol().getText(),
                        ctx.assignmentOperator().AndAssign().getSymbol().getTokenIndex());
            } else if (ctx.assignmentOperator().XorAssign() != null) {
                astToken = new ASTToken(ctx.assignmentOperator().XorAssign().getSymbol().getText(),
                        ctx.assignmentOperator().XorAssign().getSymbol().getTokenIndex());
            } else {
                astToken = new ASTToken(ctx.assignmentOperator().OrAssign().getSymbol().getText(),
                        ctx.assignmentOperator().OrAssign().getSymbol().getTokenIndex());
            }
            flags.notNeedPush = true;
            flags.inAssignExpression = true;
            ASTExpression expressionA = (ASTExpression) visitUnaryExpression(ctx.unaryExpression());
            flags.inAssignExpression = false;
            flags.notNeedPush = false;
            ASTExpression expressionB = (ASTExpression) visitAssignmentExpression(ctx.assignmentExpression());
            astNode = new ASTBinaryExpression(astToken, expressionA, expressionB);
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            String symbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Assign " + astToken.value,
                    symbol, tempSymbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
            // Generate target code
            if (ctx.assignmentOperator().Assign() != null) {
                targetCode.add("\tPOP\tEBX\n");
                targetCode.add("\tPOP\tEDI\n");
                targetCode.add("\tMOV\t[EDI], EBX\n");
            } else if (ctx.assignmentOperator().StarAssign() != null) {
                targetCode.add("\tPOP\tEBX\n");
                targetCode.add("\tPOP\tEDI\n");
                targetCode.add("\tMOV\tEAX, [EDI]\n");
                targetCode.add("\tMUL\tEBX\n");
                targetCode.add("\tMOV\t[EDI], EAX\n");
            } else if (ctx.assignmentOperator().DivAssign() != null) {
                targetCode.add("\tPOP\tEBX\n");
                targetCode.add("\tPOP\tEDI\n");
                targetCode.add("\tMOV\tEAX, [EDI]\n");
                targetCode.add("\tDIV\tEBX\n");
                targetCode.add("\tMOV\t[EDI], EAX\n");
            } else if (ctx.assignmentOperator().ModAssign() != null) {
                targetCode.add("\tPOP\tEBX\n");
                targetCode.add("\tPOP\tEDI\n");
                targetCode.add("\tMOV\tEAX, [EDI]\n");
                targetCode.add("\tDIV\tEBX\n");
                targetCode.add("\tMOV\t[EDI], EDX\n");
            } else if (ctx.assignmentOperator().PlusAssign() != null) {
                targetCode.add("\tPOP\tEBX\n");
                targetCode.add("\tPOP\tEDI\n");
                targetCode.add("\tMOV\tEAX, [EDI]\n");
                targetCode.add("\tADD\tEAX, EBX\n");
                targetCode.add("\tMOV\t[EDI], EAX\n");
            } else if (ctx.assignmentOperator().MinusAssign() != null) {
                targetCode.add("\tPOP\tEBX\n");
                targetCode.add("\tPOP\tEDI\n");
                targetCode.add("\tMOV\tEAX, [EDI]\n");
                targetCode.add("\tSUB\tEAX, EBX\n");
                targetCode.add("\tMOV\t[EDI], EAX\n");
            }
        } else {
            astNode = visitConditionalExpression(ctx.conditionalExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitDeclaration(CParser.DeclarationContext ctx) {
        ASTNode astNode;
        List<ASTToken> astTokenList = new LinkedList<>();
        List<ASTInitList> astInitListList = new LinkedList<>();
        for (int i = 0; i < ctx.declarationSpecifiers().declarationSpecifier().size(); i++) {
            ASTToken astToken;
            CParser.TypeSpecifierContext typeSpecifierContext =
                    ctx.declarationSpecifiers().declarationSpecifier(i).typeSpecifier();
            if (typeSpecifierContext.Void() != null) {
                astToken = new ASTToken(typeSpecifierContext.Void().getSymbol().getText(),
                        typeSpecifierContext.Void().getSymbol().getTokenIndex());
            } else if (typeSpecifierContext.Char() != null) {
                astToken = new ASTToken(typeSpecifierContext.Char().getSymbol().getText(),
                        typeSpecifierContext.Char().getSymbol().getTokenIndex());
            } else if (typeSpecifierContext.Int() != null) {
                astToken = new ASTToken(typeSpecifierContext.Int().getSymbol().getText(),
                        typeSpecifierContext.Int().getSymbol().getTokenIndex());
            } else if (typeSpecifierContext.Float() != null) {
                astToken = new ASTToken(typeSpecifierContext.Float().getSymbol().getText(),
                        typeSpecifierContext.Float().getSymbol().getTokenIndex());
            } else {
                astToken = new ASTToken(typeSpecifierContext.Double().getSymbol().getText(),
                        typeSpecifierContext.Double().getSymbol().getTokenIndex());
            }
            astTokenList.add(astToken);
        }
        int identifierSymbolCurrentIndex = identifierSymbolTable.get(tableStack.peek()).size();
        if (ctx.initDeclaratorList() != null) {
            for (int i = 0; i < ctx.initDeclaratorList().initDeclarator().size(); i++) {
                astInitListList.add((ASTInitList) visitInitDeclarator(ctx.initDeclaratorList().initDeclarator(i)));
            }
        }
        if (flags.inFunctionDeclarator) {
            Integer temp = tableStack.pop();
            identifierSymbolTable.get(tableStack.peek()).get(identifierSymbolCurrentIndex).type =
                    astTokenList.get(0).value;
            functionDeclarationSymbolTable.add(new FunctionDeclarationSymbol(
                    identifierSymbolTable.get(tableStack.peek()).get(identifierSymbolCurrentIndex).type,
                    identifierSymbolTable.get(tableStack.peek()).get(identifierSymbolCurrentIndex).name));
            tableStack.push(temp);
            /* TODO:
             *  Reverse orders of Declaration and Declarator, or intermediate code will be like
             *  [ Init , b , 1 , %0 ]
             *  [ VarDecl , b , int ,  ]
             *  not
             *  [ VarDecl , b , int ,  ]
             *  [ Init , b , 1 , %0 ]
             */
            // Generate intermediate code
            IntermediateCode intermediateCode = new IntermediateCode("FunDecl",
                    functionDeclarationSymbolTable.get(functionDeclarationSymbolTable.size() - 1).name,
                    functionDeclarationSymbolTable.get(functionDeclarationSymbolTable.size() - 1).type,
                    "");
            for (int i = 0; i < identifierSymbolTable.get(tableStack.peek()).size(); i++) {
                functionDeclarationSymbolTable.get(functionDeclarationSymbolTable.size() - 1).parameter.
                        add(new IdentifierSymbol(identifierSymbolTable.get(tableStack.peek()).get(i).type,
                                identifierSymbolTable.get(tableStack.peek()).get(i).name, 1));
                // Generate intermediate code
                IntermediateCode intermediateCodeParameter = new IntermediateCode("FunParam",
                        functionDeclarationSymbolTable.get(functionDeclarationSymbolTable.size() - 1).parameter.get(i).type,
                        functionDeclarationSymbolTable.get(functionDeclarationSymbolTable.size() - 1).parameter.get(i).name, "");
            }
            tableStack.pop();
        } else {
            for (int i = identifierSymbolCurrentIndex; i < identifierSymbolTable.get(tableStack.peek()).size(); i++) {
                identifierSymbolTable.get(tableStack.peek()).get(i).type = astTokenList.get(0).value;
                // Generate intermediate code
                IntermediateCode intermediateCode = new IntermediateCode("VarDecl",
                        identifierSymbolTable.get(tableStack.peek()).get(i).name,
                        identifierSymbolTable.get(tableStack.peek()).get(i).type, "");
                // Get all identifiers
                identifierSymbolRoughTable.add(identifierSymbolTable.get(tableStack.peek()).get(i));
            }
        }
        flags.inFunctionDeclarator = false;
        astNode = new ASTDeclaration(astTokenList, astInitListList);
        return astNode;
    }

    @Override
    public ASTNode visitInitDeclarator(CParser.InitDeclaratorContext ctx) {
        ASTNode astNode;
        List<ASTExpression> astExpressionList = new LinkedList<>();
        if (ctx.initializer() != null) {
            if (ctx.initializer().assignmentExpression() != null) {
                astExpressionList.add((ASTExpression) visitAssignmentExpression(ctx.initializer().assignmentExpression()));
            } else {
                for (int i = 0; i < ctx.initializer().initializerList().initializer().size(); i++) {
                    astExpressionList.add((ASTExpression) visitInitializer(ctx.initializer().initializerList().initializer(i)));
                    // Discard for intermediate code
                    intermediateSymbolTable.pop();
                }
            }
        }
        astNode = new ASTInitList((ASTDeclarator) visitDeclarator(ctx.declarator()), astExpressionList);
        if (ctx.initializer() != null) {
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            String symbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Init",
                    tempSymbol, symbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
            // Generate target code
            targetCode.add("\tPOP\tEAX\n");
            targetCode.add("\tMOV\t" + tempSymbol + ", EAX\n");
        }
        return astNode;
    }

    @Override
    public ASTNode visitTypeSpecifier(CParser.TypeSpecifierContext ctx) {
        if (ctx.Void() != null) {
            intermediateSymbolTable.push("void");
        } else if (ctx.Char() != null) {
            intermediateSymbolTable.push("char");
        } else if (ctx.Int() != null) {
            intermediateSymbolTable.push("int");
        } else if (ctx.Float() != null) {
            intermediateSymbolTable.push("float");
        } else {
            intermediateSymbolTable.push("double");
        }
        return super.visitTypeSpecifier(ctx);
    }

    @Override
    public ASTNode visitDeclarator(CParser.DeclaratorContext ctx) {
        return visitDirectDeclarator(ctx.directDeclarator());
    }

    @Override
    public ASTNode visitDirectDeclarator(CParser.DirectDeclaratorContext ctx) {
        ASTNode astNode;
        if (ctx.Identifier() != null) {
            ASTIdentifier astIdentifier;
            if (!flags.inFunctionDeclarator) {
                astIdentifier = new ASTIdentifier("_" + ctx.Identifier().getSymbol().getText(),
                        ctx.Identifier().getSymbol().getTokenIndex());
            } else {
                astIdentifier = new ASTIdentifier(ctx.Identifier().getSymbol().getText(),
                        ctx.Identifier().getSymbol().getTokenIndex());
            }
            identifierSymbolTable.get(tableStack.peek()).add(new IdentifierSymbol("Undefined", astIdentifier.value, 1));
            astNode = new ASTVariableDeclarator(astIdentifier);
            // Generate intermediate code
            intermediateSymbolTable.push(astIdentifier.value);
        } else if (ctx.declarator() != null) {
            astNode = visitDeclarator(ctx.declarator());
        } else if (ctx.directDeclarator() != null && ctx.assignmentExpression() != null) {
            flags.inArrayDeclarator = true;
            astNode = new ASTArrayDeclarator((ASTDeclarator) visitDirectDeclarator(ctx.directDeclarator()),
                    (ASTExpression) visitAssignmentExpression(ctx.assignmentExpression()));
            flags.inArrayDeclarator = false;
            identifierSymbolTable.get(tableStack.peek()).get(identifierSymbolTable.get(tableStack.peek()).size() - 1).size = arraySize;
        } else if (ctx.directDeclarator() != null && ctx.parameterTypeList() != null) {
            flags.inFunctionDeclarator = true;
            List<ASTParamsDeclarator> astParamsDeclaratorList = new LinkedList<>();
            ASTDeclarator declarator = (ASTDeclarator) visitDirectDeclarator(ctx.directDeclarator());
            tableIndex++;
            tableStack.push(tableIndex - 1);
            identifierSymbolTable.add(new ArrayList<>());
            for (int i = 0; i < ctx.parameterTypeList().parameterList().parameterDeclaration().size(); i++) {
                astParamsDeclaratorList.add((ASTParamsDeclarator) visitParameterDeclaration(ctx.parameterTypeList().parameterList().parameterDeclaration(i)));
            }
            astNode = new ASTFunctionDeclarator(declarator, astParamsDeclaratorList);
        } else {
            flags.inFunctionDeclarator = true;
            List<ASTParamsDeclarator> astParamsDeclaratorList = new LinkedList<>();
            ASTDeclarator declarator = (ASTDeclarator) visitDirectDeclarator(ctx.directDeclarator());
            tableIndex++;
            tableStack.push(tableIndex - 1);
            identifierSymbolTable.add(new ArrayList<>());
            astNode = new ASTFunctionDeclarator(declarator, astParamsDeclaratorList);
        }
        return astNode;
    }

    @Override
    public ASTNode visitParameterDeclaration(CParser.ParameterDeclarationContext ctx) {
        ASTNode astNode;
        List<ASTToken> astTokenList = new LinkedList<>();
        for (int i = 0; i < ctx.declarationSpecifiers().declarationSpecifier().size(); i++) {
            ASTToken astToken;
            CParser.TypeSpecifierContext typeSpecifierContext =
                    ctx.declarationSpecifiers().declarationSpecifier(i).typeSpecifier();
            if (typeSpecifierContext.Void() != null) {
                astToken = new ASTToken(typeSpecifierContext.Void().getSymbol().getText(),
                        typeSpecifierContext.Void().getSymbol().getTokenIndex());
            } else if (typeSpecifierContext.Char() != null) {
                astToken = new ASTToken(typeSpecifierContext.Char().getSymbol().getText(),
                        typeSpecifierContext.Char().getSymbol().getTokenIndex());
            } else if (typeSpecifierContext.Int() != null) {
                astToken = new ASTToken(typeSpecifierContext.Int().getSymbol().getText(),
                        typeSpecifierContext.Int().getSymbol().getTokenIndex());
            } else if (typeSpecifierContext.Float() != null) {
                astToken = new ASTToken(typeSpecifierContext.Float().getSymbol().getText(),
                        typeSpecifierContext.Float().getSymbol().getTokenIndex());
            } else {
                astToken = new ASTToken(typeSpecifierContext.Double().getSymbol().getText(),
                        typeSpecifierContext.Double().getSymbol().getTokenIndex());
            }
            astTokenList.add(astToken);
        }
        if (ctx.declarator() != null) {
            int identifierSymbolCurrentIndex = identifierSymbolTable.get(tableStack.peek()).size();
            astNode = new ASTParamsDeclarator(astTokenList, (ASTDeclarator) visitDeclarator(ctx.declarator()));
            for (int i = identifierSymbolCurrentIndex; i < identifierSymbolTable.get(tableStack.peek()).size(); i++) {
                identifierSymbolTable.get(tableStack.peek()).get(i).type = astTokenList.get(0).value;
            }
        } else {
            astNode = new ASTParamsDeclarator(astTokenList, null);
        }
        return astNode;
    }

    @Override
    public ASTNode visitInitializer(CParser.InitializerContext ctx) {
        if (ctx.assignmentExpression() != null) {
            return visitAssignmentExpression(ctx.assignmentExpression());
        } else {
            //TODO: May be a bug
            return visitChildren(ctx);
        }
    }

    @Override
    public ASTNode visitLabeledStatement(CParser.LabeledStatementContext ctx) {
        ASTNode astNode;
        ASTIdentifier astIdentifier;
        astIdentifier = new ASTIdentifier(ctx.Identifier().getSymbol().getText(),
                ctx.Identifier().getSymbol().getTokenIndex());
        // Generate intermediate code
        IntermediateCode intermediateCode = new IntermediateCode("Label",
                astIdentifier.value, "", "");
        astNode = new ASTLabeledStatement(astIdentifier, (ASTStatement) visitStatement(ctx.statement()));
        return astNode;
    }

    @Override
    public ASTNode visitCompoundStatement(CParser.CompoundStatementContext ctx) {
        ASTNode astNode;
        tableIndex++;
        tableStack.push(tableIndex - 1);
        identifierSymbolTable.add(new ArrayList<>());
        if (ctx.blockItemList() != null) {
            List<ASTNode> astNodeList = new LinkedList<>();
            for (int i = 0; i < ctx.blockItemList().blockItem().size(); i++) {
                astNodeList.add(visitBlockItem(ctx.blockItemList().blockItem(i)));
            }
            astNode = new ASTCompoundStatement(astNodeList);
        } else {
            astNode = null;
        }
        tableStack.pop();
        return astNode;
    }

    @Override
    public ASTNode visitExpressionStatement(CParser.ExpressionStatementContext ctx) {
        ASTNode astNode;
        if (ctx.expression() != null) {
            List<ASTExpression> astExpressionList = new LinkedList<>();
            for (int i = 0; i < ctx.expression().assignmentExpression().size(); i++) {
                astExpressionList.add((ASTExpression) visitAssignmentExpression(ctx.expression().assignmentExpression(i)));
            }
            astNode = new ASTExpressionStatement(astExpressionList);
        } else {
            astNode = null;
        }
        return astNode;
    }

    @Override
    public ASTNode visitSelectionStatement(CParser.SelectionStatementContext ctx) {
        ASTNode astNode;
        LinkedList<ASTExpression> astExpressionList = new LinkedList<>();
        for (int i = 0; i < ctx.expression().assignmentExpression().size(); i++) {
            astExpressionList.add((ASTExpression) visitAssignmentExpression(ctx.expression().assignmentExpression(i)));
        }
        // Generate intermediate code
        String jFLabel = "L" + intermediateSymbol + "F";
        String jNLabel = "L" + intermediateSymbol + "N";
        IntermediateCode intermediateCodeJF = new IntermediateCode("JF",
                intermediateSymbolTable.pop(), "", jFLabel);
        // Generate target code
        targetCode.add("\tPOP\tEAX\n");
        targetCode.add("\tCMP\tEAX, 0\n");
        targetCode.add("\tJE\t" + jFLabel + "\n");
        if (ctx.Else() != null) {
            ASTStatement statement = (ASTStatement) visitStatement(ctx.statement(0));
            IntermediateCode intermediateCodeJN = new IntermediateCode("Jmp", "", "", jNLabel);
            IntermediateCode intermediateCodeJFLabel = new IntermediateCode("Label", jFLabel, "", "");
            // Generate target code
            targetCode.add("\tJMP\t" + jNLabel + "\n");
            targetCode.add(jFLabel + ":\n");
            astNode = new ASTSelectionStatement(astExpressionList, statement,
                    (ASTStatement) visitStatement(ctx.statement(1)));
            IntermediateCode intermediateCodeJNLabel = new IntermediateCode("Label", jNLabel, "", "");
            // Generate target code
            targetCode.add(jNLabel + ":\n");
        } else {
            astNode = new ASTSelectionStatement(astExpressionList, (ASTStatement) visitStatement(ctx.statement(0)),
                    null);
            IntermediateCode intermediateCodeJFLabel = new IntermediateCode("Label", jFLabel, "", "");
            // Generate target code
            targetCode.add(jFLabel + ":\n");
        }
        return astNode;
    }

    @Override
    public ASTNode visitFirstForStatement(CParser.FirstForStatementContext ctx) {
        flags.inIteration = true;
        ASTNode astNode;
        LinkedList<ASTExpression> initList = new LinkedList<>();
        if (ctx.expressionA() != null) {
            for (int i = 0; i < ctx.expressionA().expression().assignmentExpression().size(); i++) {
                initList.add((ASTExpression) visitAssignmentExpression(ctx.expressionA().expression().assignmentExpression(i)));
            }
        } else {
            initList = null;
        }
        // Generate intermediate code
        String jLLabel = "L" + intermediateSymbol + "L";
        String jSLabel = "L" + intermediateSymbol + "S";
        String jELabel = "L" + intermediateSymbol + "E";
        String jFLabel = "L" + intermediateSymbol + "F";
        IntermediateCode intermediateCodeJLLabel = new IntermediateCode("Label", jLLabel, "", "");
        loopSymbolTable.push(intermediateSymbol.toString());
        intermediateSymbol.inc();
        // Generate target code
        targetCode.add(jLLabel + ":\n");
        LinkedList<ASTExpression> condList = new LinkedList<>();
        if (ctx.expressionB() != null) {
            for (int i = 0; i < ctx.expressionB().expression().assignmentExpression().size(); i++) {
                condList.add((ASTExpression) visitAssignmentExpression(ctx.expressionB().expression().assignmentExpression(i)));
            }
            // Generate intermediate code
            IntermediateCode intermediateCodeJF = new IntermediateCode("JF", intermediateSymbolTable.pop(), "",
                    jFLabel);
            // Generate target code
            targetCode.add("\tPOP\tEAX\n");
            targetCode.add("\tCMP\tEAX, 0\n");
            targetCode.add("\tJE\t" + jFLabel + "\n");
            targetCode.add("\tJMP\t" + jELabel + "\n");
        } else {
            condList = null;
        }
        // Generate intermediate code
        IntermediateCode intermediateCodeJSLabel = new IntermediateCode("Label", jSLabel, "", "");
        // Generate target code
        targetCode.add(jSLabel + ":\n");
        LinkedList<ASTExpression> stepList = new LinkedList<>();
        if (ctx.expressionC() != null) {
            for (int i = 0; i < ctx.expressionC().expression().assignmentExpression().size(); i++) {
                stepList.add((ASTExpression) visitAssignmentExpression(ctx.expressionC().expression().assignmentExpression(i)));
            }
        } else {
            stepList = null;
        }
        // Generate intermediate code
        IntermediateCode intermediateCodeJL = new IntermediateCode("Jmp", "", "", jLLabel);
        // Generate target code
        targetCode.add("\tJMP\t" + jLLabel + "\n");
        // Generate intermediate code
        IntermediateCode intermediateCodeJELabel = new IntermediateCode("Label", jELabel, "", "");
        // Generate target code
        targetCode.add(jELabel + ":\n");
        astNode = new ASTIterationStatement(initList, condList, stepList,
                (ASTStatement) visitStatement(ctx.statement()));
        // Generate intermediate code
        IntermediateCode intermediateCodeJS = new IntermediateCode("Jmp", "", "", jSLabel);
        IntermediateCode intermediateCodeJFLabel = new IntermediateCode("Label", jFLabel, "", "");
        // Generate target code
        targetCode.add("\tJMP\t" + jSLabel + "\n");
        targetCode.add(jFLabel + ":\n");
        flags.inIteration = false;
        return astNode;
    }

    @Override
    public ASTNode visitSecondForStatement(CParser.SecondForStatementContext ctx) {
        flags.inIteration = true;
        ASTNode astNode;
        LinkedList<ASTExpression> condList = new LinkedList<>();
        // Generate intermediate code
        String jLLabel = "L" + intermediateSymbol + "L";
        String jSLabel = "L" + intermediateSymbol + "S";
        String jFLabel = "L" + intermediateSymbol + "F";
        IntermediateCode intermediateCodeJLLabel = new IntermediateCode("Label", jLLabel, "", "");
        loopSymbolTable.push(intermediateSymbol.toString());
        intermediateSymbol.inc();
        if (ctx.expressionA() != null) {
            for (int i = 0; i < ctx.expressionA().expression().assignmentExpression().size(); i++) {
                condList.add((ASTExpression) visitAssignmentExpression(ctx.expressionA().expression().assignmentExpression(i)));
            }
            // Generate intermediate code
            IntermediateCode intermediateCodeJF = new IntermediateCode("JF", intermediateSymbolTable.pop(), "",
                    jFLabel);
        } else {
            condList = null;
        }
        // Generate intermediate code
        IntermediateCode intermediateCodeJSLabel = new IntermediateCode("Label", jSLabel, "", "");
        LinkedList<ASTExpression> stepList = new LinkedList<>();
        if (ctx.expressionB() != null) {
            for (int i = 0; i < ctx.expressionB().expression().assignmentExpression().size(); i++) {
                stepList.add((ASTExpression) visitAssignmentExpression(ctx.expressionB().expression().assignmentExpression(i)));
            }
        } else {
            stepList = null;
        }
        // Generate intermediate code
        IntermediateCode intermediateCodeJL = new IntermediateCode("Jmp", "", "", jLLabel);
        astNode = new ASTIterationDeclaredStatement((ASTDeclaration) visitDeclaration(ctx.declaration()),
                condList, stepList, (ASTStatement) visitStatement(ctx.statement()));
        // Generate intermediate code
        IntermediateCode intermediateCodeJS = new IntermediateCode("Jmp", "", "", jSLabel);
        IntermediateCode intermediateCodeJFLabel = new IntermediateCode("Label", jFLabel, "", "");
        flags.inIteration = false;
        return astNode;
    }

    @Override
    public ASTNode visitJumpStatement(CParser.JumpStatementContext ctx) {
        ASTNode astNode;
        if (ctx.Goto() != null) {
            ASTIdentifier astIdentifier = new ASTIdentifier(ctx.Identifier().getSymbol().getText(),
                    ctx.Identifier().getSymbol().getTokenIndex());
            astNode = new ASTGotoStatement(astIdentifier);
            // Generate intermediate code
            IntermediateCode intermediateCodeJL = new IntermediateCode("Jmp", "", "", astIdentifier.value);
        } else if (ctx.Continue() != null) {
            astNode = new ASTContinueStatement();
            // Generate intermediate code
            IntermediateCode intermediateCodeJL = new IntermediateCode("Jmp", "", "",
                    "@" + loopSymbolTable.peek() + "L");
        } else if (ctx.Break() != null) {
            astNode = new ASTBreakStatement();
            // Generate intermediate code
            IntermediateCode intermediateCodeJL = new IntermediateCode("Jmp", "", "",
                    "@" + loopSymbolTable.peek() + "L");
        } else {
            flags.hasReturned = true;
            if (ctx.expression() != null) {
                LinkedList<ASTExpression> astExpressionList = new LinkedList<>();
                for (int i = 0; i < ctx.expression().assignmentExpression().size(); i++) {
                    astExpressionList.add((ASTExpression) visitAssignmentExpression(ctx.expression().assignmentExpression(i)));
                    // Discard for intermediate code
                    intermediateSymbolTable.pop();
                }
                astNode = new ASTReturnStatement(astExpressionList);
                // Generate intermediate code
                IntermediateCode intermediateCodeJL = new IntermediateCode("Jmp", functionSymbolTable.pop(), "", "");
                // Generate target code
                targetCode.add("\tPOP\tEAX\n");
            } else {
                astNode = new ASTReturnStatement(null);
                // Generate intermediate code
                IntermediateCode intermediateCodeJL = new IntermediateCode("Jmp", functionSymbolTable.pop(), "", "");
            }
        }
        return astNode;
    }

    @Override
    public ASTNode visitFunctionDefinition(CParser.FunctionDefinitionContext ctx) {
        ASTNode astNode;
        List<ASTToken> astTokenList = new LinkedList<>();
        if (ctx.declarationSpecifiers() != null) {
            for (int i = 0; i < ctx.declarationSpecifiers().declarationSpecifier().size(); i++) {
                ASTToken astToken;
                CParser.TypeSpecifierContext typeSpecifierContext =
                        ctx.declarationSpecifiers().declarationSpecifier(i).typeSpecifier();
                if (typeSpecifierContext.Void() != null) {
                    astToken = new ASTToken(typeSpecifierContext.Void().getSymbol().getText(),
                            typeSpecifierContext.Void().getSymbol().getTokenIndex());
                } else if (typeSpecifierContext.Char() != null) {
                    astToken = new ASTToken(typeSpecifierContext.Char().getSymbol().getText(),
                            typeSpecifierContext.Char().getSymbol().getTokenIndex());
                } else if (typeSpecifierContext.Int() != null) {
                    astToken = new ASTToken(typeSpecifierContext.Int().getSymbol().getText(),
                            typeSpecifierContext.Int().getSymbol().getTokenIndex());
                } else if (typeSpecifierContext.Float() != null) {
                    astToken = new ASTToken(typeSpecifierContext.Float().getSymbol().getText(),
                            typeSpecifierContext.Float().getSymbol().getTokenIndex());
                } else {
                    astToken = new ASTToken(typeSpecifierContext.Double().getSymbol().getText(),
                            typeSpecifierContext.Double().getSymbol().getTokenIndex());
                }
                astTokenList.add(astToken);
            }
        }
        int identifierSymbolCurrentIndex = identifierSymbolTable.get(tableStack.peek()).size();
        flags.inFunctionDeclarator = true;
        ASTDeclarator astDeclarator = (ASTDeclarator) visitDeclarator(ctx.declarator());
        flags.inFunctionDeclarator = false;
        Integer temp = tableStack.pop();
        identifierSymbolTable.get(tableStack.peek()).get(identifierSymbolCurrentIndex).type = astTokenList.get(0).value;
        FunctionDeclarationSymbol currentFunction = new FunctionDeclarationSymbol(
                identifierSymbolTable.get(tableStack.peek()).get(identifierSymbolCurrentIndex).type,
                identifierSymbolTable.get(tableStack.peek()).get(identifierSymbolCurrentIndex).name);
        functionDeclarationSymbolTable.add(currentFunction);
        tableStack.push(temp);
        // Generate intermediate code
        functionSymbolTable.push(currentFunction.name);
        // Generate target code
        targetCode.add(currentFunction.name + "\tPROC");
        Integer paramNum = 0;
        //IntermediateCode intermediateCodePS = new IntermediateCode("ProcStart", currentFunction.name, "", "");
        for (int i = 0; i < identifierSymbolTable.get(tableStack.peek()).size(); i++) {
            functionDeclarationSymbolTable.get(functionDeclarationSymbolTable.size() - 1).parameter.
                    add(new IdentifierSymbol(identifierSymbolTable.get(tableStack.peek()).get(i).type,
                            identifierSymbolTable.get(tableStack.peek()).get(i).name, 1));
            // Generate intermediate code
            IntermediateCode intermediateCodeParam = new IntermediateCode("FunParam",
                    identifierSymbolTable.get(tableStack.peek()).get(i).type, "", "");
            // Generate target code
            targetCode.add("\t" + "_" + identifierSymbolTable.get(tableStack.peek()).get(i).name + ":dword");
            paramNum++;
        }
        targetCode.add("\n");
        int targetCodeIndex = targetCode.size();
        identifierSymbolRoughTable.clear();
        ASTCompoundStatement astCompoundStatement =
                (ASTCompoundStatement) visitCompoundStatement(ctx.compoundStatement());
        for (IdentifierSymbol symbol : identifierSymbolRoughTable) {
            if (symbol.size == 1) {
                targetCode.add(targetCodeIndex++, "\t\tLOCAL\t" + symbol.name + ":dword\n");
            } else {
                targetCode.add(targetCodeIndex++, "\t\tLOCAL\t" + symbol.name + "[" + symbol.size + "]" + ":dword\n");
            }
        }
        // Generate intermediate code
        IntermediateCode intermediateCodePE = new IntermediateCode("ProcEnd", currentFunction.name, "", "");
        // Generate target code
        targetCode.add("\tRET\t" + 4 * paramNum + "\n");
        targetCode.add(currentFunction.name + "\tENDP\n\n");
        // Pop for parameterList
        tableStack.pop();
        astNode = new ASTFunctionDefine(astTokenList, astDeclarator, astCompoundStatement);
        return astNode;
    }

    @Override
    public ASTNode visitCompilationUnit(CParser.CompilationUnitContext ctx) {
        ASTNode astNode;
        List<ASTNode> astNodeList = new LinkedList<>();
        // Generate target code
        targetCode.add(".386\n.model flat, stdcall\noption casemap:none\n\n" +
                "include msvcrt.inc\nincludelib msvcrt.lib\n\n");
        targetCode.add(".data\n");
        int targetCodeIndex = targetCode.size();
        targetCode.add("\n");
        targetCode.add(".code\n");
        tableIndex++;
        tableStack.push(tableIndex - 1);
        identifierSymbolTable.add(new ArrayList<>());
        for (int i = 0; i < ctx.translationUnit().externalDeclaration().size(); i++) {
            astNodeList.add(visitExternalDeclaration(ctx.translationUnit().externalDeclaration(i)));
        }
        tableStack.pop();
        // Generate target code
        for (int i = 1; i <= stringLiteralList.size(); i++) {
            targetCode.add(targetCodeIndex, "_string_" + i + "\tbyte\t" +
                    stringLiteralList.get(i - 1).replace("\\n", "") + ", 0ah, 0\n");
            targetCodeIndex++;
        }
        targetCode.add("start:\n\tCALL main\n\tRET\nEND start\n");
        astNode = new ASTCompilationUnit(astNodeList);
        return astNode;
    }
}
