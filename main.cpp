
#include <vector>
#include <cassert>
#include <cstddef>
#include "vector.h"

#include "test/test_macros.h"
#include "test/test_allocator.h"
#include "test/test_iterators.h"
#include "test/min_allocator.h"
#include "test/asan_testing.h"

namespace adl {
    struct S {};
    void make_move_iterator(S*) {}
}

int main(int, char**)
{
    {
        typedef vector<int> V;
        V v(100);
        int a[] = {1, 2, 3, 4, 5};
        const int N = sizeof(a)/sizeof(a[0]);
        V::iterator i = v.insert(v.cbegin() + 10, input_iterator<const int*>(a),
                                 input_iterator<const int*>(a+N));
        assert(v.size() == 100 + N);
//        assert(is_contiguous_container_asan_correct(v));
        assert(i == v.begin() + 10);
        int j;
        for (j = 0; j < 10; ++j)
            assert(v[j] == 0);
        for (std::size_t k = 0; k < N; ++j, ++k)
            assert(v[j] == a[k]);
        for (; j < 105; ++j)
            assert(v[j] == 0);
    }
    {
        typedef std::vector<int> V;
        V v(100);
        int a[] = {1, 2, 3, 4, 5};
        const int N = sizeof(a)/sizeof(a[0]);
        V::iterator i = v.insert(v.cbegin() + 10, forward_iterator<const int*>(a),
                                 forward_iterator<const int*>(a+N));
        assert(v.size() == 100 + N);
        assert(is_contiguous_container_asan_correct(v));
        assert(i == v.begin() + 10);
        int j;
        for (j = 0; j < 10; ++j)
            assert(v[j] == 0);
        for (std::size_t k = 0; k < N; ++j, ++k)
            assert(v[j] == a[k]);
        for (; j < 105; ++j)
            assert(v[j] == 0);
    }
    {
        typedef std::vector<int> V;
        V v(100);
        while(v.size() < v.capacity()) v.push_back(0); // force reallocation
        size_t sz = v.size();
        int a[] = {1, 2, 3, 4, 5};
        const unsigned N = sizeof(a)/sizeof(a[0]);
        V::iterator i = v.insert(v.cbegin() + 10, forward_iterator<const int*>(a),
                                 forward_iterator<const int*>(a+N));
        assert(v.size() == sz + N);
        assert(i == v.begin() + 10);
        std::size_t j;
        for (j = 0; j < 10; ++j)
            assert(v[j] == 0);
        for (std::size_t k = 0; k < N; ++j, ++k)
            assert(v[j] == a[k]);
        for (; j < v.size(); ++j)
            assert(v[j] == 0);
    }
    {
        typedef std::vector<int> V;
        V v(100);
        v.reserve(128); // force no reallocation
        size_t sz = v.size();
        int a[] = {1, 2, 3, 4, 5};
        const unsigned N = sizeof(a)/sizeof(a[0]);
        V::iterator i = v.insert(v.cbegin() + 10, forward_iterator<const int*>(a),
                                 forward_iterator<const int*>(a+N));
        assert(v.size() == sz + N);
        assert(i == v.begin() + 10);
        std::size_t j;
        for (j = 0; j < 10; ++j)
            assert(v[j] == 0);
        for (std::size_t k = 0; k < N; ++j, ++k)
            assert(v[j] == a[k]);
        for (; j < v.size(); ++j)
            assert(v[j] == 0);
    }
    {
        typedef std::vector<int, limited_allocator<int, 308> > V;
        V v(100);
        int a[] = {1, 2, 3, 4, 5};
        const int N = sizeof(a)/sizeof(a[0]);
        V::iterator i = v.insert(v.cbegin() + 10, input_iterator<const int*>(a),
                                 input_iterator<const int*>(a+N));
        assert(v.size() == 100 + N);
        assert(is_contiguous_container_asan_correct(v));
        assert(i == v.begin() + 10);
        int j;
        for (j = 0; j < 10; ++j)
            assert(v[j] == 0);
        for (std::size_t k = 0; k < N; ++j, ++k)
            assert(v[j] == a[k]);
        for (; j < 105; ++j)
            assert(v[j] == 0);
    }
    {
        typedef std::vector<int, limited_allocator<int, 300> > V;
        V v(100);
        int a[] = {1, 2, 3, 4, 5};
        const int N = sizeof(a)/sizeof(a[0]);
        V::iterator i = v.insert(v.cbegin() + 10, forward_iterator<const int*>(a),
                                 forward_iterator<const int*>(a+N));
        assert(v.size() == 100 + N);
        assert(is_contiguous_container_asan_correct(v));
        assert(i == v.begin() + 10);
        int j;
        for (j = 0; j < 10; ++j)
            assert(v[j] == 0);
        for (std::size_t k = 0; k < N; ++j, ++k)
            assert(v[j] == a[k]);
        for (; j < 105; ++j)
            assert(v[j] == 0);
    }

    {
        typedef std::vector<int, min_allocator<int> > V;
        V v(100);
        int a[] = {1, 2, 3, 4, 5};
        const int N = sizeof(a)/sizeof(a[0]);
        V::iterator i = v.insert(v.cbegin() + 10, input_iterator<const int*>(a),
                                 input_iterator<const int*>(a+N));
        assert(v.size() == 100 + N);
        assert(is_contiguous_container_asan_correct(v));
        assert(i == v.begin() + 10);
        int j;
        for (j = 0; j < 10; ++j)
            assert(v[j] == 0);
        for (std::size_t k = 0; k < N; ++j, ++k)
            assert(v[j] == a[k]);
        for (; j < 105; ++j)
            assert(v[j] == 0);
    }
    {
        typedef std::vector<int, min_allocator<int> > V;
        V v(100);
        int a[] = {1, 2, 3, 4, 5};
        const int N = sizeof(a)/sizeof(a[0]);
        V::iterator i = v.insert(v.cbegin() + 10, forward_iterator<const int*>(a),
                                 forward_iterator<const int*>(a+N));
        assert(v.size() == 100 + N);
        assert(is_contiguous_container_asan_correct(v));
        assert(i == v.begin() + 10);
        int j;
        for (j = 0; j < 10; ++j)
            assert(v[j] == 0);
        for (std::size_t k = 0; k < N; ++j, ++k)
            assert(v[j] == a[k]);
        for (; j < 105; ++j)
            assert(v[j] == 0);
    }
    {
        std::vector<adl::S> s;
        s.insert(s.end(), input_iterator<adl::S*>(), input_iterator<adl::S*>());
    }

    return 0;
}