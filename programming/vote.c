#include<stdio.h>

int main() {
    int age;
    char status;
    printf("Enter a age");
    scanf("%d",&age);
    printf("Enetr Status Y/N");
    scanf(" %c",&status);

    if(age >= 18) {
        if(status == 'Y' || status == 'y') {
            printf("Elegible for vote");
        } else{
             printf("Not elegiblae for vote");
        }

    }else{
        printf("Not elegiblae for vote");
    }
    return 0;
}