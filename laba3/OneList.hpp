#ifndef ONE_LIST_HPP
#define ONE_LIST_HPP
#include <iterator>

template<typename T>
struct OneList {
public:
	OneList() : start(nullptr) {}
	OneList(OneList<T> const &other) : start(nullptr) {
		if (other.empty()) return;
		// range-based for, не зря же begin и end делал
		for (T value : other) push_back(value);
	}
	OneList(std::initializer_list<T> other) : start(nullptr) {
		for (T value : other) push_back(value);
	}
	~OneList() {
		if (empty()) return;
		Element *x = start;
		start = nullptr;
		while (x != nullptr) {
			Element *prev = x;
			x = prev->next;
			delete prev;
		}
	}
	struct Element {
		T value;
		Element *next;
		void insert_after(T value) {
			Element *x = new Element();
			x->value = value;
			x->next = next;
			next = x;
		}
	} *start;
	struct iterator {
		using iterator_category = std::forward_iterator_tag;
		using difference_type = void;
		using value_type = T;
		using pointer = T *;
		using reference = T &;

		Element *current;
		iterator(Element *start) : current(start) {}
		bool operator==(iterator other) const { return current == other.current; }
		bool operator!=(iterator other) const { return current != other.current; }
		bool empty() const { return current == nullptr; }
		T operator*() {
			if (empty()) { throw "Cannot dereference empty iterator"; }
			return current->value;
		}
		iterator &operator++() {
			if (empty()) { throw "Cannot iterate over empty list"; }
			current = current->next;
			return *this;
		}
		iterator operator++(int) {
			if (empty()) { throw "Cannot iterate over empty list"; }
			iterator copy = *this;
			current = current->next;
			return copy;
		}
		void insert_after(T value) {
			if (empty()) { throw "Cannot insert into empty iterator"; }
			current->insert_after(value);
		}
	};
	Element *last_element() const {
		Element *x = start;
		while (x != nullptr && x->next != nullptr) x = x->next;
		return x;
	}
	Element *walk(size_t i) const {
		Element *x = start;
		while (x != nullptr && x->next != nullptr && i--)
			x = x->next;
		return x;
	}
	size_t size() const {
		// todo: from current to first + from current to last
		Element *x = start;
		size_t size = 0;
		while (x != nullptr) x = x->next, size++;
		return size;
	}
	bool empty() const {
		return start == nullptr;
	}
	T &front() const {
		if (empty()) { throw "Cannot get value from empty list"; }
		return start->value;
	}
	T &back() const {
		if (empty()) { throw "Cannot get value from empty list"; }
		return last_element()->value;
	}
	void push_front(T value) {
		Element *x = new Element();
		x->value = value;
		x->next = start;
		start = x;
	}
	void push_back(T value) {
		Element *x = new Element();
		x->value = value;
		x->next = nullptr;
		if (empty()) {
			start = x;
			return;
		}
		Element *last = last_element();
		last->next = x;
	}
	void insert(size_t i, T value) {
		if (i == 0) {
			push_front(value);
			return;
		}
		if (empty()) {
			push_back(value);
			return;
		}
		Element *before = walk(i-1);
		before->insert_after(value);
	}
	void pop_front() {
		if (empty()) return;
		Element *x = start;
		start = x->next;
		delete x;
	}
	void pop_back() {
		if (empty()) return;
		if (start->next == nullptr) {
			delete start;
			start = nullptr;
			return;
		}
		Element *x = start;
		while (x != nullptr && x->next != nullptr && x->next->next != nullptr) x = x->next;
		Element *last = x->next;
		delete last;
		x->next = nullptr;
	}
	void remove(T value) {
		if (empty()) return;
		while (start && start->value == value) {
			Element *next = start->next;
			delete start;
			start = next;
		}
		Element *x = start, *prev = nullptr;
		while (x != nullptr) {
			Element *next = x->next;
			if (x->value == value) {
				if (prev != nullptr) prev->next = x->next;
				delete x;
			}
			else {
				prev = x;
			}
			x = next;
		}
	}
	void reverse() {
		if (empty() || start->next == nullptr) return;
		Element *x = start, *prev = nullptr, *next;
		while (x != nullptr) {
			next = x->next;
			x->next = prev;
			prev = x;
			x = next;
		}
		start = prev;
	}
	iterator begin() const {
		return (iterator){start};
	}
	iterator end() const {
		return nullptr;
	}
	T &operator[](size_t index) const {
		if (empty() || size() <= index) { throw "Index out of bounds"; }
		Element *x = walk(index);
		return x->value;
	}
};
#endif
