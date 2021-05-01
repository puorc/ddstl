#ifndef MSTL_ALGORITHM_OTHERS_H
#define MSTL_ALGORITHM_OTHERS_H

#include "modifying.h"

namespace ddstl
{
    template <class InputIt1, class InputIt2, class OutputIt, class Compare>
    OutputIt merge_aux(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (comp(first2, first1))
            {
                *d_first = *first2;
                ++first2;
            }
            else
            {
                *d_first = *first1;
                ++first1;
            }
            ++d_first;
        }
        if (first2 != last2)
        {
            return ddstl::copy(first2, last2, d_first);
        }
        else if (first1 != last1)
        {
            return ddstl::copy(first1, last1, d_first);
        }
        else
        {
            return d_first;
        }
    }

    template <class InputIt1, class InputIt2, class OutputIt>
    inline OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first)
    {
        return merge_aux(first1, last1, first2, last2, d_first, ddstl::iter_bi_less_functor());
    }

    template <class InputIt1, class InputIt2, class OutputIt, class Compare>
    inline OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
    {
        return merge_aux(first1, last1, first2, last2, d_first, ddstl::iter_bi_pred_functor<Compare>(comp));
    }
}

#endif
