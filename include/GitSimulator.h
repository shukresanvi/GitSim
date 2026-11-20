
#ifndef GITSIMULATOR_H
#define GITSIMULATOR_H

#include "VersionControl.h"
#include "Repository.h"

class GitSimulator : public VersionControl {

private:

    Repository repository;

public:

    void initialize() override;
    void createCommit(const std::string& message) override;

void displayHistory() const override;

void restoreVersion(const std::string& commitID) override;

    void createFile(
        const std::string& filename,
        const std::string& content
    ) override;

    void addFile(
        const std::string& filename
    ) override;

    void displayStatus() const override;

};

#endif

