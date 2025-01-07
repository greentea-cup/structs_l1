#ifndef TASK_HPP
#define TASK_HPP
#include <cstdio>
#include <cstdlib>
#include <iostream>

template<typename T>
void list_process_str(std::FILE *fs, T &str) {
	if (str.empty()) return;
	bool reverse = str.size() % 2 == 0;
	for (char i = '0'; i <= '9'; i++) str.remove(i);
	for (auto it = str.begin(); !it.empty(); ++it) {
		char c = *it;
		if (c == '+' || c == '-') {
			it.insert_after(c);
			++it;
		}
	}
	if (reverse) str.reverse();
}

template<typename T>
int task(void) {
	T str;
	char c;
	while ((c = getc(stdin)) != EOF && c != '\n' && c != '\0')
		str.push_back(c);
	for (auto it = str.begin(); it != str.end(); ++it) std::cout << *it;
	std::cout << '\n';
	list_process_str(stdout, str);
	for (auto it = str.begin(); it != str.end(); ++it) std::cout << *it;
	std::cout << '\n';
	return EXIT_SUCCESS;
}
#endif
