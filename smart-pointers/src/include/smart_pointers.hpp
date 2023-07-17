// -----------------------------------------------------------------------------
//
// Header for classes 'unique_ptr' and 'shared_ptr' in C++
//
// -----------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <memory>

namespace smart_pointers {

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
public:
    unique_ptr(T& obj) : _object(&obj) {}
    unique_ptr(T* object = nullptr) : _object(object) {}

    /* Make the unique_ptr unique_ptr! */
    unique_ptr(const T& unique_ptr) = delete;
    unique_ptr operator=(const T& unique_ptr) = delete;

    ~unique_ptr() { reset(); }

    unique_ptr(unique_ptr&& other) noexcept : _object(other._object) {
        other._object = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (_object != other._object) {
            reset(other._object);
            other._object = nullptr;
        }

        return *this;
    }

    void reset(T* object = nullptr) {
        _deleter(_object);
        _object = object;
    }

    T& operator*() const { return *_object; }

    T* operator->() const { return _object; }

    T* release() {
        T* releasedObject = _object;
        _object = nullptr;
        return releasedObject;
    }

    T* get() const { return _object; }

    explicit operator bool() const { return _object != nullptr; }

    unique_ptr& operator=(std::nullptr_t) {
        reset();
        return *this;
    }

private:
    T* _object;
    Deleter _deleter;
};

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}  // namespace smart_pointers
