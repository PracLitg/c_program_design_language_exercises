#include <stdio.h>

void test() {
	int c;
	c = getchar();
	putchar(c);
	c = getchar();
	putchar(c);
	putchar('\n');
}

int main() {
	int c;
	while ((c = getchar()) != EOF) {
		if (c == '"') {
			test();
		}
		putchar(c);
	}
	putchar('\n');
	return 0;
}
