#include<cstdio>
#include<cstdlib>
struct Node {
	int value;
	Node *left_child;
	Node *right_child;
	Node(int value_) {
		value = value_;
		left_child = NULL;
		right_child = NULL;
	}
};
void Insert(int value, Node *root) {
	if (value == root->value) {
		return ;
	} else if (value < root->value) {
		if (root->left_child != NULL) {
			Insert(value, root->left_child);
		} else {
			root->left_child = new Node(value);
			return ;
		}
	} else {
		if (root->right_child != NULL) {
			Insert(value, root->right_child);
		} else {
			root->right_child = new Node(value);
			return;
		}
	}
}
void Traverse(Node *root, int depth) {
	if (root == NULL) {
		return ;
	} else {
		Traverse(root->left_child, depth + 1);
		for (int i = 0; i < depth; i++) {
			printf("    ");
		}
		printf("%d\n", root->value);
		Traverse(root->right_child, depth + 1);
	}
}
void TraverseInLine(Node *root) {
	if (root == NULL) {
		return ;
	} else {
		TraverseInLine(root->left_child);
		printf(" %d", root->value);
		TraverseInLine(root->right_child);
	}
}
int main() {
	int value = 0;
	scanf("%d", &value);
	Node *root = new Node(value);
	scanf("%d", &value);
	while (value != 0) {
		Insert(value, root);
		scanf("%d", &value);
	}
	Traverse(root, 0);
	printf("\n");
	TraverseInLine(root);
	printf("\n");

	return 0;
}

