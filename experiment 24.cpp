#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    int choice;
    char filename[100], text[500];
    fstream file;

    while (1) {
        cout << "\n--- FILE MANAGEMENT MENU ---\n";
        cout << "1. Create a file\n";
        cout << "2. Write to file\n";
        cout << "3. Read from file\n";
        cout << "4. Delete a file\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear input buffer

        switch (choice) {

        case 1:
            cout << "Enter file name to create: ";
            cin.getline(filename, 100);

            file.open(filename, ios::out);
            if (file) {
                cout << "File created successfully.\n";
            } else {
                cout << "Error creating file.\n";
            }
            file.close();
            break;

        case 2:
            cout << "Enter file name to write: ";
            cin.getline(filename, 100);

            file.open(filename, ios::out | ios::app);
            if (!file) {
                cout << "File does not exist.\n";
                break;
            }

            cout << "Enter text to write: ";
            cin.getline(text, 500);
            file << text << endl;

            cout << "Data written successfully.\n";
            file.close();
            break;

        case 3:
            cout << "Enter file name to read: ";
            cin.getline(filename, 100);

            file.open(filename, ios::in);
            if (!file) {
                cout << "File not found.\n";
                break;
            }

            cout << "\n--- File Content ---\n";
            while (file.getline(text, 500)) {
                cout << text << endl;
            }
            file.close();
            break;

        case 4:
            cout << "Enter file name to delete: ";
            cin.getline(filename, 100);

            if (remove(filename) == 0)
                cout << "File deleted successfully.\n";
            else
                cout << "Error deleting file.\n";

            break;

        case 5:
            cout << "Exiting...\n";
            return 0;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}

