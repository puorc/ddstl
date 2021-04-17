#ifndef MSTL_ALGORITHM_COMPARISON_H
#define MSTL_ALGORITHM_COMPARISON_H

namespace ddstl
{
    template <class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare_aux(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    {
        for (; first1 != last1; ++first1, (void)++first2)
        {
            if (first2 == last2)
            {
                break;
            }
            if (comp(first1, first2))
            {
                return true;
            }
            if (*first2 < *first1)
            {
                return false;
            }
        }
        return first1 == last1 && first2 != last2;
    }

    template <class InputIt1, class InputIt2, class Compare>
    inline bool
    lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    {
        return lexicographical_compare_aux(first1, last1, first2, last2, iter_bi_pred_functor<Compare>(comp));
    }

    template <class InputIt1, class InputIt2>
    inline bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        return lexicographical_compare_aux(first1, last1, first2, last2, iter_bi_less_functor());
    }

    template <bool simple>
    struct equal_aux_struct
    {
        template <class InputIt1, class InputIt2>
        static bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
        {
            for (; first1 != last1; ++first1, (void)++first2)
            {
                if (!(*first1 == *first2))
                {
                    return false;
                }
            }
            return true;
        }
    };

    template <>
    struct equal_aux_struct<true>
    {
        template <class T>
        static bool equal(T *first1, T *last1, T *first2)
        {
            size_t size = last1 - first1;
            if (size > 0)
            {
                return !memcmp(first1, first2, sizeof(T) * size);
            }
            else
            {
                return true;
            }
        }
    };

    template <class InputIt1, class InputIt2, class BinaryPredicate>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
    {
        for (; first1 != last1; ++first1, (void)++first2)
        {
            if (!p(*first1, *first2))
            {
                return false;
            }
        }
        return true;
    }

    template <class InputIt1, class InputIt2>
    inline bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        typedef typename std::iterator_traits<InputIt1>::value_type ValueType1;
        typedef typename std::iterator_traits<InputIt2>::value_type ValueType2;
        const bool simple = (std::is_integral<ValueType1>::value || std::is_pointer<ValueType1>::value) && std::is_pointer<InputIt1>::value && std::is_pointer<InputIt2>::value && std::is_same<ValueType1, ValueType2>::value;
        return equal_aux_struct<simple>().equal(first1, last1, first2);
    }
}

#endif