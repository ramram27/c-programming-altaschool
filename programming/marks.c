#include<stdio.h>

int main() {
    int marks;
    printf("Enter a marks");
    scanf("%d",&marks);
    if(marks >= 40) {
        if(marks >= 80) {
            printf("A");
        } else{
            if(marks >= 60) {
                printf("B");
            }else{
                printf("C");
            }
        }
    }else{
      printf("Fail");
    }
    return 0;
}

