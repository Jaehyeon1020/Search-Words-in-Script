#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

// read를 통해 표준 입력에서 받은 \n을 \0로 변환(문자열로 만들기)
void enterToNull(char * str) {
    for(int i = 0; i < 1024; i++) {
        if(str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

// str1과 str2가 같으면 1 반환, 같지 않으면 -1 반환
int stringCompare(char * str1, char * str2) {
    int i=0;
    int str1Len = 0;
    int str2Len = 0;

    // 첫 번째 문자열 길이 계산
    while(str1[i] != '\0') {
        i += 1;
        str1Len += 1;
    }

    i = 0; // i 초기화

    // 두 번째 문자열 길이 계산
    while(str2[i] != '\0') {
        i+= 1;
        str2Len += 1;
    }

    // 두 문자열의 길이가 다르면 -1 반환
    if(str1Len != str2Len) {
        return -1;
    }

    i = 0; // i 초기화
    while(str1[i] != '\0' && str2[i] != '\0') {
        // str1과 str2가 같지 않다면 -1 반환
        if(str1[i] - str2[i] != 0)
            return -1;
        
        i += 1;
    }

    // while문에서 return되지 않음 == str1과 str2가 같음
    return 1;
}


// 숫자 출력 함수(개행이나 공백은 없음)
void printNumber(int num) {
    // 0이 숫자로 주어진 경우 0 출력하고 return
    if(num == 0) {
        write(1, "0", 1);
        return;
    }

    int tmp = num; // 임시
    int count = 0; // 자리수
    
    // 인수로 주어진 숫자의 자리수 계산
    while(tmp != 0) {
        tmp = tmp/10;
        count += 1;
    }

    tmp = num;
    // 각 자리 숫자 구해서 출력(0~9 아스키코드: 48~57)
    for(int i = 1; i <= count; i++) {
        for(int j = 0; j < count - i; j++)
            tmp = tmp / 10;
        
        tmp = tmp % 10;

        if(tmp == 0)
            write(1, "0", 1);
        else if(tmp == 1)
            write(1, "1", 1);
        else if(tmp == 2)
            write(1, "2", 1);
        else if(tmp == 3)
            write(1, "3", 1);
        else if(tmp == 4)
            write(1, "4", 1);
        else if(tmp == 5)
            write(1, "5", 1);
        else if(tmp == 6)
            write(1, "6", 1);
        else if(tmp == 7)
            write(1, "7", 1);
        else if(tmp == 8)
            write(1, "8", 1);
        else
            write(1, "9", 1); 

        tmp = num; // 다음 계산 위해서 다시 tmp 초기화
    }
}

// 두 개의 단어 공백으로 구분된 input과 포인터 두개 받아서 각각에 저장
void tokenizeString(char * userInput, char ** input1, char ** input2) {
    int firstWordLength = 0;
    int secondWordLength = 0;
    int i;

    for(i = 0; userInput[i] != ' '; i++)
        firstWordLength++;
    
    for(i = firstWordLength+1; userInput[i] != '\0'; i++)
        secondWordLength++;

    *input1 = (char*)malloc(sizeof(char) * (firstWordLength + 1));
    *input2 = (char*)malloc(sizeof(char) * (firstWordLength + 1));


    for(i = 0; i < firstWordLength+1; i++) {
        (*input1)[i] = userInput[i];

        if(i == firstWordLength)
            (*input1)[i] = '\0'; // 첫번째 단어 끝 null문자 삽입
    }

    for(int i = 0; i < secondWordLength + 1; i++) {
        (*input2)[i] = userInput[firstWordLength + i + 1];

        if(i == secondWordLength)
            (*input2)[i] = '\0'; // 두번째 단어 끝 null문자 삽입
    }
}


int main() {
    char * userInput_1;
    char * userInput_2;

    tokenizeString("apple bananana", &userInput_1, &userInput_2);

    printf("input1 1: %s\n", userInput_1);
    printf("input2 1: %s\n", userInput_2);

    return 0;
}