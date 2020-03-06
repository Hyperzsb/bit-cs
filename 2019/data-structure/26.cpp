#include<cstdio>
#include<cstdlib>
#include<string>
namespace std_namespace {
	using std::string;
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
	struct MapNode {
		int data;
		int rote_num;
		int *route;
	};
	void bfs(MapNode *node_arr, int start, int node_num, int *flag_arr) {
		List<int> index;
		int flag = 0;
		index.pushBack(start);
		while (index.size() != 0) {
			int current_index = index.popFront();
			if (flag_arr[current_index] == 1) {
				continue;
			} else {
				if (flag == 0) {
					printf("%d", node_arr[current_index].data);
					flag = 1;
				} else {
					printf("-%d", node_arr[current_index].data);
				}
				flag_arr[current_index] = 1;
				for (int i = 0; i < node_num; i++) {
					int min = 1000000, tmp_index = 0;
//					for (int j = 0; j < node_num; j++) {
//						if (node_arr[current_index].route[j] != 0 && node_arr[current_index].route[j] < min) {
//							min = node_arr[current_index].route[j];
//							tmp_index = j;
//						}
//					}
//					index.pushBack(tmp_index);
//					node_arr[current_index].route[tmp_index] = 0;

					if (node_arr[current_index].route[i] != 0) {
						index.pushBack(i);
					}
				}
			}
		}
		return ;
	}
}

int main() {
	using namespace std_namespace;
	int node_num = 0, start = 0, end = 0, order = 0;
	scanf("%d", &node_num);
	MapNode *node_arr = (MapNode *)malloc(node_num * sizeof(MapNode));
	int *flag_arr = (int *)malloc(node_num * sizeof(int));
	for (int i = 0; i < node_num; i++) {
		node_arr[i].data = i;
		node_arr[i].rote_num = 0;
		node_arr[i].route = (int *)malloc(node_num * sizeof(int));
		for (int j = 0; j < node_num; j++) {
			node_arr[i].route[j] = 0;
		}
		flag_arr[i] = 0;
	}
	scanf("%d", &start);
	while (start != -1) {
		scanf("%d", &end);
		order++;
		node_arr[start].rote_num++;
		node_arr[start].route[end] = order;
		node_arr[end].rote_num++;
		node_arr[end].route[start] = order;
		scanf("%d", &start);
	}
	for (int i = 0; i < node_num; i++) {
		if (flag_arr[i] == 0) {
			bfs(node_arr, i, node_num, flag_arr);
			printf("\n");
		}
	}

	return 0;
}

