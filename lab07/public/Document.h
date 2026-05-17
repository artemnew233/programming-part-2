#pragma once
#include <string>
#include <ctime>

class Document {
public:
    Document(std::string title, std::string author, std::time_t created = std::time(nullptr));
    virtual ~Document() = default;

    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    std::time_t getCreatedAt() const;

    virtual std::string getType() const;
    virtual std::string summary() const;
    void printInfo() const;

protected:
    std::string title_;
    std::string author_;
    std::time_t createdAt_;
};
