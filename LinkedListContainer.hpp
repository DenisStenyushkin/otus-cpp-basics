#pragma once

#include "IContainer.hpp"

template<typename T>
class LinkedListContainer : public IContainer<T>
{
private:
    struct Node
    {
        Node* next;
        T value;
    };

    Node* head;

    Node* findLastElement() {
        Node * ptr = head;
        if (ptr == nullptr) return nullptr;

        while (ptr->next != nullptr) {
            ptr = ptr->next;
        }
        
        return ptr;
    }

    Node* findElementBeforePos(size_t pos) {
        if (pos == 0) return nullptr;
        
        Node * ptr = head;

        while ((ptr != nullptr) && (pos > 1))
        {
            ptr = ptr->next;
            --pos;
        }
        
        return ptr;
    }
public:
    // template<typename T>
    struct Iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        explicit Iterator() : m_ptr{nullptr} {}
        explicit Iterator(Node* ptr) : m_ptr{ptr} {}

        reference operator*() {
            return m_ptr->value;
        }

        pointer operator->() {
            return &(m_ptr->value);
        }

        Iterator& operator++() {
            m_ptr = m_ptr->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator t = *this;
            m_ptr = m_ptr->next;
            return t;
        }

        friend bool operator==(const Iterator& it1, const Iterator& it2) {
            return it1.m_ptr == it2.m_ptr;
        }

        friend bool operator!=(const Iterator& it1, const Iterator& it2) {
            return it1.m_ptr != it2.m_ptr;
        }

    private:
        Node* m_ptr;
    };
    

    LinkedListContainer() : head{nullptr} {}
    
    ~LinkedListContainer() override {
        Node* ptr = head;

        while (ptr != nullptr) {
            Node* t = ptr->next;
            delete ptr;
            ptr = t;
        }
    }

    void push_back(const T& v) override {
        Node* last = findLastElement();
        Node* t = new Node{nullptr, v};

        if (last != nullptr) last->next = t;
        else head = t;
    }

    void insert(size_t pos, const T& v) override {
        Node* elemBefore = findElementBeforePos(pos);

        if (elemBefore != nullptr) {
            Node* t = new Node{elemBefore->next, v};
            elemBefore->next = t;
        } else if (pos == 0) {
            head = new Node{head, v};
        }
        // Иначе - позиция и позиция-перед не существуют, вставить туда нельзя.
    }

    void erase(size_t pos) override {
        Node* elemBefore = findElementBeforePos(pos);

        if ((elemBefore != nullptr) && (elemBefore->next != nullptr)) {
            Node* t = elemBefore->next;
            elemBefore->next = elemBefore->next->next;
            delete t;
        } else if ((elemBefore == nullptr) && (pos == 0)) {
            Node* t = head;
            head = head->next;
            delete t;
        }
        // Иначе элемент не существует и удалять нечего
    }

    size_t size() const override {
        size_t cntr = 0;
        Node* ptr = head;

        while (ptr != nullptr) {
            ptr = ptr->next;
            ++cntr;
        }

        return cntr;
    }

    T& operator[](size_t pos) override {
        if ((pos == 0) && head != nullptr) {
            return head->value;
        }
        Node* t = findElementBeforePos(pos);
        return t->next->value;
    }

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};
