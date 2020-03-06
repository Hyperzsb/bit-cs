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

int ans_index[100] = {0};
int num = 0;
int ans_length = 0;
int TopologicalSort(int **node_to_routes, int **node_from_routes, int node_num, char **node_data) {
	int *origin_sum = (int *)malloc(node_num * sizeof(int));
	for (int i = 0; i < node_num; i++) {
		origin_sum[i] = node_from_routes[i][node_num];
	}
	int sum = node_num;
	while (sum > 1) {
		int flag = 1;
		for (int i = 0; i < node_num; i++) {
			if (node_from_routes[i][node_num + 1] == 0 && node_from_routes[i][node_num] == 0) {
				flag = 0;
				for (int j = 0; j < node_num; j++) {
					if (node_to_routes[i][j] != 0) {
						node_from_routes[j][node_num] -= node_to_routes[i][j];
					}
				}
				node_from_routes[i][node_num + 1] = 1;
				node_from_routes[i][node_num] = -1;
				sum--;
				break;
			}
		}
		if (flag && sum > 1) {
			printf("NO TOPOLOGICAL PATH\n");
			return 0;
		}
	}
	int flag = 1;
	for (int i = 0; i < node_num; i++) {
		if (node_from_routes[i][node_num + 1] == 0 && node_from_routes[i][node_num] == 0) {
			flag = 0;
			for (int j = 0; j < node_num; j++) {
				if (node_to_routes[i][j] != 0) {
					node_from_routes[j][node_num] -= node_to_routes[i][j];
				}
			}
			node_from_routes[i][node_num] = -1;
			sum--;
			break;
		}
	}
	if (flag) {
		printf("NO TOPOLOGICAL PATH\n");
		return 0;
	}
	for (int i = 0; i < node_num; i++) {
		node_from_routes[i][node_num] = origin_sum[i];
	}
	sum = node_num;
	while (sum > 1) {
		int flag = 1;
		for (int i = 0; i < node_num; i++) {
			if (node_from_routes[i][node_num] == 0) {
				flag = 0;
				printf("%s-", node_data[i]);
				for (int j = 0; j < node_num; j++) {
					if (node_to_routes[i][j] != 0) {
						node_from_routes[j][node_num] -= node_to_routes[i][j];
					}
				}
				node_from_routes[i][node_num] = -1;
				sum--;
				break;
			}
		}
	}
	for (int i = 0; i < node_num; i++) {
		if (node_from_routes[i][node_num] == 0) {
			printf("%s\n", node_data[i]);
			for (int j = 0; j < node_num; j++) {
				if (node_to_routes[i][j] != 0) {
					node_from_routes[j][node_num] -= node_to_routes[i][j];
				}
			}
			node_from_routes[i][node_num] = -1;
			sum--;
			break;
		}
	}
	for (int i = 0; i < node_num; i++) {
		node_from_routes[i][node_num] = origin_sum[i];
	}
	return 1;
}
void PrimaryRoute(int start, int **node_to_routes, int **node_from_routes, int node_num, List<int> &ans_list, int ans_len) {
	if (node_to_routes[start][node_num] == 0) {
		ans_list.pushBack(start);
		if (ans_len < ans_length) {
		} else if (ans_len > ans_length) {
			ans_length = ans_len;
			num = ans_list.size();
			for (int i = 0; i < num; i++) {
				ans_index[i] = ans_list.popFront();
				ans_list.pushBack(ans_index[i]);
			}
		} else {
			int size = ans_list.size(), flag = 0;
			int *tmp_ans = (int *)malloc(size * sizeof(int));
			for (int i = 0; i < size; i++) {
				tmp_ans[i] = ans_list.popFront();
				ans_list.pushBack(tmp_ans[i]);
			}
			for (int i = 0; i < num && i < size; i++) {
				if (tmp_ans[i] < ans_index[i]) {
					flag = 1;
					break;
				}
			}
			if (flag) {
				num = size;
				for (int i = 0; i < size; i++) {
					ans_index[i] = tmp_ans[i];
				}
			}
		}
		ans_list.popBack();
		return ;
	} else {
		ans_list.pushBack(start);
		for (int i = 0; i < node_num; i++) {
			if (node_to_routes[start][i] != 0) {
				ans_len += node_to_routes[start][i];
				PrimaryRoute(i, node_to_routes, node_from_routes, node_num, ans_list, ans_len);
				ans_len -= node_to_routes[start][i];
			}
		}
		ans_list.popBack();
	}
	return ;
}
int main() {
	int node_num = 0, route_num = 0;
	scanf("%d,%d", &node_num, &route_num);
	char **node_data = (char **)malloc((node_num + 3) * sizeof(char *));
	char nodes_c_str[10000] = {'\0'};
	scanf("%s", nodes_c_str);
	int index = 0;
	for (int i = 0; i < node_num; i++) {
		node_data[i] = (char *)malloc(100 * sizeof(char));
		for (int j = 0; j < 100; j++) {
			node_data[i][j] = '\0';
		}
		int j = 0;
		for (; ; j++, index++) {
			if ((nodes_c_str[index] == ',') || (nodes_c_str[index] == '\0')) {
				j++;
				index++;
				break;
			}
			node_data[i][j] = nodes_c_str[index];
		}
	}
	int **node_to_routes = (int **)malloc((node_num + 3) * sizeof(int *));
	int **node_from_routes = (int **)malloc((node_num + 3) * sizeof(int *));
	for (int i = 0; i < node_num; i++) {
		node_to_routes[i] = (int *)malloc((node_num + 3) * sizeof(int));
		node_from_routes[i] = (int *)malloc((node_num + 3) * sizeof(int));
		for (int j = 0; j < node_num + 2; j++) {
			node_to_routes[i][j] = 0;
			node_from_routes[i][j] = 0;
		}
	}
	getchar();
	int start = 0, end = 0, weight = 0;
	for (int i = 0; i < route_num - 1; i++) {
		scanf("<%d,%d,%d>,", &start, &end, &weight);
		node_to_routes[start][end] = weight;
		node_to_routes[start][node_num] += weight;
		node_from_routes[end][start] = weight;
		node_from_routes[end][node_num] += weight;
	}
	scanf("<%d,%d,%d>", &start, &end, &weight);
	node_to_routes[start][end] = weight;
	node_to_routes[start][node_num] += weight;
	node_from_routes[end][start] = weight;
	node_from_routes[end][node_num] += weight;
	int flag = TopologicalSort(node_to_routes, node_from_routes, node_num, node_data);
	if (flag) {
		List<int> ans_list;
		for (int i = 0; i < node_num; i++) {
			if (node_from_routes[i][node_num] == 0) {
				PrimaryRoute(i, node_to_routes, node_from_routes, node_num, ans_list, 0);
			}
		}
		for (int i = 0; i < num - 1; i++) {
			printf("%s-", node_data[ans_index[i]]);
		}
		printf("%s\n", node_data[ans_index[num - 1]]);
	}

	return 0;
}

