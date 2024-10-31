#include <cstdio>
#include <cstdlib>

int process_str0(std::FILE *fs, char *str, std::size_t len, std::size_t cap);

// Лабораторная 2, №3
int main(int argc, char *argv[]) {
	if (argc < 3) {
		std::fprintf(stderr, "Specify temp file and output file\n");
		return EXIT_FAILURE;
	}
	std::size_t str_capacity = 5;
	std::size_t len = 0;
	char *str = (char *)calloc(str_capacity, sizeof(*str));
	int last_char;
	while(1) {
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
	std::FILE *fs = std::fopen(argv[1], "w");
	if (fs == nullptr) {
		std::fprintf(stderr, "Error creating temporary file '%s'\n", argv[1]);
		return EXIT_FAILURE;
	}
	std::fputs(str, fs);
	std::fclose(fs);
	free(str);
	fs = fopen(argv[1], "r");
	if (fs == nullptr) {
		std::fprintf(stderr, "Error reading temporary file '%s'\n", argv[1]);
		return EXIT_FAILURE;
	}
	len = 0, str_capacity = 1;
	str = (char *)calloc(str_capacity, sizeof(*str));
	while(!std::ferror(fs)) {
		last_char = std::fgetc(fs);
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
	std::fclose(fs);
	fs = fopen(argv[2], "w");
	if (fs == nullptr) {
		std::fprintf(stderr, "Error opening output file '%s'\n", argv[2]);
		std::fclose(fs);
		free(str);
		return EXIT_FAILURE;
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
	std::fprintf(fs, "Input: '%s'\n", str);
	int status = process_str0(fs, str, len, str_capacity);
	std::fclose(fs);
	free(str);
	return EXIT_SUCCESS;
}
