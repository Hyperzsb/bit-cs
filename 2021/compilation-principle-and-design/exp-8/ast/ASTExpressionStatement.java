package ast;

import com.fasterxml.jackson.annotation.JsonTypeName;

import java.util.List;

@JsonTypeName("ExpressionStatement")
public class ASTExpressionStatement extends ASTStatement{

	public List<ASTExpression> exprs;
	public ASTExpressionStatement() {
		super("ExpressionStatement");
	}
	
	public ASTExpressionStatement(List<ASTExpression> exprs) {
		super("ExpressionStatement");
		this.exprs = exprs;
	}
	@Override
	public void accept(ASTVisitor visitor) throws Exception {
		visitor.visit(this);
	}

}
