#include<cstdio>
#include<cstdlib>
#include<memory.h>
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
	struct Node {
		char data;
		int *route;
	};
	void bfs(Node *map, int order, int max_route, int *flag_list) {
		List<int> index;
		index.pushBack(order);
		while (index.size() != 0) {
			int current_index = index.popFront();
			if (flag_list[current_index] == 1) {
				continue;
			} else {
				printf("%c", map[current_index].data);
				flag_list[current_index] = 1;
				for (int i = max_route - 1; i >= 0; i--) {
					if (map[current_index].route[i] == 1) {
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
	List<char> node_list;
	char new_node = '\0';
	scanf("%c\n", &new_node);
	while ( new_node != '*') {
		node_list.pushBack(new_node);
		scanf("%c\n", &new_node);
	}
	int size = node_list.size();
	Node *map = (Node *)malloc(size * sizeof(Node));
	int *flag_list = (int *)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		map[i].data = node_list.popFront();
		map[i].route = (int *)malloc(size * sizeof(int));
		for (int j = 0; j < size; j++) {
			map[i].route[j] = 0;
		}
		flag_list[i] = 0;
	}
	int start = 0, end = 0;
	scanf("%d,%d", &start, &end);
	while (start != -1 || end != -1) {
		map[start].route[end] = 1;
		map[end].route[start] = 1;
		scanf("%d,%d", &start, &end);
	}
	printf("the ALGraph is\n");
	for (int i = 0; i < size; i++) {
		printf("%c", map[i].data);
		for (int j = size - 1; j >= 0; j--) {
			if (map[i].route[j] == 1) {
				printf(" %d", j);
			}
		}
		printf("\n");
	}
	printf("the Breadth-First-Seacrh list:");
	for (int i = 0; i < size; i++) {
		if (flag_list[i] == 0) {
			bfs(map, i, size, flag_list);
		}
	}
	printf("\n");

	return 0;
}

