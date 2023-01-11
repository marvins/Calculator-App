/**
 * @file    String_Utilities.hpp
 * @author  Marvin Smith
 * @date    1/11/2023
 */
#pragma once

// C++ Libraries
#include <string>
#include <vector>

/**
 * @enum StringDirection
 */
enum class StringDirection : uint8_t
{
    LEFT  = 1,
    RIGHT = 2,
    BOTH  = 3,
};  // End of StringDirection Enum Class


/**
 * @brief Split a string by a designated pattern. 
 */
std::vector<std::string> String_Split( const std::string& data,
                                       const std::string& pattern );

/**
 * @brief Trim the string on both ends.
 *
 * @param[in] data String to trim.
 *
 * @return Trimmed string.
 */
std::string String_Trim( const std::string& data );


/**
 * @brief Trim the string on both ends given the strip pattern.
 *
 * @param[in] data
 * @param[in] strip_pattern
 *
 * @return Trimmed string.
 */
std::string String_Trim( const std::string& data,
                         const std::string& strip_pattern );


/**
 * @brief Trim a string.
 *
 * @param[in] data Data to trim.
 * @param[in] strip_patterns Pattern to strip.
 * @param[in] strip_direction Direction to strip.
 *
 * @return Resulting string.
 */
std::string String_Trim( const std::string&     data,
                         const std::string&     strip_patterns,
                         const StringDirection& strip_direction );

/**
 * @brief Method to check if a string is numeric
 */
bool Is_Number( const std::string& value );
