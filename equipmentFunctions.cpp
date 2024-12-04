/**
 * @file equipmentFunctions.cpp
 * @brief Implementation of the CRUD methods for equipment management.
 *
 * This file provides the implementation for CRUD methods involving an Equipment object.
 */

#include "Equipment.h"
#include <stdexcept>
#include <regex>
#include "toLowerHelper.h"

using namespace std;
using namespace crow;

extern map<string, Equipment> equipmentsMap;

response searchEquipments(string searchString)
{
    vector<Equipment> found;
    for(pair<string, Equipment> keyValuePair : equipmentsMap)
    {
        string target1 = keyValuePair.second.getName();
        string target2 = keyValuePair.second.getDescription();
        regex pattern(searchString, regex_constants::icase);

        if (regex_search(target1, pattern) || regex_search(target2, pattern))
            found.push_back(keyValuePair.second);
    }

    // Create a new JSON write value to write to the file
    json::wvalue jsonWriteValue;

    int index = 0;
    for (Equipment equipment : found)
    {
        jsonWriteValue[index] = equipment.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

// Comparator to sort pairs according to id.
struct
{
    bool operator()(pair<string, Equipment>& a, pair<string, Equipment>& b) 
    { 
        return a.second.getId() < b.second.getId(); 
    } 
} comparatorId;

response sortEquipments(string sortString) 
{
    vector<pair<string, Equipment>> equipmentsToSort;

    for (pair<string, Equipment> keyValuePair : equipmentsMap) 
        equipmentsToSort.push_back(keyValuePair);

    if (sortString == "id")
        sort(equipmentsToSort.begin(), equipmentsToSort.end(), comparatorId); 

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each Equipment in the vector, convert the T to JSON and add to the write value.
    int index = 0;
    for (pair<string, Equipment> keyValuePair : equipmentsToSort)
    {
        jsonWriteValue[index] = keyValuePair.second.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

response filterEquipments(bool available)
{
    vector<Equipment> found;

    for (pair<string, Equipment> keyValuePair : equipmentsMap)
    {
        if (keyValuePair.second.isAvailable() == available)
            found.push_back(keyValuePair.second);
    }

    // Create a new JSON write value
    json::wvalue jsonWriteValue;

    int index = 0;
    for (Equipment equipment : found)
    {
        jsonWriteValue[index] = equipment.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

/**
 * @brief Create a new Equipment.
 * 
 * This method handles the creation of a new Equipment based on the data
 * received in the request body.
 * 
 * @param req The HTTP request object.
 * @return res The HTTP response object.
 */
response createEquipment(request req) 
{
    // Load the request body string into a JSON read value.
    json::rvalue readValueJson = json::load(req.body);

    // If there was a problem converting the body text to JSON return an error.
    // 400 Bad Request: The server cannot or will not process the request due to something
    // that is perceived to be a client error (e.g., malformed request syntax, invalid 
    // request message framing, or deceptive request routing).
    if (!readValueJson) 
        return response(400, "Invalid JSON");
    
    // Create a new Equipment.
    Equipment equipment{readValueJson};

    // Add the new Equipment to the map.
    equipmentsMap[equipment.getId()] = equipment;

    // Return the create Equipment as a JSON string.
    // 201 Created: The request succeeded, and a new Equipment was created as a result.
    // This is typically the response sent after POST requests, or some PUT requests.
    return response(201, equipment.convertToJson().dump());
}

/**
 * @brief Read a specific Equipment.
 * 
 * This method retrieves a Equipment identified by a unique ID.
 * 
 * @param id The unique identifier of the Equipment.
 * @return res The HTTP response object.
 */
response readEquipment(string id) 
{
    try 
    {
        // Get the Equipment from the Equipment map.
        Equipment equipment = equipmentsMap.at(id);

        // Return the Equipment as a JSON string.
        return response(equipment.convertToJson().dump());
    } 
    catch (out_of_range& exception) 
    {
        // If the Equipment was not found in the map return a 404 not found error.
        // 404 Not Found: The server cannot find the requested Equipment.
        return response(404, "Equipment Not Found");
    }
}

/**
 * @brief Read all Equipments.
 * 
 * This method retrieves a Equipment identified by a unique ID.
 * 
 * @return res The HTTP response object.
 */
response readAllEquipments(request req) 
{
    if (req.url_params.get("search"))
        return searchEquipments(req.url_params.get("search"));

    if (req.url_params.get("sort"))
        return sortEquipments(req.url_params.get("sort"));

    if (req.url_params.get("isavailable"))
    {
        bool available = false;
        if (string(req.url_params.get("isavailable")) == "TRUE" || string(req.url_params.get("isavailable")) == "true")
            available = true;
        
        return filterEquipments(available);
    }

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each Equipment in the map, convert the Equipment to JSON and add to the write value.
    int index = 0;
    for (pair<string, Equipment> keyValuePair : equipmentsMap)
    {
        // first: gives you access to the first item in the pair.
        // second: gives you access to the second item in the pair.
        jsonWriteValue[index] = keyValuePair.second.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

/**
 * @brief Update a specific Equipment.
 * 
 * This method updates the data of a Equipment identified by a unique ID.
 * 
 * @param req The HTTP request object.
 * @param res The HTTP response object.
 * @param id The unique identifier of the Equipment.
 */
void updateEquipment(request req, response& res, string id) 
{
    try 
    {
        // Get the Equipment from the Equipment map.
        Equipment equipment = equipmentsMap.at(id);

        // Convert the request body to JSON.
        json::rvalue readValueJson = json::load(req.body);

        // If there was a problem converting the body text to JSON return an error.
        if (!readValueJson) 
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        // Update the Equipment.
        equipment.updateFromJson(readValueJson);
        equipmentsMap[id] = equipment;

        // Return the updated Equipment as a JSON string.
        // 200 OK: The request succeeded.
        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(equipment.convertToJson().dump());
        res.end();
    } 
    catch (out_of_range& exception) 
    {
        // If the Equipment was not found in the map return a 404 not found error.
        res.code = 404;
        res.end("Equipment Not Found");
    }
}

/**
 * @brief Delete a specific Equipment.
 * 
 * This method deletes a Equipment identified by a unique ID.
 * 
 * @param id The unique identifier of the Equipment.
 * @return res The HTTP response object.
 */
response deleteEquipment(string id) 
{
    try 
    {
        // Get the Equipment from the Equipment map.
        Equipment equipment = equipmentsMap.at(id);

        // Remove the Equipment from the Equipment map.
        equipmentsMap.erase(id);

        // Return a successful code 204 which means success but no content to return.
        return response(204);
    } 
    catch (out_of_range& exception) 
    {
        // If the Equipment was not found in the map return a 404 not found error.
        return response(404, "Equipment Not Found");
    }
}
