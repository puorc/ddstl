#ifndef MSTL_ALGORITHM_MINMAX_H
#define MSTL_ALGORITHM_MINMAX_H

namespace ddstl
{
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
        return *ddstl::max_element(ilist.begin(), ilist.end());
    }

    template <class T, class Compare>
    inline T max(std::initializer_list<T> ilist, Compare comp)
    {
        return *ddstl::max_element(ilist.begin(), ilist.end(), comp);
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
        return *ddstl::min_element(ilist.begin(), ilist.end());
    }

    template <class T, class Compare>
    inline T min(std::initializer_list<T> ilist, Compare comp)
    {
        return *ddstl::min_element(ilist.begin(), ilist.end(), comp);
    }
}

#endif