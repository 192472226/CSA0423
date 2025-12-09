#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createFile();
void writeFile();
void readFile();
void appendFile();
void deleteFile();

int main() {
    int choice;

    while (1) {
        printf("\n====== FILE MANAGEMENT SYSTEM ======\n");
        printf("1. Create File\n");
        printf("2. Write to File\n");
        printf("3. Read File\n");
        printf("4. Append to File\n");
        printf("5. Delete File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1: createFile(); break;
            case 2: writeFile(); break;
            case 3: readFile(); break;
            case 4: appendFile(); break;
            case 5: deleteFile(); break;
            case 6: exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void createFile() {
    char filename[100];
    FILE *fp;

    printf("Enter file name to create: ");
    scanf("%s", filename);

    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error creating file.\n");
        return;
    }

    printf("File '%s' created successfully.\n", filename);
    fclose(fp);
}

void writeFile() {
    char filename[100], data[500];
    FILE *fp;

    printf("Enter file name to write to: ");
    scanf("%s", filename);
    getchar();

    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter text to write (end with ENTER):\n");
    fgets(data, 500, stdin);

    fputs(data, fp);
    printf("Data written to file.\n");

    fclose(fp);
}

void readFile() {
    char filename[100], ch;
    FILE *fp;

    printf("Enter file name to read: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File not found or unable to open.\n");
        return;
    }

    printf("\n--- File Contents ---\n");
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    printf("\n----------------------\n");

    fclose(fp);
}

void appendFile() {
    char filename[100], data[500];
    FILE *fp;

    printf("Enter file name to append to: ");
    scanf("%s", filename);
    getchar();

    fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter text to append:\n");
    fgets(data, 500, stdin);

    fputs(data, fp);
    printf("Data appended to file.\n");

    fclose(fp);
}

void deleteFile() {
    char filename[100];

    printf("Enter file name to delete: ");
    scanf("%s", filename);

    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        printf("Error deleting file. File may not exist.\n");
    }
}
