#include<stdio.h>

int main() {
    int arr[5];
    int sum=0;
    printf("Enter a number and store in the array");
    for(int i=0;i<10;i++) {
        scanf("%d",&arr[i]);
    }
    printf("print array element :");
    for(int i=0;i<10;i++) {
        // printf("%d ",arr[i]);
        sum = sum + arr[i];
    }
    printf("sum = %d",sum);
    return 0;
}