 /*C언어로 아래 정수를 크기 순서로 정렬하며, 1)큰 수부터 화면에 출력하고 2) 이어서 2열로 출력하라*/

//34, 56, 72, 126, 31, 11, 7, 8, 29, 100
#include <stdio.h>
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {  
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int numbers[] = {34, 56, 72, 126, 31, 11, 7, 8, 29, 100};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    bubble_sort(numbers, n);
    for(int i=0; i<n;i++){
        printf("%d ",numbers[i]);
    }
    printf("\n\n");


    return 0;
}