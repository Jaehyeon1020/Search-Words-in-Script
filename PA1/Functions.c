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

// 숫자 출력 함수(개행이나 공백은 없음)
void printNumber(int num) {
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

int getFirstEnterIndex(char * str) {
    for(int enterIdx = 0; enterIdx < BUF_SIZE; enterIdx++) {
        if(str[enterIdx] == '\n') {
            return enterIdx;
        }
    }

    return -1; // 개행문자 없음
}


// checkingIndex로부터 주어진 두 개의 문자열을 비교함
// 두 문자열이 일치하면 1 반환, 같지 않으면 0 반환
int compareFromIndex(int checkingIndex, char * userInput, char * buffer) {
    int strLen = 0; // str의 글자 수
    int bufferIdx = checkingIndex;
    
    for(int i = 0; userInput[i] != '\0'; i++) {
        strLen++;
    }
    
    for(int i = 0; i < strLen; i++) {
        bufferIdx += i;

        if(userInput[i] != buffer[bufferIdx]) 
            return 0;
    }

    // 단어 뒤에 다른 글자 붙어있지 않아야 찾는 단어가 있는 것
    if(buffer[bufferIdx + 1] == '\n' || buffer[bufferIdx + 1] == ' '
        || buffer[bufferIdx + 1] == '\0')
        return 1;
    else
        return 0;
}


void findSingleWord(int fd, char * userInput) {
    char buffer[BUF_SIZE];
    int currentIdx = 0; // 현재 checking하는 index 저장
    int currentLine = 0; // 현재 checking하는 line 저장
    int matchingIdx; // 단어가 일치하는 index 저장
    int eofCheck;
    int firstEnterIdx; // 읽은 문자들 중 첫 번째 개행문자의 위치(한 줄의 끝)
    // 엔터 위치 바로 다음을 파일 포인터가 가리키도록 조정하는 offset(BUF_SIZE - firstEnterIndex + 1)
    int movingOffset;

    while(1) {
        currentLine++; // line 1부터 시작

        if((eofCheck = read(fd, buffer, sizeof(buffer))) == 0) {
            break; // eof 도달 시 탈출
        }

        firstEnterIdx = getFirstEnterIndex(buffer); // 읽어들인 문장에서 첫 번째 엔터의 idx 저장

        // 개행문자 없는 경우 -> 마지막줄임 : 개행문자 있을때만 offset 조정
        if(firstEnterIdx != -1) {
            movingOffset = BUF_SIZE - firstEnterIdx + 1;
            lseek(fd, -movingOffset, SEEK_CUR); // 여기까지 파일 포인터 땡김(이 라인까지 해서 한줄 input)
        }
        
        // 현재 읽어들인 줄에서 같은 단어가 있는지 확인: idx 1씩 올리면서 확인
        for(currentIdx = 0; currentIdx < firstEnterIdx; currentIdx++) {
            if(compareFromIndex(currentIdx, userInput, buffer) == 1) {
                // currentLine:currentIdx 출력
                printNumber(currentLine);
                write(1, ":", 1);
                printNumber(currentIdx);
            }
        }
    }
    
    write(1, "\n", 1); // 함수 종료 전 개행
}


void findMultiWord(int fd, char * userInput) {

}


void findPhrase(int fd, char * userInput) {
    
}


void findRegularExpression(int fd, char * userInput) {

}