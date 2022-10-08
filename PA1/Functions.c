#include "Functions.h"
// #include <stdio.h> // 테스트용 지워야됨 지워야됨 지워야됨

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


// read를 통해 표준 입력에서 받은 \n을 \0로 변환(문자열로 만들기)
void enterToNull(char * str) {
    for(int i = 0; i < BUF_SIZE; i++) {
        //printf("enterToNull 진입\n");
        if(str[i] == '\n') {
            //printf("enterToNULL : 위치 %d\n", i);
            str[i] = '\0';
            break;
        }
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
// 대소문자를 구분함
int compareFromIndex(int checkingIndex, char * userInput, char * buffer) {
    int strLen = 0; // str의 글자 수
    int bufferIdx = checkingIndex;
    
    for(int i = 0; userInput[i] != '\0'; i++) {
        strLen++;
    }
    
    for(int i = 0; i < strLen; i++) {
        if(userInput[i] != buffer[bufferIdx]) 
            return 0;
        
        bufferIdx += 1;
    }

    // 단어 뒤에 다른 글자 붙어있지 않아야 찾는 단어가 있는 것
    if(buffer[bufferIdx] == '\n' || buffer[bufferIdx] == ' '
        || buffer[bufferIdx] == '\0' || buffer[bufferIdx] == '\t') {
        // 단어 앞에도 다른 글자 있으면 안됨
        if(buffer[checkingIndex - 1] == '\n' || buffer[checkingIndex - 1] == ' '
            || buffer[checkingIndex - 1] == '\0' || buffer[checkingIndex -1] == '\t')
            return 1;
    }
    else
        return 0;
}


// 대소문자 구분 없이 비교하는 compareFromIndex()
// 대문자 ASCII 번호 + 32 = 소문자 ASCII 번호(A: 65, Z: 90)
int compareCaseFromIndex(int checkingIndex, char * userInput, char * buffer) {
    int strLen = 0; // str의 글자 수
    int bufferIdx = checkingIndex;
    int i = 0;
    
    for(i = 0; userInput[i] != '\0'; i++) {
        strLen++;
    }

    // 대문자 있는거 전부 소문자로 변환
    for(i = 0; i < strLen; i++) {
        // 대문자인 경우
        if(65 <= userInput[i] && userInput[i] <= 90)
            userInput[i] += 32; // 소문자로 변환
        
        if(65 <= buffer[checkingIndex + i] && buffer[checkingIndex + i] <= 90)
            buffer[checkingIndex + i] += 32;
    }
    
    // 단어끼리 비교
    for(i = 0; i < strLen; i++) {
        if(userInput[i] != buffer[bufferIdx]) 
            return 0;
        
        bufferIdx += 1;
    }

    // 단어 뒤에 다른 글자 붙어있지 않아야 찾는 단어가 있는 것 or 단어 뒤가 파일 끝
    if(buffer[bufferIdx] == '\n' || buffer[bufferIdx] == ' '
        || buffer[bufferIdx] == '\0' || buffer[bufferIdx] == '\t') {
        // 단어 앞에도 다른 글자 있으면 안됨
        if(buffer[checkingIndex - 1] == '\n' || buffer[checkingIndex - 1] == ' '
            || buffer[checkingIndex - 1] == '\0' || buffer[bufferIdx] == '\t')
            return 1;
    }
    else
        return 0;
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


// 주어진 문자열 앞 뒤에 있는 따옴표 제거
void deleteQuotation(char * userInput) {
    int i;
    int strLen = 0;
    
    // 따옴표 포함 문자열 길이 계산
    for(i = 0; userInput[i] != '\0'; i++) {
        strLen++;
    }

    // strLen번만큼 모든 문자 앞으로 한 idx씩 이동
    for(i = 0; i < strLen; i++) {
        userInput[i] = userInput[i + 1];
    }

    // null문자 한칸 앞으로 이동(마지막 따옴표 사라지면서 그곳이 문장의 끝이 됨)
    userInput[strLen - 2] = userInput[strLen - 1];
}


void findSingleWord(int fd, char * userInput) {
    //printf("findSingleWord 진입 완료\n"); // test

    char buffer[BUF_SIZE]; // 단어를 찾을 txt파일에서 한줄씩 불러와서 저장
    int currentIdx = 0; // 현재 checking하는 index 저장
    int currentLine = 0; // 현재 checking하는 line 저장
    int matchingIdx; // 단어가 일치하는 index 저장
    int eofCheck;
    int firstEnterIdx; // 읽은 문자들 중 첫 번째 개행문자의 위치(한 줄의 끝)
    int lastReadWritePointer = 0; // 누적해서 R/W pointer 위치 계산

    while(1) {
        //printf("findSingleWord while문 진입\n"); // test

        currentLine++; // line 1부터 시작
        //printf("current line: %d\n", currentLine); // test

        if((eofCheck = read(fd, buffer, sizeof(buffer))) == 0) {
            break; // eof 도달 시 탈출
        }

        firstEnterIdx = getFirstEnterIndex(buffer); // 읽어들인 문장에서 첫 번째 엔터의 idx 저장
        lastReadWritePointer += firstEnterIdx + 1;

        // 개행문자 없는 경우 -> 마지막줄임 : 개행문자 있을때만 offset 조정
        if(firstEnterIdx != -1) { 
            //printf("findSingleWord: lseek함수 사용 진입\n"); // test
            //printf("firstEnterIdx: %d\n", firstEnterIdx); // test
            //printf("lseek value: %d\n",lseek(fd, lastReadWritePointer, SEEK_SET)); // test
            lseek(fd, lastReadWritePointer, SEEK_SET); // 여기까지 파일 포인터 땡김(이 라인까지 해서 한줄 input)
        }

        // 현재 읽어들인 줄에서 같은 단어가 있는지 확인: idx 1씩 올리면서 확인
        for(currentIdx = 0; currentIdx < firstEnterIdx; currentIdx++) {
            if(compareCaseFromIndex(currentIdx, userInput, buffer) == 1) {
                // currentLine:currentIdx 출력
                printNumber(currentLine);
                write(1, ":", 1);
                printNumber(currentIdx);
                write(1, " ", 1);
            }
        }
    }
    
    //printf("findSingleWord: 함수 종료\n"); // test
    lseek(fd, 0, SEEK_SET); // 함수 종료 전 r/w포인터 원래대로
    write(1, "\n", 1); // 함수 종료 전 개행
}


void findMultiWord(int fd, char * userInput) {
    char buffer[BUF_SIZE]; // 단어 찾을 txt파일 한 줄씩 저장
    int currentIdx = 0; // 현재 checking하는 index 저장
    int currentLine = 0; // 현재 checking하는 line 저장
    int eofCheck;
    int firstEnterIdx; // 읽은 문자들 중 첫 번째 개행문자의 위치
    int lastReadWritePointer = 0; // 누적해서 lseek 사용
    char * userInput_1; // 단어 두개 받은 것 중 앞
    char * userInput_2; // 단어 두개 받은 것 중 뒤
    int isFirstWord = 0; // 이 line에 첫 번째 단어 있는지 확인
    int isSecondWord = 0; // 이 line에 두 번째 단어 있는지 확인

    tokenizeString(userInput, &userInput_1, &userInput_2); // 공백 기준으로 단어 쪼개서 저장

    while(1) {
        currentLine++;

        if((eofCheck = read(fd, buffer, sizeof(buffer))) == 0) {
            break; // eof 도달 시 탈출
        }

        firstEnterIdx = getFirstEnterIndex(buffer); // 읽어들인 문장에서 첫 번째 엔터의 index 저장
        lastReadWritePointer += firstEnterIdx + 1; // lseek 움직일 위치 누적
        
        // 개행문자 없는 경우 -> 마지막줄 : 개행문자 있을 때만 offset 조정
        if(firstEnterIdx != -1) {
            // 이 코드까지 해서 txt파일에서 한 줄 저장
            lseek(fd, lastReadWritePointer, SEEK_SET);
        }

        // 한 index에서 두 단어 모두 비교하고 단어 있으면 isFirstWord, isSecondWord set
        // for문 종료 후 isFirstWord = isSecondWord == 1이면 lineNumber 출력
        for(currentIdx = 0; currentIdx < firstEnterIdx; currentIdx++) {
            if(compareCaseFromIndex(currentIdx, userInput_1, buffer) == 1)  {
                isFirstWord = 1;
            }

            if(compareCaseFromIndex(currentIdx, userInput_2, buffer) == 1) {
                isSecondWord = 1;
            }
        }

        // 현재 line에 두 단어가 모두 존재한다면
        if(isFirstWord == 1 && isSecondWord == 1) {
            printNumber(currentLine);
            write(1, " ", 1);
        }

        isFirstWord = 0; // 1 line 검색 후 초기화
        isSecondWord = 0; // 1 line 검색 후 초기화
    }

    lseek(fd, 0, SEEK_SET); // 함주 종료 전 rw포인터 초기화
    write(1, "\n", 1); // 함수 종료 전 개행
    free(userInput_1);
    free(userInput_2);
}


void findPhrase(int fd, char * userInput) {
    char buffer[BUF_SIZE]; // 단어 찾을 txt파일에서 한 줄 저장
    int currentIdx = 0;
    int currentLine = 0;
    int matchingIdx;
    int eofCheck;
    int firstEnterIdx;
    int lastReadWritePointer = 0;

    // 큰따옴표로 감싸져서 들어온 userInput의 큰따옴표 제거
    deleteQuotation(userInput);

    while(1) {
		currentLine++;

        if((eofCheck = read(fd, buffer, sizeof(buffer))) == 0) {
            break; // eof 도달 시 탈출
        }

        firstEnterIdx = getFirstEnterIndex(buffer);
        lastReadWritePointer += firstEnterIdx + 1;

        if(firstEnterIdx != -1) {
            lseek(fd, lastReadWritePointer, SEEK_SET); // 여기까지 rw포인터 위치(한줄입력 끝)
        }

        // 현재 읽어들인 줄에서 같은 구가 있는지 확인: idx 1씩 올리며 확인
        for(currentIdx = 0; currentIdx < firstEnterIdx; currentIdx++) {
            if(compareCaseFromIndex(currentIdx, userInput, buffer) == 1) {
                // currentLine:currentIdx 출력
                printNumber(currentLine);
                write(1, ":", 1);
                printNumber(currentIdx);
                write(1, " ", 1);
            }
        }
    }

    lseek(fd, 0, SEEK_SET); // 함수 종료 전 rw포인터 초기화
    write(1, "\n", 1); // 함수 종료 전 개행
}


void findRegularExpression(int fd, char * userInput) {

}
