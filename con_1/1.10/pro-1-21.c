#include <stdio.h>

#define TAB 4

int main() {
	char c;
	int space_cnt = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (space_cnt == TAB - 1) {
				putchar('\t');
				space_cnt = 0;
			} else {
				space_cnt++;
			}
		} else {
			int i;
			for (i = 0; i < space_cnt; i++) {
				putchar(' ');
			}
			space_cnt = 0;
			putchar(c);
		}
	}
	return 0;
}

