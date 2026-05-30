#pragma once
#include <iostream>
#include <string>

struct Message {
    int         id{};
    std::string sender;
    std::string content;
    bool        read{false};

    Message() = default;
    Message(int id, std::string sender, std::string content, bool read = false)
        : id(id), sender(std::move(sender)),
          content(std::move(content)), read(read) {}

    void print() const {
        std::cout << "  [" << id << "] " << sender << ": " << content
                  << (read ? " (read)" : " (unread)") << '\n';
    }
};
