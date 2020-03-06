#include<iostream>
using namespace std;

class Data {

private:
	int _id;

public:
	Data() {
		_id = -1;
	};
	Data(int id) {
		_id = id;
	};
	void setId(int id) {
		_id = id;
		return ;
	};
	int getId() {
		return _id;
	}
};

class Stack {

private:
	struct Element {
		Data data;
		Element *next;
	} _element;
	int _size;
	Element *_HEAD;


public:
	Stack() : _size(0) , _HEAD(NULL) {};
	~Stack() {};
	void push(Data data) {
		if (_size == 0) {
			Element *newElement = new Element;
			newElement->data = data;
			newElement->next = NULL;
			_HEAD = newElement;
			_size = 1;
		} else {
			Element *newElement = new Element;
			newElement->data = data;
			newElement->next = _HEAD;
			_HEAD = newElement;
			_size++;
		}
	};
	Data pop() {
		if (_size == 0) {
			return Data();
		} else {
			Data oldData = _HEAD->data;
			Element *oldElement = _HEAD;
			_HEAD = _HEAD->next;
			delete oldElement;
			_size--;
			return oldData;
		}
	};
	Data top() {
		if (_size == 0) {
			return Data();
		} else {
			Data oldData = _HEAD->data;
			return oldData;
		}
	}
	int size() {
		return _size;
	};
};

class Queue {

private:
	struct Element {
		Data data;
		Element *next;
		Element *previous;
	} _element;
	int _size;
	Element *_HEAD;
	Element *_TAIL;

public:
	Queue(): _size(0), _HEAD(NULL), _TAIL(NULL) {};
	~Queue() {};
	void push(Data data) {
		if (_size == 0) {
			Element *newElement = new Element;
			newElement->data = data;
			newElement->next = NULL;
			_TAIL = newElement;
			_HEAD = newElement;
			_size = 1;
		} else {
			Element *newElement = new Element;
			newElement->data = data;
			newElement->next = NULL;
			_TAIL->next = newElement;
			_TAIL = newElement;
			_size++;
		}
	};
	Data pop() {
		if (_size ==  0) {
			return Data();
		} else {
			Data oldData = _HEAD->data;
			Element *oldElement = _HEAD;
			_HEAD = _HEAD->next;
			delete oldElement;
			if (_HEAD == NULL) {
				_TAIL = NULL;
			}
			_size--;
			return oldData;
		}
	};
	int size() {
		return _size;
	};
};

int main() {
	int zuShu = 0;
	cin >> zuShu;
	while (zuShu--) {
		int zhanShu = 0, carMax = 0, zhanMax = 0, huoSum = 0, ans = 0;
		cin >> zhanShu >> carMax >> zhanMax;
		Queue *queue = new Queue[zhanShu];
		Stack *stack = new Stack();
		for (int i = 0; i < zhanShu; i++) {
			int huoShu = 0;
			cin >> huoShu;
			huoSum += huoShu;
			for (int j = 0; j < huoShu; j++) {
				int dest = 0;
				cin >> dest;
				Data data = Data(dest);
				queue[i].push(data);
			}
		}
		int current = 0;
		while (huoSum) {
			if (current == zhanShu)
				current = 0;
			Data getData;
			//cout << "At " << current + 1 << ":" << endl;
			while (queue[current].size() <= zhanMax && stack->size() > 0) {
				if (queue[current].size() == zhanMax && stack->size() > 0) {
					getData = stack->top();
					if (getData.getId() == current + 1) {
						//cout << "Get Destination " << current + 1 << endl;
						stack->pop();
						huoSum--;
						ans++;
						continue;
					} else {
						break;
					}
				}
				getData = stack->pop();
				ans++;
				if (getData.getId() == current + 1) {
					//cout << "Get Destination " << current + 1 << endl;
					huoSum--;
					continue;
				} else {
					//cout << "Load " << getData.getId() << " to " << current + 1 << endl;
					queue[current].push(getData);
				}
			}
			while (queue[current].size() > 0 && stack->size() < carMax) {
				getData = queue[current].pop();
				//cout << "Reload " << getData.getId() << endl;
				ans++;
				stack->push(getData);
			}
			current++;
			ans += 2;
		}
		cout << ans - 2 << endl;
		delete []queue;
		delete stack;
	}
	return 0;
}
