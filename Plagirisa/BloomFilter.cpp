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
	table[BloomFilter::hash(word) % BloomFilter::bloomSize] = 1;
}

bool BloomFilter::exists(const std::string &word)
{
	const size_t wordLength = word.length();
	// If the hash has already been calculated, use hash roll
	// This computes the new hash value from the old hash in O(1)
	if (!lastChar)
		curHash = BloomFilter::hash(word);
	else
		curHash = BloomFilter::hashroll(curHash, lastChar, word[wordLength - 1],
			wordLength);
	
	lastChar = word[0];
	return table[curHash % BloomFilter::bloomSize];
}

uint BloomFilter::hash(const std::string &word) {
	const int wordSize = word.length();
	uint hash = 0;
	for (int i = 0; i < wordSize; ++i)
		hash += word[i] * pow(BloomFilter::NUM_ALPHABETS, wordSize - i - 1);

	return hash;
}
