#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char filename[100], pattern[100], line[500];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    printf("Enter search pattern: ");
    scanf("%s", pattern);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    printf("\nLines containing '%s':\n\n", pattern);

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, pattern) != NULL) {  
            printf("%s", line);  // Print the matching line
        }
    }

    fclose(fp);
    return 0;
}
