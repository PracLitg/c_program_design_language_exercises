#ifndef QSORT_H
#define QSORT_H

void reverse(void* lineptr[], int left, int right);
void qsortStrings(void* lineptr[], int left, int right, int (*comp)(void*, void*));

#endif
