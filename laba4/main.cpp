#include <cstdlib>
#include <utility>
#include <iostream>

void bubble_sort(int *array, size_t len) {
	if (array == nullptr || len < 2) return;
	for (std::size_t i = 0; i < len; i++) {
		for (std::size_t j = 1; j < len; j++) {
			if (array[j - 1] > array[j]) std::swap(array[j - 1], array[j]);
		}
	}
}

void shaker_sort(int *array, size_t len) {
	if (array == nullptr || len < 2) return;
	for (std::size_t l = 0, r = len; l < r;) {
		bool changed = false;
		for (size_t i = l; i < r - 1; i++) {
			if (array[i + 1] < array[i]) {
				std::swap(array[i + 1], array[i]);
				changed = true;
			}
		}
		r--;
		if (!changed) break;
		changed = false;
		for (size_t i = r - 1; i > l; i--) {
			if (array[i] < array[i - 1]) {
				std::swap(array[i - 1], array[i]);
				changed = true;
			}
		}
		l++;
		if (!changed) break;
	}
}

void comb_sort(int *array, size_t len) {
	double shrink = 1.3;
	size_t gap = (size_t)(len / shrink);
	while (gap > 1) {
		for (size_t i = gap; i < len; i++) {
			if (array[i - gap] > array[i])
				std::swap(array[i - gap], array[i]);
		}
		gap = (size_t)(gap / shrink);
	}
	bool swapped = true;
	while (swapped) {
		swapped = false;
		for (size_t i = 1; i < len; i++) {
			if (array[i - 1] > array[i]) {
				std::swap(array[i - 1], array[i]);
				swapped = true;
			}
		}
	}
}

void insertion_sort(int *array, size_t len) {
	if (array == nullptr || len < 2) return;
	for (size_t i = 1; i < len; i++) {
		if (array[i - 1] < array[i]) continue;
		size_t j = i, k = i;
		while (k > 0 && array[j] < array[k - 1]) {
			std::swap(array[j], array[k - 1]);
			k--, j = k;
		}
	}
}
// temp has same len as array
void merge_sort(int *array, int *temp, size_t len) {
	if (array == nullptr || temp == nullptr || len < 2) return;
	if (len == 2 && array[0] > array[1]) {
		std::swap(array[0], array[1]);
		return;
	}
	size_t len1 = len / 2, len2 = len1 + len % 2;
	merge_sort(array, temp, len1);
	merge_sort(array + len1, temp + len1, len2);

	size_t i = 0, j = len1, k = 0;
	while (i < len1 && j < len) {
		if (array[i] > array[j]) temp[k++] = array[j++];
		else temp[k++] = array[i++];
	}
	while (i < len1) temp[k++] = array[i++];
	while (j < len) temp[k++] = array[j++];
	for (k = 0; k < len; k++) array[k] = temp[k];
}

void selection_sort(int *array, size_t len) {
	if (array == nullptr || len < 2) return;
	for (std::size_t i = 0; i < len; i++) {
		std::size_t minj = i;
		for (std::size_t j = i; j < len; j++) {
			if (array[j] < array[minj]) minj = j;
		}
		if (minj != i) std::swap(array[i], array[minj]);
	}
}

// expected temp to have len at least (max-min)
void counting_sort(int *array, size_t *temp, size_t len, size_t temp_len) {
	if (array == nullptr || len < 2) return;
	int min = array[0], max = array[0];
	for (size_t i = 1; i < len; i++) {
		if (array[i] < min) min = array[i];
		if (array[i] > max) max = array[i];
	}
	if (temp_len < max - min + 1) return;
	for (size_t i = 0; i < temp_len; i++) temp[i] = 0;
	for (size_t i = 0; i < len; i++)
		temp[array[i] - min]++;
	for (size_t q = 0; q < temp_len; q++) std::cout << temp[q] << ' ';
	std::cout << '\n';
	int v = min;
	for (size_t j = 0; v <= max && j < len; v++) {
		while (j < len && temp[v - min] > 0) {
			array[j++] = v;
			temp[v - min]--;
		}
	}
}

int comparator(void const *l, void const *r) {
	int a = *(int const *)l, b = *(int const *)r;
	return (a > b) - (a < b);
}

void quick_sort(int *array, size_t len) {
	qsort(array, len, sizeof(int), comparator);
}

size_t quick_sort_partition(int *array, size_t start, size_t end) {
	int pivot = array[start];
	size_t i = start - 1;
	size_t j = end + 1;
	while (1) {
		do i++;
		while (array[i] < pivot);
		do j--;
		while (array[j] > pivot);
		if (i < j) std::swap(array[i], array[j]);
		else return j;
	}
}

void quicksort0(int *array, size_t start, size_t end) {
	if (start >= end) return;
	size_t p = quick_sort_partition(array, start, end);
	quicksort0(array, start, p);
	quicksort0(array, p + 1, end);
}

void real_quick_sort(int *array, size_t len) {
	if (array == nullptr || len < 2) return;
	quicksort0(array, 0, len - 1);
}

void heap_sort_makeheap(int *array, size_t len, size_t index) {
	if (array == nullptr || len < 2 || index >= len) return;
	size_t maxi = index;
	size_t left = 2 * index + 1, right = 2 * index + 2;
	if (left < len && array[left] > array[maxi]) maxi = left;
	if (right < len && array[right] > array[maxi]) maxi = right;
	if (maxi != index) {
		std::swap(array[index], array[maxi]);
		heap_sort_makeheap(array, len, maxi);
	}
}

