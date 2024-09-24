#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxWords 20      // 단어 최대 개수 정의
#define maxWordLength 50 // 단어 최대 길이 정의

int binarySearch(char arr[][maxWordLength], int size, char *target)
{
    int low = 0, high = size - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        printf("탐색 범위: low=%d, high=%d, mid=%d, 중간값: %s\n", low, high, mid, arr[mid]);
        int cmp = strcmp(arr[mid], target);
        if (cmp == 0)
        {
            return mid; // 찾으면 인덱스 반환
        }
        else if (cmp < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1; // 찾지 못했을 경우
}

int main()
{
    char words[maxWords][maxWordLength]; // 파일에서 읽은 단어들을 저장할 배열
    int index = 0;                       // 단어들의 인덱스
    FILE *file;
    // input.dat 파일 읽기 모드로 열기
    file = fopen("input1.dat", "r");
    if (file == NULL)
    {
        printf("input1.dat 파일을 열 수 없습니다.\n");
        return 1;
    }

    // input.dat 파일에서 단어 읽어오기
    while (fscanf(file, "%s", words[index]) != EOF && index < maxWords)
    {
        index++;
    }

    fclose(file); // input.dat 파일 닫기

    // 버블 정렬로 단어 정렬 (사전순으로 오름차순 정렬)
    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 0; j < index - 1 - i; j++)
        {
            if (strcmp(words[j], words[j + 1]) > 0) // 사전순 비교
            {
                char temp[maxWordLength];
                strcpy(temp, words[j]);
                strcpy(words[j], words[j + 1]);
                strcpy(words[j + 1], temp);
            }
        }
    }

    // output.dat 파일 쓰기 모드로 열기
    file = fopen("output.dat", "w");
    if (file == NULL)
    {
        printf("output.dat 파일을 열 수 없습니다.\n");
        return 1;
    }

    // 정렬된 단어들을 output.dat 파일에 저장
    for (int i = 0; i < index; i++)
    {
        fprintf(file, "%s\n", words[i]);
    }

    fclose(file); // output.dat 파일 닫기

    // output.dat 파일에서 다시 읽어오기
    file = fopen("output.dat", "r");
    if (file == NULL)
    {
        printf("output.dat 파일을 열 수 없습니다.\n");
        return 1;
    }

    // 단어들을 다시 읽어옴
    index = 0;
    while (fscanf(file, "%s", words[index]) != EOF && index < maxWords)
    {
        index++;
    }

    fclose(file); // output.dat 파일 닫기

    // 정렬된 단어 출력
    printf("output.dat에서 읽은 정렬된 단어들:\n");
    for (int i = 0; i < index; i++)
    {
        printf("%s, ", words[i]);
    }
    printf("\n");

    // 키보드에서 값을 입력받아 순위 출력
    char target[maxWordLength];
    while (1)
    {
        printf("순위를 알고 싶은 단어를 입력하세요(종료: 0): ");
        scanf("%s", target);

        if (strcmp(target, "0") == 0)
        {
            break; // 0 입력 시 프로그램 종료
        }

        // 순위 계산
        int result = binarySearch(words, index, target);

        if (result != -1)
        {
            printf("단어 %s의 순위는 %d입니다.\n", target, result + 1);
        }
        else
        {
            printf("단어 %s는 목록에 없습니다.\n", target);
        }
    }
    return 0;
}
