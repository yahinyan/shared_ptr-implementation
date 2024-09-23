#include "shared_ptr.hpp"

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
    : m_ptr{ptr}
    , m_count{new int(1)}
{}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& other) 
    : m_ptr{other.m_ptr}
    , m_count{other.m_count}
{
    ++(*m_count);
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& other) {
    if(this != &other) {
        if (--(*m_count) == 0) {
            delete m_ptr;
            delete m_count;
        }
    
        m_ptr = other.m_ptr;
        m_count = other.m_count;
        ++(*m_count);
    }
    return *this;
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& other) 
    : m_ptr{std::exchange(other.m_ptr, nullptr)}
    , m_count{std::exchange(other.m_count, nullptr)}
{}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& other) {
    if(this != &other) {
        if (--(*m_count) == 0) {
            delete m_ptr;
            delete m_count;
        }

        m_ptr = std::exchange(other.m_ptr, nullptr);
        m_count = std::exchange(other.m_count, nullptr);
    }
    return *this;
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    if (m_count && --(*m_count) == 0) {
        delete m_ptr;
        delete m_count;
    }
}


template <typename T>
long shared_ptr<T>::use_count() const noexcept {
    return m_count ? *m_count : 0; 
}

template <typename T>
void shared_ptr<T>::reset(T* ptr) {
    if (--(*m_count) == 0) {
        delete m_ptr;
        delete m_count;
    }
    m_ptr = ptr;
    m_count = new int(1);
}

template <typename T>
T* shared_ptr<T>::get() const noexcept {
    return m_ptr;
}

template <typename T>
T* shared_ptr<T>::operator->() const noexcept {
    return m_ptr;
}

template <typename T>
T& shared_ptr<T>::operator*() const noexcept {
    return *m_ptr;
}
