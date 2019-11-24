#include<string>
#include<iostream>
#include<cstdio>
#include<cstdlib>
namespace std_namespace {
	using std::string;
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
			}
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
		Element *top_;
		Element *base_;
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
			case '%':
				return 2;
			case '^':
				return 3;
		}
	}
	int Caculate(int num_1, int num_2, char oper) {
		switch (oper) {
			case '+':
				return num_1 + num_2;
			case '-':
				return num_1 - num_2;
			case'*':
				return num_1 * num_2;
			case '/':
				return num_1 / num_2;
			case '%':
				return num_1 % num_2;
			case '^': {
				int ans = 1;
				for (int i = 0; i < num_2; i++)
					ans *= num_1;
				return ans;
			}
		}
	}
}

int main() {
	using namespace std_namespace;
	int zuShu = 0;
	scanf("%d", &zuShu);
	while (zuShu--) {
		char sentence[1000] = {'\0'};
		scanf("%s", sentence);
		bool need_oper = false, legal = true;
		int bracket_num[2] = {0}, sign = 1;
		for (int i = 0; sentence[i] != '\0'; i++) {
			if (sentence[i] >= '0' && sentence[i] <= '9') {
				if (need_oper) {
					legal = false;
					break;
				} else {
					int num = 0;
					while (sentence[i] >= '0' && sentence[i] <= '9') {
						num = num * 10 + (sentence[i] - '0');
						i++;
					}
					need_oper = true;
					sign = 1;
					i--;
				}
			} else {
				if (sentence[i] == '(') {
					bracket_num[0]++;
				}
				if (sentence[i] == ')') {
					bracket_num[1]++;
				}
				if (need_oper) {
					if (sentence[i] == '(') {
						legal = false;
						break;
					} else if (sentence[i] == ')') {
						continue;
					} else {
						need_oper = false;
					}
				} else {
					if (sentence[i] == '-') {
						if (sentence[i + 1] >= '0' && sentence[i + 1] <= '9') {
							sign = -1;
						} else {
							legal = false;
							break;
						}
					} else if (sentence[i] == '(') {
						continue;
					} else {
						legal = false;
						break;
					}
				}
			}
		}
		if (bracket_num[0] != bracket_num[1]) {
			legal = false;
		}
		if (!legal) {
			printf("error.\n");
			continue;
		}

		Stack<char> *oper_stack = new Stack<char>();
		Stack<int> *num_stack = new Stack<int>();
		bool is_oper = false;
		int final_flag = 0;
		for (int i = 0; sentence[i] != '\0'; i++) {
			if (final_flag != 0)
				break;
			if (sentence[i] == '+' || (sentence[i] == '-' && is_oper) ||
			    sentence[i] == '*' || sentence[i] == '/' || sentence[i] == '%') {
				char new_oper = sentence[i], previous_oper;
				bool flag = true;
				while (!oper_stack->Empty()) {
					previous_oper = oper_stack->Top();
					if (OperPriority(previous_oper) < OperPriority(new_oper)) {
						oper_stack->Push(new_oper);
						flag = false;
						break;
					} else {
						int num_2 = num_stack->Pop(), num_1 = num_stack->Pop();
						if (previous_oper == '/') {
							if (num_2 == 0) {
								final_flag = 1;
								break;
							}
						} else if (previous_oper == '^') {
							if (num_2 < 0) {
								final_flag = 2;
								break;
							}
						}
						num_stack->Push(Caculate(num_1, num_2, previous_oper));
						//printf("! %d %c %d = %d\n", num_1, previous_oper, num_2, Caculate(num_1, num_2, previous_oper));
						oper_stack->Pop();
					}
				}
				if (flag) {
					oper_stack->Push(new_oper);
				}
				is_oper = false;
			} else if (sentence[i] == '^') {
				char new_oper = sentence[i];
				oper_stack->Push(new_oper);
				is_oper = false;
			} else if (sentence[i] == '(' || sentence[i] == ')') {
				if (sentence[i] == '(') {
					oper_stack->Push(sentence[i]);
				} else {
					char previous_oper = oper_stack->Pop();
					while (previous_oper != '(') {
						int num_2 = num_stack->Pop(), num_1 = num_stack->Pop();
						if (previous_oper == '/') {
							if (num_2 == 0) {
								final_flag = 1;
								break;
							}
						} else if (previous_oper == '^') {
							if (num_2 < 0) {
								final_flag = 2;
								break;
							}
						}
						num_stack->Push(Caculate(num_1, num_2, previous_oper));
						//printf("! %d %c %d = %d\n", num_1, previous_oper, num_2, Caculate(num_1, num_2, previous_oper));
						previous_oper = oper_stack->Pop();
					}
				}
			} else {
				int sign = 1;
				if (sentence[i] == '-') {
					sign = -1;
					i++;
				}
				int new_num = 0;
				for (; sentence[i] >= '0' && sentence[i] <= '9'; i++) {
					new_num = new_num * 10 + (sentence[i] - '0');
				}
				num_stack->Push(new_num * sign);
				is_oper = true;
				i--;
			}
		}
		if (final_flag == 0) {
			char previous_oper;
			while (!oper_stack->Empty()) {
				previous_oper = oper_stack->Pop();
				int num_2 = num_stack->Pop(), num_1 = num_stack->Pop();
				if (previous_oper == '/') {
					if (num_2 == 0) {
						final_flag = 1;
						break;
					}
				} else if (previous_oper == '^') {
					if (num_2 < 0) {
						final_flag = 2;
						break;
					}
				}
				num_stack->Push(Caculate(num_1, num_2, previous_oper));
				//printf("! %d %c %d = %d\n", num_1, previous_oper, num_2, Caculate(num_1, num_2, previous_oper));
			}
		}
		if (final_flag == 0) {
			printf("%d\n", num_stack->Pop());
			continue;
		} else if (final_flag == 1) {
			printf("Divide 0.\n");
			continue;
		} else {
			printf("error.\n");
			continue;
		}
	}
	return 0;
}
