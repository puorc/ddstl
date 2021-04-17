#ifndef MSTL_ITERATOR_H
#define MSTL_ITERATOR_H

#include <iterator>
#include <type_traits>
#include <vector>

namespace ddstl {
    template<class InputIt>
    typename std::iterator_traits<InputIt>::difference_type
    distance_aux(InputIt first, InputIt last, std::input_iterator_tag) {
        typename std::iterator_traits<InputIt>::difference_type n = 0;
        while (first != last) {
            ++first;
            ++n;
        }
        return n;
    }

    template<class InputIt>
    typename std::iterator_traits<InputIt>::difference_type
    distance_aux(InputIt first, InputIt last, std::random_access_iterator_tag) {
        return last - first;
    }

    template<class InputIt>
    typename std::iterator_traits<InputIt>::difference_type
    distance(InputIt first, InputIt last) {
        return distance_aux(first, last, typename std::iterator_traits<InputIt>::iterator_category());
    }

    template<class InputIt, class Distance>
    void advance_aux(InputIt &it, Distance n, std::input_iterator_tag) {
        while (n > 0) {
            ++it;
            --n;
        }
    }

    template<class BiDirectionalIt, class Distance>
    void advance_aux(BiDirectionalIt &it, Distance n, std::bidirectional_iterator_tag) {
        if (n > 0) {
            while (n-- > 0) {
                ++it;
            }
        } else {
            while (n++ < 0) {
                --it;
            }
        }
    }

    template<class RandomAccessIt, class Distance>
    void advance_aux(RandomAccessIt &it, Distance n, std::random_access_iterator_tag) {
        it += n;
    }

    template<class InputIt, class Distance>
    inline void advance(InputIt &it, Distance n) {
        typename std::iterator_traits<InputIt>::difference_type d = n;
        advance_aux(it, d, typename std::iterator_traits<InputIt>::iterator_category());
    }
}

#endif //MSTL_ITERATOR_H