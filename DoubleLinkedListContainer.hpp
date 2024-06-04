#pragma once

#include "IContainer.hpp"


template<typename T>
class DoubleLinkedListContainer : public IContainer<T>
{
private:
    struct Node
    {
        Node* prev;
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

    Node* findElementAtPos(size_t pos) {
        Node* ptr = head;

        if ((pos == 0) && (head != nullptr)) {
            return head;
        }

        while (ptr != nullptr) {
            ptr = ptr->next;
            pos --;

            if (pos==0) break;
        }
        
        return ptr;
    }

public:
    DoubleLinkedListContainer() : head{nullptr} {}

    ~DoubleLinkedListContainer() override {
        Node* ptr = head;

        while (ptr != nullptr) {
            Node* t = ptr->next;
            delete ptr;
            ptr = t;
        }
    }

    void push_back(const T& v) override {
        Node* last = findLastElement();
        Node* t = new Node{last, nullptr, v};

        if (last != nullptr) last->next = t;
        else head = t;
    }

    void insert(size_t pos, const T& v) override {
        if (pos == 0) {
            Node* t = new Node{nullptr, head, v};
            head = t;
        }
        else {
            Node* elemAtPos = findElementAtPos(pos);
            Node* elemBefore = elemAtPos->prev;

            Node* t = new Node{elemBefore, elemAtPos, v};
            elemBefore->next = t;
            elemAtPos->prev = t;
        }
    }

    void erase(size_t pos) override {
        Node* elem = findElementAtPos(pos);

        if (elem->prev != nullptr) {
            elem->prev->next = elem->next;
        }
        if (elem->next != nullptr) {
            elem->next->prev = elem->prev;
        }

        delete elem;
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
        Node* t = findElementAtPos(pos);
        return t->value;
    }
};
