#include <stdio.h>

int main() {
    int num;
    printf("Enter a num");
    scanf("%d",&num);

    if(num < 0) {
        printf("Negative number");
    } else if(num > 0) {
        printf("positive number");
    } else{
        printf("Zero");
    }

    return 0;
}