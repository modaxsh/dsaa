#include "sort.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

static int _partition(struct sortable_array array, int left, int right,
		      cmp_func cmp, swap_func swap)
{
	char *data = (char *)array.data;
	size_t data_size = array.data_size;

	char *pivot = malloc(data_size);
	memcpy(pivot, &data[left * data_size], data_size); // pivot = data[left]

	int i = left - 1;
	int j = right + 1;

	while (1) {
		do {
			i++;
		} while (cmp(pivot,
			     &data[i * data_size])); // while pivot > data[i]

		do {
			j--;
		} while (cmp(&data[j * data_size],
			     pivot)); // while data[j] > pivot

		if (i >= j) {
			free(pivot);
			return j;
		}
		swap(&data[i * data_size], &data[j * data_size]);
	}
}

static void _quick_sort(struct sortable_array array, int left, int right,
			cmp_func cmp, swap_func swap)
{
	if (right - left > 15) {
		int j = _partition(array, left, right, cmp, swap);
		_quick_sort(array, left, j, cmp, swap); // 注意是 j
		_quick_sort(array, j + 1, right, cmp, swap); // 不是 j+2
	} else if (right - left > 0) {
		char *data = (char *)array.data;

		struct sortable_array tmp = {
			.data_size = array.data_size,
			.data = &data[left * array.data_size],
			.count = right - left + 1
		};
		insertion_sort(tmp, cmp, swap);
	}
}

#if defined(__OPTIMIZE__) && defined(__LTO__)
__attribute__((always_inline)) inline
#endif
	void
	quick_sort(struct sortable_array array, cmp_func cmp, swap_func swap)
{
	_quick_sort(array, 0, array.count - 1, cmp, swap);
}