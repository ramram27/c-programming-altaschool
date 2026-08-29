#include <stdio.h>
int main() {
    int num1,num2,num3;
    float avg;
    printf("Enter a number num1");
    scanf("%d",&num1);
    printf("Enter a number num2 :");
    scanf("%d",&num2);
    printf("Enter a numer num3");
    scanf("%d",&num3);
    avg = (num1+num2+num3)/3;
    printf("%f",avg);
    return 0;
}