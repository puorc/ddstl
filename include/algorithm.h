#ifndef MSTL_ALGORITHM_H
#define MSTL_ALGORITHM_H

#include <iterator>
#include <cstdio>
#include <cstring>
#include "utility.h"
#include "ops.h"
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

    template <class InputIt, class UnaryPredicate>
    typename std::iterator_traits<InputIt>::difference_type
    count_if_aux(InputIt first, InputIt last, UnaryPredicate p)
    {
        typename std::iterator_traits<InputIt>::difference_type count = 0;
        while (first != last)
        {
            if (p(first))
            {
                ++count;
            }
            ++first;
        }
        return count;
    }

    template <class InputIt, class UnaryPredicate>
    typename std::iterator_traits<InputIt>::difference_type inline count_if(InputIt first, InputIt last, UnaryPredicate p)
    {
        return count_if_aux(first, last, ddstl::iter_pred_functor<UnaryPredicate>(p));
    }

    template <class InputIt, class T>
    typename std::iterator_traits<InputIt>::difference_type inline count(InputIt first, InputIt last, const T &value)
    {
        return count_if_aux(first, last, ddstl::iter_equal_value_functor<T>(value));
    }

    template <class InputIt, class UnaryPredicate>
    InputIt find_if_aux(InputIt first, InputIt last, UnaryPredicate p, bool negate)
    {
        while (first != last)
        {
            if (negate)
            {
                if (!p(first))
                {
                    return first;
                }
            }
            else
            {
                if (p(first))
                {
                    return first;
                }
            }
            ++first;
        }
        return first;
    }

    template <class InputIt, class T>
    inline InputIt find(InputIt first, InputIt last, const T &value)
    {
        return find_if_aux(first, last, ddstl::iter_equal_value_functor<T>(value), false);
    }

    template <class InputIt, class UnaryPredicate>
    inline InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
    {
        return find_if_aux(first, last, ddstl::iter_pred_functor<UnaryPredicate>(p), false);
    }

    template <class InputIt, class UnaryPredicate>
    inline InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate q)
    {
        return find_if_aux(first, last, ddstl::iter_pred_functor<UnaryPredicate>(q), true);
    }

    template <class ForwardIt1, class ForwardIt2>
    ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last)
    {
        for (; first != last; ++first)
        {
            for (ForwardIt2 iter = s_first; iter != s_last; ++iter)
            {
                if (*iter == *first)
                {
                    return first;
                }
            }
        }
        return last;
    }

    template <class ForwardIt1, class ForwardIt2, class BinaryPredicate>
    ForwardIt1
    find_first_of(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
    {
        for (; first != last; ++first)
        {
            for (ForwardIt2 iter = s_first; iter != s_last; ++iter)
            {
                if (p(*first, *iter))
                {
                    return first;
                }
            }
        }
        return last;
    }

    template <class ForwardIt1, class ForwardIt2, class BinaryPredicate>
    bool range_equal_aux(ForwardIt1 first, ForwardIt1 last,
                         ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
    {
        for (; s_first != s_last; ++s_first)
        {
            if (first == last)
            {
                return false;
            }
            if (!p(first, s_first))
            {
                return false;
            }
            ++first;
        }
        return true;
    }

    template <class ForwardIt1, class ForwardIt2, class BinaryPredicate>
    ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
                      ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
    {
        for (; first != last; ++first)
        {
            if (range_equal_aux(first, last, s_first, s_last, ddstl::iter_bi_pred_functor<BinaryPredicate>(p)))
            {
                return first;
            }
        }
        return first;
    }

    template <class ForwardIt1, class ForwardIt2>
    inline ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
                             ForwardIt2 s_first, ForwardIt2 s_last)
    {
        return search(first, last, s_first, s_last, ddstl::iter_bi_equal_functor());
    }

    template <class ForwardIt1, class ForwardIt2, class BinaryPredicate>
    ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
    {
        if (s_first == s_last)
        {
            return last;
        }
        ForwardIt1 result(last);
        for (; first != last; ++first)
        {
            if (range_equal_aux(first, last, s_first, s_last, ddstl::iter_bi_pred_functor<BinaryPredicate>(p)))
            {
                result = first;
            }
        }
        return result;
    }

    template <class ForwardIt1, class ForwardIt2>
    inline ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last)
    {
        return find_end(first, last, s_first, s_last, ddstl::iter_bi_equal_functor());
    }

    template <class ForwardIt, class BinaryPredicate>
    ForwardIt adjacent_find(ForwardIt first, ForwardIt last, BinaryPredicate p)
    {
        if (first == last)
        {
            return last;
        }
        ForwardIt prev(first);
        ++first;
        for (; first != last; ++first)
        {
            if (p(*prev, *first))
            {
                return prev;
            }
            prev = first;
        }
        return last;
    }

    template <class ForwardIt>
    inline ForwardIt adjacent_find(ForwardIt first, ForwardIt last)
    {
        return adjacent_find(first, last, ddstl::iter_bi_equal_functor());
    }

    template <class ForwardIt, class Size, class T, class BinaryPredicate>
    ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T &value,
                       BinaryPredicate p)
    {
        if (count == 0)
        {
            return first;
        }
        typename std::iterator_traits<ForwardIt>::difference_type len(0);
        ForwardIt fast(first), slow(first);
        while (fast != last)
        {
            if (p(*fast, value))
            {
                ++fast;
                ++len;
                if (len >= count)
                {
                    return slow;
                }
            }
            else
            {
                ++fast;
                slow = fast;
                len = 0;
            }
        }
        return len >= count ? slow : last;
    }

    template <class ForwardIt, class Size, class T>
    inline ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T &value)
    {
        return search_n(first, last, count, value, ddstl::iter_bi_equal_functor());
    }

    template <class ForwardIt1, class ForwardIt2, class BinaryPredicate>
    bool is_permutation_aux(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, BinaryPredicate p)
    {
        for (; first1 != last1; ++first1, (void)++first2)
        {
            if (!p(first1, first2))
            {
                break;
            }
        }
        if (first1 == last1)
        {
            return true;
        }
        ForwardIt2 last2 = first2;
        ddstl::advance(last2, ddstl::distance(first1, last1));

        for (ForwardIt1 iter = first1; iter != last1; ++iter)
        {
            ForwardIt1 prev = ddstl::find_if_aux(first1, iter,
                                                 iter_comp_iter_functor<BinaryPredicate, ForwardIt1>(p, iter), false);
            if (prev != iter)
            {
                // has been checked in previous element, skip
                continue;
            }
            auto matches = ddstl::count_if_aux(first2, last2,
                                               iter_comp_iter_functor<BinaryPredicate, ForwardIt1>(p, iter));
            if (matches == 0 ||
                matches !=
                    ddstl::count_if_aux(iter, last1, iter_comp_iter_functor<BinaryPredicate, ForwardIt1>(p, iter)))
            {
                return false;
            }
        }
        return true;
    }

    template <class ForwardIt1, class ForwardIt2, class BinaryPredicate>
    inline bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, BinaryPredicate p)
    {
        return is_permutation_aux(first1, last1, first2, iter_bi_pred_functor<BinaryPredicate>(p));
    }

    template <class ForwardIt1, class ForwardIt2>
    inline bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2)
    {
        return is_permutation(first1, last1, first2, iter_bi_equal_functor());
    }

    template <class BidirIt, class Compare>
    bool next_permutation_aux(BidirIt first, BidirIt last, Compare comp)
    {
        if (first == last)
        {
            return false;
        }
        BidirIt it = last;
        --it;
        if (it == first)
        {
            return false;
        }

        for (; it != first; --it)
        {
            BidirIt prev = it;
            --prev;
            if (comp(prev, it))
            {
                break;
            }
        }
        if (it == first)
        {
            reverse(first, last);
            return false;
        }
        else
        {
            BidirIt back = last;
            --back;
            --it;
            for (; back != it; --back)
            {
                if (comp(it, back))
                {
                    break;
                }
            }
            swap(*it, *back);
            ++it;
            reverse(it, last);
            return true;
        }
    }

    template <class BidirIt, class Compare>
    inline bool next_permutation(BidirIt first, BidirIt last, Compare comp)
    {
        return next_permutation_aux(first, last, iter_bi_pred_functor<Compare>(comp));
    }

    template <class BidirIt>
    inline bool next_permutation(BidirIt first, BidirIt last)
    {
        return next_permutation_aux(first, last, iter_bi_less_functor());
    }

    template <class BidirIt, class Compare>
    bool prev_permutation_aux(BidirIt first, BidirIt last, Compare comp)
    {
        if (first == last)
        {
            return false;
        }
        BidirIt it = last;
        --it;
        if (it == first)
        {
            return false;
        }
        for (; it != first; --it)
        {
            BidirIt prev = it;
            --prev;
            if (comp(it, prev))
            {
                break;
            }
        }
        if (it == first)
        {
            reverse(first, last);
            return false;
        }
        else
        {
            BidirIt back = last;
            --back;
            --it;
            for (; back != it; --back)
            {
                if (comp(back, it))
                {
                    break;
                }
            }
            swap(*it, *back);
            ++it;
            reverse(it, last);
            return true;
        }
    }

    template <class BidirIt, class Compare>
    inline bool prev_permutation(BidirIt first, BidirIt last, Compare comp)
    {
        return prev_permutation_aux(first, last, iter_bi_pred_functor<Compare>(comp));
    }

    template <class BidirIt>
    inline bool prev_permutation(BidirIt first, BidirIt last)
    {
        return prev_permutation_aux(first, last, iter_bi_less_functor());
    }

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

    template <class ForwardIt, class Compare>
    ForwardIt max_element_aux(ForwardIt first, ForwardIt last, Compare comp)
    {
        if (first == last)
        {
            return last;
        }
        ForwardIt max_ele = first;
        for (; first != last; ++first)
        {
            if (comp(max_ele, first))
            {
                max_ele = first;
            }
        }
        return max_ele;
    }

    template <class ForwardIt, class Compare>
    inline ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp)
    {
        return max_element_aux(first, last, iter_bi_pred_functor<Compare>(comp));
    }

    template <class ForwardIt>
    inline ForwardIt max_element(ForwardIt first, ForwardIt last)
    {
        return max_element_aux(first, last, iter_bi_less_functor());
    }

    template <class ForwardIt, class Compare>
    ForwardIt min_element_aux(ForwardIt first, ForwardIt last, Compare comp)
    {
        if (first == last)
        {
            return last;
        }
        ForwardIt min_ele = first;
        for (; first != last; ++first)
        {
            if (comp(first, min_ele))
            {
                min_ele = first;
            }
        }
        return min_ele;
    }

    template <class ForwardIt, class Compare>
    inline ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp)
    {
        return min_element_aux(first, last, iter_bi_pred_functor<Compare>(comp));
    }

    template <class ForwardIt>
    inline ForwardIt min_element(ForwardIt first, ForwardIt last)
    {
        return min_element_aux(first, last, iter_bi_less_functor());
    }

    template <typename T>
    inline const T &max(const T &a, const T &b)
    {
        return a < b ? b : a;
    }

    template <class T, class Compare>
    inline const T &max(const T &a, const T &b, Compare comp)
    {
        return comp(a, b) ? b : a;
    }

    template <class T>
    inline T max(std::initializer_list<T> ilist)
    {
        return *max_element(ilist.begin(), ilist.end());
    }

    template <class T, class Compare>
    inline T max(std::initializer_list<T> ilist, Compare comp)
    {
        return *max_element(ilist.begin(), ilist.end(), comp);
    }

    // interesting, it has a requirement which element to return when equal
    template <class T>
    inline const T &min(const T &a, const T &b)
    {
        return b < a ? b : a;
    }

    template <class T, class Compare>
    inline const T &min(const T &a, const T &b, Compare comp)
    {
        return comp(b, a) ? b : a;
    }

    template <class T>
    inline T min(std::initializer_list<T> ilist)
    {
        return *min_element(ilist.begin(), ilist.end());
    }

    template <class T, class Compare>
    inline T min(std::initializer_list<T> ilist, Compare comp)
    {
        return *min_element(ilist.begin(), ilist.end(), comp);
    }

    template <class RandomIt, class Compare, class Distance>
    RandomIt is_heap_until_aux(RandomIt first, Distance dist, Compare comp)
    {
        Distance parent = 0;
        for (Distance child = 1; child < dist; ++child)
        {
            if (comp(first + parent, first + child))
            {
                return first + child;
            }
            if ((child & 1) == 0)
            {
                ++parent;
            }
        }
        return first + dist;
    }

    template <class RandomIt>
    inline RandomIt is_heap_until(RandomIt first, RandomIt last)
    {
        return is_heap_until_aux(first, ddstl::distance(first, last), ddstl::iter_bi_less_functor());
    }

    template <class RandomIt, class Compare>
    inline RandomIt is_heap_until(RandomIt first, RandomIt last, Compare comp)
    {
        return is_heap_until_aux(first, ddstl::distance(first, last), ddstl::iter_bi_pred_functor<Compare>(comp));
    }

    template <class RandomIt>
    inline bool is_heap(RandomIt first, RandomIt last)
    {
        return ddstl::is_heap_until(first, last) == last;
    }

    template <class RandomIt, class Compare>
    inline bool is_heap(RandomIt first, RandomIt last, Compare comp)
    {
        return ddstl::is_heap_until(first, last, comp) == last;
    }

    template <class RandomIt, class Compare, class Distance>
    void push_heap_aux(RandomIt first, Distance n, Compare comp)
    {
        if (n == 0)
        {
            return;
        }
        Distance child = n - 1;
        while (child > 0)
        {
            Distance parent = ((child - 1) >> 1);
            if (comp(first + parent, first + child))
            {
                ddstl::iter_swap(first + parent, first + child);
                child = parent;
            }
            else
            {
                break;
            }
        }
    }

    template <class RandomIt, class Compare>
    inline void push_heap(RandomIt first, RandomIt last, Compare comp)
    {
        push_heap_aux(first, ddstl::distance(first, last), iter_bi_pred_functor<Compare>(comp));
    }

    template <class RandomIt>
    inline void push_heap(RandomIt first, RandomIt last)
    {
        push_heap_aux(first, ddstl::distance(first, last), iter_bi_less_functor());
    }

    template <class RandomIt, class Compare, class Distance>
    void pop_heap_aux(RandomIt first, Distance n, Compare comp)
    {
        if (n <= 1)
        {
            return;
        }
        ddstl::iter_swap(first, first + (n - 1));
        Distance parent = 0;
        --n;

        while (parent < n)
        {
            Distance lchild = parent * 2 + 1;
            Distance rchild = lchild + 1;
            if (lchild < n && rchild < n)
            {
                Distance large = comp(first + lchild, first + rchild) ? rchild : lchild;
                if (comp(first + parent, first + large))
                {
                    ddstl::iter_swap(first + parent, first + large);
                    parent = large;
                }
                else
                {
                    break;
                }
            }
            else if (lchild < n)
            {
                if (comp(first + parent, first + lchild))
                {
                    ddstl::iter_swap(first + parent, first + lchild);
                    parent = lchild;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

    template <class RandomIt, class Compare>
    inline void pop_heap(RandomIt first, RandomIt last, Compare comp)
    {
        pop_heap_aux(first, ddstl::distance(first, last), iter_bi_pred_functor<Compare>(comp));
    }

    template <class RandomIt>
    inline void pop_heap(RandomIt first, RandomIt last)
    {
        pop_heap_aux(first, ddstl::distance(first, last), iter_bi_less_functor());
    }
}

#endif //MSTL_ALGORITHM_H
