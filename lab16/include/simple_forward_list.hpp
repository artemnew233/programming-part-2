#pragma once
#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>

template <typename T>
class SimpleForwardList {
private:
    struct Node {
        T     value;
        Node* next{};
    };

    Node*       head_{};
    std::size_t size_{};

public:
    class const_iterator;

    class iterator {
        friend class const_iterator;
        friend class SimpleForwardList;

    public:
        using iterator_concept  = std::forward_iterator_tag;
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        iterator() = default;
        explicit iterator(Node* current) noexcept : current_(current) {}

        reference operator*()  const noexcept { return current_->value; }
        pointer   operator->() const noexcept { return std::addressof(current_->value); }

        iterator& operator++() noexcept {
            current_ = current_->next;
            return *this;
        }
        iterator operator++(int) noexcept {
            iterator old = *this;
            ++(*this);
            return old;
        }

        friend bool operator==(iterator l, iterator r) noexcept { return l.current_ == r.current_; }
        friend bool operator!=(iterator l, iterator r) noexcept { return !(l == r); }

    private:
        Node* current_{};
    };

    class const_iterator {
    public:
        using iterator_concept  = std::forward_iterator_tag;
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator() = default;
        explicit const_iterator(const Node* current) noexcept : current_(current) {}
        const_iterator(iterator it) noexcept : current_(it.current_) {}

        reference operator*()  const noexcept { return current_->value; }
        pointer   operator->() const noexcept { return std::addressof(current_->value); }

        const_iterator& operator++() noexcept {
            current_ = current_->next;
            return *this;
        }
        const_iterator operator++(int) noexcept {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        friend bool operator==(const_iterator l, const_iterator r) noexcept { return l.current_ == r.current_; }
        friend bool operator!=(const_iterator l, const_iterator r) noexcept { return !(l == r); }

    private:
        const Node* current_{};
    };

    SimpleForwardList() = default;

    SimpleForwardList(const SimpleForwardList& other) { copy_from(other); }

    SimpleForwardList(SimpleForwardList&& other) noexcept
        : head_(other.head_), size_(other.size_) {
        other.head_ = nullptr;
        other.size_ = 0;
    }

    SimpleForwardList& operator=(SimpleForwardList other) noexcept {
        swap(other);
        return *this;
    }

    ~SimpleForwardList() { clear(); }

    void swap(SimpleForwardList& other) noexcept {
        using std::swap;
        swap(head_, other.head_);
        swap(size_, other.size_);
    }

    [[nodiscard]] bool        empty() const noexcept { return head_ == nullptr; }
    [[nodiscard]] std::size_t size()  const noexcept { return size_; }

    T& front() {
        if (empty()) throw std::out_of_range("SimpleForwardList::front");
        return head_->value;
    }
    const T& front() const {
        if (empty()) throw std::out_of_range("SimpleForwardList::front");
        return head_->value;
    }

    void push_front(const T& value) {
        head_ = new Node{value, head_};
        ++size_;
    }
    void push_front(T&& value) {
        head_ = new Node{std::move(value), head_};
        ++size_;
    }

    template <typename... Args>
    T& emplace_front(Args&&... args) {
        head_ = new Node{T(std::forward<Args>(args)...), head_};
        ++size_;
        return head_->value;
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("SimpleForwardList::pop_front");
        Node* old = head_;
        head_     = head_->next;
        delete old;
        --size_;
    }

    template <typename... Args>
    iterator emplace_after(iterator pos, Args&&... args) {
        if (pos.current_ == nullptr)
            throw std::out_of_range("SimpleForwardList::emplace_after");
        Node* cur  = pos.current_;
        cur->next  = new Node{T(std::forward<Args>(args)...), cur->next};
        ++size_;
        return iterator{cur->next};
    }

    iterator insert_after(iterator pos, const T& value) { return emplace_after(pos, value); }
    iterator insert_after(iterator pos, T&& value)      { return emplace_after(pos, std::move(value)); }

    iterator erase_after(iterator pos) {
        if (pos.current_ == nullptr || pos.current_->next == nullptr)
            throw std::out_of_range("SimpleForwardList::erase_after");
        Node* erased      = pos.current_->next;
        pos.current_->next = erased->next;
        delete erased;
        --size_;
        return iterator{pos.current_->next};
    }

    void clear() noexcept {
        while (head_) {
            Node* old = head_;
            head_     = head_->next;
            delete old;
        }
        size_ = 0;
    }

    iterator       begin()  noexcept { return iterator{head_}; }
    iterator       end()    noexcept { return iterator{nullptr}; }
    const_iterator begin()  const noexcept { return const_iterator{head_}; }
    const_iterator end()    const noexcept { return const_iterator{nullptr}; }
    const_iterator cbegin() const noexcept { return const_iterator{head_}; }
    const_iterator cend()   const noexcept { return const_iterator{nullptr}; }

private:
    void copy_from(const SimpleForwardList& other) {
        Node** tail = &head_;
        try {
            for (const T& value : other) {
                *tail = new Node{value, nullptr};
                tail  = &((*tail)->next);
                ++size_;
            }
        } catch (...) {
            clear();
            throw;
        }
    }
};

template <typename T>
void swap(SimpleForwardList<T>& l, SimpleForwardList<T>& r) noexcept { l.swap(r); }

// Compile-time concept checks
static_assert(std::forward_iterator<SimpleForwardList<int>::iterator>);
static_assert(std::forward_iterator<SimpleForwardList<int>::const_iterator>);
static_assert(std::ranges::forward_range<SimpleForwardList<int>>);
