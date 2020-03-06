#include<cstdio>
#include<cstdlib>
#include<cstring>
template <typename T>
class List {

public:
	List() : _size(0), _HEAD(NULL), _TAIL(NULL), _CURRENT(NULL), _INDEX(NULL) {}
	~List() {}
	void pushBack(const T &newData) {
		if (_size == 0) {
			Node *newNode = new Node;
			newNode->data = newData;
			newNode->previous = NULL;
			newNode->next = NULL;
			_HEAD = newNode;
			_TAIL = newNode;
			_size = 1;
		} else {
			Node *newNode = new Node;
			newNode->data = newData;
			newNode->previous = _TAIL;
			newNode->next = NULL;
			_TAIL->next = newNode;
			_TAIL = newNode;
			_size++;
		}
	}
	void pushFront(const T &newData) {
		if (_size == 0) {
			Node *newNode = new Node;
			newNode->data = newData;
			newNode->previous = NULL;
			newNode->next = NULL;
			_HEAD = newNode;
			_TAIL = newNode;
			_size = 1;
		} else {
			Node *newNode = new Node;
			newNode->data = newData;
			newNode->previous = NULL;
			newNode->next = _HEAD;
			_HEAD->previous = newNode;
			_HEAD = newNode;
			_size++;
		}
	}
	T back() {
		if (_size == 0) {
			return T();
		} else {
			return _TAIL->data;
		}
	}
	T front() {
		if (_size == 0) {
			return T();
		} else {
			return _HEAD->data;
		}
	}
	T popBack() {
		if (_size == 0) {
			return T();
		} else {
			T getData = _TAIL->data;
			Node *oldNode = _TAIL;
			_TAIL = _TAIL->previous;
			delete oldNode;
			_size--;
			return getData;
		}
	}
	T popFront() {
		if (_size == 0) {
			return T();
		} else {
			T getData = _HEAD->data;
			Node *oldNode = _HEAD;
			_HEAD = _HEAD->next;
			delete oldNode;
			_size--;
			return getData;
		}
	}
	int size() {
		return _size;
	}

private:
	struct Node {
		T data;
		Node *previous;
		Node *next;
	};
	int _size;
	Node *_HEAD;
	Node *_TAIL;
	Node *_CURRENT;
	Node **_INDEX;
};
struct TreeNode {
	char data;
	TreeNode *parent;
	TreeNode **child;
	int status;
	int height;
	int child_num;
	int win_num;
	int lose_num;
	TreeNode(char data_) {
		data = data_;
		parent = NULL;
		child = NULL;
		child_num = 0;
		status = 0;
		height = 1;
		win_num = 0;
		lose_num = 0;
	}
};
TreeNode *CreateTree(char *tree_str, TreeNode *parent, List<TreeNode *> &leaf_list) {
	int str_len = strlen(tree_str), child_num = 0, child_index = 0, barket[2] = {0}, start = 3, end = 3;
	TreeNode *root = new TreeNode(tree_str[1]);
	for (int i = 3; i < str_len - 1; i++) {
		if (tree_str[i] == '(') {
			barket[0]++;
		} else if (tree_str[i] == ')') {
			barket[1]++;
			if (barket[0] == barket[1]) {
				child_num++;
				barket[0] = barket[1] = 0;
			}
		} else {
			continue;
		}
	}
	if (child_num == 0) {
		leaf_list.pushBack(root);
		root->parent = parent;
		root->win_num = 1;
	} else {
		root->parent = parent;
		root->child_num = child_num;
		TreeNode **child_list = (TreeNode **)malloc(child_num * sizeof(TreeNode *));
		barket[0] = barket[1] = 0;
		for (int i = 3; i < str_len - 1; i++) {
			if (tree_str[i] == '(') {
				end++;
				barket[0]++;
			} else if (tree_str[i] == ')') {
				end++;
				barket[1]++;
				if (barket[0] == barket[1]) {
					char *child_str = (char *)malloc((end - start + 2) * sizeof(char));
					for (int j = 0; j < end - start + 1; j++) {
						child_str[j] = tree_str[start + j];
					}
					child_str[end - start + 1] = '\0';
					child_list[child_index] = CreateTree(child_str, root, leaf_list);
					if (child_list[child_index]->height + 1 > root->height) {
						root->height = child_list[child_index]->height + 1;
					}
					child_index++;
					barket[0] = barket[1] = 0;
					free(child_str);
					i++;
					start = end = i + 1;
				}
			} else {
				end++;
				continue;
			}
		}
		root->child = child_list;
	}
	return root;
}
void TraverseTree(TreeNode *root) {
	printf("%c\n", root->data);
	for (int i = 0; i < root->child_num; i++) {
		TraverseTree(root->child[i]);
	}
	return ;
}
void ReTraverse(TreeNode *leaf) {
	if (leaf->parent == NULL) {
		return ;
	} else {
		if (leaf->status != leaf->child_num) {
			return ;
		} else {
			leaf->parent->win_num += leaf->lose_num;
			leaf->parent->lose_num += leaf->win_num;
			leaf->parent->status++;
			ReTraverse(leaf->parent);
		}
	}
}
TreeNode *NextMove(TreeNode *root) {
	List<int> min_height;
	List<int> max_height;
	for (int i = 0; i < root->child_num; i++) {
		//printf("At: %c(%d), lose_num: %d\n", root->child[i]->data, i, root->child[i]->lose_num);
		if (root->child[i]->lose_num == 0) {
			//printf("min_height add %c(%d)\n", root->child[i]->data, i);
			min_height.pushBack(i);
		} else {
			//printf("max_height add %c(%d)\n", root->child[i]->data, i);
			max_height.pushBack(i);
		}
	}
	if (min_height.size() == 1) {
		//printf("At: 1 min_height size: %d max_height size: %d\n", min_height.size(), max_height.size());
		return root->child[min_height.popFront()];
	} else if (min_height.size() == 0) {
		//printf("At 2 min_height size: %d max_height size: %d\n", min_height.size(), max_height.size());
		int height = 0, size = max_height.size(), current = 0, final = 0;
		for (int i = 0; i < size; i++) {
			current = max_height.popFront();
			if (height < root->child[current]->height) {
				height = root->child[current]->height;
				final = current;
			}
		}
		return root->child[final];
	} else {
		//printf("At 3 min_height size: %d max_height size: %d\n", min_height.size(), max_height.size());
		int height = 0, size = min_height.size(), current = 0, final = 0;
		for (int i = 0; i < size; i++) {
			current = min_height.popFront();
			if (height > root->child[current]->height) {
				height = root->child[current]->height;
				final = current;
			}
		}
		//printf("final: %d\n", final);
		return root->child[final];
	}
}
int main() {
	List<TreeNode *> leaf_list;
	char tree_str[1000] = {'\0'};
	scanf("%s", tree_str);
	TreeNode *root = CreateTree(tree_str, NULL, leaf_list), *current = root;
	TraverseTree(root);
	int leaf_num = leaf_list.size();
	for (int i = 0; i < leaf_num; i++) {
		ReTraverse(leaf_list.popFront());
	}

	char order = '\0', move;
	int first_player = 0, flag = 1;
	do {
		current = root;
		printf("Who play first(0: computer; 1: player )?\n");
		scanf("%d", &first_player);
		if (first_player) {
			flag = 1;
			while (flag) {
				printf("player:\n");
				getchar();
				//fflush(stdin);
				scanf("%c", &move);
				int tmp_flag = 1;
				for (int i = 0; i < current->child_num; i++) {
					if (current->child[i]->data == move) {
						tmp_flag = 0;
						current = current->child[i];
						break;
					}
				}
				if (tmp_flag) {
					printf("illegal move.\n");
					continue;
				} else {
					if (current->child_num == 0) {
						printf("Congratulate, you win.\n");
						flag = 0;
					} else {
						current = NextMove(current);
						printf("computer: %c\n", current->data);
						if (current->child_num == 0) {
							printf("Sorry, you lost.\n");
							flag = 0;
						}
					}
				}
			}
		} else {
			flag = 1;
			while (flag) {
				current = NextMove(current);
				printf("computer: %c\n", current->data);
				if (current->child_num == 0) {
					printf("Sorry, you lost.\n");
					flag = 0;
					continue;
				}
				while (true) {
					printf("player:\n");
					getchar();
					//fflush(stdin);
					scanf("%c", &move);
					int tmp_flag = 1;
					for (int i = 0; i < current->child_num; i++) {
						if (current->child[i]->data == move) {
							tmp_flag = 0;
							current = current->child[i];
							break;
						}
					}
					if (tmp_flag) {
						printf("illegal move.\n");
						continue;
					} else {
						break;
					}
				}
				if (current->child_num == 0) {
					printf("Congratulate, you win.\n");
					flag = 0;
				}
			}
		}
		printf("Continue(y/n)?\n");
		getchar();
		//fflush(stdin);
		scanf("%c", &order);
	} while (order != 'n');
}
