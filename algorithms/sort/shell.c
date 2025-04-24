#include "sort.h"
#include <string.h>

#if defined(__OPTIMIZE__) && defined(__LTO__)
__attribute__((always_inline)) inline
#endif
	void
	shell_sort(struct sortable_array array, cmp_func cmp, swap_func swap)
{
	int step = 1;
	int data_size = array.data_size;

	char *data = (char *)array.data;

	while (step < array.count / 3)
		step = 3 * step + 1; // 1, 4, 13, 40, ...

	while (step >= 1) {
		for (int i = step; i < array.count; i++) {
			for (int j = i; j >= step; j -= step) {
				char *d1 = &data[j * data_size];
				char *d2 = &data[(j - step) * data_size];
				if (cmp(d1, d2))
					break;
				swap(d1, d2);
			}
		}
		step = step / 3;
	}
}
/*
         1  3  2  4  6  9  8  -1  -2  3  i=4, j=4, j-=h
4-sort:
        [6] 3  2  4 [1] 9  8  -1  -2  3
         6 [9] 2  4  1 [3] 8  -1  -2  3
         6  9 [8] 4  1  3 [2] -1  -2  3
         -
1-sort:


*/
