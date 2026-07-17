#pragma once
#include "Message.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ── Custom deleter resource 
// MessageQueueHandle represents an OS-level message queue handle.
// It must be released with closeMessageQueue(), not just some plain delete, mhm.
struct MessageQueueHandle {
    int         queueId{};
    std::string name;
    bool        open{false};

    MessageQueueHandle(int id, std::string n)
        : queueId(id), name(std::move(n)), open(true) {
        std::cout << "[MQ] Queue '" << name
                  << "' (id=" << queueId << ") opened\n";
    }
};

// Domain-specific release function — cannot be replaced with plain delete.
void closeMessageQueue(MessageQueueHandle* handle);

// ── Class with std::unique_ptr field (Task 7) comments are cool lolololololololol
class MessageQueue {
public:
    explicit MessageQueue(std::string name);

    // Not copyable — basially unique ownership
    MessageQueue(const MessageQueue&)            = delete;
    MessageQueue& operator=(const MessageQueue&) = delete;
    MessageQueue(MessageQueue&&)                 = default;
    MessageQueue& operator=(MessageQueue&&)      = default;

    void send(const Message& msg);
    void printHandle() const;

private:
    std::string name_;
    std::unique_ptr<MessageQueueHandle,
                    decltype(&closeMessageQueue)> handle_;
};

// ── Shared/weak scenario: ChatRoom / ChatMessage 
class ChatRoom;

class ChatMessage {
public:
    ChatMessage(int id, std::string text, std::weak_ptr<ChatRoom> room);

    int                getId()   const { return id_; }
    const std::string& getText() const { return text_; }
    void print() const;

private:
    int                     id_;
    std::string             text_;
    std::weak_ptr<ChatRoom> room_;
};

class ChatRoom {
public:
    explicit ChatRoom(std::string name);

    void addMessage(std::shared_ptr<ChatMessage> msg);
    void printMessages() const;
    const std::string& getName() const { return name_; }

private:
    std::string                               name_;
    // shared ownership of every ChatMessage
    std::vector<std::shared_ptr<ChatMessage>> messages_;
};

// ── Doubly linked list node (weak_ptr cycle demo)
struct Node {
    int                   value{};
    std::shared_ptr<Node> next;
    std::weak_ptr<Node>   previous; // weak: breaks the reference cycle

    explicit Node(int v) : value(v) {
        std::cout << "[Node] Created:   " << value << '\n';
    }
    ~Node() {
        std::cout << "[Node] Destroyed: " << value << '\n';
    }
};
