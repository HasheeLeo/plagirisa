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

// Function to calculate mod value of two integers.
// Even if the value of a is negative, output is correct.
int calculateMod(int a, int b)
{
    return (a % b + b) % b;
}
