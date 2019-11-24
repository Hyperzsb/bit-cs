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
			return top_data;
		}
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
