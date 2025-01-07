#include <iostream>
#include "DoubleList.hpp"
#include "task.hpp"

int double_main(void) {
	std::cout << std::boolalpha;
	DoubleList<int> whatever;
	std::cout << "Created double list.\nDouble list empty?: " << whatever.empty() << "\n";
	std::cout << "Double list size: " << whatever.size() << "\n";
	whatever.push_back(42);
	std::cout << "Put 42 in list.\nDouble list empty?: " << whatever.empty() << "\n";
	std::cout << "Double list size: " << whatever.size() << "\n";
	std::cout << "First element in list: " << whatever.front() << "\n";
	std::cout << "Last element in list: " << whatever.back() << "\n";
	std::cout << "First == last?: " << (whatever.front() == whatever.back()) << "\n";
	whatever.push_back(123);
	std::cout << "Put 123 in list.\nDouble list empty?: " << whatever.empty() << "\n";
	std::cout << "Double list size: " << whatever.size() << "\n";
	std::cout << "First element in list: " << whatever.front() << "\n";
	std::cout << "Last element in list: " << whatever.back() << "\n";
	DoubleList<int>::iterator iter = whatever.begin();
	std::cout << "Got iterator.\nFirst element is: " << *iter << "\n";
	++iter;
	std::cout << "Next element is: " << *iter << "\n";
	--iter;
	std::cout << "First element again is: " << *iter << "\n";
	return 0;
}

int main(void) {
	// return double_main();
	return task<DoubleList<char>>();
}
