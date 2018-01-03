/*******************************************************************************
    File: rabinkarp.cpp
    Purpose: Implements the Rabin-Karp algorithm.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

// Including libraries.
#include "rabinkarp.hpp"
#include <iostream>
using namespace std;

// Macros and constants.
#define PRIME_NUMBER 101
#define NUMBER_ALPHABETS 256

// Function rabinkarp_find to search a pattern in a text.
std::vector<int> rabinkarp_find(std::string pattern, std::string text)
{
    // Local variables.
    auto patternLength = static_cast<int>(pattern.length());
    auto textLength = static_cast<int>(text.length());
    int i, j;
    int patternHash = 0;
    int textHash = 0;
    int hash = 1;
    std::vector <int> indices;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < patternLength-1; i++)
        hash = (hash*NUMBER_ALPHABETS)%PRIME_NUMBER;

    // Calculate the hash value of pattern and first
    // window of text of size equal to pattern.
    for (i = 0; i < patternLength; i++)
    {
        patternHash = (NUMBER_ALPHABETS*patternHash + pattern[i])%PRIME_NUMBER;
        textHash = (NUMBER_ALPHABETS*textHash + text[i])%PRIME_NUMBER;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= textLength - patternLength; i++)
    {
        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters on by one
        if ( patternHash == textHash )
        {
            // Check for characters one by one.
            for (j = 0; j < patternLength; j++)
            {
                // If no character match is found break the loop.
                if (text[i+j] != pattern[j])
                    break;
            }

            // If p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1].
            if (j == patternLength) {
                printf("Pattern found at index %d \n", i);
                indices.push_back(i);
            }
        }

        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit.
        if ( i < textLength - patternLength )
        {
            textHash = (NUMBER_ALPHABETS*(textHash - text[i]*hash) +
				text[i+patternLength])%PRIME_NUMBER;

            // We might get negative value of t, converting it
            // to positive
            if (textHash < 0)
                textHash = (textHash + PRIME_NUMBER);
        }
    }
    return indices;
}