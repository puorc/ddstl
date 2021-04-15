#ifndef MSTL_VECTOR_H
#define MSTL_VECTOR_H

#include <memory>
#include <type_traits>
#include <limits>
#include <type_traits>
#include <utility>
#include <stdexcept>

namespace ddstl {
    template<class T, class Allocator = std::allocator<T>>
    class vector {
    public:
        using value_type = T;
        using allocator_type = Allocator;
        using allocator_traits_type = typename std::allocator_traits<allocator_type>;
        using size_type = typename allocator_traits_type::size_type;
        using difference_type = typename allocator_traits_type::difference_type;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = typename std::allocator_traits<Allocator>::pointer;
        using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    private:
        static const size_t max_allowed_size = std::numeric_limits<std::size_t>::max();
        pointer data_;
        size_type capacity_;
        size_type size_;
        allocator_type alloc_;

        size_type propose_new_size(size_type add_size);

    public:
        // O(1) Default constructor. Constructs an empty container with a default-constructed allocator.
        vector();

        // O(1) Constructs an empty container with the given allocator alloc.
        explicit vector(const Allocator &alloc) noexcept;

        // O(n) Constructs the container with count copies of elements with value value
        vector(size_type count, const T &value, const Allocator &alloc = Allocator());

        // O(n) Constructs the container with count default-inserted instances of T. No copies are made.
        explicit vector(size_type count, const Allocator &alloc = Allocator());

        // O(n) Constructs the container with the contents of the range [first, last).
        template<class InputIt>
        vector(InputIt first, InputIt last, const Allocator &alloc = Allocator());

        // O(n) Copy constructor. Constructs the container with the copy of the contents of other, the allocator is obtained as if by calling
        vector(const vector &other);

        // O(n) Constructs the container with the copy of the contents of other, using alloc as the allocator.
        vector(const vector &other, const Allocator &alloc);

        // O(1) Move constructor. Constructs the container with the contents of other using move semantics.
        // Allocator is obtained by move-construction from the allocator belonging to other.
        // After the move, other is guaranteed to be empty().
        vector(vector &&other) noexcept;

        // Linear if alloc != other.get_allocator(), otherwise constant. Allocator-extended move constructor.
        // Using alloc as the allocator for the new container,
        // moving the contents from other; if alloc != other.get_allocator(),
        // this results in an element-wise move. (in that case,
        // other is not guaranteed to be empty after the move)
        vector(vector &&other, const Allocator &alloc);

        // O(n) Constructs the container with the contents of the initializer list init.
        vector(std::initializer_list<T> init,
               const Allocator &alloc = Allocator());

        ~vector();

        vector &operator=(const vector &other);

        vector &operator=(vector &&other) noexcept;

        vector &operator=(std::initializer_list<T> ilist);

        void assign(size_type count, const T &value);

        template<class InputIt>
        void assign(InputIt first, InputIt last);

        void assign(std::initializer_list<T> ilist);

        allocator_type get_allocator() const noexcept;

        reference at(size_type pos);

        const_reference at(size_type pos) const;

        reference operator[](size_type pos);

        const_reference operator[](size_type pos) const;

        reference front() {
            return *begin();
        }

        const_reference front() const {
            return *begin();
        }

        reference back() {
            return *(end() - 1);
        }

        const_reference back() const {
            return *(end() - 1);
        }

        iterator begin() noexcept {
            return data_;
        }

        const_iterator begin() const noexcept {
            return data_;
        }

        const_iterator cbegin() const noexcept {
            return data_;
        }

        iterator end() noexcept {
            return data_ + size_;
        }

        const_iterator end() const noexcept {
            return data_ + size_;
        }

        const_iterator cend() const noexcept {
            return data_ + size_;
        }

        reverse_iterator rbegin() noexcept;

        const_reverse_iterator rbegin() const noexcept;

        const_reverse_iterator crbegin() const noexcept;

        reverse_iterator rend() noexcept;

        const_reverse_iterator rend() const noexcept;

