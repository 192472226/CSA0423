#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m];

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Maximum Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    int finish[n], safeSeq[n], index = 0;

    for (i = 0; i < n; i++)
        finish[i] = 0;

    int need[n][m];

    // Calculate NEED matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Banker's Algorithm
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 0;

                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    // process can be allocated
                    safeSeq[index++] = i;
                    for (j = 0; j < m; j++)
                        avail[j] += alloc[i][j];

                    finish[i] = 1;
                }
            }
        }
    }

    // Check if all processes completed
    int flag = 1;
    for (i = 0; i < n; i++) {
        if (finish[i] == 0) {
            flag = 0;
            printf("\nSystem is in UNSAFE state! Deadlock may occur.\n");
            break;
        }
    }

    if (flag == 1) {
        printf("\nSystem is in SAFE state.\nSafe Sequence: ");
        for (i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    }

    return 0;
}

