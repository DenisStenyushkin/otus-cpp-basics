#pragma once

#include "IContainer.hpp"

template<typename T>
class SerialContainer : public IContainer<T>
{
private:
    T* elems;
    size_t sz;

    void allocate_new_storage() {
        T* new_elems = new T[sz + 1];

        for (size_t i = 0; i < sz; ++i) {
            new_elems[i] = elems[i];
        }

        delete [] elems;
        elems = new_elems;
        ++sz;
    }

    void trim_storage() {
        --sz;
        T* new_elems = new T[sz];

        for (size_t i = 0; i < sz; ++i) {
            new_elems[i] = elems[i];
        }

        delete [] elems;
        elems = new_elems;
    }
public:
    SerialContainer() : elems{nullptr}, sz{0} {}

    ~SerialContainer() override {
        delete [] elems;
        elems = nullptr;
        sz = 0;
    }

    void push_back(const T& v) override {
        allocate_new_storage();
        elems[sz-1] = v;
    }

    void insert(size_t pos, const T& v) override {
        allocate_new_storage();
        for (size_t i = sz - 2; i >= pos; --i) {
            elems[i+1] = elems[i];

            if (i == 0) break;
        }
        elems[pos] = v;
    }

    void erase(size_t pos) override {
        for (size_t i = pos; i < sz-1; ++i) {
            elems[i] = elems[i+1];
        }
        trim_storage();
    }

    size_t size() const override {
        return sz;
    }

    T& operator[](size_t pos) override {
        return elems[pos];
    }
};
