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

#include <stdio.h>
int main() {
    int i, j;
    int n = 5;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i == j || j== n-i+1) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
