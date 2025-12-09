#include <stdio.h>

int main() {
    int start, length, i;

    printf("Enter starting block of file: ");
    scanf("%d", &start);

    printf("Enter number of blocks required: ");
    scanf("%d", &length);

    printf("\nSequential File Allocation:\n");
    printf("Blocks allocated: ");

    for (i = 0; i < length; i++)
        printf("%d ", start + i);

    printf("\nFile is stored in continuous blocks.\n");

    return 0;
}
