#include <stdio.h>

int main()
{
    FILE *fp;

    fp = fopen("data.txt", "w");

    if (fp == NULL)
    {
        printf("File cannot be opened");
        return 1;
    }

    fprintf(fp, "Hello Students!");

    fclose(fp);

    printf("Data written successfully");

    return 0;
}