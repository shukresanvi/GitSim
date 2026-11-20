
#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "CommitHistory.h"
#include <unordered_map>

#include <string>
#include <filesystem>

#include "LinkedList.h"

using namespace std;

struct StagedFile {

    string filename;
    string content;

};

class Repository {


    private:

    std::filesystem::path repositoryPath;
    std::filesystem::path workingDirectory;


    // Custom linked list for staging
    LinkedList<StagedFile> stagingArea;

    CommitHistory commitHistory;

    bool initialized;

    bool isValidFilename(const string& filename) const;

public:

    Repository();

    bool initialize();

    bool createFile(
        const string& filename,
        const string& content
    
    );
    bool createCommit(const std::string& message);

void displayHistory() const;

bool restoreCommit(const std::string& commitID);

    bool stageFile(const string& filename);

    void displayStatus() const;

};

#endif