void heap_sort(int *array, size_t len) {
	if (array == nullptr || len < 2) return;
	for (size_t i = len / 2 - 1; i > 0; i--)
		heap_sort_makeheap(array, len, i);
	heap_sort_makeheap(array, len, 0);
	for (size_t i = len - 1; i > 0; i--) {
		std::swap(array[0], array[i]);
		heap_sort_makeheap(array, i, 0);
	}
}

ssize_t binary_search(int const *array, size_t len, int value) {
	if (array == nullptr || len < 2) return -1;
	size_t left = 0, right = len - 1;
	while (left <= right) {
		size_t mid = left + (right - left) / 2;
		if (array[mid] == value) return (ssize_t)mid;
		else if (array[mid] < value) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}

typedef struct Node {
	int value;
	struct Node *left;
	struct Node *right;
} Node;

#ifndef BFS_MAX_STACK_SIZE
#define BFS_MAX_STACK_SIZE 256
#endif
Node const *bfs(Node const *start, int value) {
	if (start == nullptr) return nullptr;
	size_t const qcap = BFS_MAX_STACK_SIZE;
	Node const *temp[qcap] = {start};
	size_t qfront = 0, qback = 1;
	while (qback > qfront) {
		Node const *x = temp[qfront++ % qcap];
		if (x == nullptr) continue;
		if (x->value == value) return x;
		if (x->left != nullptr) temp[qback++ % qcap] = x->left;
		if (x->right != nullptr) temp[qback++ % qcap] = x->right;
	}
	return nullptr;
}

Node const *dfs(Node const *start, size_t max_depth, int value) {
	if (start == nullptr || max_depth == 0) return nullptr;
	if (start->value == value) return start;
	Node const *res;
	res = dfs(start->left, max_depth - 1, value);
	if (res == nullptr)
		res = dfs(start->right, max_depth - 1, value);
	return res;
}

int merge_main(void) {
	size_t const len = 10;
	int data[len] = {5, 1, 3, 4, 0, 9, 8, 7, 6, 2};
	int temp[len];
	merge_sort(data, temp, len);
	for (size_t i = 0; i < len; i++) std::cout << data[i] << ' ';
	std::cout << '\n';
	return 0;
}

int comb_main(void) {
	size_t const len = 10;
	int data[len] = {5, 1, 3, 4, 0, 9, 8, 7, 6, 2};
	comb_sort(data, len);
	for (size_t i = 0; i < len; i++) std::cout << data[i] << ' ';
	std::cout << '\n';
	return 0;
}

int counting_main(void) {
	size_t const len = 50, temp_len = 21; // [-10:+10]
	int data[len] = {6, 5, 5, -2, -2, 7, 5, 2, -7, 3, 0, 4, 9, 2, -8, 0, 0, -7, 9, 9, -5, 10, 0, -5, 5, -7, 5, 5, 3, -7, -3, 0, -10, -2, -8, 8, 9, -1, 5, -6, -8, -5, 9, 2, 8, -2, -4, -10, -9, 9};
	size_t temp[temp_len];
	counting_sort(data, temp, len, temp_len);
	for (size_t i = 0; i < len; i++) std::cout << data[i] << ' ';
	std::cout << '\n';
	return 0;
}

int heap_main(void) {
	size_t const len = 10;
	int data[len] = {5, 1, 3, 4, 0, 9, 8, 7, 6, 2};
	heap_sort(data, len);
	for (size_t i = 0; i < len; i++) std::cout << data[i] << ' ';
	std::cout << '\n';
	return 0;
}

int binary_search_main(void) {
	size_t const len = 10;
	int data[len] = {0, 1, 5, 6, 8, 13, 17, 18, 20, 22};
	ssize_t i = binary_search(data, len, 20);
	ssize_t j = binary_search(data, len, 1);
	ssize_t k = binary_search(data, len, 40);
	ssize_t l = binary_search(data, len, 11);
	for (size_t i = 0; i < len; i++) std::cout << data[i] << ' ';
	std::cout << '\n' << i << ' ' << j << ' ' << k << ' ' << l << '\n';
	return 0;
}

int dfs_main(void) {
	Node data[10] = {{0}, {1}, {5}, {6}, {8}, {13}, {17}, {18}, {20}, {22}};
	data[0].left = &data[1];
	data[0].right = &data[2];
	data[1].left = &data[3];
	data[1].right = &data[4];
	data[2].left = &data[5];
	data[2].right = &data[6];
	data[3].left = &data[7];
	data[3].right = &data[8];
	data[4].left = &data[9];
	Node const *x = dfs(&data[0], 4, 18);
	std::cout << std::boolalpha;
	std::cout << "x == nullptr?: " << (x == nullptr) << '\n';
	if (x == nullptr) return 1;
	std::cout << "x = " << x->value << '\n';
	std::cout << "x is data[7]?: " << (x == &data[7]) << '\n';
	return 0;
}

int bfs_main(void) {
	Node data[10] = {{0}, {1}, {5}, {6}, {8}, {13}, {17}, {18}, {20}, {22}};
	data[0].left = &data[1];
	data[0].right = &data[2];
	data[1].left = &data[3];
	data[1].right = &data[4];
	data[2].left = &data[5];
	data[2].right = &data[6];
	data[3].left = &data[7];
	data[3].right = &data[8];
	data[4].left = &data[9];
	Node const *x = bfs(&data[0], 18);
	std::cout << std::boolalpha;
	std::cout << "x == nullptr?: " << (x == nullptr) << '\n';
	if (x == nullptr) return 1;
	std::cout << "x = " << x->value << '\n';
	std::cout << "x is data[7]?: " << (x == &data[7]) << '\n';
	return 0;
}

int main(void) {
	// return counting_main();
	// return binary_search_main();
	// return heap_main();
	// return bfs_main();
	return 0;
}
