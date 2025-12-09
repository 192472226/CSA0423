#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[30];
    float salary;
};

void addEmployee();
void displayEmployees();
void searchEmployee();
void updateEmployee();

int main() {
    int choice;

    while (1) {
        printf("\n===== RANDOM ACCESS FILE - EMPLOYEE DETAILS =====\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Update Employee Salary\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: updateEmployee(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

void addEmployee() {
    FILE *fp;
    struct Employee emp;

    fp = fopen("employee.dat", "ab");
    if (!fp) {
        printf("File cannot be opened!\n");
        return;
    }

    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Name: ");
    scanf("%s", emp.name);
    printf("Enter Salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(emp), 1, fp);
    fclose(fp);

    printf("Employee added successfully!\n");
}

void displayEmployees() {
    FILE *fp;
    struct Employee emp;

    fp = fopen("employee.dat", "rb");
    if (!fp) {
        printf("File not found!\n");
        return;
    }

    printf("\n--- EMPLOYEE LIST ---\n");
    while (fread(&emp, sizeof(emp), 1, fp)) {
        printf("ID: %d | Name: %s | Salary: %.2f\n",
               emp.id, emp.name, emp.salary);
    }

    fclose(fp);
}

void searchEmployee() {
    FILE *fp;
    struct Employee emp;
    int id, found = 0;

    fp = fopen("employee.dat", "rb");
    if (!fp) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Employee ID to Search: ");
    scanf("%d", &id);

    while (fread(&emp, sizeof(emp), 1, fp)) {
        if (emp.id == id) {
            printf("\n--- Employee Found ---\n");
            printf("ID: %d\nName: %s\nSalary: %.2f\n",
                   emp.id, emp.name, emp.salary);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Employee not found!\n");

    fclose(fp);
}

void updateEmployee() {
    FILE *fp;
    struct Employee emp;
    int id, found = 0;

    fp = fopen("employee.dat", "r+b");  // read + write in binary
    if (!fp) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Employee ID to Update Salary: ");
    scanf("%d", &id);

    while (fread(&emp, sizeof(emp), 1, fp)) {
        if (emp.id == id) {
            printf("Current Salary: %.2f\n", emp.salary);
            printf("Enter New Salary: ");
            scanf("%f", &emp.salary);

            // Move file pointer 1 record backward
            fseek(fp, -sizeof(emp), SEEK_CUR);

            fwrite(&emp, sizeof(emp), 1, fp);
            printf("Salary updated successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Employee not found!\n");

    fclose(fp);
}

