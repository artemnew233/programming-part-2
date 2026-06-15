#pragma once
#include <string>

// Abstract base class — cannot be instantiated directly.
class Document {
public:
    Document(std::string title, std::string author);
    virtual ~Document() = default;

    // Pure virtual — every concrete document must define its type and describe itself
    virtual std::string getType() const = 0;
    virtual std::string describe() const = 0;
    virtual void print() const;

    const std::string& getTitle() const;
    const std::string& getAuthor() const;

protected:
    std::string title_;
    std::string author_;
};
