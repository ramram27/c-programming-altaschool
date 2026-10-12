#include<stdio.h>
int main() {
    int arr[8]; 
    printf("enter a number : ");
    for(int i=0;i<8;i++) {
        scanf("%d",&arr[i]);
    }
    int largest = arr[0];
    for(int i=1;i<8;i++) {
        if(arr[i] > largest) {
            largest=arr[i];
        }
    }
    printf("%d",largest);
    return 0;
}