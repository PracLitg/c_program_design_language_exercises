#include <stdio.h>

int main() {
	int c;
	while ((c = getchar()) != EOF) {
		if (c == '/') {
			c = getchar();
			if (c == '/') {
				while ((c = getchar()) != '\n')
					;
				putchar(c);
			} else if (c == '*') {
				while (c = getchar()) {
					if (c == '*') {
						c = getchar();
						if (c == '/') {
							putchar('\n');
							break;
						}
					}
				}
			}
		} else {
			putchar(c);
		}
	}
	return 0;
}
