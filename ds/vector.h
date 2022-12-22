#ifndef DATA_STRUCTURES_VECTOR_H
#define DATA_STRUCTURES_VECTOR_H

#include <memory>
#include <stdexcept>

namespace ds {
    template<class ValueType>
    class vector {
    public:
        using value_type = ValueType;
        using size_type = std::size_t;

        class iterator {
        public:
            iterator() = delete;

            explicit iterator(const vector *vector);

            iterator(const vector *vector, size_type index);

        public:
            iterator &operator++();

            iterator &operator--();

            iterator &operator+=(size_type update_index);

            iterator &operator-=(size_type update_index);

            const value_type &operator*();

            bool operator==(const iterator &other);

            bool operator!=(const iterator &other);

        private:
            const vector<value_type> *p_vector_{nullptr};
            size_type m_index_{0};
        };

    public:
        vector() = default;

        ~vector() = default;

        vector(const vector &other);

        vector(vector &&other) noexcept;

        explicit vector(size_type size);

        vector(size_type size, const value_type &value);

    public:
        size_type size() const { return m_size_; }

        size_type capacity() const { return m_capacity_; }

        bool empty() const { return m_size_ == 0; }

    public:
        void clear();

        void reserve(size_type capacity);

        void resize(size_type size, const value_type &value = value_type());

        void push_back(const value_type &value);

        void push_back(value_type &&value);

        void pop_back();

    public:
        vector &operator=(const vector &other);

        vector &operator=(vector &&other) noexcept;

        value_type &operator[](size_type index) const;

    public:
        iterator begin();

        iterator end();

    private:
        size_type m_size_{0};
        size_type m_capacity_{0};
        std::unique_ptr<value_type[]> p_array_{nullptr};
    };

    template<class ValueType>
    vector<ValueType>::iterator::iterator(const vector *vector) :
            p_vector_(vector) {
    }

    template<class ValueType>
    vector<ValueType>::iterator::iterator(const vector *vector, const size_type index) :
            p_vector_(vector), m_index_(index) {
    }

    template<class ValueType>
    typename vector<ValueType>::iterator &vector<ValueType>::iterator::operator++() {
        ++m_index_;
        return *this;
    }

    template<class ValueType>
    typename vector<ValueType>::iterator &vector<ValueType>::iterator::operator--() {
        --m_index_;
        return *this;
    }

    template<class ValueType>
    typename vector<ValueType>::iterator &vector<ValueType>::iterator::operator+=(const size_type update_index) {
        m_index_ += update_index;
        return *this;
    }

    template<class ValueType>
    typename vector<ValueType>::iterator &vector<ValueType>::iterator::operator-=(const size_type update_index) {
        m_index_ -= update_index;
        return *this;
    }

    template<class ValueType>
    const typename vector<ValueType>::value_type &vector<ValueType>::iterator::operator*() {
        return p_vector_->operator[](m_index_);
    }

    template<class ValueType>
    bool vector<ValueType>::iterator::operator==(const iterator &other) {
        return m_index_ == other.m_index_;
    }

    template<class ValueType>
    bool vector<ValueType>::iterator::operator!=(const iterator &other) {
        return m_index_ != other.m_index_;
    }

    template<class ValueType>
    vector<ValueType>::vector(const vector &other) :
            m_size_(other.m_size_), m_capacity_(other.m_capacity_),
            p_array_(std::unique_ptr<value_type[]>(new value_type[other.m_capacity_])) {
        std::copy(other.p_array_.get(), other.p_array_.get() + other.m_size_, p_array_.get());
    }

    template<class ValueType>
    vector<ValueType>::vector(vector &&other) noexcept :
            m_size_(other.m_size_), m_capacity_(other.m_capacity_),
            p_array_(std::move(other.p_array_)) {
        other.m_size_ = 0;
        other.m_capacity_ = 0;
        other.p_array_ = nullptr;
    }

    template<class ValueType>
    vector<ValueType>::vector(const size_type size) :
            m_size_(size), m_capacity_(size),
            p_array_(std::unique_ptr<value_type[]>(new value_type[size])) {
        std::fill(p_array_.get(), p_array_.get() + m_size_, value_type());
    }

