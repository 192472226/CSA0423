#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *directory;
    struct dirent *entry;

    // Open current directory
    directory = opendir(".");
    if (directory == NULL) {
        printf("Error: Unable to open directory.\n");
        return 1;
    }

    printf("Contents of current directory:\n\n");

    // Read files one by one
    while ((entry = readdir(directory)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(directory);
    return 0;
}
