#include <stdio.h>  // 표준 입출력 함수 헤더
#include <ctype.h>  // 문자 처리 함수 헤더 (예: isalpha, isdigit)
#include <stdlib.h> // 표준 라이브러리 함수 헤더

int main()
{
    FILE *fp;              // 파일 포인터 선언
    char ch;               // 파일에서 읽어올 문자를 저장할 변수
    int letters = 0;       // 영문자 개수를 세는 변수
    int digits = 0;        // 숫자 개수를 세는 변수
    int special_chars = 0; // 특수문자 개수를 세는 변수

    // 파일 열기
    fp = fopen("I_have_a_dream_Num.txt", "r"); // "ihaveadream.txt" 파일을 읽기 모드로 엽니다
    if (fp == NULL)
    { // 파일 열기 실패 시 처리
        printf("파일 열기에 실패했습니다.\n");
        return -1; // 프로그램 종료
    }

    // 파일에서 한 문자씩 읽어서 분석
    while ((ch = fgetc(fp)) != EOF)
    { // 파일에서 한 문자씩 읽어 EOF(파일의 끝)까지 반복

        if (isalpha(ch))
        {              // 영문자인지 검사
            letters++; // 영문자일 경우 카운트 증가
            printf("영문자: %c %d\n", ch, letters);
        }
        else if (isdigit(ch))
        {             // 숫자인지 검사
            digits++; // 숫자일 경우 카운트 증가
            printf("숫자: %c %d\n", ch, digits);
        }
        else if (ispunct(ch))
        {                    // 특수문자인지 검사
            special_chars++; // 특수문자일 경우 카운트 증가
            printf("특수문자:%c %d\n", ch, special_chars);
        }
    }

    // 결과 출력
    printf("영문자 개수: %d\n", letters);
    printf("숫자 개수: %d\n", digits);
    printf("특수문자 개수: %d\n", special_chars);

    // 파일 닫기
    fclose(fp);
    return 0;
}