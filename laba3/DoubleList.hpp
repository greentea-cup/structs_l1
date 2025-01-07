#ifndef DOUBLE_LIST_HPP
#define DOUBLE_LIST_HPP
#include <iterator>

template<typename T>
struct DoubleList {
public:
	DoubleList() : start(nullptr) {}
	struct Element {
		T value;
		Element *next;
		Element *prev;
		void insert_after(T value) {
			Element *x = new Element();
			x->value = value;
			x->prev = this;
			x->next = next;
			if (next != nullptr) next->prev = x;
			next = x;
		}
		void insert_before(T value) {
			Element *x = new Element();
			x->value = value;
			x->next = this;
			x->prev = prev;
			if (prev != nullptr) prev->next = x;
			prev = x;
		}
	} *start;
	struct iterator {
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = void;
		using value_type = T;
		using pointer = T *;
		using reference = T &;

		Element *current;
		iterator(Element *start) : current(start) {}
		bool empty() {
			return current == nullptr;
		}
		bool operator==(iterator other) { return current == other.current; }
		bool operator!=(iterator other) { return current != other.current; }
		T operator*() {
			if (empty()) { throw "Cannot dereference empty iterator"; }
			return current->value;
		}
		iterator &operator++() {
			if (empty()) { throw "Cannot iterate over empty list"; }
			current = current->next;
			return *this;
		}
		iterator &operator--() {
			if (empty()) { throw "Cannot iterate over empty list"; }
			current = current->prev;
			return *this;
		}
		void insert_after(T value) {
			if (empty()) { throw "Cannot insert into empty iterator"; }
			current->insert_after(value);
		}
		void insert_before(T value) {
			if (empty()) { throw "Cannot insert into empty iterator"; }
			current->insert_before(value);
		}
	};
	Element *last_element() {
		Element *x = start;
		while (x != nullptr && x->next != nullptr) x = x->next;
		return x;
	}
	Element *prelast_element() {
		Element *x = start;
		while (x != nullptr && x-> next != nullptr && x->next->next != nullptr) x = x->next;
		return x;
	}
	Element *walk(size_t i) {
		Element *x = start;
		while (x != nullptr && x->next != nullptr && i--) x = x->next;
		return x;
	}
	size_t size() {
		// todo: from current to first + from current to last
		Element *x = start;
		size_t size = 0;
		while (x != nullptr) x = x->next, size++;
		return size;
	}
	bool empty() {
		return start == nullptr;
	}
	T &front() {
		return start->value;
	}
	T &back() {
		return last_element()->value;
	}
	void push_front(T value) {
		Element *x = new Element();
		x->value = value;
		x->prev = nullptr;
		x->next = start;
		if (start != nullptr) start->prev = x;
		start = x;
	}
	void push_back(T value) {
		Element *x = new Element();
		x->value = value;
		x->next = nullptr;
		if (empty()) {
			x->prev = nullptr;
			start = x;
			return;
		}
		Element *last = last_element();
		last->next = x;
		x->prev = last;
	}
	void insert(size_t i, T value) {
		if (empty()) {
			push_back(value);
			return;
		}
		Element *before = walk(i);
		before->insert_after(value);
	}
	/*
	Pop from empty list is forbidden
	*/
	T pop_front() {
		if (empty()) { throw "Cannot get value from empty list"; }
		Element *x = start;
		start = x->next;
		start->prev = nullptr;
		T value = x->value;
		delete x;
		return value;
	}
	/*
	Pop from empty list is forbidden
	*/
	T pop_back() {
		if (empty()) { throw "Cannot get value from empty list"; }
		if (start->next == nullptr) {
			Element *last = start;
			start = nullptr;
			T value = last->value;
			delete last;
			return value;
		}
		Element *x = prelast_element();
		Element *last = x->next;
		x->next == nullptr;
		T value = last->value;
		delete last;
		return value;
	}
	void remove(T value) {
		if (empty()) return;
		while (start && start->value == value) {
			Element *next = start->next;
			next->prev = nullptr;
			delete start;
			start = next;
		}
		Element *x = start;
		while (x != nullptr) {
			Element *next = x->next, *prev = x->prev;
			if (x->value == value) {
				prev->next = x->next;
				next->prev = x->prev;
				delete x;
			}
			x = next;
		}
	}
	void reverse() {
		if (empty() || start->next == nullptr) return;
		Element *x = start, *prev = nullptr;
		while (x != nullptr) {
			prev = x->prev;
			x->prev = x->next;
			x->next = prev;
			x = x->prev;
		}
		if (prev != nullptr) start = prev->prev;
	}
	iterator begin() {
		return (iterator){start};
	}
	iterator end() {
		return nullptr;
	}
	T operator[](size_t index) {
		if (empty() || size() <= index) { throw "Index out of bounds"; }
		Element *x = walk(index);
		return x->value;
	}
};
#endif
