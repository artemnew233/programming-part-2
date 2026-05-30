#include "DomainTypes.h"

// ── Custom deleter uooooooooooooooo 
void closeMessageQueue(MessageQueueHandle* handle) {
    if (handle) {
        if (handle->open) {
            std::cout << "[MQ] Queue '" << handle->name
                      << "' (id=" << handle->queueId
                      << ") closed via closeMessageQueue\n";
            handle->open = false;
        }
        delete handle;
    }
}

// ── Message Queue 
MessageQueue::MessageQueue(std::string name)
    : name_(std::move(name)),
      handle_(new MessageQueueHandle(42, name_), &closeMessageQueue) {}

void MessageQueue::send(const Message& msg) {
    std::cout << "[MQ:" << name_ << "] Sending: " << msg.content << '\n';
}

void MessageQueue::printHandle() const {
    if (handle_)
        std::cout << "[MQ:" << name_ << "] Handle: id=" << handle_->queueId
                  << " open=" << (handle_->open ? "yes" : "no") << '\n';
}

// ── Chat Message or messages
ChatMessage::ChatMessage(int id, std::string text, std::weak_ptr<ChatRoom> room)
    : id_(id), text_(std::move(text)), room_(std::move(room)) {}

void ChatMessage::print() const {
    auto room = room_.lock();
    std::cout << "  [" << id_ << "] \"" << text_ << "\""
              << (room ? " in #" + room->getName() : " (room gone)") << '\n';
}

// ── Chat Room 
ChatRoom::ChatRoom(std::string name) : name_(std::move(name)) {}

void ChatRoom::addMessage(std::shared_ptr<ChatMessage> msg) {
    messages_.push_back(std::move(msg));
}

void ChatRoom::printMessages() const {
    std::cout << "ChatRoom #" << name_
              << " (" << messages_.size() << " messages):\n";
    for (const auto& m : messages_) m->print();
}
