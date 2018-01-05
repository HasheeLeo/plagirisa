/*******************************************************************************
    File: rabinkarp_test.cpp
    Purpose: Implements tests for the rabinkarp function.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#include "stdafx.hpp"
#include "rabinkarp_test.hpp"
#include "rabinkarp.hpp"

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

void rabinkarp_test() {
    const std::string text1 = "The quick brown fox jumps over the lazy dog!\n";
	const std::vector<std::string> patterns1 = { "quick", "brown", "jumps" };
    std::vector<int> indices = rabinkarp(text1, patterns1);
    assert(indices[0] == 4);
	assert(indices[1] == 10);
	assert(indices[2] == 20);
    assert(indices.size() == 3);

	const std::string text2 = "aabaacaadaabaaba";
	const std::vector<std::string> patterns2 = { "a", "b", "d" };
    indices = rabinkarp(text2, patterns2);
    assert(indices[0] == 0);
    assert(indices[1] == 1);
	assert(indices[2] == 2);
	assert(indices[3] == 3);
	assert(indices[4] == 4);
	assert(indices[5] == 6);
	assert(indices[6] == 7);
	assert(indices[7] == 8);
	assert(indices[8] == 9);
	assert(indices[9] == 10);
	assert(indices[10] == 11);
	assert(indices[11] == 12);
	assert(indices[12] == 13);
	assert(indices[13] == 14);
	assert(indices[14] == 15);
    assert(indices.size() == 15);

    std::cout << "rabinkarp: All tests passed.\n";
}
