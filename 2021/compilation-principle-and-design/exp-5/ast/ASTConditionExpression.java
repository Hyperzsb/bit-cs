package ast;

import com.fasterxml.jackson.annotation.JsonTypeName;

import java.util.LinkedList;

@JsonTypeName("ConditionExpression")
public class ASTConditionExpression extends ASTExpression{
	
	public  ASTExpression condExpr;
	public  LinkedList<ASTExpression> trueExpr;
	public  ASTExpression falseExpr;
	
	public ASTConditionExpression() {
		super("ConditionExpression");
	}
	
	public ASTConditionExpression(ASTExpression cond,LinkedList<ASTExpression> trueExpr, ASTExpression falseExpr) {
		super("ConditionExpression");
		this.condExpr = cond;
		this.trueExpr = trueExpr;
		this.falseExpr = falseExpr;
	}
	@Override
	public void accept(ASTVisitor visitor) throws Exception {
		visitor.visit(this);
	}

}
