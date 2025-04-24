#include "sort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void _conquer(struct sortable_array array, int left, int mid, int right,
		    char *temp, cmp_func cmp)
{
	char *data = (char *)array.data;
	size_t data_size = array.data_size;

	int i = left;
	int j = mid + 1;
	int index = 0;
	while (i <= mid && j <= right) {
		char *di = &data[i * data_size];
		char *dj = &data[j * data_size];
		if (!cmp(di, dj)) {
			memcpy(&temp[index * data_size], di, data_size);
			index++, i++;
		} else {
			memcpy(&temp[index * data_size], dj, data_size);
			index++, j++;
		}
	}

	if (i <= mid) {
		size_t total = mid - i + 1;
		memcpy(&temp[index * data_size], &data[i * data_size],
		       total * data_size);
	}

	if (j <= right) {
		size_t total = right - j + 1;
		memcpy(&temp[index * data_size], &data[j * data_size],
		       total * data_size);
	}

	if (left <= right) {
		size_t total = right - left + 1;
		int *arr = (int *)temp;
		memcpy(&data[left * data_size], temp, total * data_size);
	}
}

static void _divide(struct sortable_array array, int left, int right, char *temp,
		   cmp_func cmp)
{
	if (left < right) {
		int mid = left + (right - left) / 2;
		_divide(array, left, mid, temp, cmp);
		_divide(array, mid + 1, right, temp, cmp);
		_conquer(array, left, mid, right, temp, cmp);
	}
}

#if defined(__OPTIMIZE__) && defined(__LTO__)
__attribute__((always_inline)) inline
#endif
	void
	merge_sort(struct sortable_array array, cmp_func cmp)
{
	size_t cnt = array.count;
	int data_size = array.data_size;

	char *temp = (char *)malloc(cnt * data_size);

	_divide(array, 0, cnt - 1, temp, cmp);

	free(temp);
}