#include <stdio.h>
#include "shell.h"
#include "gaps.h"

void shell_sort(Stats *stats, uint32_t *arr, uint32_t length) {
	int g;
	for (g = 0; g <= GAPS; ++g) {
		int i;
        	for (i = g; i <= length; ++i) {
			uint32_t j = i;
			uint32_t temp = arr[i];
			while(j >= gaps[g] && temp < arr[j - gaps[g]]) {
				arr[j] = arr[j - gaps[g]];
				j -= gaps[g];
			}
			arr[j] = temp;
		}	
	}
	
}

