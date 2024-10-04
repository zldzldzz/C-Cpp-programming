#include <stdio.h>
#include <stdlib.h>

#define maxNumbers 25 // 숫자 최대 개수 정의

// 이진 검색 함수
int binarySearch(int arr[], int size, int target)
{
    int low = 0, high = size - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == target)
        {
            return mid; // 찾으면 인덱스 반환
        }
        else if (arr[mid] < target)
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
    int numbers[maxNumbers]; // 파일에서 읽어들인 숫자를 저장할 배열
    int index = 0;           // 숫자들의 인덱스
    FILE *file;

    // input.dat 파일 읽기
    file = fopen("input.dat", "r"); // dat 파일 읽기 모드로 열기
    if (file == NULL)
    {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    // 파일에서 숫자 읽기
    while (fscanf(file, "%d", &numbers[index]) != EOF && index < maxNumbers)
    {
        index++;
    }
    fclose(file); // 파일 닫기

    // 버블 정렬 (오름차순)
    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 0; j < index - 1 - i; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    // 정렬된 숫자 출력
    printf("정렬된 숫자:\n");
    for (int i = 0; i < index; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // 사용자 입력 반복 처리
    int input;
    while (1)
    {
        printf("찾을 숫자를 입력하세요 (종료: 0): ");
        scanf("%d", &input);

        if (input == 0)
        {
            break; // 0 입력 시 프로그램 종료
        }

        // 이진 검색 수행
        int result = binarySearch(numbers, index, input);

        if (result != -1)
        {
            printf("%d는 정렬된 리스트에서 %d번째에 있습니다.\n", input, result + 1);
        }
        else
        {
            printf("%d는 리스트에 없습니다.\n", input);
        }
    }

    return 0;
}
