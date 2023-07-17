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
    /**
     * @brief Constructs a unique_ptr that manages the given object.
     *
     * @param obj The object to manage.
     */
    unique_ptr(T& obj);

    /**
     * @brief Constructs a unique_ptr that manages the given object pointer.
     *
     * @param object The object pointer to manage.
     */
    unique_ptr(T* object = nullptr);

    // Make the unique_ptr non-copyable
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr operator=(const unique_ptr&) = delete;

    /**
     * @brief Moves the ownership of the managed object from 'other' to the
     * current unique_ptr.
     *
     * @param other The unique_ptr to move from.
     */
    unique_ptr(unique_ptr&& other) noexcept;

    /**
     * @brief Moves the ownership of the managed object from 'other' to the
     * current unique_ptr.
     *
     * @param other The unique_ptr to move from.
     * @return A reference to the current unique_ptr.
     */
    unique_ptr& operator=(unique_ptr&& other) noexcept;

    /**
     * @brief Resets the unique_ptr to manage the new object pointer.
     *
     * @param object The new object pointer to manage.
     */
    void reset(T* object = nullptr);

    /**
     * @brief Dereferences the managed object.
     *
     * @return A reference to the managed object.
     */
    T& operator*() const;

    /**
     * @brief Returns the managed object pointer.
     *
     * @return The managed object pointer.
     */
    T* operator->() const;

    /**
     * @brief Releases the ownership of the managed object and returns the
     * object pointer.
     *
     * @return The object pointer.
     */
    T* release();

    /**
     * @brief Returns the managed object pointer.
     *
     * @return The managed object pointer.
     */
    T* get() const;

    /**
     * @brief Checks if the unique_ptr is not null.
     *
     * @return 'true' if the unique_ptr is not null, 'false' otherwise.
     */
    explicit operator bool() const;

    /**
     * @brief Resets the unique_ptr to manage a null object pointer.
     *
     * @return A reference to the current unique_ptr.
     */
    unique_ptr& operator=(std::nullptr_t);

    /**
     * @brief Destructor that releases the ownership of the managed object.
     */
    ~unique_ptr();

