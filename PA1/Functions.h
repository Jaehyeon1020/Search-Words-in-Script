#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#define BUF_SIZE 1024

void findSingleWord(int fd, char * userInput); // function 1
void findMultiWord(int fd, char * userInput); // function 2
void findPhrase(int fd, char * userInput); // function 3
void findRegularExpression(int fd, char * userInput); // function 4

int stringCompare(char * str1, char * str2);
void enterToNull(char * str);
int isBlankInString(char * str);
int isStarInString(char * str);

#endif