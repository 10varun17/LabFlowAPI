
/**
 * @file Professor.cpp
 * @brief Implementation of Professor class.
 * 
 * This file provides the implementation for the Professor class, which represents 
 * a professor involved in a lab and contains their personal information and lab activities.
 */

#include "Professor.h"
#include <algorithm> 

using namespace crow;

/**
 * @brief Constructs a Professor object from JSON data.
 * 
 * @param readValueJson JSON object containing professor details.
 */
Professor::Professor(crow::json::rvalue readValueJson) : User(readValueJson)
{
    updateFromJson(readValueJson);
}

/**
 * @brief Converts the Professor object to a JSON representation.
 * 
 * @return A JSON object containing the professor's details.
 */
crow::json::wvalue Professor::convertToJson()
{
    crow::json::wvalue writeJson = User::convertToJson();

    // Serialize experimentIds
    std::vector<json::wvalue> experimentIdsArray;
    for (std::string id : experimentIds)
    {
        experimentIdsArray.push_back(id);
    }
    writeJson["experimentIds"] = std::move(experimentIdsArray);

    return writeJson;
}

/**
 * @brief Updates the Professor object from a JSON representation.
 * 
 * @param readValueJson JSON object containing updated professor details.
 */
void Professor::updateFromJson(crow::json::rvalue readValueJson)
{
    User::updateFromJson(readValueJson);

    if (readValueJson.has("experimentIds"))
    {
        experimentIds.clear();
        for (auto& idJson : readValueJson["experimentIds"])
        {
            experimentIds.push_back(idJson.s());
        }
    }
}
