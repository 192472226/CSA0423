#include <stdio.h>

int main() {
    int indexBlock, n, blocks[50], i;

    printf("Enter index block number: ");
    scanf("%d", &indexBlock);

    printf("Enter number of blocks in file: ");
    scanf("%d", &n);

    printf("Enter block numbers allocated to file:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &blocks[i]);

    printf("\nIndexed File Allocation:\n");
    printf("Index Block ? %d\n", indexBlock);

    printf("Pointers:\n");
    for (i = 0; i < n; i++)
        printf("Index[%d] -> Block %d\n", i, blocks[i]);

    return 0;
}
