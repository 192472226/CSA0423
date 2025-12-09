#include <stdio.h>
#include <stdlib.h>

int main() {
    int req[50], n, head, disk, i, j, total = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter request queue: ");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size: ");
    scanf("%d", &disk);

    // Sort requests
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (req[i] > req[j]) {
                int temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }

    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Head Movement Order: %d ", head);

    // Move right
    for (i = 0; i < n; i++)
        if (req[i] >= head)
            break;

    for (j = i; j < n; j++) {
        total += abs(head - req[j]);
        head = req[j];
        printf("? %d ", head);
    }

    // Jump to beginning
    total += abs((disk - 1) - 0);
    printf("? 0 ");
    head = 0;

    // Continue from left side
    for (j = 0; j < i; j++) {
        total += abs(head - req[j]);
        head = req[j];
        printf("? %d ", head);
    }

    printf("\nTotal Head Movement = %d\n", total);
    return 0;
}
