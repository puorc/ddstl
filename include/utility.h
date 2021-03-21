#ifndef MSTL_UTILITY_H
#define MSTL_UTILITY_H

#include <type_traits>

namespace ddstl {
    template< class T >
    typename std::remove_reference<T>::type&& move( T&& t ) noexcept;
}















#endif //MSTL_UTILITY_H
