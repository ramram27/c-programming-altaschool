#include <stdio.h>

int main() {
    int n;
    long long fact=1;
    printf("Enter a numer");
    scanf("%d",&n);
    if(n==0 || n==1) {
        printf("fact= %lld",fact);
        return 0;
    }
    while (n>1)
    {
       fact = fact*n;
       n--;
    }
    printf("%lld",fact);
    return 0;
}