
#ifndef VERSIONCONTROL_H
#define VERSIONCONTROL_H

#include <string>
using namespace std;

class VersionControl {

public:

    virtual void initialize() = 0;

    virtual void createFile(
        const string& filename,
        const string& content
    ) = 0;

    virtual void addFile(
        const string& filename
    ) = 0;

    virtual void displayStatus() const = 0;
    virtual void createCommit(const string& message) = 0;

virtual void displayHistory() const = 0;

virtual void restoreVersion(const string& commitID) = 0;

    virtual ~VersionControl() = default;
};

#endif
