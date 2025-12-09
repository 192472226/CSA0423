#include <stdio.h>
#include <stdlib.h>

int main() {
    int req[50], n, head, i, total = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter request queue: ");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nFCFS Disk Scheduling:\n");
    printf("Head Movement Order: %d ", head);

    for (i = 0; i < n; i++) {
        total += abs(head - req[i]);
        head = req[i];
        printf("? %d ", head);
    }

    printf("\nTotal Head Movement = %d\n", total);
    return 0;
}