    template<class ValueType>
    vector<ValueType>::vector(const size_type size, const value_type &value) :
            m_size_(size), m_capacity_(size),
            p_array_(std::unique_ptr<value_type[]>(new value_type[size])) {
        std::fill(p_array_.get(), p_array_.get() + m_size_, value);
    }

    template<class ValueType>
    void vector<ValueType>::clear() {
        m_size_ = 0;
        m_capacity_ = 0;
        p_array_ = nullptr;
    }

    template<class ValueType>
    void vector<ValueType>::reserve(const size_type capacity) {
        std::unique_ptr<value_type[]> new_array(new value_type[capacity]);
        if (capacity > m_size_) {
            std::copy(p_array_.get(), p_array_.get() + m_size_, new_array.get());
        } else {
            std::copy(p_array_.get(), p_array_.get() + capacity, new_array.get());
            m_size_ = capacity;
        }

        m_capacity_ = capacity;
        p_array_ = std::move(new_array);
    }

    template<class ValueType>
    void vector<ValueType>::resize(const size_type size, const value_type &value) {
        m_size_ = size;
        if (size < m_capacity_) {
            std::fill(p_array_.get(), p_array_.get() + m_size_, value);
            return;
        }

        m_capacity_ = size;
        std::unique_ptr<value_type[]> new_array(new value_type[size]);
        std::fill(new_array.get(), new_array.get() + m_size_, value);
        p_array_ = std::move(new_array);
    }

    template<class ValueType>
    void vector<ValueType>::push_back(const value_type &value) {
        if (m_size_ == m_capacity_) {
            if (m_capacity_ == 0)
                m_capacity_ = 1;

            reserve(m_capacity_ * 2);
        }

        p_array_[m_size_] = value;
        ++m_size_;
    }

    template<class ValueType>
    void vector<ValueType>::push_back(value_type &&value) {
        if (m_size_ == m_capacity_) {
            if (m_capacity_ == 0)
                m_capacity_ = 1;

            reserve(m_capacity_ * 2);
        }

        p_array_[m_size_] = std::move(value);
        ++m_size_;
    }

    template<class ValueType>
    void vector<ValueType>::pop_back() {
        if (m_size_ == 0)
            throw std::logic_error("empty before pop");

        --m_size_;
        if (m_size_ * 2 != m_capacity_)
            return;

        m_capacity_ /= 2;
        std::unique_ptr<value_type[]> new_array(new value_type[m_capacity_]);
        std::copy(p_array_.get(), p_array_.get() + m_size_, new_array.get());
        p_array_ = std::move(new_array);
    }

    template<class ValueType>
    vector<ValueType> &vector<ValueType>::operator=(const vector &other) {
        if (this == &other)
            return *this;

        m_size_ = other.m_size_;
        m_capacity_ = other.m_capacity_;
        p_array_ = std::unique_ptr<value_type[]>(new value_type[other.m_capacity_]);
        std::copy(other.p_array_.get(), other.p_array_.get() + other.m_size_, p_array_.get());

        return *this;
    }

    template<class ValueType>
    vector<ValueType> &vector<ValueType>::operator=(vector &&other) noexcept {
        if (this == &other)
            return *this;

        m_size_ = other.m_size_;
        m_capacity_ = other.m_capacity_;
        p_array_ = std::move(other.p_array_);

        other.m_size_ = 0;
        other.m_capacity_ = 0;
        other.p_array_ = nullptr;

        return *this;
    }

    template<class ValueType>
    typename vector<ValueType>::value_type &vector<ValueType>::operator[](const size_type index) const {
        return index >= m_size_ ? throw std::out_of_range("index out of range") : p_array_[index];
    }

    template<class ValueType>
    typename vector<ValueType>::iterator vector<ValueType>::begin() {
        return iterator(this);
    }

    template<class ValueType>
    typename vector<ValueType>::iterator vector<ValueType>::end() {
        return iterator(this, m_size_);
    }
} // ds

#endif // DATA_STRUCTURES_VECTOR_H
