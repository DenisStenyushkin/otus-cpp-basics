#pragma once

#include <cstddef>

template<typename T>
class IContainer {
public:
    virtual void push_back(const T& v) = 0;
    virtual void insert(size_t pos, const T& v) = 0;
    virtual void erase(size_t pos) = 0;
    virtual size_t size() const = 0;
    virtual T& operator[](size_t pos) = 0;
    virtual ~IContainer() = default;
};
