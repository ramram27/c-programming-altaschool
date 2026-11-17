#include <stdio.h>

int main() {
    char arr[100];
    int digits = 0, special = 0,alph=0;

    printf("Enter a string: ");
    scanf("%99s", arr);

    for(int i = 0; arr[i] != '\0'; i++) {
        if(arr[i] >= '0' && arr[i] <= '9') {
            digits++;
        }
        else if(((arr[i] >= 'A' && arr[i] <= 'Z') ||
                  (arr[i] >= 'a' && arr[i] <= 'z'))) {
            alph++;
        } else{
            special++;
        }
    }

    printf("Digits = %d\n", digits);
    printf("Special Characters = %d\n", special);
    printf("alphbate Characters = %d\n", alph);

    return 0;
}