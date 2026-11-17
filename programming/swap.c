// #include <stdio.h>

// int main() {
//     int a,b,temp;
//     printf("enter a number a");
//     scanf("%d",&a);
//     printf("Enter a number b");
//     scanf("%d",&b);
//     printf("%d %d",a,b);
//     temp=a;
//     a=b;
//     b=temp;
//     printf("%d %d",a,b);
// }

#include <stdio.h>

int fun(int n) {

    if(n==1) {
        return 1;
    } else {
        return 1+fun(n-1);
    }
}

int main() {
    printf("Try clicking the Run button.",fun(3));
    return 0;
}