#include <cstdio>
#include <cstdlib>

static int fail(void) {
	std::fprintf(stderr, "Cannot process string: result does not fit in buffer\n");
	return EXIT_FAILURE;
}

static bool isdigit(char c) {
	return c >= '0' && c <= '9';
}

int process_str0(std::FILE *fs, char *str, std::size_t len, std::size_t cap) {
	bool reverse = len % 2 == 0;

	for (std::size_t i = 0; i < len; i++) {
		if (!isdigit(str[i])) continue;
		std::size_t j = i;
	std:
		;
		size_t added = 0;
		for (; j < len && isdigit(str[j]); j++);
		for (std::size_t x = i, y = j; x < cap && y < len; x++, y++)
			str[x] = str[y];
		len -= j - i;
	}
	std::fprintf(fs, "Output 1: '%.*s'\n", (int)len, str);

	for (std::size_t i = 0; i < len; i++) {
		if (str[i] == '+' || str[i] == '-') {
			if (++len >= cap) return fail();
			for (std::size_t j = len - 1; j > i; j--)
				str[j] = str[j - 1];
			i++;
		}
	}
	std::fprintf(fs, "Output 2: '%.*s'\n", (int)len, str);

	if (reverse) {
		for (std::size_t i = 0, j = len / 2; i < j; i++) {
			char c = str[i];
			str[i] = str[len - 1 - i];
			str[len - 1 - i] = c;
		}
	}
	std::fprintf(fs, "Output 3: '%.*s'\n", (int)len, str);
	return EXIT_SUCCESS;
}

int process_str(char *str, std::size_t len, std::size_t cap) {
	return process_str0(stdout, str, len, cap);
}
