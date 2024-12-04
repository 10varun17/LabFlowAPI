#include "Lab.h"
#include <algorithm> 

using namespace std;
using namespace crow;

// Constructor from JSON
Lab::Lab(json::rvalue readValueJson)
{
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Lab::convertToJson()
{
    json::wvalue writeJson;
    writeJson["labId"] = labId;
    writeJson["labAdminId"] = labAdminId;
    writeJson["name"] = name;
    writeJson["location"] = location;
    writeJson["capacity"] = capacity;

    // Serialize budget
    writeJson["budget"] = budget.convertToJson(); 

    // Serialize equipmentIds
    std::vector<json::wvalue> equipmentIdsArray;
    for (std::string id : equipmentIds) 
    {
        equipmentIdsArray.push_back(id);
    }
    writeJson["equipmentIds"] = std::move(equipmentIdsArray);

    // Serialize experimentIds
    std::vector<json::wvalue> experimentIdsArray;
    for (std::string id : experimentIds) 
    {
        experimentIdsArray.push_back(id);
    }
    writeJson["experimentIds"] = std::move(experimentIdsArray);

    // Serialize userIds
    std::vector<json::wvalue> userIdsArray;
    for (std::string id : userIds) 
    {
        userIdsArray.push_back(id);
    }
    writeJson["userIds"] = std::move(userIdsArray);

    return writeJson;
}

// Update from JSON
void Lab::updateFromJson(json::rvalue readValueJson)
{
    labId = readValueJson["labId"].s();
    labAdminId = readValueJson["labAdminId"].s();
    name = readValueJson["name"].s();
    location = readValueJson["location"].s();
    capacity = readValueJson["capacity"].s();

    // Update budget
    if (readValueJson.has("budget")) 
    {
        budget.updateFromJson(readValueJson["budget"]);
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

    // Update experimentIds
    experimentIds.clear();
    if (readValueJson.has("experimentIds")) 
    {
        for (auto& idJson : readValueJson["experimentIds"]) 
        {
            experimentIds.push_back(idJson.s());
        }
    }

    // Update userIds
    userIds.clear();
    if (readValueJson.has("userIds")) 
    {
        for (auto& idJson : readValueJson["userIds"]) 
        {
            userIds.push_back(idJson.s());
        }
    }
}