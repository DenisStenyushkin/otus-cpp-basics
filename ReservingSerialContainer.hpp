#pragma once

#include <cmath>
#include "SerialContainer.hpp"


template<typename T>
class ReservingSerialContainer : public SerialContainer<T> {
private:
    float reserve_scale;

protected:
    size_t capacity;

    void allocate_new_storage() override {
        if (this->sz == capacity) {
            capacity = capacity == 0
                       ? 1
                       : std::ceil(capacity * reserve_scale);
            T* new_elems = new T[capacity];

            for (size_t i = 0; i < this->sz; ++i) {
                new_elems[i] = this->elems[i];
            }

            delete [] this->elems;
            this->elems = new_elems;
        }

        ++this->sz;
    }

    void trim_storage() override {
        // Просто уменьшаем размер задействованной части не трогая выделенную память
        --this->sz;
    }

public:
    explicit ReservingSerialContainer(float reserve_scale) : SerialContainer<T>{}, reserve_scale{reserve_scale} {
        capacity = 0;
    }

    ~ReservingSerialContainer() override {
        delete [] this->elems;
        this->elems = nullptr;
        this->sz = 0;
        capacity = 0;
    }
};
