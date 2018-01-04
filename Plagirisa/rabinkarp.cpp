/*******************************************************************************
    File: rabinkarp.cpp
    Purpose: Implements the Rabin-Karp algorithm.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#include "stdafx.hpp"
#include "rabinkarp.hpp"

#include <cmath>

static constexpr int NUM_ALPHABETS = 127;

inline static uint rabinkarp_hashslide(uint lastHash, char prevChar,
	char nextChar, size_t patternLength)
{
	uint hash = lastHash - (prevChar * pow(NUM_ALPHABETS, patternLength - 1));
	hash *= NUM_ALPHABETS;
	hash += nextChar;
	return hash;
}

static uint rabinkarp_hash(const std::string &word) {
	const int wordSize = word.length();
	uint hash = 0;
	for (int i = 0; i < wordSize; ++i)
		hash += word[i] * pow(NUM_ALPHABETS, wordSize - i - 1);

	return hash;
}

std::vector<int> rabinkarp(const std::string &text, const std::string &pattern)
{
	std::vector<int> indices;
	const int patternHash = rabinkarp_hash(pattern);
	const int textLength = text.length();
	const int patternLength = pattern.length();
	int curHash = -1;

	for (int i = 0; i < textLength - patternLength + 1; ++i) {
		// If we have calculated a hash last time, slide hash
		if (curHash != -1)
			curHash = rabinkarp_hashslide(curHash, text[i - 1],
				text[i + patternLength - 1], patternLength);
		else
			curHash = rabinkarp_hash(text.substr(i, patternLength));

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
