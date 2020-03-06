#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<string>
namespace std_namespace {
	using std::string;
	using std::cin;
	template <typename T>
	class List {

	public:
		List() : _size(0), _HEAD(NULL), _TAIL(NULL){}
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
	};
	bool CompareStr(string new_str, List<string> &str_list) {
		int list_size = str_list.size();
		for (int i = 0; i < list_size; i++) {
			string old_str = str_list.popFront();
			if (new_str.length() > old_str.length()) {
				int index = new_str.find(old_str);
				if (index == 0) {
					printf("%s\n", new_str.c_str());
					return false;
				}
			} else {
				int index = old_str.find(new_str);
				if (index == 0) {
					printf("%s\n", new_str.c_str());
					return false;
				}
			}
			str_list.pushBack(old_str);
		}
		return true;
	}
}

int main() {
	using namespace std_namespace;
	int zuShu = 0, flag = 0;
	List<string> str_list;
	cin >> zuShu;
	for (int i = 0; i < zuShu; i++) {
		string new_str;
		cin >> new_str;
		if (flag) {
			continue;
		} else {
			if (CompareStr(new_str, str_list)) {
				str_list.pushBack(new_str);
				continue;
			} else {
				flag = 1;
			}
		}
	}
	if (flag) {
		return 0;
	} else {
		printf("YES\n");
		return 0;
	}

	return 0;
}

