
#include "sort.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// icx -o build/t_shell algorithms/sort/shell.c test/algorithms/sort/t_shell.c -I./algorithms/sort/ -flto -O3 ; ./build/t_shell

void print_arr(int *arr, int len)
{
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

#if defined(__OPTIMIZE__) && defined(__LTO__)
__attribute__((always_inline)) inline
#endif
int comp(const void *d1, const void *d2)
{
	int *x = (int *)d1;
	int *y = (int *)d2;
	if (*x > *y)
		return 1;
	else
		return 0;
}

#if defined(__OPTIMIZE__) && defined(__LTO__)
__attribute__((always_inline)) inline
#endif
void swap(void *d1, void *d2)
{
	int *x = (int *)d1;
	int *y = (int *)d2;
	*x = *x ^ *y;
	*y = *y ^ *x;
	*x = *y ^ *x;
}

int check_avx_support() {
    uint32_t eax, ebx, ecx, edx;

    // 执行 CPUID 指令，传入 0x00000001 查询 CPU 的功能标志
    __asm__ __volatile__(
        "cpuid"
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(0x1)  // CPUID 功能标志 0x1 用于获取处理器的功能
    );

    // 检查 AVX 支持
    if (ecx & (1 << 28)) {
        return 1;  // CPU 支持 AVX
    }

    return 0;  // 不支持 AVX
}

void check_sorted(int *arr, int cnt) {
	int k = arr[0] > arr[1];
	for (size_t i = 0; i < cnt - 1; i++)
	{
		if (!(arr[i] <= arr[i + 1]))
		{
			printf("error: %d=>%d, %d=>%d!\n", i, i + 1, arr[i], arr[i+1]);
			return;
		}
	}
	printf("The array is sorted!\n");
}

// gcc -o ouput/shell shell.c ; ./ouput/shell
int main()
{
	srand(time(NULL));
	clock_t start, end;
	double cpu_time_used;

	int cnt = 100000000;
	int *arr = (int *)malloc(sizeof(int) * cnt);

    // 生成并存储 cnt 个随机整数
    for (int i = 0; i < cnt; i++) {
        arr[i] = rand();  // 使用 rand() 生成一个随机数
    }

	print_arr(arr, cnt > 15 ? 15 : cnt);
	struct sortable_array array = { .count = cnt,
					.data = arr,
					.data_size = 4 };
	start = clock(); // 记录开始时间
	qsort(array.data, array.count, array.data_size, comp);
	// quick_sort(array, comp, swap);
	end = clock(); // 记录结束时间
	cpu_time_used =
		((double)(end - start)) / CLOCKS_PER_SEC; // 计算时间差（秒）

	printf("执行时间: %.6f 秒\n", cpu_time_used);

	start = clock(); // 记录开始时间
	// qsort(array.data, array.count, array.data_size, comp);
	end = clock(); // 记录结束时间
	cpu_time_used =
		((double)(end - start)) / CLOCKS_PER_SEC; // 计算时间差（秒）

	printf("执行时间: %.6f 秒\n", cpu_time_used);
	// printf("%d \n", check_avx_support());
	print_arr(arr, cnt > 15 ? 15 : cnt);
	check_sorted(arr, cnt);
    free(arr);
}




