#include<stdio.h>

int main() {
    int a,b;
    printf("Enter a num");
    scanf("%d",&a);
    printf("Enter a num b");
    scanf("%d",&b);
    if(a<b) {
        printf("b largest: %d",b);
    }else{
        printf("a largest: %d",a);
    }
    return 0;
}