#include <cstdio>
#include <cstdlib>

int process_str(char *str, std::size_t len, std::size_t cap);

// 1 способ хранения строки:
// Строка как массив символов
int main(void) {
	std::size_t const str_capacity = 256;
	std::size_t len = 0;
	char str[str_capacity];
	int last_char;
	while (len <= str_capacity) {
		last_char = std::getchar();
		if (last_char == EOF || last_char == '\n') break;
		str[len++] = last_char;
		if (len == str_capacity) break;
	}
	std::printf("Input: '%.*s'\n", (int)len, str);
	return process_str(str, len, str_capacity);
}
