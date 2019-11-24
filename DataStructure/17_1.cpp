#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
namespace std_namespace {
	using std::string;
	void CreateTree(char *in_order_str, int in_range[2], char *post_order_str, int post_range[2], char *tree_str, int index) {
		if ((in_range[0] == in_range[1]) && (post_range[0] == post_range[1])) {
//			if (in_range[0] == in_range[1]) {
//				printf("!\n");
//			} else {
//				printf("?\n");
//			}
//			printf("Leaf: %c at %d\n", post_order_str[post_range[1]], post_range[1]);
			tree_str[index] = post_order_str[post_range[1]];
			return;
		} else {
//			printf("in_order_str: ");
//			for (int i = in_range[0]; i <= in_range[1]; i++) {
//				printf("%c", in_order_str[i]);
//			}
//			printf("\n");
//			printf("post_order_str: ");
//			for (int i = post_range[0]; i <= post_range[1]; i++) {
//				printf("%c", post_order_str[i]);
//			}
//			printf("\n");
			char root = post_order_str[post_range[1]];
			if (in_order_str[in_range[1]] == post_order_str[post_range[1]]) {
//				printf("No left child: %c at %d\n", root, post_range[1]);
				int new_in_range[2] = {in_range[0], in_range[1] - 1};
				int new_post_range[2] = {post_range[0], post_range[1] - 1};
				tree_str[index] = root;
				CreateTree(in_order_str, new_in_range, post_order_str, new_post_range, tree_str, index * 2 + 1);
			} else if (in_order_str[in_range[0]] == post_order_str[post_range[1]]) {
//				printf("No right child: %c at %d\n", root, post_range[1]);
				int new_in_range[2] = {in_range[0] + 1, in_range[1]};
				int new_post_range[2] = {post_range[0], post_range[1] - 1};
				tree_str[index] = root;
				CreateTree(in_order_str, new_in_range, post_order_str, new_post_range, tree_str, index * 2 + 2);
			} else {
//				printf("At: %c at %d\n", root, post_range[1]);
//				printf("origin: in_range = { %d, %d } post_range = { %d, %d }\n",
//				       in_range[0], in_range[1], post_range[0], post_range[1]);
				int left_in_range[2], right_in_range[2];
				int left_post_range[2], right_post_range[2];
				int tmp_index;
				for (int i = in_range[0]; i <= in_range[1]; i++) {
					if (in_order_str[i] == root) {
						tmp_index = i;
						break;
					}
				}
				left_in_range[0] = in_range[0], left_in_range[1] = tmp_index - 1;
				right_in_range[0] = tmp_index + 1, right_in_range[1] = in_range[1];
				left_post_range[0] = post_range[0], left_post_range[1] = post_range[1] - 1 - (in_range[1] - tmp_index);
				right_post_range[0] = left_post_range[1] + 1, right_post_range[1] = post_range[1] - 1;
//				printf("left_child: in_range = { %d, %d } post_range = { %d, %d }\n",
//				       left_in_range[0], left_in_range[1], left_post_range[0], left_post_range[1]);
//				printf("right_child: in_range = { %d, %d } post_range = { %d, %d }\n",
//				       right_in_range[0], right_in_range[1], right_post_range[0], right_post_range[1]);
				tree_str[index] = root;
				CreateTree(in_order_str, left_in_range, post_order_str, left_post_range, tree_str, index * 2 + 1);
				CreateTree(in_order_str, right_in_range, post_order_str, right_post_range, tree_str, index * 2 + 2);
			}
		}
	}
}

int main() {
	using namespace std_namespace;
	char in_order_str[100] = {'\0'}, post_order_str[100] = {'\0'}, tree_str[1000] = {'\0'};
	scanf("%s%s", in_order_str, post_order_str);
	int tree_size = strlen(in_order_str), sum = 0;
	int in_range[2] = {0, tree_size - 1}, post_range[2] = {0, tree_size - 1};
	CreateTree(in_order_str, in_range, post_order_str, post_range, tree_str, 0);
	for (int i = 0; i < 1000; i++) {
		if (sum == tree_size) {
			break;
		}
		if (tree_str[i] != '\0') {
			printf("%c", tree_str[i]);
			sum++;
		}
	}
	printf("\n");
	return 0;
}

