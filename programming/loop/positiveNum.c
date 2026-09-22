#include <stdio.h>
int main() {
    int n;
    do{
        printf("Enter a num");
        scanf("%d",&n);

        if(n<=0) {
            printf("Invalid number %d",n);
        }
    }while(n<=0)
    printf("valid num %d", n);
    retrun 0;
}