/*******************************************************************************
    File: RabinKarp.hpp
    Purpose: Implements the Rabin Karp algorithm for string matching.
    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

// Macros
#define numberOfAlphas 256
#define primeNumber 101

// Function to calculate hash of a given string.
double calculateHash(const string &input)
{
    int hash = 1, i;
    for (i = 0; i < input.length() - 1; i++)
    {
        hash = (hash * numberOfAlphas) % primeNumber;
    }
    return hash;
}
