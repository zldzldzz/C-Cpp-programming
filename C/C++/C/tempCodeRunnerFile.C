#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 숫자인지 확인하는 함수
int is_number(const char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isdigit(word[i])) {
            return 0;
        }
    }
    return 1;
}

// 한 줄에서 첫 번째 단어인지 확인하는 함수 (레이블 확인)
int is_first_word(const char *line, const char *word) {
    // line에서 첫 번째 단어 추출
    char first_word[100];
    sscanf(line, "%s", first_word);
    return (strcmp(first_word, word) == 0);
}

int main() {
    FILE *file;
    char word[100]; // 단어 저장 버퍼
    char line[100]; // 한 줄 저장 버퍼

    // 파일 열기
    file = fopen("A.TXT", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    // 파일에서 한 줄씩 읽기
    while (fgets(line, sizeof(line), file)) {
        // 공백을 기준으로 단어를 분리하여 처리
        char *token = strtok(line, " \t\n");
        int first_word_checked = 0; // 한 줄에서 첫 번째 단어를 체크했는지 여부

        while (token != NULL) {
            // 첫 번째 단어인 경우 레이블로 처리
            if (first_word_checked == 0 && is_first_word(line, token)) {
                printf("%s [LAB]\n", token);
                first_word_checked = 1; // 첫 번째 단어 체크 완료
            }
            // 숫자인 경우
            else if (is_number(token)) {
                printf("%s [NUM]\n", token);
            }
            // 그 외의 경우
            else {
                printf("%s [ABC]\n", token);
            }
            // 다음 단어로 넘어가기
            token = strtok(NULL, " \t\n");
        }
    }

    // 파일 닫기
    fclose(file);

    return 0;
}
