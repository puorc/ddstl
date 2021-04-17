#ifndef MSTL_ALGORITHM_MODIFYING_H
#define MSTL_ALGORITHM_MODIFYING_H

#include <cstring>
#include "iterator.h"

namespace ddstl
{
    template <bool IsSimple, typename Category>
    struct copy_aux
    {
        template <class InputIt, class OutputIt>
        static OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
        {
            while (first != last)
            {
                *d_first = *first;
                ++d_first;
                ++first;
            }
            return d_first;
        }
    };

    template <>
    struct copy_aux<true, std::random_access_iterator_tag>
    {
        template <class T>
        static T *copy(const T *first, const T *last, T *d_first)
        {
            std::ptrdiff_t count = last - first;
            if (count > 0)
            {
                memmove(d_first, first, sizeof(T) * count);
            }
            return d_first + count;
        }
    };

    template <class InputIt, class OutputIt>
    OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
    {
        typedef typename std::iterator_traits<InputIt>::value_type IValue;
        typedef typename std::iterator_traits<OutputIt>::value_type OValue;
        typedef typename std::iterator_traits<InputIt>::iterator_category category;
        const bool simple = (std::is_trivially_copyable<InputIt>::value && std::is_pointer<InputIt>::value && std::is_pointer<OutputIt>::value && std::is_same<IValue, OValue>::value);
        return copy_aux<simple, category>::copy(first, last, d_first);
    }

    template <class InputIt, class Size, class OutputIt>
    inline OutputIt copy_n(InputIt first, Size count, OutputIt result)
    {
        if (count > 0)
        {
            InputIt end = first;
            ddstl::advance(end, count);
            return copy(first, end, result);
        }
        return result;
    }

    template <class ForwardIt1, class ForwardIt2>
    inline void iter_swap(ForwardIt1 a, ForwardIt2 b)
    {
        ddstl::swap(*a, *b);
    }

    template <class RandomAccessIt>
    void reverse_aux(RandomAccessIt first, RandomAccessIt last, std::random_access_iterator_tag)
    {
        if (first == last)
        {
            return;
        }
        --last;
        while (first < last)
        {
            iter_swap(first, last);
            ++first;
            --last;
        }
    }

    template <class BidirIt>
    void reverse_aux(BidirIt first, BidirIt last, std::bidirectional_iterator_tag)
    {
        while (first != last && first != --last)
        {
            iter_swap(first, last);
            ++first;
        }
    }

    template <class BidirIt>
    inline void reverse(BidirIt first, BidirIt last)
    {
        reverse_aux(first, last, typename std::iterator_traits<BidirIt>::iterator_category());
    }
}

#endif