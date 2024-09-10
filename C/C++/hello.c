#include <stdio.h>
#include <stdlib.h>

#define maxNumbers 20 // 숫자 최대 개수 정의

int data[20] = {3, 4, 23, 493, 54, 13, 56, 76, 123, 888, 413, 234, 5, 432, 324, 11, 43, 53, 99, 1};

int main()
{
    int numbers[maxNumbers]; // 실질적으로 수가 들어있는 공간
    int index = 0;           // 숫자들의 인덱스
    FILE *file;

    file = fopen("input.dat", "w"); // 쓰기 모드로 dat파일 열기

    // 만약 키보드에서 입력받아서 하는 경우 이 부분 주석 취소하면 됩니다.
    char input[100]; // 숫자를 입력할 공간
    printf("텍스트를 입력하세요: ");
    fgets(input, sizeof(input), stdin);
    fprintf(file, "%s", input);

    // 만약 키보드에서 입력받아서 하는 경우 아래 반복문을 주석 처리하면 됩니다.
    // for (int i = 0; i < 20; i++) // 리스트에 있는 데이터를 저장 하는 형식
    //{
    //    fprintf(file, "%d ", data[i]);
    //}

    fclose(file); // 파일 닫기

    file = fopen("input.dat", "r"); // dat파일 읽기모드로 열기

    if (file == NULL) // 파일이 존재하지 않는 경우
    {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    // 해당 파일의 숫자 읽어오기 maxNumbers의 개수만큼
    while (fscanf(file, "%d", &numbers[index]) != EOF && index < maxNumbers)
    {
        index++;
    }

    fclose(file); // 파일 사용 후 파일 닫기

    // 버블 정렬로 숫자 정렬
    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 0; j < index - 1 - i; j++)
        {
            // 작은 숫자 먼저 나오고 싶으면 아래 <를 >로 바꾸면 된다.
            if (numbers[j] < numbers[j + 1])
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
        printf("%d, ", numbers[i]);
    }

    return 0;
}
