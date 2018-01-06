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

static void multiplepattern_test() {
    const std::string text1 = "The quick brown fox jumps over the lazy dog!\n";
	const std::vector<std::string> patterns1 = { "brown", "over", "mps", "og",
		"wow" };
    std::vector<int> indices = rabinkarp(text1, patterns1);
	assert(indices[0] == 10);
	assert(indices[1] == 22);
	assert(indices[2] == 26);
	assert(indices[3] == 41);
    assert(indices.size() == 4);

	const std::string text2 = "aabaacaadaabaaba";
	const std::vector<std::string> patterns2 = { "aaba", "baa", "daaba",
		"lala"};
    indices = rabinkarp(text2, patterns2);
    assert(indices[0] == 0);
    assert(indices[1] == 2);
	assert(indices[2] == 8);
	assert(indices[3] == 9);
	assert(indices[4] == 11);
	assert(indices[5] == 12);
    assert(indices.size() == 6);

    std::cout << "rabinkarp_multiplepattern: All tests passed.\n";
}

static void singlepattern_test() {
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

	std::cout << "rabinkarp_singlepattern: All tests passed.\n";
}

void rabinkarp_test() {
	singlepattern_test();
	multiplepattern_test();
	std::cout << "rabinkarp: All tests passed.\n";
}
