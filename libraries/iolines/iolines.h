/*
 * real=dlines: 读取输入,以换行符为界
 * params: array[] of pointer, int limit lines
 * return type: int of lines
 * note: 需要释放申请的空间
 *
 * writelines: 输出读取的内容
 * params: array[] of pointer, int limit lines
 * return type: void none
 */

#ifndef IOLINES_H
#define IOLINES_H

int getch();
void ungetch(int c);
int readlines(char* lineptr[], int nlines);
void writelines(char* lineptr[], int nlines);
void freeReadMemory(char* lineptr[], int nlines);

#endif
