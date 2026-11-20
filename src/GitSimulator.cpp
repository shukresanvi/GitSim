
#include "../include/GitSimulator.h"

#include <iostream>

using namespace std;


// Initialize repository
void GitSimulator::initialize() {

    if (repository.initialize()) {

        cout << "\nRepository initialized successfully!\n";

    }
    else {

        cout << "\nRepository initialization failed!\n";

    }

}


// Create file
void GitSimulator::createFile(
    const string& filename,
    const string& content
) {

    if (repository.createFile(filename, content)) {

        cout << "\nFile created successfully: "
             << filename << "\n";

    }
    else {

        cout << "\nCould not create file.\n";

        cout << "Initialize the repository first, "
             << "or check the filename and existing files.\n";

    }

}


// Add file
void GitSimulator::addFile(
    const string& filename
) {

    if (repository.stageFile(filename)) {

        cout << "\nFile added to staging area: "
             << filename << "\n";

    }
    else {

        cout << "\nCould not stage the file.\n";

        cout << "Check whether the file exists "
             << "and the repository is initialized.\n";

    }

}


// Display status
void GitSimulator::displayStatus() const {

    repository.displayStatus();

}

void GitSimulator::createCommit(const string& message) {

    repository.createCommit(message);

}


void GitSimulator::displayHistory() const {

    repository.displayHistory();

}


void GitSimulator::restoreVersion(const string& commitID) {

    repository.restoreCommit(commitID);

}
