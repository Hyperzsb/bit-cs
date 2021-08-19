import ast.ASTNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.antlr.v4.gui.TreeViewer;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import org.antlr.v4.runtime.CharStreams;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;

public class ASTParser {
    public static void main(String[] args) throws IOException {
        CharStream charStream = CharStreams.fromFileName("test/1.c");

        CLexer lexer = new CLexer(charStream);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        CParser parser = new CParser(tokens);
        ParseTree tree = parser.compilationUnit();

        ASTConstructorVisitor visitor = new ASTConstructorVisitor();
        ASTNode root = visitor.visit(tree);

        ObjectMapper mapper = new ObjectMapper();
        mapper.writeValue(new File("test/out.json"), root);

        TreeViewer treeViewer = new TreeViewer(Arrays.asList(parser.getRuleNames()), tree);
        treeViewer.open();
    }
}
