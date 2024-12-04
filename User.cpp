
/**
 * @file User.cpp
 * @brief Implementation of User class for user registrations.
 * 
 * This file provides the implementation for the User class, which represents a generic user
 * and contains their user ID and name.
 */

#include "User.h"

using namespace crow;

/**
 * @brief Constructs a User object from JSON data.
 * 
 * @param readValueJson JSON object containing user details.
 */
User::User(json::rvalue readValueJson)
{
    updateFromJson(readValueJson);
}

/**
 * @brief Converts the User object to a JSON representation.
 * 
 * @return A JSON object containing the user's details.
 */
json::wvalue User::convertToJson()
{
    json::wvalue writeJson;
    writeJson["userId"] = userId;
    writeJson["userName"] = userName;

    return writeJson;
}

/**
 * @brief Updates the User object from a JSON representation.
 * 
 * @param readValueJson JSON object containing updated user details.
 */
void User::updateFromJson(json::rvalue readValueJson)
{
    userId = readValueJson["userId"].s();
    userName = readValueJson["userName"].s();
}
