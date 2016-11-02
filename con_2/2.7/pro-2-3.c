#include <stdio.h>

#define MAX 100
#define MIN_NUM 0x10000000

int htoi(char str[], int size) {
	//printf("%d\n", size);
	if (str[0] != '0' || str[1] != 'x') {
		printf("Format Error\n");
		return MIN_NUM;
	}
	int i;
	int res = 0;
	for (i = 2; i < size; i++) {
		int num;
		if (str[i] >= 'a' && str[i] <= 'f')
			num = str[i] - 'a' + 10;
		else
			num = str[i] - '0';
		//printf("%d\n", num);
		res = res * 16 + num;
	}
	return res;
}

int main() {
	int c;
	int is_hex = 0;
	int cnt = 0;
	char str[MAX];
	while ((c = getchar()) != EOF) {
		if (c != '\n') {
			if (c >= 'A' && c <= 'Z')
				c = c + 'a' - 'A';
			str[cnt++] = c;
		} else {
			str[cnt] = '\0';
			//printf("%s\n", str);
			printf("Hex->Dec: %d\n", htoi(str, cnt));
			cnt = 0;
		}
	}
	return 0;
}

