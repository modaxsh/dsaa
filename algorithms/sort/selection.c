#include "sort.h"

#if defined(__OPTIMIZE__) && defined(__LTO__)
__attribute__((always_inline)) inline
#endif
	void
	selection_sort(struct sortable_array array, cmp_func cmp,
		       swap_func swap)
{
	char *data = (char *)array.data;
    int data_size = array.data_size;

	for (size_t i = 0; i < array.count; i++) {
		for (size_t j = i + 1; j < array.count; j++) {
            char *d1 = &data[i * data_size];
            char *d2 = &data[j * data_size];

			if (cmp(d1, d2))
				swap(d1, d2);
		}
	}
}
