 #include <stdio.h>
#include <string.h>

#define MAX 50

struct Directory {
    char dname[20];
    char fname[20][20];
    int fcount;
} dir;

int main() {
    int choice;
    char name[20];

    strcpy(dir.dname, "root");
    dir.fcount = 0;

    while (1) {
        printf("\nSingle Level Directory");
        printf("\n1. Create File");
        printf("\n2. Delete File");
        printf("\n3. Search File");
        printf("\n4. Display Files");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (dir.fcount == MAX) {
                    printf("Directory full\n");
                    break;
                }
                printf("Enter file name: ");
                scanf("%s", name);
                for (int i = 0; i < dir.fcount; i++) {
                    if (strcmp(name, dir.fname[i]) == 0) {
                        printf("File already exists\n");
                        goto skip1;
                    }
                }
                strcpy(dir.fname[dir.fcount], name);
                dir.fcount++;
                printf("File created\n");
                skip1:
                break;

            case 2:
                printf("Enter file name to delete: ");
                scanf("%s", name);
                for (int i = 0; i < dir.fcount; i++) {
                    if (strcmp(name, dir.fname[i]) == 0) {
                        strcpy(dir.fname[i], dir.fname[dir.fcount - 1]);
                        dir.fcount--;
                        printf("File deleted\n");
                        goto skip2;
                    }
                }
                printf("File not found\n");
                skip2:
                break;

            case 3:
                printf("Enter file name to search: ");
                scanf("%s", name);
                for (int i = 0; i < dir.fcount; i++) {
                    if (strcmp(name, dir.fname[i]) == 0) {
                        printf("File found\n");
                        goto skip3;
                    }
                }
                printf("File not found\n");
                skip3:
                break;

            case 4:
                if (dir.fcount == 0) {
                    printf("Directory is empty\n");
                } else {
                    printf("Directory: %s\n", dir.dname);
                    for (int i = 0; i < dir.fcount; i++)
                        printf("%s\n", dir.fname[i]);
                }
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}
