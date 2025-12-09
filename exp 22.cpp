#include <stdio.h>

int main() {
    int nb, np, i, j;

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);

    int blockSize[nb], blockAlloc[nb];

    printf("Enter size of each block:\n");
    for (i = 0; i < nb; i++) {
        scanf("%d", &blockSize[i]);
        blockAlloc[i] = -1;  // block free initially
    }

    printf("Enter number of processes: ");
    scanf("%d", &np);

    int processSize[np], processAlloc[np];

    printf("Enter size of each process:\n");
    for (i = 0; i < np; i++) {
        scanf("%d", &processSize[i]);
        processAlloc[i] = -1;  // not allocated initially
    }

    // Best Fit Allocation
    for (i = 0; i < np; i++) {
        int bestIndex = -1;

        for (j = 0; j < nb; j++) {
            if (blockAlloc[j] == -1 && blockSize[j] >= processSize[i]) {
                if (bestIndex == -1 || blockSize[j] < blockSize[bestIndex]) {
                    bestIndex = j;
                }
            }
        }

        if (bestIndex != -1) {
            processAlloc[i] = bestIndex;
            blockAlloc[bestIndex] = i;
            blockSize[bestIndex] -= processSize[i];
        }
    }

    // Output
    printf("\nProcess No.\tProcess Size\tBlock Allocated\n");
    for (i = 0; i < np; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (processAlloc[i] != -1)
            printf("%d\n", processAlloc[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}