        const_reverse_iterator crend() const noexcept;

        bool empty() const noexcept {
            return size_ == 0;
        }

        size_type size() const noexcept {
            return size_;
        }

        size_type max_size() const noexcept {
            return max_allowed_size;
        }

        void reserve(size_type new_cap);

        size_type capacity() const noexcept {
            return capacity_;
        }

        void shrink_to_fit();

        void clear() noexcept;

        iterator insert(const_iterator pos, const T &value);

        iterator insert(const_iterator pos, T &&value);

        iterator insert(const_iterator pos, size_type count, const T &value);

        template<class InputIt, typename = typename std::enable_if<
                std::is_convertible<typename std::iterator_traits<InputIt>::iterator_category, std::input_iterator_tag>::value>::type>
        iterator insert(const_iterator pos, InputIt first, InputIt last);

        iterator insert(const_iterator pos, std::initializer_list<T> ilist);

        template<class... Args>
        iterator emplace(const_iterator pos, Args &&... args);

        iterator erase(const_iterator pos);

        iterator erase(const_iterator first, const_iterator last);

        void push_back(const T &value);

        void push_back(T &&value);

        template<class... Args>
        void emplace_back(Args &&... args);

        void pop_back();

        void resize(size_type count);

        void resize(size_type count, const value_type &value);

        void swap(vector &other) noexcept;
    };


    template<class T, class Allocator>
    vector<T, Allocator>::vector()
            : alloc_(), data_(nullptr), capacity_(0), size_(0) {}

    template<class T, class Allocator>
    vector<T, Allocator>::vector(vector::size_type count, const Allocator &alloc) {
        vector();
        for (int i = 0; i < count; i++) {
            push_back(T());
        }
    }

