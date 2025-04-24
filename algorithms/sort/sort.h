#ifndef SORT_INCLUDED
#define SORT_INCLUDED
#include <stddef.h>

struct sortable_array {
	void *data;
	size_t count;
	size_t data_size;
};

typedef int (*cmp_func)(const void *, const void *);
typedef void (*swap_func)(void *, void *);

extern void shell_sort(struct sortable_array array, cmp_func cmp,
		       swap_func swap);
extern void selection_sort(struct sortable_array array, cmp_func cmp,
			   swap_func swap);
extern void insertion_sort(struct sortable_array array, cmp_func cmp,
			   swap_func swap);

extern void merge_sort(struct sortable_array array, cmp_func cmp);

extern void quick_sort(struct sortable_array array, cmp_func cmp,
		       swap_func swap);
#endif
