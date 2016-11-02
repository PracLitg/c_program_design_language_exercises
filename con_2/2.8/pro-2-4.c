#include <stdio.h>

#define MAXLINE 50

void squeeze(char ori[], char tar[]) {
	int i, j, k;
	for (i = j = 0; ori[i] != '\0'; i++) {
		int exist = 0;
		for (k = 0; tar[k] != '\0'; k++) {
			if (ori[i] == tar[k]) {
				exist = 1;
				break;
			}
		}
		if (!exist)
			ori[j++] = ori[i];
	}
	ori[j] = '\0';
}	

int main() {
	char ori[MAXLINE];
	char tar[MAXLINE];
	scanf("%s%s", ori, tar);
	//printf("%s %s", ori, tar);
	squeeze(ori, tar);
	printf("%s\n", ori);
	return 0;
}

