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
	Element *head_;
	Element *tail_;
};
