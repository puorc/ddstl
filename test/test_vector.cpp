//#define CATCH_CONFIG_MAIN
//
//#include "vector.h"
//#include <vector>
//#include <catch2/catch.hpp>
//#include <string>
//
//TEST_CASE("vectors can be inserted and erased", "[vector]") {
//    vector<int> a;
//    for (int i = 0; i < 10; i++) {
//        a.push_back(i);
//    }
//    a.insert(a.end(), 5, 3);
//    std::vector<int> c;
//    c.push_back(1);
//    c.push_back(2);
//    c.push_back(3);
//    a.insert(a.end(), c.begin(), c.end());
//    for (auto b : a) {
//        std::cout << b << std::endl;
//    }
//    REQUIRE(a.size() == 5);
//}
