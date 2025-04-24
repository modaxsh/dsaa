#include "sort.h"

#if defined(__OPTIMIZE__) && defined(__LTO__)
__attribute__((always_inline)) inline
#endif
	void
	insertion_sort(struct sortable_array array, cmp_func cmp,
		       swap_func swap)
{
    char *data = (char *)array.data;
    int data_size = array.data_size;

	for (size_t i = 1; i < array.count; i++) {
		for (size_t j = i; j > 0; j--) {
            char *d1 = &data[j * data_size];
            char *d2 = &data[(j - 1) * data_size];
            
			if (cmp(d1, d2))
				break;
            swap(d1, d2);
		}
	}
}