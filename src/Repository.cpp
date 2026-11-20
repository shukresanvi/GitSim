
#include "../include/Repository.h"
#include "../include/FileManager.h"

#include <iostream>

using namespace std;

Repository::Repository() {

    repositoryPath = "data/repository";

    workingDirectory = repositoryPath / "working";

    initialized = false;
}


// Validate filename to prevent directory traversal
bool Repository::isValidFilename(
    const string& filename
) const {

    if (filename.empty()) {
        return false;
    }

    filesystem::path p(filename);

    return p.filename().string() == filename
        && filename != "."
        && filename != "..";
}


// Initialize repository
bool Repository::initialize() {

    try {

        filesystem::create_directories(workingDirectory);

        initialized = true;

        return true;

    }
    catch (const filesystem::filesystem_error&) {

        return false;

    }
}


// Create a new file
bool Repository::createFile(
    const string& filename,
    const string& content
) {

    if (!initialized || !isValidFilename(filename)) {
        return false;
    }

    filesystem::path filePath =
        workingDirectory / filename;

    if (filesystem::exists(filePath)) {
        return false;
    }

    return FileManager::createFile(filePath, content);
}


// Add file to staging area
bool Repository::stageFile(
    const string& filename
) {

    if (!initialized || !isValidFilename(filename)) {
        return false;
    }

    filesystem::path filePath =
        workingDirectory / filename;

    string content;

    if (!FileManager::readFile(filePath, content)) {
        return false;
    }

    // Check whether file is already staged
    StagedFile* existingFile = stagingArea.find(
        [&](const StagedFile& file) {
            return file.filename == filename;
        }
    );

    if (existingFile != nullptr) {

        // Update staged content
        existingFile->content = content;

    }
    else {

        // Insert new staged file
        StagedFile newFile;

        newFile.filename = filename;
        newFile.content = content;

        stagingArea.append(newFile);

    }

    return true;
}


// Display staging status
void Repository::displayStatus() const {

    cout << "\n========== REPOSITORY STATUS ==========\n";

    if (stagingArea.isEmpty()) {

        cout << "No files currently staged.\n";

    }
    else {

        cout << "\nFiles ready to be committed:\n";

        stagingArea.forEach(
            [](const StagedFile& file) {

                cout << "  [STAGED] "
                     << file.filename << "\n";

            }
        );

    }

    cout << "\nTotal staged files: "
         << stagingArea.size() << "\n";

    cout << "=======================================\n";

}

bool Repository::createCommit(const string& message) {

    if (!initialized) {

        cout << "\nInitialize repository first.\n";

        return false;

    }

    if (message.empty()) {

        cout << "\nCommit message cannot be empty.\n";

        return false;

    }

    if (stagingArea.isEmpty()) {

        cout << "\nNo changes to commit.\n";

        return false;

    }

    // Start with the previous commit's snapshot
    unordered_map<string, string> snapshot =
        commitHistory.getLatestSnapshot();

    // Apply newly staged files
    stagingArea.forEach(
        [&](const StagedFile& file) {

            snapshot[file.filename] = file.content;

        }
    );

    // Create a new commit
    Commit newCommit(message, snapshot);

    // Store it in commit history
    commitHistory.addCommit(newCommit);

    cout << "\nCommit created successfully!\n";

    cout << "Commit ID: "
         << newCommit.getID() << "\n";

    cout << "Message: "
         << newCommit.getMessage() << "\n";

    // Clear staging after successful commit
    stagingArea.clear();

    return true;

}
void Repository::displayHistory() const {

    commitHistory.displayHistory();

}

bool Repository::restoreCommit(const string& commitID) {

    if (!initialized) {

        cout << "\nInitialize repository first.\n";

        return false;

    }

    // Search for the requested commit
    Commit* targetCommit =
        commitHistory.findCommit(commitID);

    if (targetCommit == nullptr) {

        cout << "\nCommit not found!\n";

        return false;

    }

    // Obtain the saved snapshot
    const auto& snapshot = targetCommit->getSnapshot();

    try {

        // Remove current files from working directory
        for (const auto& entry :
             filesystem::directory_iterator(workingDirectory)) {

            if (entry.is_regular_file()) {

                filesystem::remove(entry.path());

            }

        }

        // Recreate files from the selected snapshot
        for (const auto& file : snapshot) {

            filesystem::path filePath =
                workingDirectory / file.first;

            if (!FileManager::createFile(
                    filePath,
                    file.second
                )) {

                cout << "\nCould not restore file: "
                     << file.first << "\n";

                return false;

            }

        }

        // Clear staged changes
        stagingArea.clear();

        cout << "\nVersion restored successfully!\n";

        cout << "Restored Commit: "
             << commitID << "\n";

        return true;

    }
    catch (const filesystem::filesystem_error&) {

        cout << "\nFilesystem error during restoration.\n";

        return false;

    }

}