private:
    T* _object;
    Deleter _deleter;
};

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(T& obj) : _object(&obj) {}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::~unique_ptr() {
    reset();
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(T* object) : _object(object) {}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(unique_ptr&& other) noexcept
    : _object(other._object) {
    other._object = nullptr;
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>& unique_ptr<T, Deleter>::operator=(
    unique_ptr&& other) noexcept {
    if (_object != other._object) {
        reset(other._object);
        other._object = nullptr;
    }

    return *this;
}

template <typename T, typename Deleter>
void unique_ptr<T, Deleter>::reset(T* object) {
    _deleter(_object);
    _object = object;
}

template <typename T, typename Deleter>
T& unique_ptr<T, Deleter>::operator*() const {
    return *_object;
}

template <typename T, typename Deleter>
T* unique_ptr<T, Deleter>::operator->() const {
    return _object;
}

template <typename T, typename Deleter>
T* unique_ptr<T, Deleter>::release() {
    T* releasedObject = _object;
    _object = nullptr;
    return releasedObject;
}

template <typename T, typename Deleter>
T* unique_ptr<T, Deleter>::get() const {
    return _object;
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::operator bool() const {
    return _object != nullptr;
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>& unique_ptr<T, Deleter>::operator=(std::nullptr_t) {
    reset();
    return *this;
}

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

/**
 * @brief Constructs a unique_ptr that manages a new object created with the
 * provided arguments.
 *
 * @tparam T The type of the object to create.
 * @tparam Args The types of the arguments to forward to the object constructor.
 * @param args The arguments to forward to the object constructor.
 * @return A unique_ptr that manages the created object.
 */
template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args);

template <typename T, typename Deleter = std::default_delete<T>>
class shared_ptr {
public:
    /**
     * @brief Constructs a shared_ptr that manages the given object pointer.
     *
     * @param object The object pointer to manage.
     */
    shared_ptr(T* object = nullptr);

    /**
     * @brief Constructs a shared_ptr that shares ownership with the given
     * shared_ptr.
     *
     * @param ptr The shared_ptr to share ownership with.
     */
    shared_ptr(const shared_ptr<T>& ptr);

    /**
     * @brief Assigns the ownership of the managed object from another
     * shared_ptr.
     *
     * @param object The shared_ptr to assign ownership from.
     * @return A reference to the current shared_ptr.
     */
    shared_ptr& operator=(const shared_ptr<T>& object);

    /**
     * @brief Moves the ownership of the managed object from 'other' to the
     * current shared_ptr.
     *
     * @param other The shared_ptr to move from.
     */
    shared_ptr(shared_ptr&& other) noexcept;

    /**
     * @brief Dectructs the object if there're no any owners.
     */
    ~shared_ptr();

    /**
     * @brief Moves the ownership of the managed object from 'other' to the
     * current shared_ptr.
     *
     * @param other The shared_ptr to move from.
     * @return A reference to the current shared_ptr.
     */
    shared_ptr& operator=(shared_ptr&& other) noexcept;

    /**
     * @brief Resets the shared_ptr to manage the new object pointer.
     *
     * @param new_object The new object pointer to manage.
     */
    void reset(T* new_object = nullptr);

    /**
     * @brief Returns the managed object pointer.
     *
     * @return The managed object pointer.
     */
    T* get() const;

    /**
     * @brief Dereferences the managed object.
     *
     * @return A reference to the managed object.
     */
    T& operator*() const;

    /**
     * @brief Returns the managed object pointer.
     *
     * @return The managed object pointer.
     */
    T* operator->() const;

    /**
     * @brief Returns the number of shared_ptr instances sharing the ownership
     * of the managed object.
     *
     * @return The number of shared_ptr instances sharing the ownership.
     */
    size_t use_count() const;

    /**
     * @brief Checks if the shared_ptr is the sole owner of the managed object.
     *
     * @return 'true' if the shared_ptr is the sole owner, 'false' otherwise.
     */
    bool unique() const;

    /**
     * @brief Checks if the shared_ptr manages a non-null object pointer.
     *
     * @return 'true' if the shared_ptr manages a non-null object pointer,
     * 'false' otherwise.
     */
    explicit operator bool() const;

private:
    T* _object;
    Deleter _deleter;
    size_t* _refcnt;

    /**
     * @brief Releases the ownership of the managed object and deallocates it if
     * necessary.
     */
    void release();

    /**
     *
     * @brief Resets the shared_ptr to manage the new object pointer and updates
     * the reference count pointer.
     *
     * @param new_object The new object pointer to manage.
     * @param new_refcnt The new reference count pointer to update.
     */
    void reset_internal(T* new_object, size_t* new_refcnt);
};

/**
 * @brief Constructs a shared_ptr that manages a new object created with the
 * provided arguments.
 *
 * @tparam T The type of the object to create.
 * @tparam Args The types of the arguments to forward to the object constructor.
 * @param args The arguments to forward to the object constructor.
 * @return A shared_ptr that manages the created object.
 */
template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args);

template <typename T, typename Deleter>
shared_ptr<T, Deleter>::shared_ptr(T* object)
    : _object(object), _refcnt(nullptr) {
    if (_object != nullptr) {
        _refcnt = new size_t(1);
    }
}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>::shared_ptr(const shared_ptr<T>& ptr)
    : _object(ptr._object), _refcnt(ptr._refcnt) {
    if (_object != nullptr) {
        ++(*_refcnt);
    }
}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>& shared_ptr<T, Deleter>::operator=(
    const shared_ptr<T>& object) {
    if (_object != object._object) {
        reset_internal(object._object, object._refcnt);
        if (_refcnt != nullptr) {
            ++(*_refcnt);
        }
    }
    return *this;
}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>::shared_ptr(shared_ptr&& other) noexcept
    : _object(other._object), _refcnt(other._refcnt) {
    other._object = nullptr;
    other._refcnt = nullptr;
}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>& shared_ptr<T, Deleter>::operator=(
    shared_ptr&& other) noexcept {
    if (this != &other) {
        reset_internal(other._object, other._refcnt);
        other._object = nullptr;
        other._refcnt = nullptr;
    }
    return *this;
}

template <typename T, typename Deleter>
void shared_ptr<T, Deleter>::reset_internal(T* new_object, size_t* new_refcnt) {
    release();
    _object = new_object;
    _refcnt = new_refcnt;
}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>::~shared_ptr() {
    release();
}

template <typename T, typename Deleter>
void shared_ptr<T, Deleter>::reset(T* new_object) {
    _deleter(_object);
    _object = new_object;
    if (new_object != nullptr) {
        *_refcnt = 1;
    } else {
        *_refcnt = 0;
    }
}

template <typename T, typename Deleter>
T* shared_ptr<T, Deleter>::get() const {
    return _object;
}

template <typename T, typename Deleter>
T& shared_ptr<T, Deleter>::operator*() const {
    return *_object;
}

template <typename T, typename Deleter>
T* shared_ptr<T, Deleter>::operator->() const {
    return _object;
}

template <typename T, typename Deleter>
size_t shared_ptr<T, Deleter>::use_count() const {
    return *_refcnt;
}

template <typename T, typename Deleter>
bool shared_ptr<T, Deleter>::unique() const {
    return *_refcnt == 1;
}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>::operator bool() const {
    return _object != nullptr;
}

template <typename T, typename Deleter>
void shared_ptr<T, Deleter>::release() {
    if (_refcnt != nullptr) {
        if (--(*_refcnt) == 0) {
            delete _refcnt;
            _deleter(_object);
            _object = nullptr;
            _refcnt = nullptr;
        }
    }
}

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}

}  // namespace smart_pointers
