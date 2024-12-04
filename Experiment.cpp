
/**
 * @file Experiment.cpp
 * @brief Implementation of the Experiment class.
 * 
 * This file provides the implementation for the Experiment class, which holds
 * various details about an experiment conducted in a lab.
 */

#include "Experiment.h"
#include <algorithm> // For std::remove

using namespace std;
using namespace crow;

/**
 * @brief Constructs an Experiment object from JSON data.
 * 
 * @param readValueJson JSON object containing experiment details.
 */
Experiment::Experiment(json::rvalue readValueJson)
{
    updateFromJson(readValueJson);
}

/**
 * @brief Converts the Experiment object to a JSON representation.
 * 
 * @return A JSON object containing the experiment details.
 */
json::wvalue Experiment::convertToJson()
{
    json::wvalue writeJson;
    writeJson["experimentId"] = experimentId;
    writeJson["title"] = title;
    writeJson["description"] = description;
    writeJson["startTime"] = startTime;
    writeJson["endTime"] = endTime;
    writeJson["cost"] = cost;
    writeJson["approvalStatus"] = approvalStatus;

    // Serialize userIds
    std::vector<json::wvalue> userIdsArray;
    for (std::string id : userIds) 
    {
        userIdsArray.push_back(id);
    }
    writeJson["userIds"] = std::move(userIdsArray);

    // Serialize equipmentIds
    std::vector<json::wvalue> equipmentIdsArray;
    for (std::string id : equipmentIds) 
    {
        equipmentIdsArray.push_back(id);
    }
    writeJson["equipmentIds"] = std::move(equipmentIdsArray);

    // Serialize researchOutput
    writeJson["researchOutput"] = researchOutput.convertToJson(); 

    return writeJson;
}

/**
 * @brief Updates the Experiment object from a JSON representation.
 * 
 * @param readValueJson JSON object containing updated experiment details.
 */
void Experiment::updateFromJson(json::rvalue readValueJson)
{
    experimentId = readValueJson["experimentId"].s();
    title = readValueJson["title"].s();
    description = readValueJson["description"].s();
    startTime = readValueJson["startTime"].s();
    endTime = readValueJson["endTime"].s();
    cost = readValueJson["cost"].d();
    approvalStatus = readValueJson["approvalStatus"].b();

    // Update userIds
    userIds.clear();
    if (readValueJson.has("userIds")) 
    {
        for (auto& idJson : readValueJson["userIds"]) 
        {
            userIds.push_back(idJson.s());
        }
    }

    // Update equipmentIds
    equipmentIds.clear();
    if (readValueJson.has("equipmentIds")) 
    {
        for (auto& idJson : readValueJson["equipmentIds"]) 
        {
            equipmentIds.push_back(idJson.s());
        }
    }

    // Update researchOutput
    if (readValueJson.has("researchOutput")) 
    {
        researchOutput.updateFromJson(readValueJson["researchOutput"]); 
    }
}
