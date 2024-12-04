/**
 * @file Budget.cpp
 * @brief Implementation of the Budget class.
 * 
 * This file provides the implementation for the Budget class, which represents 
 * the current budget status and tracks total, spent, and remaining amounts.
 */

#include "Budget.h"

using namespace crow;

/**
 * @brief Constructs a Budget object from JSON data.
 * 
 * @param readValueJson JSON object containing budget details.
 */
Budget::Budget(json::rvalue readValueJson)
{
    updateFromJson(readValueJson);
}

/**
 * @brief Converts the Budget object to a JSON representation.
 * 
 * @return A JSON object containing the budget details.
 */
json::wvalue Budget::convertToJson()
{
    json::wvalue writeJson;
    writeJson["totalAmount"] = totalAmount;
    writeJson["spentAmount"] = spentAmount;
    writeJson["remainingAmount"] = remainingAmount;
    return writeJson;
}

/**
 * @brief Updates the Budget object from a JSON representation.
 * 
 * @param readValueJson JSON object containing updated budget details.
 */
void Budget::updateFromJson(json::rvalue readValueJson)
{
    totalAmount = readValueJson["totalAmount"].d();
    spentAmount = readValueJson["spentAmount"].d();
    remainingAmount = readValueJson["remainingAmount"].d();
}
