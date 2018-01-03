/*******************************************************************************
    File: rabinkarp.hpp
    Purpose: Defines the Rabin-Karp algorithm.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#ifndef rabinkarp
#define rabinkarp

// Including libraries.
#include <vector>
#include <string>

std::vector<int> rabinkarp_find(std::string pattern, std::string text);

#endif