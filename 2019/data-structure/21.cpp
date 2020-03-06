#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
namespace std_namespace {
	using std::string;
	struct TreeNode {
		char data;
		int status;
		TreeNode *left_child;
		TreeNode *right_child;
		TreeNode() {
			data = '\0';
			status = -1000000;
			left_child = NULL;
			right_child = NULL;
		}
		TreeNode(char data_) {
			data = data_;
			status = 1;
			left_child = NULL;
			right_child = NULL;
		}
	};
	bool AddToTree(TreeNode *root, char *tree_str) {
		int str_len = strlen(tree_str);
		TreeNode *current_node = root;
		for (int i = 0; i < str_len; i++) {
			if (i == str_len - 1) {
				if (current_node->left_child == NULL && current_node->right_child == NULL) {
					if (current_node->status > 1) {
						printf("%s\n", tree_str);
						return false;
					}
				}
				if (tree_str[i] == '1') {
					if (current_node->left_child != NULL) {
						printf("%s\n", tree_str);
						return false;
					} else {
						current_node->left_child = new TreeNode('1');
						return true;
					}
				} else {
					if (current_node->right_child != NULL) {
						printf("%s\n", tree_str);
						return false;
					} else {
						current_node->right_child = new TreeNode('0');
						return true;
					}
				}
			} else {
				if (current_node->left_child == NULL && current_node->right_child == NULL) {
					if (current_node->status > 1) {
						printf("%s\n", tree_str);
						return false;
					}
				}
				if (tree_str[i] == '1') {
					if (current_node->left_child != NULL) {
						current_node = current_node->left_child;
						current_node->status++;
					} else {
						current_node->left_child = new TreeNode('1');
						current_node = current_node->left_child;
					}
				} else {
					if (current_node->right_child != NULL) {
						current_node = current_node->right_child;
						current_node->status++;
					} else {
						current_node->right_child = new TreeNode('0');
						current_node = current_node->right_child;
					}
				}
			}
		}
	}
}

int main() {
	using namespace std_namespace;
	int zuShu = 0, flag = 0;
	TreeNode *root = new TreeNode();
	char tree_str[100000] = {'\0'};
	scanf("%d", &zuShu);
	for (int i = 0; i < zuShu; i++) {
		scanf("%s", tree_str);
		if (flag) {
			continue;
		} else {
			if (!AddToTree(root, tree_str)) {
				flag = 1;
			}
		}
	}
	if (!flag) {
		printf("YES\n");
	}
	return 0;
}

