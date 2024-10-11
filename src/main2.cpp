#include <iostream>
#include <cstdlib>

int process_str(char *str, std::size_t len, std::size_t cap);

int main(void) {
	std::size_t const str_capacity = 256;
	char str[str_capacity];
	std::cin.getline(str, str_capacity);
	std::cout << "Input: '" << str << "'\n";
	std::size_t len = 0;
	while (len < str_capacity && str[len] != '\0') len++;
	return process_str(str, len, str_capacity);
}
