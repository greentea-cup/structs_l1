#include <iostream>
#include "OneList.hpp"
#include "task.hpp"

int one_main(void) {
	std::cout << std::boolalpha;
	OneList<int> whatever;
	std::cout << "Created one list.\nOne list empty?: " << whatever.empty() << "\n";
	std::cout << "One list size: " << whatever.size() << "\n";
	whatever.push_back(42);
	std::cout << "Put 42 in list.\nOne list empty?: " << whatever.empty() << "\n";
	std::cout << "One list size: " << whatever.size() << "\n";
	std::cout << "First element in list: " << whatever.front() << "\n";
	std::cout << "Last element in list: " << whatever.back() << "\n";
	std::cout << "First == last?: " << (whatever.front() == whatever.back()) << "\n";
	whatever.push_back(123);
	std::cout << "Put 123 in list.\nOne list empty?: " << whatever.empty() << "\n";
	std::cout << "One list size: " << whatever.size() << "\n";
	std::cout << "First element in list: " << whatever.front() << "\n";
	std::cout << "Last element in list: " << whatever.back() << "\n";
	OneList<int>::iterator iter = whatever.begin();
	std::cout << "Got iterator.\nFirst element is: " << *iter << "\n";
	++iter;
	std::cout << "Next element is: " << *iter << "\n";
	whatever.push_back(456);
	whatever.push_back(789);
	for (iter = whatever.begin(); iter != whatever.end(); ++iter)
		std::cout << *iter << " ";
	std::cout << '\n';
	return 0;
}

int main(void) {
	// return one_main();
	return task<OneList<char >> ();
}
