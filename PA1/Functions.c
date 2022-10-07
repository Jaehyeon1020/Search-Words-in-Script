#include "Functions.h"

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


// read를 통해 표준 입력에서 받은 \n을 \0로 변환(문자열로 만들기)
void enterToNull(char * str) {
    for(int i = 0; i < BUF_SIZE; i++) {
        if(str[i] == '\n') {
            str[i] = '\0';
            break;
        }

        i += 1;
    }
}


// 주어진 문자열에 공백 있는지 확인
// 있으면 1, 없으면 0 반환
int isBlankInString(char * str) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == ' ')
            return 1;
    }

    return 0;
}


// 문자열에 별 있으면 1 반환 없으면 0 반환
int isStarInString(char * str) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == '*')
            return 1;
    }

    return 0;
}