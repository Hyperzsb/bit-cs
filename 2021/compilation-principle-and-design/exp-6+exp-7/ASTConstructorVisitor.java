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

        public Flags() {
            hasError = false;
            inFunctionCall = false;
            inFunctionCallParameterList = false;
            inFunctionDeclarator = false;
            inIteration = false;
            hasReturned = false;
        }
    }

    private final Flags flags = new Flags();

    public static class IdentifierSymbol {
        public String type;
        public String name;

        public IdentifierSymbol(String type, String name) {
            this.type = type;
            this.name = name;
        }
    }

    public final List<List<IdentifierSymbol>> identifierSymbolTable = new ArrayList<>();

    public static class LabelSymbol {
        public String name;

        public LabelSymbol(String name) {
            this.name = name;
        }
    }

    public final List<LabelSymbol> labelSymbolTable = new ArrayList<>();

    public final List<LabelSymbol> unmatchedLabelSymbolTable = new ArrayList<>();

    public static class FunctionDeclarationSymbol {
        public String type;
        public String name;
        public List<String> parameterType;

        public FunctionDeclarationSymbol(String type, String name) {
            this.type = type;
            this.name = name;
            this.parameterType = new ArrayList<>();
        }
    }

    public final List<FunctionDeclarationSymbol> functionDeclarationSymbolTable = new ArrayList<>();

    private final List<String> functionParameterTypeList = new ArrayList<>();

    public Integer tableIndex = 0;

    private final Stack<Integer> tableStack = new Stack<Integer>();

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
            System.out.println("[ " + op + " , " + arg_a + " , " + arg_b + " , " + dst + " ]");
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
            return "%" + index;
        }
    }

    private static final IntermediateSymbol intermediateSymbol = new IntermediateSymbol();

    private final Stack<String> intermediateSymbolTable = new Stack<>();

    private final Stack<String> loopSymbolTable = new Stack<>();

    private final Stack<String> functionSymbolTable = new Stack<>();

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
            boolean identifierDeclared = false;
            for (Integer i : tableStack) {
                for (IdentifierSymbol symbol : identifierSymbolTable.get(i)) {
                    if (((ASTIdentifier) astNode).value.equals(symbol.name)) {
                        identifierDeclared = true;
                        if (flags.inFunctionCallParameterList) {
                            functionParameterTypeList.add(symbol.type);
                        }
                        break;
                    }
                }
            }
            if (!identifierDeclared) {
                if (!flags.hasError) {
                    System.out.println("------------------------------------");
                    flags.hasError = true;
                }
                if (!flags.inFunctionCall) {
                    System.out.println("ES1 >> Identifier: " + ((ASTIdentifier) astNode).value + " is not defined.");
                } else {
                    System.out.println("ES1 >> FunctionCall: " + ((ASTIdentifier) astNode).value + " is not declared.");
                }
            }
            if (flags.inFunctionCall) {
                FunctionDeclarationSymbol functionDeclarationSymbol = null;
                for (FunctionDeclarationSymbol symbol : functionDeclarationSymbolTable) {
                    if (symbol.name.equals(((ASTIdentifier) astNode).value)) {
                        functionDeclarationSymbol = symbol;
                    }
                }
                if (functionDeclarationSymbol != null) {
                    if (functionDeclarationSymbol.parameterType.size() != functionParameterTypeList.size()) {
                        if (!flags.hasError) {
                            System.out.println("------------------------------------");
                            flags.hasError = true;
                        }
                        System.out.println("ES4 >> FunctionCall: " + functionDeclarationSymbol.name +
                                "'s param num is not matched");
                    } else {
                        for (int i = 0; i < functionDeclarationSymbol.parameterType.size(); i++) {
                            if (!functionDeclarationSymbol.parameterType.get(i).equals(functionParameterTypeList.get(i))) {
                                if (!flags.hasError) {
                                    System.out.println("------------------------------------");
                                    flags.hasError = true;
                                }
                                System.out.println("ES4 >> FunctionCall: " + functionDeclarationSymbol.name +
                                        "'s param type is not matched");
                            }
                        }
                    }
                }
                functionParameterTypeList.clear();
            }
            // Get symbol for IC
            intermediateSymbolTable.push(((ASTIdentifier) astNode).value);
        } else if (ctx.IntegerConstant() != null) {
            astNode = new ASTIntegerConstant(Integer.parseInt(ctx.IntegerConstant().getSymbol().getText()),
                    ctx.IntegerConstant().getSymbol().getTokenIndex());
            if (flags.inFunctionCallParameterList) {
                functionParameterTypeList.add("int");
            }
            // Get symbol for IC
            intermediateSymbolTable.push(((ASTIntegerConstant) astNode).value.toString());
        } else if (ctx.FloatingConstant() != null) {
            astNode = new ASTFloatConstant(Double.parseDouble(ctx.FloatingConstant().getSymbol().getText()),
                    ctx.FloatingConstant().getSymbol().getTokenIndex());
            if (flags.inFunctionCallParameterList) {
                functionParameterTypeList.add("float");
            }
            // Get symbol for IC
            intermediateSymbolTable.push(((ASTFloatConstant) astNode).value.toString());
        } else if (ctx.CharacterConstant() != null) {
            astNode = new ASTCharConstant(ctx.CharacterConstant().getSymbol().getText(),
                    ctx.CharacterConstant().getSymbol().getTokenIndex());
            if (flags.inFunctionCallParameterList) {
                functionParameterTypeList.add("char");
            }
            // Get symbol for IC
            intermediateSymbolTable.push(((ASTCharConstant) astNode).value);
        } else if (ctx.StringLiteral() != null) {
            astNode = new ASTStringConstant(ctx.StringLiteral().getSymbol().getText(),
                    ctx.StringLiteral().getSymbol().getTokenIndex());
            if (flags.inFunctionCallParameterList) {
                functionParameterTypeList.add("string");
            }
            // Get symbol for IC
            intermediateSymbolTable.push(((ASTStringConstant) astNode).value);
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
            IntermediateCode intermediateCode = new IntermediateCode("[]", intermediateSymbolTable.pop(), tempSymbol,
                    intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
        } else if (ctx.RightParen() != null && ctx.LeftParen() != null) {
            flags.inFunctionCallParameterList = true;
            List<ASTExpression> astNodeList = new LinkedList<>();
            if (ctx.argumentExpressionList() != null) {
                for (int i = 0; i < ctx.argumentExpressionList().assignmentExpression().size(); i++) {
                    astNodeList.add((ASTExpression) visitAssignmentExpression(ctx.argumentExpressionList().assignmentExpression(i)));
                    // Discard arguments for intermediate code
                    intermediateSymbolTable.pop();
                }
            }
            flags.inFunctionCallParameterList = false;
            flags.inFunctionCall = true;
            astNode = new ASTFunctionCall((ASTExpression) visitPostfixExpression(ctx.postfixExpression()), astNodeList);
            flags.inFunctionCall = false;
            // Generate intermediate code
            IntermediateCode intermediateCode = new IntermediateCode("FunCall", intermediateSymbolTable.pop(), "",
                    intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
        } else if (ctx.PlusPlus() != null || ctx.MinusMinus() != null) {
            ASTToken astToken;
            if (ctx.PlusPlus() != null) {
                astToken = new ASTToken(ctx.PlusPlus().getSymbol().getText(),
                        ctx.PlusPlus().getSymbol().getTokenIndex());
            } else {
                astToken = new ASTToken(ctx.MinusMinus().getSymbol().getText(),
                        ctx.MinusMinus().getSymbol().getTokenIndex());
            }
            astNode = new ASTPostfixExpression((ASTExpression) visitPostfixExpression(ctx.postfixExpression()),
                    astToken);
            // Generate intermediate code
            IntermediateCode intermediateCode = new IntermediateCode("Postfix " + astToken.value,
                    intermediateSymbolTable.pop(), "", intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
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
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Binary " + astToken.value,
                    intermediateSymbolTable.pop(), tempSymbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
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
            String jFLabel = "@" + intermediateSymbol + "F";
            String jNLabel = "@" + intermediateSymbol + "N";
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
            astNode = new ASTBinaryExpression(astToken,
                    (ASTExpression) visitUnaryExpression(ctx.unaryExpression()),
                    (ASTExpression) visitAssignmentExpression(ctx.assignmentExpression()));
            // Generate intermediate code
            String tempSymbol = intermediateSymbolTable.pop();
            IntermediateCode intermediateCode = new IntermediateCode("Assign " + astToken.value,
                    intermediateSymbolTable.pop(), tempSymbol, intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
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
                functionDeclarationSymbolTable.get(functionDeclarationSymbolTable.size() - 1).parameterType.
                        add(identifierSymbolTable.get(tableStack.peek()).get(i).type);
                // Generate intermediate code
                IntermediateCode intermediateCodeParameter = new IntermediateCode("FunParam",
                        functionDeclarationSymbolTable.get(functionDeclarationSymbolTable.size() - 1).parameterType.get(i),
                        "", "");
            }
            tableStack.pop();
        } else {
            for (int i = identifierSymbolCurrentIndex; i < identifierSymbolTable.get(tableStack.peek()).size(); i++) {
                identifierSymbolTable.get(tableStack.peek()).get(i).type = astTokenList.get(0).value;
                // Generate intermediate code
                IntermediateCode intermediateCode = new IntermediateCode("VarDecl",
                        identifierSymbolTable.get(tableStack.peek()).get(i).name,
                        identifierSymbolTable.get(tableStack.peek()).get(i).type, "");
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
            IntermediateCode intermediateCode = new IntermediateCode("Init",
                    tempSymbol, intermediateSymbolTable.pop(), intermediateSymbol.toString());
            intermediateSymbolTable.push(intermediateSymbol.toString());
            intermediateSymbol.inc();
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
            ASTIdentifier astIdentifier = new ASTIdentifier(ctx.Identifier().getSymbol().getText(),
                    ctx.Identifier().getSymbol().getTokenIndex());
            for (IdentifierSymbol symbol : identifierSymbolTable.get(tableStack.peek())) {
                if (astIdentifier.value.equals(symbol.name)) {
                    if (!flags.hasError) {
                        System.out.println("------------------------------------");
                        flags.hasError = true;
                    }
                    if (!flags.inFunctionDeclarator) {
                        System.out.println("ES2 >> Declaration: " + astIdentifier.value + " has been declared");
                    } else {
                        System.out.println("ES2 >> FunctionDefine: " + astIdentifier.value + " has been defined.");
                    }
                    break;
                }
            }
            identifierSymbolTable.get(tableStack.peek()).add(new IdentifierSymbol("Undefined", astIdentifier.value));
            astNode = new ASTVariableDeclarator(astIdentifier);
            // Generate intermediate code
            intermediateSymbolTable.push(astIdentifier.value);
        } else if (ctx.declarator() != null) {
            astNode = visitDeclarator(ctx.declarator());
        } else if (ctx.directDeclarator() != null && ctx.assignmentExpression() != null) {
            astNode = new ASTArrayDeclarator((ASTDeclarator) visitDirectDeclarator(ctx.directDeclarator()),
                    (ASTExpression) visitAssignmentExpression(ctx.assignmentExpression()));
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
        labelSymbolTable.add(new LabelSymbol(astIdentifier.value));
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
        String jFLabel = "@" + intermediateSymbolTable.peek() + "F";
        String jNLabel = "@" + intermediateSymbolTable.peek() + "N";
        IntermediateCode intermediateCodeJF = new IntermediateCode("JF",
                intermediateSymbolTable.pop(), "", jFLabel);
        if (ctx.Else() != null) {
            ASTStatement statement = (ASTStatement) visitStatement(ctx.statement(0));
            IntermediateCode intermediateCodeJN = new IntermediateCode("Jmp", "", "", jNLabel);
            IntermediateCode intermediateCodeJFLabel = new IntermediateCode("Label", jFLabel, "", "");
            astNode = new ASTSelectionStatement(astExpressionList, statement,
                    (ASTStatement) visitStatement(ctx.statement(1)));
            IntermediateCode intermediateCodeJNLabel = new IntermediateCode("Label", jNLabel, "", "");
        } else {
            astNode = new ASTSelectionStatement(astExpressionList, (ASTStatement) visitStatement(ctx.statement(0)),
                    null);
            IntermediateCode intermediateCodeJFLabel = new IntermediateCode("Label", jFLabel, "", "");
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
        String jLLabel = "@" + intermediateSymbol + "L";
        String jSLabel = "@" + intermediateSymbol + "S";
        String jFLabel = "@" + intermediateSymbol + "F";
        IntermediateCode intermediateCodeJLLabel = new IntermediateCode("Label", jLLabel, "", "");
        loopSymbolTable.push(intermediateSymbol.toString());
        intermediateSymbol.inc();
        LinkedList<ASTExpression> condList = new LinkedList<>();
        if (ctx.expressionB() != null) {
            for (int i = 0; i < ctx.expressionB().expression().assignmentExpression().size(); i++) {
                condList.add((ASTExpression) visitAssignmentExpression(ctx.expressionB().expression().assignmentExpression(i)));
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
        if (ctx.expressionC() != null) {
            for (int i = 0; i < ctx.expressionC().expression().assignmentExpression().size(); i++) {
                stepList.add((ASTExpression) visitAssignmentExpression(ctx.expressionC().expression().assignmentExpression(i)));
            }
        } else {
            stepList = null;
        }
        // Generate intermediate code
        IntermediateCode intermediateCodeJL = new IntermediateCode("Jmp", "", "", jLLabel);
        astNode = new ASTIterationStatement(initList, condList, stepList,
                (ASTStatement) visitStatement(ctx.statement()));
        // Generate intermediate code
        IntermediateCode intermediateCodeJS = new IntermediateCode("Jmp", "", "", jSLabel);
        IntermediateCode intermediateCodeJFLabel = new IntermediateCode("Label", jFLabel, "", "");
        flags.inIteration = false;
        return astNode;
    }

    @Override
    public ASTNode visitSecondForStatement(CParser.SecondForStatementContext ctx) {
        flags.inIteration = true;
        ASTNode astNode;
        LinkedList<ASTExpression> condList = new LinkedList<>();
        // Generate intermediate code
        String jLLabel = "@" + intermediateSymbol + "L";
        String jSLabel = "@" + intermediateSymbol + "S";
        String jFLabel = "@" + intermediateSymbol + "F";
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
            unmatchedLabelSymbolTable.add(new LabelSymbol(astIdentifier.value));
            astNode = new ASTGotoStatement(astIdentifier);
            // Generate intermediate code
            IntermediateCode intermediateCodeJL = new IntermediateCode("Jmp", "", "", astIdentifier.value);
        } else if (ctx.Continue() != null) {
            astNode = new ASTContinueStatement();
            // Generate intermediate code
            IntermediateCode intermediateCodeJL = new IntermediateCode("Jmp", "", "",
                    "@" + loopSymbolTable.peek() + "L");
        } else if (ctx.Break() != null) {
            if (!flags.inIteration) {
                if (!flags.hasError) {
                    System.out.println("------------------------------------");
                    flags.hasError = true;
                }
                System.out.println("ES3 >> BreakStatement: must be in a IterationStatement.");
            }
            astNode = new ASTBreakStatement();
            // Generate intermediate code
            // IntermediateCode intermediateCodeJL = new IntermediateCode("Jmp", "", "",
            //        "@" + loopSymbolTable.peek() + "L");
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
        IntermediateCode intermediateCodePS = new IntermediateCode("ProcStart", currentFunction.name, "", "");
        for (int i = 0; i < identifierSymbolTable.get(tableStack.peek()).size(); i++) {
            functionDeclarationSymbolTable.get(functionDeclarationSymbolTable.size() - 1).parameterType.
                    add(identifierSymbolTable.get(tableStack.peek()).get(i).type);
            // Generate intermediate code
            IntermediateCode intermediateCodeParam = new IntermediateCode("FunParam",
                    identifierSymbolTable.get(tableStack.peek()).get(i).type, "", "");
        }
        ASTCompoundStatement astCompoundStatement =
                (ASTCompoundStatement) visitCompoundStatement(ctx.compoundStatement());
        // Generate intermediate code
        IntermediateCode intermediateCodePE = new IntermediateCode("ProcEnd", currentFunction.name, "", "");
        // Pop for parameterList
        tableStack.pop();
        if (!flags.hasReturned) {
            if (!flags.hasError) {
                System.out.println("------------------------------------");
                flags.hasError = true;
            }
            System.out.println("ES8 >> Function: " + currentFunction.name + " must have a return in the end.");
        }
        astNode = new ASTFunctionDefine(astTokenList, astDeclarator, astCompoundStatement);
        return astNode;
    }

    @Override
    public ASTNode visitCompilationUnit(CParser.CompilationUnitContext ctx) {
        ASTNode astNode;
        List<ASTNode> astNodeList = new LinkedList<>();
        tableIndex++;
        tableStack.push(tableIndex - 1);
        identifierSymbolTable.add(new ArrayList<>());
        for (int i = 0; i < ctx.translationUnit().externalDeclaration().size(); i++) {
            astNodeList.add(visitExternalDeclaration(ctx.translationUnit().externalDeclaration(i)));
        }
        tableStack.pop();
        // Match goto labels
        for (LabelSymbol unmatchedSymbol : unmatchedLabelSymbolTable) {
            boolean isMatched = false;
            for (LabelSymbol symbol : labelSymbolTable) {
                if (symbol.name.equals(unmatchedSymbol.name)) {
                    isMatched = true;
                    break;
                }
            }
            if (!isMatched) {
                if (!flags.hasError) {
                    System.out.println("------------------------------------");
                    flags.hasError = true;
                }
                System.out.println("ES7 >> Label: " + unmatchedSymbol.name + " is not defined.");
            }
        }
        if (flags.hasError) {
            System.out.println("------------------------------------");
        }
        astNode = new ASTCompilationUnit(astNodeList);
        return astNode;
    }
}
