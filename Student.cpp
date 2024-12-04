
/**
 * @file Student.cpp
 * @brief Implementation of Student class.
 * 
 * This file provides the implementation for the Student class, which represents 
 * a student involved in a lab and contains their personal information and lab activities.
 */

#include "Student.h"
#include <algorithm> 

using namespace crow;

/**
 * @brief Constructs a Student object from JSON data.
 * 
 * @param readValueJson JSON object containing student details.
 */
Student::Student(crow::json::rvalue readValueJson) : User(readValueJson)
{
    updateFromJson(readValueJson);
}

/**
 * @brief Converts the Student object to a JSON representation.
 * 
 * @return A JSON object containing the student's details.
 */
crow::json::wvalue Student::convertToJson()
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
 * @brief Updates the Student object from a JSON representation.
 * 
 * @param readValueJson JSON object containing updated student details.
 */
void Student::updateFromJson(crow::json::rvalue readValueJson)
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
