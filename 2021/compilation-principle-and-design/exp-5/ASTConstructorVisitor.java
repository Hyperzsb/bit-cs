import ast.*;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class ASTConstructorVisitor extends CBaseVisitor<ASTNode> {

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
        } else if (ctx.IntegerConstant() != null) {
            astNode = new ASTIntegerConstant(Integer.parseInt(ctx.IntegerConstant().getSymbol().getText()),
                    ctx.IntegerConstant().getSymbol().getTokenIndex());
        } else if (ctx.FloatingConstant() != null) {
            astNode = new ASTFloatConstant(Double.parseDouble(ctx.FloatingConstant().getSymbol().getText()),
                    ctx.FloatingConstant().getSymbol().getTokenIndex());
        } else if (ctx.CharacterConstant() != null) {
            astNode = new ASTCharConstant(ctx.CharacterConstant().getSymbol().getText(),
                    ctx.CharacterConstant().getSymbol().getTokenIndex());
        } else if (ctx.StringLiteral() != null) {
            astNode = new ASTStringConstant(ctx.StringLiteral().getSymbol().getText(),
                    ctx.StringLiteral().getSymbol().getTokenIndex());
        } else {
            astNode = visitExpression(ctx.expression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitPostfixExpression(CParser.PostfixExpressionContext ctx) {
        ASTNode astNode;
        if (ctx.expression() != null) {
            List<ASTExpression> astNodeList = new LinkedList<>();
            for (int i = 0; i < ctx.expression().assignmentExpression().size(); i++)
                astNodeList.add((ASTExpression) visitAssignmentExpression(ctx.expression().assignmentExpression(i)));

            astNode = new ASTArrayAccess((ASTExpression) visitPostfixExpression(ctx.postfixExpression()), astNodeList);
        } else if (ctx.RightParen() != null && ctx.LeftParen() != null) {
            List<ASTExpression> astNodeList = new LinkedList<>();
            if (ctx.argumentExpressionList() != null) {
                for (int i = 0; i < ctx.argumentExpressionList().assignmentExpression().size(); i++)
                    astNodeList.add((ASTExpression) visitAssignmentExpression(ctx.argumentExpressionList().assignmentExpression(i)));
            }
            astNode = new ASTFunctionCall((ASTExpression) visitPostfixExpression(ctx.postfixExpression()), astNodeList);
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
        } else if (ctx.Sizeof() != null && ctx.unaryExpression() != null) {
            ASTToken astToken = new ASTToken(ctx.Sizeof().getSymbol().getText(),
                    ctx.Sizeof().getSymbol().getTokenIndex());
            astNode = new ASTUnaryExpression(astToken, (ASTExpression) visitUnaryExpression(ctx.unaryExpression()));
        } else if (ctx.Sizeof() != null && ctx.typeName() != null) {
            ASTToken astToken = new ASTToken(ctx.Sizeof().getSymbol().getText(),
                    ctx.Sizeof().getSymbol().getTokenIndex());
            astNode = new ASTUnaryExpression(astToken, (ASTExpression) visitTypeName(ctx.typeName()));
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
        } else {
            astNode = visitLogicalAndExpression(ctx.logicalAndExpression());
        }
        return astNode;
    }

    @Override
    public ASTNode visitConditionalExpression(CParser.ConditionalExpressionContext ctx) {
        ASTNode astNode;
        if (ctx.logicalOrExpression() != null && ctx.expression() != null && ctx.conditionalExpression() != null) {
            LinkedList<ASTExpression> astNodeList = new LinkedList<>();
            for (int i = 0; i < ctx.expression().assignmentExpression().size(); i++)
                astNodeList.add((ASTExpression) visitAssignmentExpression(ctx.expression().assignmentExpression(i)));
            astNode = new ASTConditionExpression((ASTExpression) visitLogicalOrExpression(ctx.logicalOrExpression()),
                    astNodeList,
                    (ASTExpression) visitConditionalExpression(ctx.conditionalExpression()));
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
        if (ctx.initDeclaratorList() != null) {
            for (int i = 0; i < ctx.initDeclaratorList().initDeclarator().size(); i++) {
                astInitListList.add((ASTInitList) visitInitDeclarator(ctx.initDeclaratorList().initDeclarator(i)));
            }
        }
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
                }
            }
        }
        astNode = new ASTInitList((ASTDeclarator) visitDeclarator(ctx.declarator()), astExpressionList);
        return astNode;
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
            astNode = new ASTVariableDeclarator(astIdentifier);
        } else if (ctx.declarator() != null) {
            astNode = visitDeclarator(ctx.declarator());
        } else if (ctx.directDeclarator() != null && ctx.assignmentExpression() != null) {
            astNode = new ASTArrayDeclarator((ASTDeclarator) visitDirectDeclarator(ctx.directDeclarator()),
                    (ASTExpression) visitAssignmentExpression(ctx.assignmentExpression()));
        } else if (ctx.directDeclarator() != null && ctx.parameterTypeList() != null) {
            List<ASTParamsDeclarator> astParamsDeclaratorList = new LinkedList<>();
            for (int i = 0; i < ctx.parameterTypeList().parameterList().parameterDeclaration().size(); i++) {
                astParamsDeclaratorList.add((ASTParamsDeclarator) visitParameterDeclaration(ctx.parameterTypeList().parameterList().parameterDeclaration(i)));
            }
            astNode = new ASTFunctionDeclarator((ASTDeclarator) visitDirectDeclarator(ctx.directDeclarator()),
                    astParamsDeclaratorList);
        } else {
            List<ASTParamsDeclarator> astParamsDeclaratorList = new LinkedList<>();
            astNode = new ASTFunctionDeclarator((ASTDeclarator) visitDirectDeclarator(ctx.directDeclarator()),
                    astParamsDeclaratorList);
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
            astNode = new ASTParamsDeclarator(astTokenList, (ASTDeclarator) visitDeclarator(ctx.declarator()));
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
        astNode = new ASTLabeledStatement(astIdentifier, (ASTStatement) visitStatement(ctx.statement()));
        return astNode;
    }

    @Override
    public ASTNode visitCompoundStatement(CParser.CompoundStatementContext ctx) {
        ASTNode astNode;
        if (ctx.blockItemList() != null) {
            List<ASTNode> astNodeList = new LinkedList<>();
            for (int i = 0; i < ctx.blockItemList().blockItem().size(); i++) {
                astNodeList.add(visitBlockItem(ctx.blockItemList().blockItem(i)));
            }
            astNode = new ASTCompoundStatement(astNodeList);
        } else {
            astNode = null;
        }
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
        if (ctx.Else() != null) {
            astNode = new ASTSelectionStatement(astExpressionList, (ASTStatement) visitStatement(ctx.statement(0)),
                    (ASTStatement) visitStatement(ctx.statement(1)));
        } else {
            astNode = new ASTSelectionStatement(astExpressionList, (ASTStatement) visitStatement(ctx.statement(0)),
                    null);
        }
        return astNode;
    }

    @Override
    public ASTNode visitFirstForStatement(CParser.FirstForStatementContext ctx) {
        ASTNode astNode;
        LinkedList<ASTExpression> initList = new LinkedList<>();
        if (ctx.expressionA() != null) {
            for (int i = 0; i < ctx.expressionA().expression().assignmentExpression().size(); i++) {
                initList.add((ASTExpression) visitAssignmentExpression(ctx.expressionA().expression().assignmentExpression(i)));
            }
        } else {
            initList = null;
        }
        LinkedList<ASTExpression> condList = new LinkedList<>();
        if (ctx.expressionB() != null) {
            for (int i = 0; i < ctx.expressionB().expression().assignmentExpression().size(); i++) {
                condList.add((ASTExpression) visitAssignmentExpression(ctx.expressionB().expression().assignmentExpression(i)));
            }
        } else {
            condList = null;
        }
        LinkedList<ASTExpression> stepList = new LinkedList<>();
        if (ctx.expressionC() != null) {
            for (int i = 0; i < ctx.expressionC().expression().assignmentExpression().size(); i++) {
                stepList.add((ASTExpression) visitAssignmentExpression(ctx.expressionC().expression().assignmentExpression(i)));
            }
        } else {
            stepList = null;
        }
        astNode = new ASTIterationStatement(initList, condList, stepList,
                (ASTStatement) visitStatement(ctx.statement()));
        return astNode;
    }

    @Override
    public ASTNode visitSecondForStatement(CParser.SecondForStatementContext ctx) {
        ASTNode astNode;
        LinkedList<ASTExpression> condList = new LinkedList<>();
        if (ctx.expressionA() != null) {
            for (int i = 0; i < ctx.expressionA().expression().assignmentExpression().size(); i++) {
                condList.add((ASTExpression) visitAssignmentExpression(ctx.expressionA().expression().assignmentExpression(i)));
            }
        } else {
            condList = null;
        }
        LinkedList<ASTExpression> stepList = new LinkedList<>();
        if (ctx.expressionB() != null) {
            for (int i = 0; i < ctx.expressionB().expression().assignmentExpression().size(); i++) {
                stepList.add((ASTExpression) visitAssignmentExpression(ctx.expressionB().expression().assignmentExpression(i)));
            }
        } else {
            stepList = null;
        }
        astNode = new ASTIterationDeclaredStatement((ASTDeclaration) visitDeclaration(ctx.declaration()),
                condList, stepList, (ASTStatement) visitStatement(ctx.statement()));
        return astNode;
    }

    @Override
    public ASTNode visitJumpStatement(CParser.JumpStatementContext ctx) {
        ASTNode astNode;
        if (ctx.Goto() != null) {
            ASTIdentifier astIdentifier = new ASTIdentifier(ctx.Identifier().getSymbol().getText(),
                    ctx.Identifier().getSymbol().getTokenIndex());
            astNode = new ASTGotoStatement(astIdentifier);
        } else if (ctx.Continue() != null) {
            astNode = new ASTContinueStatement();
        } else if (ctx.Break() != null) {
            astNode = new ASTBreakStatement();
        } else {
            if (ctx.expression() != null) {
                LinkedList<ASTExpression> astExpressionList = new LinkedList<>();
                for (int i = 0; i < ctx.expression().assignmentExpression().size(); i++) {
                    astExpressionList.add((ASTExpression) visitAssignmentExpression(ctx.expression().assignmentExpression(i)));
                }
                astNode = new ASTReturnStatement(astExpressionList);
            } else {
                astNode = new ASTReturnStatement(null);
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
        ASTDeclarator astDeclarator = (ASTDeclarator) visitDeclarator(ctx.declarator());
        ASTCompoundStatement astCompoundStatement =
                (ASTCompoundStatement) visitCompoundStatement(ctx.compoundStatement());
        astNode = new ASTFunctionDefine(astTokenList, astDeclarator, astCompoundStatement);
        return astNode;
    }

    @Override
    public ASTNode visitCompilationUnit(CParser.CompilationUnitContext ctx) {
        ASTNode astNode;
        List<ASTNode> astNodeList = new LinkedList<>();
        for (int i = 0; i < ctx.translationUnit().externalDeclaration().size(); i++) {
            astNodeList.add(visitExternalDeclaration(ctx.translationUnit().externalDeclaration(i)));
        }
        astNode = new ASTCompilationUnit(astNodeList);
        return astNode;
    }
}
