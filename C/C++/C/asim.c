#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LENGTH 100
#define OUT_FILE "out.txt"

// 라벨 판별 함수: 단어가 ':'로 끝나는지 확인
bool is_label(const char *word)
{
    size_t len = strlen(word);
    return len > 0 && word[len - 1] == ':';
}

// 라벨에서 ':' 제거
void remove_colon(char *word)
{
    size_t len = strlen(word);
    if (len > 0 && word[len - 1] == ':')
    {
        word[len - 1] = '\0';
    }
}

// DB/DW 판별 함수
bool is_data_declaration(const char *word)
{
    return strcmp(word, "DB") == 0 || strcmp(word, "DW") == 0;
}

int main()
{
    FILE *input_file = fopen("symbol.txt", "r");
    FILE *output_file = fopen(OUT_FILE, "w");
    if (input_file == NULL || output_file == NULL)
    {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    char line[MAX_LENGTH];
    int word_count = 0;
    char *words[MAX_LENGTH] = {0};  // 단어 저장 배열
    int word_positions[MAX_LENGTH]; // 위치 저장 배열
    int total_words = 0;            // 전체 단어 수

    // 첫 번째 단계: 단어와 위치 저장
    while (fgets(line, sizeof(line), input_file))
    {
        char *token = strtok(line, " \t\n");
        char *previous_token = NULL; // DB/DW 앞의 단어를 추적하기 위한 변수
        while (token != NULL)
        {
            word_positions[total_words] = ++word_count;
            words[total_words] = strdup(token); // 단어 저장

            // DB/DW 앞에 위치한 단어인 경우 출력
            if (is_data_declaration(token) && previous_token != NULL)
            {
                printf("단어: %s, 위치: %d번째 단어\n", previous_token, word_positions[total_words - 1]);
            }

            // 라벨인 경우 위치 출력
            if (is_label(token))
            {
                remove_colon(token); // ':' 제거
                printf("라벨: %s, 위치: %d번째 단어\n", token, word_positions[total_words]);
            }

            previous_token = token; // 현재 토큰을 이전 토큰으로 설정
            total_words++;
            token = strtok(NULL, " \t\n");
        }
    }

    // 두 번째 단계: OUT.txt에 위치로 대체하여 저장
    rewind(input_file);
    word_count = 0; // 단어 카운트를 초기화

    while (fgets(line, sizeof(line), input_file))
    {
        char *token = strtok(line, " \t\n");
        while (token != NULL)
        {
            bool replaced = false;

            for (int i = 0; i < total_words; i++)
            {
                // 현재 토큰이 저장된 단어와 일치하면 위치로 대체
                if (strcmp(token, words[i]) == 0)
                {
                    if (is_label(words[i]) || (i > 0 && is_data_declaration(words[i - 1])))
                    {
                        fprintf(output_file, "%d ", word_positions[i]);
                    }
                    else
                    {
                        fprintf(output_file, "%s ", token);
                    }
                    replaced = true;
                    break;
                }
            }

            if (!replaced)
            {
                fprintf(output_file, "%s ", token); // 대체되지 않은 단어 그대로 출력
            }

            token = strtok(NULL, " \t\n");
        }
        fprintf(output_file, "\n"); // 줄바꿈
    }

    // 동적 메모리 해제
    for (int i = 0; i < total_words; i++)
    {
        free(words[i]);
    }

    fclose(input_file);
    fclose(output_file);

    printf("변환 결과가 %s에 저장되었습니다.\n", OUT_FILE);
    return 0;
}
