#ifndef OO1_FILECMDS_H
#define OO1_FILECMDS_H
#include "../Command.h"
#include <fstream>

class FileCmds : public Command {
public:
    void set(std::vector<std::string>, Reader *r) override;

    static bool fileExists(const std::string &s);

protected:
    std::string filename;

    static bool quoted(const std::string &s);

    void validateFileNotFound(const std::string &s) const;

    void validateFileFound(const std::string &s) const;

    bool isBatch = false;
};

#endif //OO1_FILECMDS_H
