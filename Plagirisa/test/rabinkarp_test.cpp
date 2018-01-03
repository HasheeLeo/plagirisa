/*******************************************************************************
    File: rabinkarp_test.cpp
    Purpose: Implements tests for the rabinkarp function.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#include "rabinkarp_test.hpp"
#include "rabinkarp.hpp"

#include <iostream>
#include <cassert>
#include <vector>

void rabinkarp_test() {
    const char *text1 = "The quick brown fox jumps over the lazy dog!\n";
    std::vector<int> indices = rabinkarp(text1, "brown");
    assert(indices[0] == 10);
    assert(indices.size() == 1);

	const char *text2 = "aabaacaadaabaaba";
    indices = rabinkarp(text2, "aaba");
    assert(indices[0] == 0);
    assert(indices[1] == 9);
	assert(indices[2] == 12);
    assert(indices.size() == 3);

    std::cout << "rabinkarp: All tests passed.\n";
}
