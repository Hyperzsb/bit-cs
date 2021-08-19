package ast;

import com.fasterxml.jackson.annotation.JsonTypeName;

import java.util.ArrayList;
import java.util.List;

@JsonTypeName("CompoundStatement")
public class ASTCompoundStatement extends ASTStatement{
	public  List<ASTNode> blockItems; // ����ֻ���� ���� ���� �������
	
	public ASTCompoundStatement() {
		super("CompoundStatement");
		this.blockItems = new ArrayList<ASTNode>();
	}
	public ASTCompoundStatement(List<ASTNode> items) {
		super("CompoundStatement");
		this.blockItems = items;
	}
	@Override
	public void accept(ASTVisitor visitor) throws Exception {
		visitor.visit(this);
	}

}
