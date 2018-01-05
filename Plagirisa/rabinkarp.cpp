/*******************************************************************************
    File: rabinkarp.cpp
    Purpose: Implements the Rabin-Karp algorithm.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#include "stdafx.hpp"
#include "rabinkarp.hpp"
#include "BloomFilter.hpp"

#include <string>
#include <vector>

std::vector<int> rabinkarp(const std::string &text,
	const std::vector<std::string> &patterns)
{
	std::vector<int> indices;
	const int textLength = text.length();
	const int patternLength = patterns[0].length();
	BloomFilter bloomFilter;
	bloomFilter.insert(patterns);

	for (int i = 0; i < textLength - patternLength + 1; ++i) {
		if (bloomFilter.exists(text.substr(i, patternLength)))
			indices.push_back(i);
	}
	return indices;
}
