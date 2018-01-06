/*******************************************************************************
    File: BloomFilter.hpp
    Purpose: Defines the BloomFilter class.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#ifndef BLOOMFILTER_HPP
#define BLOOMFILTER_HPP

#include <bitset>
#include <vector>
#include <string>

using uint = unsigned int;

class BloomFilter {
public:
	void insert(const std::string &word);
	bool exists(const std::string &word);

	static uint hash(const std::string &word);
	
	static inline uint BloomFilter::hashroll(uint lastHash, char prevChar,
		char nextChar, size_t patternLength)
	{
		uint hash = lastHash - (prevChar * pow(BloomFilter::NUM_ALPHABETS,
			patternLength - 1));
		hash *= BloomFilter::NUM_ALPHABETS;
		hash += nextChar;
		return hash;
	}

	static constexpr int NUM_ALPHABETS = 127;
private:
	// Is a prime number
	static constexpr int bloomSize = 997;
	std::bitset<BloomFilter::bloomSize> table = { 0 };
	uint curHash = 0;
	char lastChar = 0;
};

#endif // BLOOMFILTER_HPP
