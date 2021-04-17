#ifndef MSTL_PERMUTATION_MODIFYING_H
#define MSTL_PERMUTATION_MODIFYING_H

namespace ddstl
{
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
            ddstl::reverse(first, last);
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
            ddstl::swap(*it, *back);
            ++it;
            ddstl::reverse(it, last);
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
            ddstl::reverse(first, last);
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
            ddstl::swap(*it, *back);
            ++it;
            ddstl::reverse(it, last);
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
}

#endif