#ifndef MSTL_OPS_H
#define MSTL_OPS_H

#include "utility.h"

namespace ddstl {
    template<typename Value>
    struct iter_equal_value_functor {
        const Value &m_val;

        explicit iter_equal_value_functor(const Value &val) : m_val(val) {}

        template<typename Iterator>
        bool operator()(Iterator it) {
            return *it == m_val;
        }
    };

    template<typename Predicate>
    struct iter_pred_functor {
        const Predicate &m_predicate;

        explicit iter_pred_functor(const Predicate &predicate) : m_predicate(ddstl::move(predicate)) {}

        template<typename Iterator>
        bool operator()(Iterator it) {
            return bool(m_predicate(*it));
        }
    };


}

#endif //MSTL_OPS_H
