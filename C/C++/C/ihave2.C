#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // 문자 처리 함수 헤더 (예: isalpha, isdigit)

int main() {
    // 파일 포인터 선언
    FILE *file;
    // 단어를 저장할 배열 선언 (최대 100바이트 길이로 가정)
    char word[100];
    int Eng = 0;
    int num = 0;

    // 파일 열기 (읽기 모드로)
    file = fopen("I_have_a_dream_Num.txt", "r");

    // 파일이 정상적으로 열렸는지 확인
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    // 파일에서 단어를 하나씩 읽어 처리
    while (fscanf(file, "%s", word) == 1) {
        // 영문자인지 확인할 플래그
        int is_eng = 1;

        // 단어의 모든 문자가 영문자인지 확인
        for (int i = 0; i < strlen(word); i++) {
            if (!isalpha(word[i])) {
                is_eng = 0;  // 영문자가 아닌 문자가 있으면 플래그를 0으로 설정
                break;
            }
        }

        // 모든 문자가 영문자인 경우
        if (is_eng) {
            printf("영문자 맞음: %s\n", word);
            Eng++;  // Eng 변수 증가
        }

        // 숫자인지 확인할 플래그
        int is_number = 1;

        // 단어의 모든 문자가 숫자인지 확인
        for (int j = 0; j < strlen(word); j++) {
            if (!isdigit(word[j])) {
                is_number = 0;  // 숫자가 아닌 문자가 있으면 플래그를 0으로 설정
                break;
            }
        }

        // 모든 문자가 숫자인 경우
        if (is_number) {
            printf("숫자 맞음: %s\n", word);
            num++;  // num 변수 증가
        }
    }

    // 결과 출력
    printf("영문자 단어 갯수: %d\n", Eng);
    printf("숫자 단어 갯수: %d\n", num);

    // 파일 닫기
    fclose(file);

    return 0;
}
