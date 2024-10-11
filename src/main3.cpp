#include <cstdio>
#include <cstdlib>

int process_str(char *str, std::size_t len, std::size_t cap);

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::fprintf(stderr, "Specify input file\n");
		return EXIT_FAILURE;
	}
	std::size_t const str_capacity = 256;
	char str[str_capacity];
	std::FILE *fs = fopen(argv[1], "r");
	if (fs == nullptr) {
		std::fprintf(stderr, "Error opening file '%s'\n", argv[1]);
		return EXIT_FAILURE;
	}
	std::fgets(str, (int)str_capacity, fs);
	if (std::ferror(fs)) {
		std::fprintf(stderr, "Error reading file '%s'\n", argv[1]);
		fclose(fs);
		return EXIT_FAILURE;
	}
	std::fclose(fs);
	std::size_t i = 0;
	for (; i < str_capacity; i++) {
		if (str[i] == '\n') {
			str[i] = '\0';
			break;
		}
	}
	std::printf("Input: '%s'\n", str);
	return process_str(str, i, str_capacity);
}
