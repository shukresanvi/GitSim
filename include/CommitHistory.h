
#ifndef COMMITHISTORY_H
#define COMMITHISTORY_H

#include "LinkedList.h"
#include "Commit.h"

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class CommitHistory {

private:

    // Custom linked list stores Commit objects
    LinkedList<Commit> commits;

public:

    // Add a new commit
    void addCommit(const Commit& commit) {

        commits.append(commit);

    }

    // Find commit using its ID
    Commit* findCommit(const string& id) {

        return commits.find(
            [&](const Commit& commit) {

                return commit.getID() == id;

            }
        );

    }

    // Check whether history is empty
    bool isEmpty() const {

        return commits.isEmpty();

    }

    // Display all commits
    void displayHistory() const {

        if (commits.isEmpty()) {

            cout << "\nNo commits available.\n";

            return;

        }

        cout << "\n========== COMMIT HISTORY ==========\n";

        commits.forEach(
            [](const Commit& commit) {

                cout << "\nCommit ID: "
                     << commit.getID();

                cout << "\nMessage: "
                     << commit.getMessage();

                cout << "\nDate: "
                     << commit.getTimestamp();

                cout << "\n------------------------------------\n";

            }
        );

    }

    // Get the latest commit snapshot
    unordered_map<string, string> getLatestSnapshot() const {

        unordered_map<string, string> snapshot;

        commits.forEach(
            [&](const Commit& commit) {

                snapshot = commit.getSnapshot();

            }
        );

        return snapshot;

    }

};

#endif
