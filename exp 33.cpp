#include <stdio.h>

int main() {
    int frames, pages, page[50], frame[10], i, j, k, faults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter page reference string: ");
    for (i = 0; i < pages; i++)
        scanf("%d", &page[i]);

    for (i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (i = 0; i < pages; i++) {
        int found = 0;

        for (j = 0; j < frames; j++)
            if (frame[j] == page[i])
                found = 1;

        if (!found) {
            int pos[10];

            for (j = 0; j < frames; j++) {
                pos[j] = -1;
                for (k = i + 1; k < pages; k++) {
                    if (frame[j] == page[k]) {
                        pos[j] = k;
                        break;
                    }
                }
            }

            int replace = 0;
            for (j = 1; j < frames; j++)
                if (pos[j] > pos[replace])
                    replace = j;

            frame[replace] = page[i];
            faults++;
        }

        printf("Page %d -> ", page[i]);
        for (j = 0; j < frames; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}