    template<class T, class Allocator>
    vector<T, Allocator>::~vector() {
        for (auto iter = begin(); iter != end(); ++iter) {
            allocator_traits_type::destroy(alloc_, iter);
        }
        allocator_traits_type::deallocate(alloc_, data_, capacity_);
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::at(vector::size_type pos) {
        if (pos >= size()) {
            throw std::out_of_range("Out of range.");
        }
        return data_[pos];
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(vector::size_type pos) const {
        if (pos >= size()) {
            throw std::out_of_range("Out of range.");
        }
        return data_[pos];
    }

    template<class T, class Allocator>
    inline typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](vector::size_type pos) {
        return data_[pos];
    }

    template<class T, class Allocator>
    inline typename vector<T, Allocator>::const_reference
    vector<T, Allocator>::operator[](vector::size_type pos) const {
        return data_[pos];
    }

    template<class T, class Allocator>
    void vector<T, Allocator>::push_back(const T &value) {
        // resize
        if (capacity() - 1 < size()) {
            insert(end(), value);
        } else {
            // push back
            allocator_traits_type::construct(alloc_, end(), value);
            ++size_;
        }
    }

    template<class T, class Allocator>
    void vector<T, Allocator>::push_back(T &&value) {
        T &t = value;
        push_back(t);
    }

    template<class T, class Allocator>
    template<class... Args>
    void vector<T, Allocator>::emplace_back(Args &&... args) {
        allocator_traits_type::construct(alloc_, end(), args...);
        ++size_;
    }

    template<class T, class Allocator>
    void vector<T, Allocator>::pop_back() {
        if (empty()) return;
        allocator_traits_type::destroy(alloc_, end() - 1);
        --size_;
    }

    template<class T, class Allocator>
    void vector<T, Allocator>::shrink_to_fit() {
        allocator_traits_type::deallocate(alloc_, end(), capacity() - size());
        capacity_ = size_;
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(vector::const_iterator pos, const T &value) {
        return insert(pos, 1, value);
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::iterator
    vector<T, Allocator>::insert(vector::const_iterator pos, vector::size_type count, const T &value) {
        if (capacity() - size() < count) {
            size_type proposed_size = propose_new_size(count);
            T *new_pool = allocator_traits_type::allocate(alloc_, proposed_size);
            T *ptr = new_pool;
            T *inserted = nullptr;
            for (auto iter = begin(); iter <= end(); ++iter) {
                if (iter == pos) {
                    for (size_type i = 0; i < count; ++i) {
                        allocator_traits_type::construct(alloc_, ptr, value);
                        if (inserted == nullptr) {
                            inserted = ptr;
                        }
                        ++ptr;
                    }
                }
                if (iter != end()) {
                    alloc_.construct(ptr, *iter);
                    alloc_.destroy(iter);
                }
                ++ptr;
            }
            alloc_.deallocate(data_, capacity());

            data_ = new_pool;
            capacity_ = proposed_size;
            size_ += count;
            return inserted;
        } else {
            for (auto ptr = end() + (count - 1); ptr != pos + (count - 1); --ptr) {
                T *previous = ptr - count;
                if (ptr < end()) {
                    alloc_.destroy(ptr);
                }
                alloc_.construct(ptr, *previous);
            }

            const_iterator pos_ptr = pos;
            for (int i = 0; i < count; ++i) {
                if (pos_ptr < end()) {
                    alloc_.destroy(pos_ptr);
                }
                alloc_.construct(pos_ptr, value);
                ++pos_ptr;
            }
            size_ += count;
            return const_cast<vector<T, Allocator>::iterator>(pos);
        }
    }

    template<class T, class Allocator>
    template<class InputIt, class A>
    typename vector<T, Allocator>::iterator
    vector<T, Allocator>::insert(vector::const_iterator pos, InputIt first, InputIt last) {
        size_type count = std::distance(first, last);
        size_type proposed_size = size() + count;
        if (proposed_size > capacity() / 2) {
            size_type new_capacity = std::min(max_size(), proposed_size * 2);
            T *new_pool = alloc_.allocate(new_capacity);
            T *ptr = new_pool;
            T *inserted = nullptr;
            for (auto iter = begin(); iter <= end(); ++iter) {
                if (iter == pos) {
                    for (auto ii = first; ii != last; ++ii) {
                        alloc_.construct(ptr, *ii);
                        if (inserted == nullptr) {
                            inserted = ptr;
                        }
                        ++ptr;
                    }
                }
                if (iter != end()) {
                    alloc_.construct(ptr, *iter);
                    alloc_.destroy(iter);
                }
                ++ptr;
            }
            alloc_.deallocate(data_, capacity());

            data_ = new_pool;
            capacity_ = new_capacity;
            size_ += count;
            return inserted;
        } else {
            for (auto ptr = end() + (count - 1); ptr != pos + (count - 1); --ptr) {
                T *previous = ptr - count;
                if (ptr < end()) {
                    alloc_.destroy(ptr);
                }
                alloc_.construct(ptr, *previous);
            }

            const_iterator pos_ptr = pos;
            for (auto ii = first; ii != last; ++ii) {
                if (pos_ptr < end()) {
                    alloc_.destroy(pos_ptr);
                }
                alloc_.construct(pos_ptr, *ii);
                ++pos_ptr;
            }
            size_ += count;
            return const_cast<vector<T, Allocator>::iterator>(pos);
        }
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(vector::const_iterator pos) {
        return erase(pos, pos + 1);
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::iterator
    vector<T, Allocator>::erase(vector::const_iterator first, vector::const_iterator last) {
        size_type count = last - first;
        for (auto iter = first; iter != end(); ++iter) {
            auto next = iter + count;
            alloc_.destroy(iter);
            if (next < end()) {
                alloc_.construct(iter, *next);
            }
        }
        size_ -= count;
        return const_cast<vector<T, Allocator>::iterator>(first);
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::propose_new_size(vector::size_type add_size) {
        size_type base_size = std::max(add_size, size());
        if (max_size() / 2 <= base_size) {
            return max_size();
        } else {
            return 2 * base_size;
        }
    }
}

#endif //MSTL_VECTOR_H
