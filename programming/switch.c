#include<stdio.h>
int main() {
    int num;
    printf("Enter a number 1-5");
    scanf("%d",&num);
    switch (num)
    {
    case 1:
        printf("pizza");
        break;
    case 2:

    
        printf("cold coffie");
        break;
    case 3:
         print("tea");
         break;
    default:
        printf("Invalid num");
        break;

    }
    return 0;
}



// #include <stdio.h>

// int main() {
//     int num;
//     if(num==1) {
//         printf("pizza");
//     } else if(num == 2) {
//         printf("Burger");
//     }else if(num== 3) {
//         printf("Cold coffie");
//     }else if(num == 4) {
//         printf("tea");
//     } else{
//         printf("invalid num");
//     }
//     return 0;
// }