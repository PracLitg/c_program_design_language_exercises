#include <stdio.h>

#define MAXLINE 1000

int myGetline(char line[], int maxline);
int rmSpacesOfEnd(char to[], char from[], int length);

int main() {
	int len;
	char line[MAXLINE];
	char modified[MAXLINE];

	while ((len = myGetline(line, MAXLINE)) > 0) {
		int res = rmSpacesOfEnd(modified, line, len);
		printf("%s %d\n", modified, res);
	}
	return 0;
}

int myGetline(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		s[i] = c;
	}
	s[i] = '\0';
	return i;
}

int rmSpacesOfEnd(char to[], char from[], int length) {
	int i = length - 1;
	while (from[i] == ' ' || from[i] == '\t')
		i--;
	int j = 0;
	while ((to[j] = from[j]) && j <= i)
		j++;
	to[j] = '\0';
	return j;
}
