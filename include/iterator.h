#ifndef MSTL_ITERATOR_H
#define MSTL_ITERATOR_H

#endif //MSTL_ITERATOR_H

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
}