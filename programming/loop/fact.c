#include<stdio.h>
int main() {
    int n,i=1;
    long long fact=1;
    printf("Enter a number n");
    scanf("%d",&n);
    if(n==0||n==1) {
        printf("%d",fact);
        return 1;
    }
    while(i<=n) {
      fact = fact*i;
      i++;
    }
    printf("%lld",fact);
    return 0;
}