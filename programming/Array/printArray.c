#include<stdio.h>

int main() {
    int arr[5];

    printf("take input in the array");
    for(int i=0;i<5;i++) {
        scanf("%d",&arr[i]);
    }

    printf("print array \n");
   for(int i=0;i<5;i++) {
    printf("%d ",arr[i]);
   }
   return 0;
}