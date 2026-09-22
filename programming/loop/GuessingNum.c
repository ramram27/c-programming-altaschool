#include<stdio.h>

int main(){
    int gessNum=8;
    int num;
    do{
        printf("Enter a number num");
        scanf("%d",&num);

        if(num != gessNum) {
            printf("You loss game %d",num);
        }
    }while(num != gessNum)
    printf("You are win %d",num);
}