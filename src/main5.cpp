#include <cstdio>
#include <cstdlib>

int process_str(char *str, std::size_t len, std::size_t cap);

// Лабораторная 2, №2
int main(void) {
	std::size_t str_capacity = 5;
	std::size_t len = 0;
	char *str = (char *)calloc(str_capacity, sizeof(*str));
	int last_char;
	while (1) {
		last_char = std::getchar();
		if (last_char == EOF || last_char == '\n') {
			str[len] = '\0';
			break;
		}
		if (len + 1 == str_capacity) {
			size_t new_capacity = str_capacity+5;
			char *tmp = (char *)realloc(str, new_capacity * sizeof(*tmp));
			if (tmp == nullptr) {
				free(str);
				return EXIT_FAILURE;
			}
			str = tmp;
			str_capacity = new_capacity;
		}
		str[len++] = last_char;
	}
	{
		std::size_t new_capacity = str_capacity * 2;
		char *tmp = (char *)realloc(str, new_capacity * sizeof(*tmp));
		if (tmp == nullptr) {
			free(str);
			return EXIT_FAILURE;
		}
		str_capacity = new_capacity;
	}
	std::printf("Input: '%.*s'\n", (int)len, str);
	return process_str(str, len, str_capacity);
}
