#include <stdio.h>

int main() {
    int a,b,temp;
    printf("enter a number a");
    scanf("%d",&a);
    printf("Enter a number b");
    scanf("%d",&b);
    printf("%d %d",a,b);
    temp=a;
    a=b;
    b=temp;
    printf("%d %d",a,b);
}