#include<stdio.h>
#include<limits.h>
int main() {
    int arr[5];
    int largest=INT_MIN;
    int secLargest=INT_MIN;

    printf("Enter a number:");
    for(int i=0;i<5;i++) {
        scanf("%d",&arr[i]);
    }
    for(int i=0;i<5;i++) {
        if(arr[i]>largest) {
            secLargest=largest;
            largest=arr[i];
        } else if(arr[i]>secLargest && arr[i] != largest) {
            secLargest=arr[i];
        }
    }
    printf("Largest = %d, secLargset = %d ", largest,secLargest);
    return 0;

}