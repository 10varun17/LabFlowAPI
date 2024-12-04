
/**
 * @file toLowerHelper.cpp
 * @brief Implementation of the toLower method.
 * 
 * This file contains the implementation of a helper function to convert a string to lowercase.
 */

#include "toLowerHelper.h"

/**
 * @brief Converts a string to lowercase.
 * 
 * @param input The input string to be converted.
 * @return A new string where all characters are in lowercase.
 */
std::string toLower(const std::string& input) {
    std::string result = input;
    for (char& c : result) {
        c = std::tolower(c); // Convert each character to lowercase
    }
    return result;
}
