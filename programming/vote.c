// #include <stdio.h>

// int main() {
//     int num;

//     do {
//         printf("Enter number: ");
//         scanf("%d", &num);

//         if (num <= 0) {
//             printf("Please enter a positive number.\n");
//         }

//     } while (num <= 0);

//     printf("Valid number: %d\n", num);

//     return 0;
// }
#include<stdio.h>
int main() {
    int n=5,num=1;
    for(int i=1;i<=n;i++) {
       for(int j=1;j<=i;j++) {
        printf("%d",num++);
       }
       printf("\n");
    }  
    return 0;
}