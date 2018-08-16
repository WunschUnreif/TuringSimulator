#ifndef __FILE_H
#define __FILE_H
#include "inc.h"

class File {
protected:
    std::vector<std::string> lines;

    std::vector<std::string>::iterator lineIterator;
    std::string::iterator charIterator;

public:
    explicit File(const std::string& fileName);

    void reset();

    void next();
    void prev();
    char& getch();

    bool atHead();
    bool atTail();

    int lineNum();
    int colNum();
};

class ProgFile: public File {
public:
    explicit ProgFile(const std::string& fileName);
    
    std::string readToken();
    char readChar();
    bool readStructureChar(char ch);
};

#endif // !__FILE_H