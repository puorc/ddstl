#ifndef MSTL_ALGORITHM_SET_H
#define MSTL_ALGORITHM_SET_H

namespace ddstl
{
    template <class InputIt1, class InputIt2, class Compare>
    bool includes_aux(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    {
        for (; first2 != last2; ++first2)
        {
            while (first1 != last1 && comp(first1, first2))
            {
                ++first1;
            }
            if (first1 == last1)
            {
                return false;
            }
            else if (comp(first2, first1))
            {
                return false;
            }
            else
            {
                ++first1;
            }
        }
        return first2 == last2;
    }

    template <class InputIt1, class InputIt2>
    inline bool includes(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        return includes_aux(first1, last1, first2, last2, ddstl::iter_bi_less_functor());
    }

    template <class InputIt1, class InputIt2, class Compare>
    inline bool includes(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    {
        return includes_aux(first1, last1, first2, last2, ddstl::iter_bi_pred_functor<Compare>(comp));
    }

    template <class InputIt1, class InputIt2, class OutputIt, class Compare>
    OutputIt set_difference_aux(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        for (; first1 != last1; ++first1)
        {
            while (first2 != last2 && comp(first2, first1))
            {
                ++first2;
            }
            if (first2 == last2 || comp(first1, first2))
            {
                *d_first = *first1;
                ++d_first;
            }
            else
            {
                ++first2;
            }
        }
        return d_first;
    }

    template <class InputIt1, class InputIt2, class OutputIt>
    inline OutputIt set_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first)
    {
        return set_difference_aux(first1, last1, first2, last2, d_first, ddstl::iter_bi_less_functor());
    }

    template <class InputIt1, class InputIt2, class OutputIt, class Compare>
    inline OutputIt set_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        return set_difference_aux(first1, last1, first2, last2, d_first, ddstl::iter_bi_pred_functor<Compare>(comp));
    }

    template <class InputIt1, class InputIt2, class OutputIt, class Compare>
    OutputIt set_intersection_aux(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (comp(first1, first2))
            {
                ++first1;
            }
            else if (comp(first2, first1))
            {
                ++first2;
            }
            else
            {
                *d_first = *first1;
                ++d_first;
                ++first1;
                ++first2;
            }
        }
        return d_first;
    }

    template <class InputIt1, class InputIt2, class OutputIt>
    inline OutputIt set_intersection(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first)
    {
        return set_intersection_aux(first1, last1, first2, last2, d_first, ddstl::iter_bi_less_functor());
    }

    template <class InputIt1, class InputIt2,
              class OutputIt, class Compare>
    inline OutputIt set_intersection(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
                                     OutputIt d_first, Compare comp)
    {
        return set_intersection_aux(first1, last1, first2, last2, d_first, ddstl::iter_bi_pred_functor<Compare>(comp));
    }

    template <class InputIt1, class InputIt2, class OutputIt, class Compare>
    OutputIt set_symmetric_difference_aux(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (comp(first1, first2))
            {
                *d_first = *first1;
                ++first1;
                ++d_first;
            }
            else if (comp(first2, first1))
            {
                *d_first = *first2;
                ++first2;
                ++d_first;
            }
            else
            {
                ++first1;
                ++first2;
            }
        }
        if (first1 != last1)
        {
            return ddstl::copy(first1, last1, d_first);
        }
        else if (first2 != last2)
        {
            return ddstl::copy(first2, last2, d_first);
        }
        else
        {
            return d_first;
        }
    }

    template <class InputIt1, class InputIt2, class OutputIt>
    inline OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1,
                                             InputIt2 first2, InputIt2 last2,
                                             OutputIt d_first)
    {
        return set_symmetric_difference_aux(first1, last1, first2, last2, d_first, ddstl::iter_bi_less_functor());
    }

    template <class InputIt1, class InputIt2,
              class OutputIt, class Compare>
    inline OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1,
                                             InputIt2 first2, InputIt2 last2,
                                             OutputIt d_first, Compare comp)
    {
        return set_symmetric_difference_aux(first1, last1, first2, last2, d_first, ddstl::iter_bi_pred_functor<Compare>(comp));
    }

    template <class InputIt1, class InputIt2, class OutputIt, class Compare>
    OutputIt set_union_aux(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (comp(first1, first2))
            {
                *d_first = *first1;
                ++first1;
            }
            else if (comp(first2, first1))
            {
                *d_first = *first2;
                ++first2;
            }
            else
            {
                *d_first = *first1;
                ++first1;
                ++first2;
            }
            ++d_first;
        }
        if (first1 != last1)
        {
            return ddstl::copy(first1, last1, d_first);
        }
        else if (first2 != last2)
        {
            return ddstl::copy(first2, last2, d_first);
        }
        else
        {
            return d_first;
        }
    }

    template <class InputIt1, class InputIt2, class OutputIt>
    inline OutputIt set_union(InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2,
                              OutputIt d_first)
    {
        return set_union_aux(first1, last1, first2, last2, d_first, ddstl::iter_bi_less_functor());
    }

    template <class InputIt1, class InputIt2, class OutputIt, class Compare>
    inline OutputIt set_union(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        return set_union_aux(first1, last1, first2, last2, d_first, ddstl::iter_bi_pred_functor<Compare>(comp));
    }
}

#endif