#include<stdio.h>

int main() {

    int exp,salary;
    printf("Enter a exp");
    scanf("%d",&exp);
    printf("Enter a salary");
    scanf("%d",&salary);
    if(exp >= 4) {
      if(salary >= 50000) {
        printf("elegible for bunos");
      } else{
        printf("not elgible for bonus");
      }
    }else {
        printf("not elgible for bonus");
    }
    return 0;
}