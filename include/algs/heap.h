#ifndef MSTL_ALGORITHM_HEAP_H
#define MSTL_ALGORITHM_HEAP_H

#include "iterator.h"

namespace ddstl
{
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

#endif