/**
 * @file Administrator.cpp
 * @brief Implementation of the Administrator class.
 * 
 * This file provides the implementation for the Administrator class, allowing 
 * administrators to set up and manage labs.
 */

#include "Administrator.h"
#include <algorithm> 
#include <map>

using namespace crow;

extern std::map<std::string, Lab> labsMap;

/**
 * @brief Constructs an Administrator object from JSON data.
 * 
 * @param readValueJson JSON object containing administrator details.
 */
Administrator::Administrator(crow::json::rvalue& readValueJson) : User(readValueJson), labManaged(nullptr)
{
    updateFromJson(readValueJson);
}

/**
 * @brief Converts the Administrator object to a JSON representation.
 * 
 * @return A JSON object containing administrator details and the lab they manage.
 */
crow::json::wvalue Administrator::convertToJson()
{
    crow::json::wvalue writeJson = User::convertToJson();

    // Serialize the managed lab
    writeJson["labManaged"] = labManaged->convertToJson();

    return writeJson;
}

/**
 * @brief Updates the Administrator object from a JSON representation.
 * 
 * @param readValueJson JSON object containing updated administrator and lab details.
 */
void Administrator::updateFromJson(crow::json::rvalue readValueJson)
{
    User::updateFromJson(readValueJson);
    
    // Directly access labManaged from JSON
    const crow::json::rvalue& labJson = readValueJson["labManaged"];
    std::string labId = labJson["labId"].s();

    // Set labManaged to point to the Lab in labsMap
    labManaged = &(labsMap[labId]);

    // Update the Lab details
    labManaged->updateFromJson(labJson);
}
