#include <stdio.h>

int main()
{
    int arr[5] = {10, 20, 30, 40, 50};

    int *p = arr;

    for(int i = 0; i < 5; i++)
    {
        printf("%d ", (p + i));
    }

    return 0;
}