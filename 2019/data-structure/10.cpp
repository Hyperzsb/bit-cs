#include<string>
#include<cstdio>
#include<cstdlib>
#include<list>

namespace std_namespace {
	using std::string;
	using std::list;
	enum Status {Buy, Sell, Default};
	struct Transaction {
		int id;
		float price;
		int quantity;
		Status status;
		Transaction() {
			id = -1;
			price = -1;
			quantity = -1;
			status = Default;
		}
		Transaction(int _id, float _price, int _quantity, Status _status) {
			id = _id;
			price = _price;
			quantity = _quantity;
			status = _status;
		}
	};
	class MatchQueue {

	public:
		MatchQueue(const string &stock_id): stock_id_(stock_id), buy_queue_size_(0), sell_queue_size_(0) {
			buy_queue_head_ = new Node(Transaction(), NULL);
			buy_queue_tail_ = NULL;
			sell_queue_head_ = new Node(Transaction(), NULL);
			sell_queue_tail_ = NULL;
		}
		~MatchQueue() {}
		void Push(Transaction &new_transaction) {
			Status status = new_transaction.status;
			switch (status) {
				case Buy: {
					Node *previous = sell_queue_head_, *current = sell_queue_head_;
					while (current->next != NULL) {
						previous = current;
						current = current->next;
						if (current->transaction.price <= new_transaction.price) {
							if (current->transaction.quantity > new_transaction.quantity) {
								printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n",
								       (current->transaction.price + new_transaction.price) / 2,
								       new_transaction.quantity, new_transaction.id, current->transaction.id);
								current->transaction.quantity -= new_transaction.quantity;
								new_transaction.quantity -= new_transaction.quantity;
								break;
							} else if (current->transaction.quantity == new_transaction.quantity) {
								printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n",
								       (current->transaction.price + new_transaction.price) / 2,
								       new_transaction.quantity, new_transaction.id, current->transaction.id);
								new_transaction.quantity -= new_transaction.quantity;
								this->Erase(current->transaction);
								current = previous;
								break;
							} else {
								printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n",
								       (current->transaction.price + new_transaction.price) / 2,
								       current->transaction.quantity, new_transaction.id, current->transaction.id);
								new_transaction.quantity -= current->transaction.quantity;
								this->Erase(current->transaction);
								current = previous;
							}
						}
					}
					if (new_transaction.quantity > 0) {
						if (buy_queue_size_ == 0) {
							Node *new_node = new Node(new_transaction, NULL);
							buy_queue_head_->next = new_node;
							buy_queue_tail_ = new_node;
							buy_queue_size_ = 1;
						} else {
							Node *previous = buy_queue_head_, *current = buy_queue_head_;
							int flag = 1;
							while (current->next != NULL) {
								previous = current;
								current = current->next;
								if (current->transaction.price < new_transaction.price) {
									Node *new_node = new Node(new_transaction, current);
									previous->next = new_node;
									flag = 0;
									++buy_queue_size_;
									break;
								}
							}
							if (flag) {
								Node *new_node = new Node(new_transaction, NULL);
								buy_queue_tail_->next = new_node;
								buy_queue_tail_ = new_node;
								++buy_queue_size_;
							}
						}
					}
					break;
				}
				case Sell: {
					Node *previous = buy_queue_head_, *current = buy_queue_head_;
					while (current->next != NULL) {
						previous = current;
						current = current->next;
						if (current->transaction.price >= new_transaction.price) {
							if (current->transaction.quantity > new_transaction.quantity) {
								printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n",
								       (current->transaction.price + new_transaction.price) / 2,
								       new_transaction.quantity, new_transaction.id, current->transaction.id);
								current->transaction.quantity -= new_transaction.quantity;
								new_transaction.quantity -= new_transaction.quantity;
								break;
							} else if (current->transaction.quantity == new_transaction.quantity) {
								printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n",
								       (current->transaction.price + new_transaction.price) / 2,
								       new_transaction.quantity, new_transaction.id, current->transaction.id);
								new_transaction.quantity -= new_transaction.quantity;
								this->Erase(current->transaction);
								current = previous;
								break;
							} else {
								printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n",
								       (current->transaction.price + new_transaction.price) / 2,
								       current->transaction.quantity, new_transaction.id, current->transaction.id);
								new_transaction.quantity -= current->transaction.quantity;
								this->Erase(current->transaction);
								current = previous;
							}
						}
					}
					if (new_transaction.quantity > 0) {
						if (sell_queue_size_ == 0) {
							Node *new_node = new Node(new_transaction, NULL);
							sell_queue_head_->next = new_node;
							sell_queue_tail_ = new_node;
							sell_queue_size_ = 1;
						} else {
							Node *previous = sell_queue_head_, *current = sell_queue_head_;
							int flag = 1;
							while (current->next != NULL) {
								previous = current;
								current = current->next;
								if (current->transaction.price > new_transaction.price) {
									Node *new_node = new Node(new_transaction, current);
									previous->next = new_node;
									flag = 0;
									++sell_queue_size_;
									break;
								}
							}
							if (flag) {
								Node *new_node = new Node(new_transaction, NULL);
								sell_queue_tail_->next = new_node;
								sell_queue_tail_ = new_node;
								++sell_queue_size_;
							}
						}
					}
					break;
				}
			}
			return ;
		}
		void Erase(Transaction &selected_transaction) {
			Status status = selected_transaction.status;
			switch (status) {
				case Buy: {
					Node *previous = buy_queue_head_, *current = buy_queue_head_;
					while (current->next != NULL) {
						previous = current;
						current = current->next;
						if (current->transaction.id == selected_transaction.id) {
							previous->next = current->next;
							delete current;
							current = previous;
							buy_queue_size_--;
							break;
						}
					}
					break;
				}
				case Sell: {
					Node *previous = sell_queue_head_, *current = sell_queue_head_;
					while (current->next != NULL) {
						previous = current;
						current = current->next;
						if (current->transaction.id == selected_transaction.id) {
							previous->next = current->next;
							delete current;
							current = previous;
							sell_queue_size_--;
							break;
						}
					}
					break;
				}
			}
			return ;
		}
		void Erase(int transaction_id) {
			bool flag = true;
			Node *previous = buy_queue_head_, *current = buy_queue_head_;
			while (current->next != NULL) {
				previous = current;
				current = current->next;
				if (current->transaction.id == transaction_id) {
					printf("deleted order:orderid: %04d, stockid:%s, price: %6.1f, quantity: %4d, b/s: b\n",
					       current->transaction.id, this->stock_id_.c_str(), current->transaction.price, current->transaction.quantity);
					previous->next = current->next;
					flag = false;
					delete current;
					current = previous;
					buy_queue_size_--;
					break;
				}
			}
			if (!flag) {
				return ;
			}
			previous = sell_queue_head_, current = sell_queue_head_;
			while (current->next != NULL) {
				previous = current;
				current = current->next;
				if (current->transaction.id == transaction_id) {
					printf("deleted order:orderid: %04d, stockid:%s, price: %6.1f, quantity: %4d, b/s: s\n",
					       current->transaction.id, this->stock_id_.c_str(), current->transaction.price, current->transaction.quantity);
					previous->next = current->next;
					flag = false;
					delete current;
					current = previous;
					sell_queue_size_--;
					break;
				}
			}
			if (flag) {
				printf("not found\n");
			}
			return ;
		}
		void TraverseQueue(Status status) {
			switch (status) {
				case Buy: {
					if (buy_queue_size_ != 0) {
						Node *current = buy_queue_head_;
						printf("buy orders:\n");
						while (current->next != NULL) {
							current = current->next;
							printf("orderid: %04d, stockid:%s, price: %6.1f, quantity: %4d, b/s: b\n",
							       current->transaction.id, this->stock_id_.c_str(), current->transaction.price, current->transaction.quantity);
						}
					} else {
						printf("buy orders:\n");
					}
					break;
				}
				case Sell: {
					if (sell_queue_size_ != 0) {
						Node *current = sell_queue_head_;
						printf("sell orders:\n");
						while (current->next != NULL) {
							current = current->next;
							printf("orderid: %04d, stockid:%s, price: %6.1f, quantity: %4d, b/s: s\n",
							       current->transaction.id, this->stock_id_.c_str(), current->transaction.price, current->transaction.quantity);
						}
					} else {
						printf("sell orders:\n");
					}
					break;
				}
			}
		}
		string stock_id() {
			return stock_id_;
		}
		int buy_queue_size() {
			return buy_queue_size_;
		}
		int sell_queue_size() {
			return sell_queue_size_;
		}
		MatchQueue *me() {
			return this;
		}

	private:
		struct Node {
			Transaction transaction;
			Node *next;
			Node(const Transaction &_transaction, Node *_next) {
				transaction = _transaction;
				next = _next;
			}
		};
		string stock_id_;
		int buy_queue_size_;
		int sell_queue_size_;
		Node *buy_queue_head_;
		Node *buy_queue_tail_;
		Node *sell_queue_head_;
		Node *sell_queue_tail_;
	};
}
int main() {
	using namespace std_namespace;
	int order_type = 0, order_sum = 1;
	list<MatchQueue> match_queue_list;
	MatchQueue *order_arr[1000] = {NULL};
	while (scanf("%d", &order_type)) {
		switch (order_type) {
			case 1: {
				int quantity = 0, flag = 1;
				float price = 0;
				char c_stock_id[5] = {'\0'}, oper = ' ';
				scanf(" %c%c%c%c %f %d %c", &c_stock_id[0], &c_stock_id[1], &c_stock_id[2], &c_stock_id[3],
				      &price, &quantity, &oper);
				string stock_id = c_stock_id;
				Transaction new_transaction;
				switch (oper) {
					case 'b': {
						new_transaction = Transaction(order_sum, price, quantity, Buy);
						break;
					}
					case 's': {
						new_transaction = Transaction(order_sum, price, quantity, Sell);
						break;
					}
				}
				printf("orderid: %04d\n", order_sum++);
				list<MatchQueue>::iterator match_queue_list_iter = match_queue_list.begin();
				for (; match_queue_list_iter != match_queue_list.end(); match_queue_list_iter++) {
					if (match_queue_list_iter->stock_id() == stock_id) {
						flag = 0;
						order_arr[order_sum - 1] = match_queue_list_iter->me();
						match_queue_list_iter->Push(new_transaction);
						break;
					}
				}
				if (flag) {
					MatchQueue new_stock = MatchQueue(stock_id);
					order_arr[order_sum - 1] = &new_stock;
					new_stock.Push(new_transaction);
					match_queue_list.push_back(new_stock);
				}
				break;
			}
			case 2: {
				char c_stock_id[5] = {'\0'};
				scanf(" %c%c%c%c", &c_stock_id[0], &c_stock_id[1], &c_stock_id[2], &c_stock_id[3]);
				string stock_id = c_stock_id;
				int flag = 1;
				list<MatchQueue>::iterator match_queue_list_iter = match_queue_list.begin();
				for (; match_queue_list_iter != match_queue_list.end(); match_queue_list_iter++) {
					if (match_queue_list_iter->stock_id() == stock_id) {
						flag = 0;
						match_queue_list_iter->TraverseQueue(Buy);
						match_queue_list_iter->TraverseQueue(Sell);
						break;
					}
				}
				if (flag) {
					printf("buy orders:\n");
					printf("sell orders:\n");
				}
				break;
			}
			case 3: {
				char c_transaction_id[5] = {'\0'};
				scanf(" %c%c%c%c", &c_transaction_id[0], &c_transaction_id[1], &c_transaction_id[2], &c_transaction_id[3]);
				int transaction_id = 0;
				for (int i = 0; i < 4; i++) {
					if (c_transaction_id[i] != '0')
						transaction_id = transaction_id * 10 + (c_transaction_id[i] - '0');
				}
				if (order_arr[transaction_id] != NULL) {
					order_arr[transaction_id]->Erase(transaction_id);
				} else {
					printf("not found\n");
				}
				break;
			}
			default: {
				return 0;
			}
		}
	}
}
