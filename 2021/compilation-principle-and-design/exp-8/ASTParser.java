import ast.ASTNode;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import org.antlr.v4.runtime.CharStreams;

import java.io.IOException;

public class ASTParser {
    public static void main(String[] args) throws IOException {
        CharStream charStream = CharStreams.fromFileName("test/nc_test/3.c");

        CLexer lexer = new CLexer(charStream);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        CParser parser = new CParser(tokens);
        ParseTree tree = parser.compilationUnit();

        ASTConstructorVisitor visitor = new ASTConstructorVisitor();
        ASTNode root = visitor.visit(tree);

        for (String str : visitor.targetCode) {
            System.out.print(str);
        }

//        for (int i = 0; i < visitor.identifierSymbolTable.size(); i++) {
//            System.out.println("Block " + i + ":");
//            for (int j = 0; j < visitor.identifierSymbolTable.get(i).size(); j++) {
//                System.out.println("Type: " + visitor.identifierSymbolTable.get(i).get(j).type +
//                        " Name: " + visitor.identifierSymbolTable.get(i).get(j).name);
//            }
//        }

//        for (ASTConstructorVisitor.FunctionDeclarationSymbol symbol : visitor.functionDeclarationSymbolTable) {
//            System.out.print("Function: " + symbol.type + " " + symbol.name);
//            for (String type : symbol.parameterType) {
//                System.out.print(" " + type);
//            }
//            System.out.println("");
//        }

        //ObjectMapper mapper = new ObjectMapper();
        //mapper.writeValue(new File("test/out.json"), root);

//        TreeViewer treeViewer = new TreeViewer(Arrays.asList(parser.getRuleNames()), tree);
//        treeViewer.open();
    }
}
