/*******************************************************************************
    File: BloomFilter.cpp
    Purpose: Implements the BloomFilter class.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#include "stdafx.hpp"
#include "BloomFilter.hpp"

#include <vector>
#include <string>

void BloomFilter::insert(const std::string &word) {
	table[hash(word) % bloomSize] = 1;
}

void BloomFilter::insert(const std::vector<std::string> &words) {
	for (const std::string &word : words)
		insert(word);
}

bool BloomFilter::exists(const std::string &word)
{
	const size_t wordLength = word.length();
	// If the hash has already been calculated, use hash roll
	// This computes the new hash value from the old hash in O(1)
	if (!lastChar)
		curHash = hash(word);
	else
		curHash = hashroll(curHash, lastChar, word[wordLength - 1], wordLength);
	
	lastChar = word[0];
	return table[curHash % bloomSize];
}

inline uint BloomFilter::hashroll(uint lastHash, char prevChar, char nextChar,
	size_t patternLength)
{
	uint hash = lastHash - (prevChar * pow(NUM_ALPHABETS, patternLength - 1));
	hash *= NUM_ALPHABETS;
	hash += nextChar;
	return hash;
}

uint BloomFilter::hash(const std::string &word) {
	const int wordSize = word.length();
	uint hash = 0;
	for (int i = 0; i < wordSize; ++i)
		hash += word[i] * pow(NUM_ALPHABETS, wordSize - i - 1);

	return hash;
}
