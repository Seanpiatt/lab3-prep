#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <cassert>
#include <utility>

template <typename T>
class UniquePtr {
public:
    UniquePtr() : mItem(nullptr) {}
    explicit UniquePtr(T* item) : mItem(item) {}
    ~UniquePtr() { delete mItem; }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : mItem(other.mItem) {
        other.mItem = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete mItem;
            mItem = other.mItem;
            other.mItem = nullptr;
        }
        return *this;
    }

    T* release() {
        T* temp = mItem;
        mItem = nullptr;
        return temp;
    }

    template <typename U>
    UniquePtr(UniquePtr<U>&& other) : mItem(other.release()) {}

    T& operator*() const {
        assert(mItem != nullptr);
        return *mItem;
    }

    T* operator->() const {
        assert(mItem != nullptr);
        return mItem;
    }

    T* get() const {
        return mItem;
    }

    bool operator==(const UniquePtr& other) const {
        return mItem == other.mItem;
    }

    void reset(T* newPtr = nullptr) {
        T* old = mItem;
        mItem = newPtr;
        delete old;
    }

    void swap(UniquePtr& other) noexcept {
        T* temp = mItem;
        mItem = other.mItem;
        other.mItem = temp;
    }

    explicit operator bool() const {
        return mItem != nullptr;
    }

private:
    T* mItem;
};

template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif
