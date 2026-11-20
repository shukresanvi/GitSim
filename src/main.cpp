
#include <iostream>
#include <string>
#include <limits>

#include "../include/GitSimulator.h"
#include "../include/VersionControl.h"

using namespace std;

int main() {

    GitSimulator simulator;

    // Demonstrating runtime polymorphism
    VersionControl& system = simulator;

    int choice;

    string filename;
    string content;

    cout << "\n";
    cout << "====================================\n";
    cout << "       GITSIM - VERSION CONTROL      \n";
    cout << "====================================\n";

    do {

        cout << "\n------------- MAIN MENU -------------\n";

        cout << "1. Initialize Repository\n";
        cout << "2. Create File\n";
        cout << "3. Add File to Staging Area\n";
        cout << "4. View Repository Status\n";
        cout << "5. Create Commit\n";
        cout << "6. View Commit History\n";
        cout << "7. Restore Previous Version\n";
        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "\nInvalid input. Enter a number.\n";

            continue;

        }

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );


        switch (choice) {

            case 1:

                system.initialize();

                break;


            case 2:

                cout << "\nEnter filename: ";

                getline(cin, filename);

                cout << "Enter file content: ";

                getline(cin, content);

                system.createFile(filename, content);

                break;


            case 3:

                cout << "\nEnter filename to add: ";

                getline(cin, filename);

                system.addFile(filename);

                break;


            case 4:

                system.displayStatus();

                break;

case 5:

    cout << "\nEnter commit message: ";

    getline(cin, content);

    system.createCommit(content);

    break;


case 6:

    system.displayHistory();

    break;


case 7:

    cout << "\nEnter Commit ID to restore: ";

    getline(cin, filename);

    system.restoreVersion(filename);

    break;



            case 0:

                cout << "\nExiting GitSim. Goodbye!\n";

                break;


            default:

                cout << "\nInvalid choice. Try again.\n";

        }

    } while (choice != 0);


    return 0;

}
