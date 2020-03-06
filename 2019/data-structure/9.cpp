#include<string>
#include<cstdio>
#include<cstdlib>
namespace std_namespace {
	using std::string;
	struct Data {
		char num;
		char oper;
		Data() {
			num = '?';
			oper = '?';
		}
		Data(char _num, char _oper) {
			num = _num;
			oper = _oper;
		}
	};
	template <typename T>
	class Stack {

	public:
		Stack() : size_(0) {
			top_ = new Element();
			base_ = top_;
		}
		~Stack() {}
		void Push(const T &data) {
			if (size_ == 0) {
				top_->next = new Element(data, NULL);
				base_ = top_->next;
				size_ = 1;
				return ;
			} else {
				top_->next = new Element(data, top_->next);
				size_++;
				return ;
			}
		}
		T Top() {
			if (size_ == 0) {
				return top_->data;
			} else {
				return top_->next->data;
			}
		}
		T Pop() {
			if (size_ == 0) {
				return top_->data;
			} else {
				Element *top_element = top_->next;
				T top_data = top_element->data;
				top_->next = top_element->next;
				delete top_element;
				size_--;
				return top_data;
			}
		}
		void TraverseStack() {
			Element *current = top_;
			while (current->next != NULL) {
				current = current->next;
				printf("%c\n", current->data.oper);
			}
			return ;
		}
		int size() {
			return size_;
		}
		bool empty() {
			if (size_ == 0) {
				return true;
			} else {
				return false;
			}
		}

	private:
		struct Element {
			T data;
			Element *next;
			Element() {
				data = T();
				next = NULL;
			}
			Element(const T &_data, Element *_next) {
				data = _data;
				next = _next;
			}
		};
		int size_;
		Element *top_;
		Element *base_;
	};

	template <typename T>
	class Queue {

	public:
		Queue(): size_(0) {
			head_ = new Element();
			tail_ = head_;
		}
		~Queue() {}
		void Push(const T &data) {
			if (size_ == 0) {
				Element *newElement = new Element(data, NULL);
				tail_ = newElement;
				head_->next = newElement;
				size_ = 1;
			} else {
				Element *newElement = new Element(data, NULL);
				tail_->next = newElement;
				tail_ = newElement;
				size_++;
			}
		}
		T Pop() {
			if (size_ ==  0) {
				return head_->data;
			} else {
				Element *front_element = head_->next;
				T front_data = front_element->data;
				head_->next = front_element->next;
				delete front_element;
				if (head_->next == NULL) {
					tail_ = head_;
				}
				size_--;
				return front_element;
			}
		};
		T Front() {
			if (size_ == 0) {
				return head_->data;
			} else {
				return head_->next->data;
			}
		}
		T Back() {
			return tail_->data;
		}
		void TraverseQueue() {
			Element *current = head_;
			while (current->next != NULL) {
				current = current->next;
				if (current->data.num != '!') {
					printf("%c", current->data.num);
				} else {
					printf("%c", current->data.oper);
				}
			}
			printf("\n");
			return ;
		}
		int size() {
			return size_;
		}
		bool Empty() {
			if (size_ == 0) {
				return true;
			} else {
				return false;
			}
		}

	private:
		struct Element {
			T data;
			Element *next;
			Element() {
				data = T();
				next = NULL;
			}
			Element(const T &_data, Element *_next) {
				data = _data;
				next = _next;
			}
		};
		int size_;
		Element *head_;
		Element *tail_;
	};

	int OperPriority(const char &oper) {
		switch (oper) {
			case '(':
				return 0;
			case '+':
				return 1;
			case '-':
				return 1;
			case '*':
				return 2;
			case '/':
				return 2;
			case '^':
				return 3;
		}
	}
}

int main() {
	using namespace std_namespace;
	int zuShu = 0;
	scanf("%d", &zuShu);
	while (zuShu--) {
		Stack<Data> *oper_stack = new Stack<Data>();
		Queue<Data> *num_queue = new Queue<Data>();
		char sentence[1000] = {'\0'};
		scanf("%s", sentence);
		for (int i = 0; sentence[i] != '#'; i++) {
			if ((sentence[i] >= 'a' && sentence[i] <= 'z') || (sentence[i] >= 'A' && sentence[i] <= 'Z')) {
				Data *new_num = new Data(sentence[i], '!');
				num_queue->Push(*new_num);
				delete new_num;
			} else {
				Data *new_oper = new Data('!', sentence[i]);
				if (new_oper->oper == '(' || new_oper->oper == ')') {
					if (new_oper->oper == '(') {
						oper_stack->Push(*new_oper);
						delete new_oper;
					} else {
						Data previous_oper = oper_stack->Top();
						while (previous_oper.oper != '(') {
							num_queue->Push(previous_oper);
							oper_stack->Pop();
							previous_oper = oper_stack->Top();
						}
						oper_stack->Pop();
						delete new_oper;
					}
				} else {
					if (new_oper->oper == '^') {
						oper_stack->Push(*new_oper);
						delete new_oper;
					} else {
						int flag = 1;
						Data previous_oper;
						while (!oper_stack->empty()) {
							previous_oper = oper_stack->Top();
							if (OperPriority(previous_oper.oper) < OperPriority(new_oper->oper)) {
								flag = 0;
								oper_stack->Push(*new_oper);
								delete new_oper;
								break;
							} else {
								num_queue->Push(previous_oper);
								oper_stack->Pop();
							}
						}
						if (flag) {
							oper_stack->Push(*new_oper);
							delete new_oper;
						}
					}
				}
			}
		}
		while (!oper_stack->empty()) {
			num_queue->Push(oper_stack->Pop());
		}
		num_queue->TraverseQueue();
	}
	return 0;
}
