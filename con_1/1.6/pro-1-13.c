#include <stdio.h>
#include <string.h>

void vertical_dist(int* dist, int size) {
	int tmp[size];
	int i, j;
	for (i = 0; i < size; i++) {
		tmp[i] = *(dist + i);
	}
	for (int i = 10; i > 0; i--) {
		for (int j = 1; j < size; j++) {
			if (tmp[j] == i) {
				printf("*");
				tmp[j]--;
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}
}
			

void horizon_dist(int* dist, int size) {
	int i, j;
	for (i = 1; i < size; i++) {
		printf("Len %3d:", i);
        for (j = 0; j < *(dist + i); j++) {
			printf("*");
		}
		printf("\n");
	}
}

int main() {
	int c, word_len = 0;
	int length[11];
	memset(length, 0, sizeof(length));
	while ((c = getchar()) != EOF) {
		if (c != ' ' && c != '\n' && c != '\t') {
			word_len++;
			//putchar(c);
		} else {
			length[word_len]++;
			word_len = 0;
		}
	}
	//horizon_dist(length, 11);
	vertical_dist(length, 11);
	return 0;
}
