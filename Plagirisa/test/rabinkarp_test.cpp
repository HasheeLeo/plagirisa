/*******************************************************************************
    File: rabinkarp_test.cpp
    Purpose: Implements tests for the rabinkarp function.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#include <iostream>
#include <cassert>
#include <vector>

void rabinkarp_test() {
    const char *haystack = "The quick brown fox jumps over the lazy dog!\n";
    std::vector<int> indices = rabinkarp(haystack, "brown");
    assert(indices[0] == 10);
    assert(indices.size() == 1);

    indices = rabinkarp(haystack, "tHE");
    assert(indices[0] == 0);
    assert(indices[1] == 31);
    assert(indices.size() == 2);

    std::cout << "rabinkarp: All tests passed.\n";
}
