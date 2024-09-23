#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <iostream>

template <typename T>
class shared_ptr {
    public:
        shared_ptr(T* ptr);
        shared_ptr(const shared_ptr& other);
        shared_ptr& operator=(const shared_ptr& other);
        shared_ptr(shared_ptr&& other);
        shared_ptr& operator=(shared_ptr&& other);
        ~shared_ptr();

        long use_count() const noexcept;
        void reset(T* ptr);
        T* get() const noexcept;
        T* operator->() const noexcept;
        T& operator*() const noexcept;

    private:
        T* m_ptr;
        int* m_count;
};

#include "shared_ptr.cpp"
#endif // SHARED_PTR_HPP