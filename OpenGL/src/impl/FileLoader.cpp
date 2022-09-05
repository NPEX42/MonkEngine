#include "FileLoader.h"

std::string loadFileToString(char const* const fname)
{
    std::ifstream ifile(fname);
    std::string filetext;

    while (ifile.good()) {
        std::string line;
        std::getline(ifile, line);
        filetext.append(line + "\n");
    }

    return filetext;
}