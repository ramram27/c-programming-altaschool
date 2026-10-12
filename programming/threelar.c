#include<sdtio.h>

int main(){
    int a,b,c;
    printf("Enter a number a,b,c");
    scanf("%d %d %d",&a,&b,&c);
    if(a>=b && a>=c){
        printf("%d",a);
    }else if(b>=a && b>=c) {
        printf("%d",b);
    }else if(c>=a && c>=b) {
        printf("%d",c);
    }
    return 0;
}