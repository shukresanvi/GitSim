
#ifndef COMMIT_H
#define COMMIT_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

class Commit {

private:
    string commitID;
    string message;
    string timestamp;
    string parentCommitID;

    // Complete snapshot of project files
    unordered_map<string, string> fileSnapshot;

    // Generates unique commit IDs
    inline static int nextID = 1;

    // Generate current timestamp
    string getCurrentTime() {
        time_t now = time(nullptr);
        tm* localTime = localtime(&now);

        stringstream ss;
        ss << put_time(localTime, "%d-%m-%Y %H:%M:%S");

        return ss.str();
    }

public:
    // Constructor
    Commit(
        const string& msg,
        const unordered_map<string, string>& snapshot,
        const string& parentID = ""
    ) {
        stringstream ss;

        ss << "C"
           << setw(3)
           << setfill('0')
           << nextID++;

        commitID = ss.str();
        message = msg;
        timestamp = getCurrentTime();
        fileSnapshot = snapshot;
        parentCommitID = parentID;
    }

    string getID() const {
        return commitID;
    }

    string getMessage() const {
        return message;
    }

    string getTimestamp() const {
        return timestamp;
    }

    const unordered_map<string, string>& getSnapshot() const {
        return fileSnapshot;
    }

    string getParentID() const {
        return parentCommitID;
    }
};

#endif
