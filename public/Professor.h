#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>

class Professor {
public:
    Professor(const std::string& name, const std::string& rank);
    std::string getName() const;
    std::string getRank() const;

private:
    std::string name;
    std::string rank;
};

#endif
