#ifndef MSTL_PRIORITYQUEUE_H
#define MSTL_PRIORITYQUEUE_H

#include "algorithm.h"
#include <vector>
#include <queue>
#include <functional>
#include "type_traits.h"

namespace ddstl
{
    template <typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
    class priority_queue
    {
    public:
        using container_type = Container;
        using value_compare = Compare;
        using value_type = typename Container::value_type;
        using size_type = typename Container::size_type;
        using reference = typename Container::reference;
        using const_reference = typename Container::const_reference;

        container_type c;
        value_compare comp;

        template <typename Seq = Container, typename Requires = typename std::enable_if<and_trait<std::is_default_constructible<Compare>,
                                                                                                  std::is_default_constructible<Seq>>::value>::type>
        priority_queue() : c(), comp() {}

        explicit priority_queue(const Compare &compare)
            : c(), comp(compare) {}

        priority_queue(const Compare &compare, const Container &cont) : c(cont), comp(compare)
        {
            ddstl::make_heap(c.begin(), c.end(), comp);
        }

        priority_queue(const Compare &compare, Container &&cont) : c(ddstl::move(cont)), comp(compare)
        {
            ddstl::make_heap(c.begin(), c.end(), comp);
        }

        template <class InputIt>
        priority_queue(InputIt first, InputIt last,
                       const Compare &compare, const Container &cont) : c(cont), comp(compare)
        {
            c.insert(c.end(), first, last);
            ddstl::make_heap(c.begin(), c.end(), comp);
        }

        template <class InputIt>
        priority_queue(InputIt first, InputIt last,
                       const Compare &compare = Compare(),
                       Container &&cont = Container()) : c(ddstl::move(cont)), comp(compare)
        {
            c.insert(c.end(), first, last);
            ddstl::make_heap(c.begin(), c.end(), comp);
        }

        const_reference top() const
        {
            return c.front();
        }

        bool empty() const
        {
            return c.empty();
        }

        size_type size() const
        {
            return c.size();
        }

        void push(value_type &&value)
        {
            c.push_back(ddstl::move(value));
            ddstl::push_heap(c.begin(), c.end(), comp);
        }

        void push(const value_type &value)
        {
            c.push_back(value);
            ddstl::push_heap(c.begin(), c.end(), comp);
        }

        template <class... Args>
        void emplace(Args &&...args)
        {
            c.emplace_back(ddstl::forward<Args>(args)...);
            ddstl::push_heap(c.begin(), c.end(), comp);
        }

        void pop()
        {
            ddstl::pop_heap(c.begin(), c.end(), comp);
            c.pop_back();
        }

        void swap(priority_queue &other) noexcept
        {
            ddstl::swap(c, other.c);
            ddstl::swap(comp, other.comp);
        }
    };
}

#endif