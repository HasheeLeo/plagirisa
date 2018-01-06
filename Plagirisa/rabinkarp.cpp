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

// Multiple pattern overload
std::vector<int> rabinkarp(const std::string &text,
	const std::vector<std::string> &patterns)
{
	std::vector<int> indices;
	const int textLength = text.length();
	int patternLength = INT_MAX;
	// Set patternLength to the length of smallest pattern string
	for (const std::string &str : patterns) {
		const int curLength = str.length();
		if (patternLength > curLength)
			patternLength = curLength;
	}
	BloomFilter bloomFilter;
	const int totalPatterns = patterns.size();
	// Insert only the first n characters of every pattern
	// n = size of the smallest pattern string
	for(int i = 0; i < totalPatterns; ++i)
		bloomFilter.insert(patterns[i].substr(0, patternLength));

	for (int i = 0; i < textLength - patternLength + 1; ++i) {
		if (bloomFilter.exists(text.substr(i, patternLength)))
			indices.push_back(i);
	}
	return indices;
}

// Single pattern overload
std::vector<int> rabinkarp(const std::string &text, const std::string &pattern)
{
	std::vector<int> indices;
	const int patternHash = BloomFilter::hash(pattern);
	const int textLength = text.length();
	const int patternLength = pattern.length();
	int curHash = -1;

	for (int i = 0; i < textLength - patternLength + 1; ++i) {
		// If we have calculated a hash last time, slide hash
		if (curHash != -1)
			curHash = BloomFilter::hashroll(curHash, text[i - 1],
				text[i + patternLength - 1], patternLength);
		else
			curHash = BloomFilter::hash(text.substr(i, patternLength));

		// If hashes match, match the words character by character to ensure it
		// was not a hash collision
		if (curHash == patternHash) {
			bool matched = true;
			for (int j = 0; j < patternLength; ++j) {
				if (text[i + j] != pattern[j]) {
					matched = false;
					break;
				}
			}

			if (matched)
				indices.push_back(i);
		}
	}
	return indices;
}
