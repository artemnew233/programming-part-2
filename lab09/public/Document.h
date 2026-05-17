#pragma once
#include <string>

class Document {
public:
    explicit Document(std::string title = "", std::string author = "");
    virtual ~Document() = default;
    virtual std::string getTitle() const;
    virtual std::string getAuthor() const;
    virtual void info() const;
    virtual std::string describe() const;
protected:
    std::string title_;
    std::string author_;
};
