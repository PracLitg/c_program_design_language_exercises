#include "qsort.h"

void swap(void** fir, void** sec) {
    char* temp;
    temp = *fir;
    *fir = *sec;
    *sec = temp;
}

void reverse(void* lineptr[], int left, int right) {
    while (left < right) {
        swap(&lineptr[left], &lineptr[right]);
        left++;
        right--;
    }
}

void qsortStrings(void* lineptr[], int left, int right, int (*comp)(void*, void*)) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;
    swap(&lineptr[left], &lineptr[mid]);
    int i, last;
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(lineptr[i], lineptr[left]) < 0)
            swap(&lineptr[i], &lineptr[++last]);
    swap(&lineptr[left], &lineptr[last]);
    qsortStrings(lineptr, left, last - 1, comp);
    qsortStrings(lineptr, last + 1, right, comp);
}
