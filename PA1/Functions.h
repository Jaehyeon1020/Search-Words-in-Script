#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define BUF_SIZE 1024

void findSingleWord(int fd, char * userInput); // function 1
void findMultiWord(int fd, char * userInput); // function 2
void findPhrase(int fd, char * userInput); // function 3
void findRegularExpression(int fd, char * userInput); // function 4

int stringCompare(char * str1, char * str2);
void enterToNull(char * str);
int isBlankInString(char * str);
int isStarInString(char * str);
int getFirstEnterIndex(char * str);
int compareFromIndex(int checkingIndex, char * userInput, char * buffer);
int compareCaseFromIndex(int checkingIndex, char * userInput, char * buffer); // 대소문자 구분 없이 비교
void printNumber(int num);
void tokenizeString(char * userInput, char ** input1, char ** input2);
void tokenizeStringByStar(char * userInput, char ** input1, char ** input2);
void deleteQuotation(char * userInput);
int isExistRegularExpression(int checkingIndex, char * userInput_1, char * userInput_2, char * buffer);
int compareCaseFromIndex_ReturnIndex(int checkingIndex, char * userInput, char * buffer);
#endif