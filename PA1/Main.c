#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "Functions.h"

// #include <stdio.h> // 지워야됨 지워야됨 지워야됨 지워야됨 테스트용

int main(int argc, char *argv[]) {
    int fd; // file descriptor
    char readBuffer[BUF_SIZE];
    
    // 파일 열기
    if((fd = open(argv[1], O_RDONLY)) < 0) {
        //printf("error\n"); // test
        exit(1);
    }

    /*
     * 입력의 경우를 나눠서 함수 실행
     * 참고: fd=0 표준 입력, fd=1 표준 출력, fd=2 표준에러
     */
    while(1) {
        //printf("main함수 while문 진입\n"); // test

        read(0, readBuffer, sizeof(readBuffer)); // user input을 readBuffer에 저장
        //printf("readbuffer1: %s\n", readBuffer); // test
        enterToNull(readBuffer); // 개행문자 널문자로 교체
        //printf("readbuffer2 : %s\n", readBuffer); // test

        // PA1EXIT 입력된경우 종료
        if(stringCompare(readBuffer, "PA1EXIT") == 1)
            break;
        
        // user input이 큰 따옴표로 시작하는 경우: findPhrase() 사용
        if(readBuffer[0] == '\"') {
            findPhrase(fd, readBuffer);
        }
        // 큰 따옴표로 시작하지 않으면서 공백문자가 있는 경우: findMultiWord() 사용
        else if(isBlankInString(readBuffer) == 1) {
            findMultiWord(fd, readBuffer);
        }
        // 중간에 *이 있는 경우: findRegularExpression() 사용
        else if(isStarInString(readBuffer) == 1) {
            findRegularExpression(fd, readBuffer);
        }
        // 그 외: findSingleWord() 사용
        else {
            //printf("findSingleWord 함수 진입 전\n"); // test
            findSingleWord(fd, readBuffer);
        }
    }


    if(close(fd) < 0) {
        //perror("close");
        exit(1);
    }
    
    return 0;
}