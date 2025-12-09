#include <stdio.h>

int main() {
    int frames, pages, page[50], frame[10], use[10], i, j, faults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter page reference string: ");
    for (i = 0; i < pages; i++)
        scanf("%d", &page[i]);

    for (i = 0; i < frames; i++) {
        frame[i] = -1;
        use[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");

    for (i = 0; i < pages; i++) {
        int found = 0;

        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                found = 1;
                use[j] = i + 1;
                break;
            }
        }

        if (!found) {
            int min = 0;
            for (j = 1; j < frames; j++)
                if (use[j] < use[min])
                    min = j;

            frame[min] = page[i];
            use[min] = i + 1;
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
