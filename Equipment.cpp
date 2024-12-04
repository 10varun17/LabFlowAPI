/**
 * @file Equipment.cpp
 * @brief Implementation of the Equipment class.
 * 
 * This file provides the implementation for the Equipment class, which represents 
 * an equipment in a lab and holds various information such as name, description, 
 * and availability.
 */

#include "Equipment.h"

using namespace crow;

/**
 * @brief Constructs an Equipment object from JSON data.
 * 
 * @param readValueJson JSON object containing equipment details.
 */
Equipment::Equipment(json::rvalue readValueJson)
{
    updateFromJson(readValueJson);
}

/**
 * @brief Converts the Equipment object to a JSON representation.
 * 
 * @return A JSON object containing the equipment details.
 */
json::wvalue Equipment::convertToJson()
{
    json::wvalue writeJson;
    writeJson["equipmentId"] = equipmentId;
    writeJson["name"] = name;
    writeJson["description"] = description;
    writeJson["available"] = available;

    return writeJson;
}

/**
 * @brief Updates the Equipment object from a JSON representation.
 * 
 * @param readValueJson JSON object containing updated equipment details.
 */
void Equipment::updateFromJson(json::rvalue readValueJson)
{
    equipmentId = readValueJson["equipmentId"].s();
    name = readValueJson["name"].s();
    description = readValueJson["description"].s();
    available = readValueJson["available"].b();
}
