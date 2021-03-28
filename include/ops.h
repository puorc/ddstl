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

    template<typename BiPredicate>
    struct iter_bi_pred_functor {
        BiPredicate &m_predicate;

        explicit iter_bi_pred_functor(BiPredicate &pred) : m_predicate(pred) {}

        template<typename ForwardIt1, typename ForwardIt2>
        bool operator()(ForwardIt1 it1, ForwardIt2 it2) {
            return bool(m_predicate(*it1, *it2));
        }
    };

    struct iter_bi_equal_functor {
        template<typename Value1, typename Value2>
        bool operator()(Value1 v1, Value2 v2) {
            return v1 == v2;
        }
    };
}

#endif //MSTL_OPS_H
