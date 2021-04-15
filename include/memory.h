#ifndef MSTL_MEMORY_H
#define MSTL_MEMORY_H

#include <type_traits>
#include <memory>
#include "type_traits.h"
#include "algorithm.h"

namespace ddstl {
    template<typename Tp, typename Dp, typename = void>
    struct PtrProxy {
        using type = Tp *;
    };

    template<typename Tp, typename Dp>
    struct
    PtrProxy<Tp, Dp, std::void_t<typename std::remove_reference<Dp>::type::pointer>> {
        using type = typename std::remove_reference<Dp>::type::pointer;
    };

    template<typename T, typename Deleter = std::default_delete<T>>
    class unique_ptr {
    public:
        using pointer = typename PtrProxy<T, Deleter>::type;
        using element_type = T;
        using deleter_type = Deleter;
    private:
        pointer m_ptr;
        Deleter m_del;
        template<typename U, typename E>
        using safe_conversion_up = and_trait<
                std::is_convertible<typename unique_ptr<U, E>::pointer, pointer>,
                not_trait<std::is_array<U>>
        >;
    public:
        constexpr unique_ptr() noexcept: m_ptr(), m_del() {}

        constexpr unique_ptr(std::nullptr_t) noexcept: m_ptr(), m_del() {}

        explicit unique_ptr(pointer p) noexcept: m_ptr(p), m_del() {}

        unique_ptr(const unique_ptr &) = delete;

        unique_ptr(unique_ptr &&u) noexcept: m_ptr(u.release()),
                                             m_del(ddstl::forward<Deleter>(u.get_deleter())) {}

        template<typename Del = deleter_type,
                typename DelUnref = typename std::remove_reference<Del>::type>
        unique_ptr(pointer, typename std::enable_if<std::is_lvalue_reference<Del>::value,
                DelUnref &&>::type) = delete;

        template<typename Del = deleter_type,
                typename = ddstl::Require<std::is_copy_constructible<Del>>>
        unique_ptr(pointer p, const deleter_type &d) noexcept: m_ptr(p), m_del(d) {}

        template<typename Del = deleter_type,
                typename = ddstl::Require<std::is_move_constructible<Del>>>
        unique_ptr(pointer p,
                   std::enable_if<!std::is_lvalue_reference<Del>::value,
                           Del &&> d) noexcept: m_ptr(p), m_del(ddstl::move(d)) {}

        template<class U, class E, class = ddstl::Require<
                safe_conversion_up<U, E>,
                typename std::conditional<std::is_reference<Deleter>::value,
                        std::is_same<E, Deleter>,
                        std::is_convertible<E, Deleter>>::type>>
        unique_ptr(unique_ptr<U, E> &&u) noexcept:m_ptr(u.release()),
                                                  m_del(ddstl::forward<Deleter>(u.get_deleter())) {}

        ~unique_ptr() {
            if (m_ptr != nullptr) {
                get_deleter()(ddstl::move(m_ptr));
            }
        }

        unique_ptr &operator=(const unique_ptr &) = delete;

        unique_ptr &operator=(unique_ptr &&r) noexcept {
            reset(r.release());
            m_del = ddstl::forward<Deleter>(r.get_deleter());
            return *this;
        }

        template<class U, class E>
        typename std::enable_if<
                and_trait<safe_conversion_up<U, E>, std::is_assignable<deleter_type &, E &&>>::value,
                unique_ptr &>::type
        operator=(unique_ptr<U, E> &&r) noexcept {
            reset(r.release());
            m_del = ddstl::forward<E>(r.get_deleter());
            return *this;
        }

        unique_ptr &operator=(std::nullptr_t) noexcept {
            reset();
            return *this;
        }

        pointer release() noexcept {
            pointer res = m_ptr;
            m_ptr = pointer();
            return res;
        }

        void reset(pointer ptr = pointer()) noexcept {
            pointer old = m_ptr;
            m_ptr = ptr;
            get_deleter()(ddstl::move(old));
        }

        void swap(unique_ptr &other) noexcept {
            ddstl::swap(m_ptr, other.m_ptr);
        }

        pointer get() const noexcept {
            return m_ptr;
        }

        Deleter &get_deleter() noexcept {
            return m_del;
        }

        const Deleter &get_deleter() const noexcept {
            return m_del;
        }

        explicit operator bool() const noexcept {
            return get() != pointer();
        }

        typename std::add_lvalue_reference<T>::type operator*() const {
            return *get();
        }

        pointer operator->() const noexcept {
            return get();
        }
    };
}


#endif //MSTL_MEMORY_H
