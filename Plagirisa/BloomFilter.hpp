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

	static constexpr int NUM_ALPHABETS = 127;
private:
	// Is a prime number
	static constexpr int bloomSize = 997;
	std::bitset<bloomSize> table = { 0 };
	uint curHash = 0;
	char lastChar = 0;

	uint hash(const std::string &word);
	inline uint hashroll(uint lastHash, char prevChar, char nextChar,
		size_t patternLength);
};

#endif // BLOOMFILTER_HPP
