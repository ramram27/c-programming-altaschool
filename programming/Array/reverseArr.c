#include<stdio.h>

int main() {

    int arr[5],n=5;

    printf("Enter a array number: ");

    for(int i=0;i<n;i++) {
        scanf("%d",&arr[i]);
    }

    printf("print array element :  \n");

    for(int i=n-1;i>=0;i--) {
        printf("%d ",arr[i]);
    }
    return 0;
}