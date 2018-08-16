#include "inc.h"

File::File(const std::string& fileName) {
    std::ifstream fin(fileName);

    std::string line;
    while(std::getline(fin, line)) {
        lines.push_back(line + "\n");
    }

    reset();

    fin.close();
}

void File::reset() {
    lineIterator = lines.begin();
    if(lineIterator != lines.end()) {
        charIterator = lineIterator->begin();
    }
}

void File::next() {
    if(lineIterator != lines.end()) {
        ++charIterator;
        if(charIterator == lineIterator->end()) {
            ++lineIterator;
            charIterator = lineIterator->begin();
        }
    } else {
        throw std::out_of_range("File iterator meet end!");
    }
}

void File::prev() {
    if(lineIterator == lines.begin() && charIterator == lineIterator->begin()) {
        throw std::out_of_range("File iterator meet head!");
    }
    if(charIterator == lineIterator->begin()) {
        --lineIterator;
        charIterator = lineIterator->end() - 1;
    } else {
        --charIterator;
    }
}

char& File::getch() {
    return *charIterator;
}

bool File::atHead() {
    return charIterator == lineIterator->begin() && lineIterator == lines.begin();
}

bool File::atTail() {
    return lineIterator == lines.end();
}

int File::lineNum() {
    return lineIterator - lines.begin() + 1;
}

int File::colNum() {
    return charIterator - lineIterator->begin() + 1;
}

ProgFile::ProgFile(const std::string& fileName):
    File(fileName) {}

std::string ProgFile::readToken() {
    std::string token = "";
    char ch;

    while(!atTail() && isspace(ch = getch())) next();
    if(!atTail()) {token += ch; next();}
    while(!atTail() && isalnum(ch = getch())) {
        token += ch;
        next();
    }
    
    return token;
}

char ProgFile::readChar() {
    char ch;

    while(!atTail() && isspace(ch = getch())) next();

    if(atTail()) return 0;
    next();
    return ch;
}

bool ProgFile::readStructureChar(char ch) {
    if(readChar() == ch) return true;
    return false;
}
