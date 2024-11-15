#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10 // 초기 배열 크기

void add_symbol(char ***sym, int *size, int *count, const char *new_symbol)
{
    if (*count >= *size)
    {
        *size *= 2; // 배열 크기를 두 배로 증가
        *sym = realloc(*sym, *size * sizeof(char *));
        if (*sym == NULL)
        {
            perror("메모리 할당 실패");
            exit(1);
        }
    }

    // 새 심볼 추가
    (*sym)[*count] = strdup(new_symbol); // strdup로 문자열 복사 및 추가
    if ((*sym)[*count] == NULL)
    {
        perror("메모리 할당 실패");
        exit(1);
    }

    (*count)++;
}

void free_symbols(char **sym, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(sym[i]); // 동적 할당된 문자열 해제
    }
    free(sym); // 전체 배열 해제
}

int main()
{
    char **sym = malloc(INITIAL_SIZE * sizeof(char *)); // 초기 메모리 할당
    if (sym == NULL)
    {
        perror("메모리 할당 실패");
        return 1;
    }

    int size = INITIAL_SIZE;
    int count = 0;

    // 테스트용 심볼 추가
    add_symbol(&sym, &size, &count, "MOV");
    add_symbol(&sym, &size, &count, "ADD");
    add_symbol(&sym, &size, &count, "SUBs");
    add_symbol(&sym, &size, &count, "SUBs");
    add_symbol(&sym, &size, &count, "SUBs");
    add_symbol(&sym, &size, &count, "SUBs");
    add_symbol(&sym, &size, &count, "SUBs");
    add_symbol(&sym, &size, &count, "SUBs");
    add_symbol(&sym, &size, &count, "SUBs");
    add_symbol(&sym, &size, &count, "SUBs");
    add_symbol(&sym, &size, &count, "SUBs");
    add_symbol(&sym, &size, &count, "SUBs");

    // 배열 출력
    for (int i = 0; i < count; i++)
    {
        printf("sym[%d]: %s\n", i, sym[i]);
    }

    // 메모리 해제
    free_symbols(sym, count);

    return 0;
}
