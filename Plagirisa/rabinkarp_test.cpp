#include "rabinkarp_test.hpp"
/*******************************************************************************
    File: rabinkarp_test.cpp
    Purpose: Implements tests for the rabinkarp function.
    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/
#include "rabinkarp.hpp"
#include <iostream>
#include <cassert>

void rabinkarp_test() {
    std::string haystack = "The quick brown fox jumps over the lazy dog!\n";
    std::vector<int> indices = rabinkarp_find("brown", haystack);
    assert(indices[0] == 10);
    assert(indices.size() == 1);

    indices = rabinkarp_find("quick", haystack);
    assert(indices[0] == 4);
    assert(indices.size() == 1);

    indices = rabinkarp_find("fox", haystack);
    assert(indices[0] == 16);
    assert(indices.size() == 1);


    std::cout << "rabinkarp: All tests passed.\n";
}