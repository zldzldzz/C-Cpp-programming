#include <stdio.h>

// 내림차순 정렬 함수
void sort_desc(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] < arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// 이진 탐색 함수
void binary_search(int arr[], int left, int right, int target)
{
    while (left <= right)
    {
        int mid = (left + right) / 2;

        // 현재 탐색 범위를 출력
        for (int i = left; i <= right; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");

        if (arr[mid] == target)
        {
            printf("찾은 값: %d\n", arr[mid]);
            return;
        }
        else if (arr[mid] < target)
        { // 왼쪽에 존재
            right = mid - 1;
        }
        else
        { // 오른쪽에 존재
            left = mid + 1;
        }
    }

    printf("값을 찾지 못했습니다.\n");
}

int main()
{
    int arr[] = {34, 56, 72, 126, 31, 11, 7, 8, 29, 100};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 72;

    // 배열을 내림차순으로 정렬
    sort_desc(arr, n);

    // 정렬된 배열 출력
    printf("정렬된 수: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 이진 탐색 실행 및 과정 출력
    printf("이진 탐색 과정:\n");
    binary_search(arr, 0, n - 1, target);

    return 0;
}
