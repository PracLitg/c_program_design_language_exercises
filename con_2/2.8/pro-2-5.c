#include <stdio.h>

#define MAXLINE 50

int any(char tar[], char ori[]) {
	int i, k;
	for (i = 0; tar[i] != '\0'; i++) {
		for (k = 0; ori[k] != '\0'; k++) {
			if (tar[i] == ori[k])
				return i;
		}
	}
	return -1;
}

int main() {
	char tar[MAXLINE];
	char ori[MAXLINE];
	scanf("%s%s", tar, ori);
	printf("%d\n", any(tar, ori));
	return 0;
}
