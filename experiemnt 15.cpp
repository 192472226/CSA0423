/*
 * two_level_directory.c
 *
 * Two-Level Directory Structure Simulation
 * Fully debugged for Dev-C++ (MinGW)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 10
#define MAX_FILES 50
#define NAME_LEN 30
#define LINE_BUF 100

/* User Directory Structure */
struct UserDirectory {
    char uname[NAME_LEN];
    char fname[MAX_FILES][NAME_LEN];
    int file_count;
};

/* Function to read a line safely */
void read_line(char *buf, int size) {
    if (fgets(buf, size, stdin) != NULL) {
        int len = strlen(buf);
        if (len > 0 && buf[len-1] == '\n')
            buf[len-1] = '\0';
    }
}

/* Trim leading/trailing spaces */
void trim(char *s) {
    int i;
    while (*s == ' ' || *s == '\t') s++;

    for (i = strlen(s) - 1; i >= 0 && (s[i]==' ' || s[i]=='\t'); i--)
        s[i] = '\0';
}

int main() {
    struct UserDirectory dir[MAX_USERS];
    int user_count = 0;

    char line[LINE_BUF];
    char username[NAME_LEN];
    char filename[NAME_LEN];

    int choice, i, j, k, found_user, found_file;

    while (1) {
        printf("\n===============================\n");
        printf(" Two-Level Directory Structure\n");
        printf("===============================\n");
        printf("1. Create User Directory\n");
        printf("2. Create File in User Directory\n");
        printf("3. Delete File from User Directory\n");
        printf("4. Search File in User Directory\n");
        printf("5. Display Files of a User\n");
        printf("6. Display All Users & Files\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        read_line(line, sizeof(line));
        choice = atoi(line);

        switch(choice) {

        /* Create User Directory */
        case 1:
            if (user_count == MAX_USERS) {
                printf("Maximum user directories created!\n");
                break;
            }

            printf("Enter new user name: ");
            read_line(username, sizeof(username));
            trim(username);

            /* Check duplicate user */
            for (i = 0, found_user = 0; i < user_count; i++) {
                if (strcmp(username, dir[i].uname) == 0) {
                    found_user = 1;
                    break;
                }
            }

            if (found_user)
                printf("User '%s' already exists!\n", username);
            else {
                strcpy(dir[user_count].uname, username);
                dir[user_count].file_count = 0;
                user_count++;
                printf("User directory '%s' created.\n", username);
            }
            break;

        /* Create File */
        case 2:
            printf("Enter user name: ");
            read_line(username, sizeof(username));
            trim(username);

            /* Find user */
            found_user = -1;
            for (i = 0; i < user_count; i++) {
                if (strcmp(username, dir[i].uname) == 0) {
                    found_user = i;
                    break;
                }
            }

            if (found_user == -1) {
                printf("User not found!\n");
                break;
            }

            if (dir[found_user].file_count == MAX_FILES) {
                printf("File limit reached for this user!\n");
                break;
            }

            printf("Enter file name to create: ");
            read_line(filename, sizeof(filename));
            trim(filename);

            /* Check duplicate file */
            for (j = 0, found_file = 0; j < dir[found_user].file_count; j++) {
                if (strcmp(filename, dir[found_user].fname[j]) == 0) {
                    found_file = 1;
                    break;
                }
            }

            if (found_file)
                printf("File '%s' already exists for user '%s'!\n",
                       filename, username);
            else {
                strcpy(dir[found_user].fname[dir[found_user].file_count], filename);
                dir[found_user].file_count++;
                printf("File '%s' created under user '%s'.\n",
                       filename, username);
            }
            break;

        /* Delete File */
        case 3:
            printf("Enter user name: ");
            read_line(username, sizeof(username));
            trim(username);

            /* Find user */
            found_user = -1;
            for (i = 0; i < user_count; i++) {
                if (strcmp(username, dir[i].uname) == 0) {
                    found_user = i;
                    break;
                }
            }

            if (found_user == -1) {
                printf("User not found!\n");
                break;
            }

            printf("Enter file name to delete: ");
            read_line(filename, sizeof(filename));
            trim(filename);

            /* Delete file */
            found_file = -1;
            for (j = 0; j < dir[found_user].file_count; j++) {
                if (strcmp(filename, dir[found_user].fname[j]) == 0) {
                    found_file = j;
                    break;
                }
            }

            if (found_file == -1) {
                printf("File not found!\n");
            } else {
                for (k = found_file; k < dir[found_user].file_count - 1; k++)
                    strcpy(dir[found_user].fname[k],
                           dir[found_user].fname[k+1]);
                dir[found_user].file_count--;
                printf("File '%s' deleted.\n", filename);
            }
            break;

        /* Search File */
        case 4:
            printf("Enter user name: ");
            read_line(username, sizeof(username));
            trim(username);

            found_user = -1;
            for (i = 0; i < user_count; i++) {
                if (strcmp(username, dir[i].uname) == 0) {
                    found_user = i;
                    break;
                }
            }

            if (found_user == -1) {
                printf("User not found!\n");
                break;
            }

            printf("Enter file name to search: ");
            read_line(filename, sizeof(filename));
            trim(filename);

            found_file = 0;
            for (j = 0; j < dir[found_user].file_count; j++) {
                if (strcmp(filename, dir[found_user].fname[j]) == 0) {
                    found_file = 1;
                    break;
                }
            }

            if (found_file)
                printf("File '%s' found under user '%s'.\n",
                       filename, username);
            else
                printf("File '%s' NOT found.\n", filename);
            break;

        /* Display Files of One User */
        case 5:
            printf("Enter user name: ");
            read_line(username, sizeof(username));
            trim(username);

            found_user = -1;
            for (i = 0; i < user_count; i++) {
                if (strcmp(username, dir[i].uname) == 0) {
                    found_user = i;
                    break;
                }
            }

            if (found_user == -1) {
                printf("User not found!\n");
                break;
            }

            printf("\nUser: %s\n", username);
            if (dir[found_user].file_count == 0)
                printf("  No files.\n");
            else {
                for (j = 0; j < dir[found_user].file_count; j++)
                    printf("  %d. %s\n", j+1, dir[found_user].fname[j]);
            }
            break;

        /* Display All Users & Their Files */
        case 6:
            printf("\n--- All Users & Files ---\n");
            for (i = 0; i < user_count; i++) {
                printf("\nUser: %s\n", dir[i].uname);
                if (dir[i].file_count == 0)
                    printf("  (No files)\n");
                else {
                    for (j = 0; j < dir[i].file_count; j++)
                        printf("  %d. %s\n", j+1, dir[i].fname[j]);
                }
            }
            break;

        case 7:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

