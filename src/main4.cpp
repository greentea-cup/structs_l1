#include <cstdio>
#include <cstdlib>

int process_str(char *str, std::size_t len, std::size_t cap);

// Лабораторная 2, №1
int main(void) {
	std::size_t str_capacity = 1;
	std::size_t len = 0;
	char *str = (char *)malloc(str_capacity * sizeof(*str));
	int last_char;
	while (len <= str_capacity) {
		last_char = std::getchar();
		if (last_char == EOF || last_char == '\n') {
			str[len] = '\0';
			break;
		}
		{
			size_t new_capacity = str_capacity+1;
			char *tmp = (char *)malloc(new_capacity * sizeof(*tmp));
			if (tmp == nullptr) {
				free(str);
				return EXIT_FAILURE;
			}
			for (size_t i = 0; i < len; i++) tmp[i] = str[i];
			free(str);
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
