/**
 * @file labFunctions.cpp
 * @brief Implementation of CRUD methods for a lab management.
 *
 * This file provides the implementation for CRUD methods involving a Lab object.
 */

#include "Lab.h"
#include <stdexcept>
#include <regex>
#include "toLowerHelper.h"

using namespace std;
using namespace crow;

extern map<string, Lab> labsMap;

/**
 * @brief Searches labs with names or locations matching to the input
 * 
 * @param searchString Target string to match with names and locations of labs
 * @return All the labs of which names and locations matching searchString in json
 */
response searchLabs(string searchString)
{
    vector<Lab> found;
    for(pair<string, Lab> keyValuePair : labsMap)
    {
        string target1 = keyValuePair.second.getName();
        string target2 = keyValuePair.second.getLocation();
        regex pattern(searchString, regex_constants::icase);

        if (regex_search(target1, pattern) || regex_search(target2, pattern))
            found.push_back(keyValuePair.second);
    }

    // Create a new JSON write value to write to the file
    json::wvalue jsonWriteValue;

    int index = 0;
    for (Lab resource : found)
    {
        jsonWriteValue[index] = resource.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

// Comparator to sort pairs according to name.
struct
{
    bool operator()(pair<string, Lab>& a, pair<string, Lab>& b) 
    { 
        return a.second.getName() < b.second.getName(); 
    } 
} comparatorName;

// Comparator to sort pairs according to id.
struct
{
    bool operator()(pair<string, Lab>& a, pair<string, Lab>& b) 
    { 
        return a.second.getId() < b.second.getId(); 
    } 
} comparatorId;

// Comparator to sort pairs according to total budget.
struct
{
    bool operator()(pair<string, Lab>& a, pair<string, Lab>& b) 
    { 
        return a.second.getBudget().getTotalAmount() < b.second.getBudget().getTotalAmount(); 
    } 
} comparatorTotalAmount;

// Comparator to sort pairs according to remaining budget.
struct
{
    bool operator()(pair<string, Lab>& a, pair<string, Lab>& b) 
    { 
        return a.second.getBudget().getRemainingAmount() < b.second.getBudget().getRemainingAmount(); 
    } 
} comparatorRemainingAmount;

// Comparator to sort pairs according to spent budget.
struct
{
    bool operator()(pair<string, Lab>& a, pair<string, Lab>& b) 
    { 
        return a.second.getBudget().getSpentAmount() < b.second.getBudget().getSpentAmount(); 
    } 
} comparatorSpentAmount;

// Comparator to sort pairs according to number of experiments conducted.
struct
{
    bool operator()(pair<string, Lab>& a, pair<string, Lab>& b) 
    { 
        return a.second.getExperimentIds().size() < b.second.getExperimentIds().size(); 
    } 
} comparatorNumExperiments;

// Comparator to sort pairs according to number of equipments.
struct
{
    bool operator()(pair<string, Lab>& a, pair<string, Lab>& b) 
    { 
        return a.second.getEquipmentIds().size() < b.second.getEquipmentIds().size(); 
    } 
} comparatorNumEquipments;

/**
 * @brief Sorts labs by a key string
 * 
 * @param sortString a string indicating the sorting criterion
 * @return a response object containing a JSON array of sorted T objects. 
 * If an unsupported sortString is provided, returns the T in their original order.
*/
response sortLabs(string sortString) 
{
    vector<pair<string, Lab>> labsToSort;

    for (pair<string, Lab> keyValuePair : labsMap) 
        labsToSort.push_back(keyValuePair);

    if (sortString == "name")
        sort(labsToSort.begin(), labsToSort.end(), comparatorName); 

    if (sortString == "id")
        sort(labsToSort.begin(), labsToSort.end(), comparatorId); 

    if (toLower(sortString) == "totalamount")
        sort(labsToSort.begin(), labsToSort.end(), comparatorTotalAmount); 

    if (toLower(sortString) == "remainingamount")
        sort(labsToSort.begin(), labsToSort.end(), comparatorRemainingAmount); 

    if (toLower(sortString) == "spentamount")
        sort(labsToSort.begin(), labsToSort.end(), comparatorSpentAmount); 

    if (toLower(sortString) == "numexperiments")
        sort(labsToSort.begin(), labsToSort.end(), comparatorNumExperiments); 

    if (toLower(sortString) == "numequipments")
        sort(labsToSort.begin(), labsToSort.end(), comparatorNumEquipments); 

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each Lab in the vector, convert the T to JSON and add to the write value.
    int index = 0;
    for (pair<string, Lab> keyValuePair : labsToSort)
    {
        jsonWriteValue[index] = keyValuePair.second.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

/**
 * @brief Filters labs that has a given minimum amount of budget of a given type
 * 
 * @param type A string representing the type of budget information to filter by.
 * There are three valid such types: totalamount, remaniningamount, spentamount
 * @param amount A float representing the minimum budget when filtering labs
 * @return A list of all labs that has a given minimum amount of budget of a given type
 */
response filterLabs(string type, float amount)
{
    vector<Lab> found;

    for (pair<string, Lab> keyValuePair : labsMap)
    {
        Budget budget = keyValuePair.second.getBudget();
        if (toLower(type) == "totalamount" && budget.getTotalAmount() >= amount)
            found.push_back(keyValuePair.second);
        else if (toLower(type) == "remainingamount" && budget.getRemainingAmount() >= amount)
            found.push_back(keyValuePair.second);
        else if (toLower(type) == "spentamount" && budget.getSpentAmount() >= amount)
            found.push_back(keyValuePair.second);
    }

    // Create a new JSON write value
    json::wvalue jsonWriteValue;

    int index = 0;
    for (Lab lab : found)
    {
        jsonWriteValue[index] = lab.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

/**
 * @brief Create a new Lab.
 * 
 * This method handles the creation of a new Lab based on the data
 * received in the request body.
 * 
 * @param req The HTTP request object that contains the information of a lab to create.
 * @return The HTTP response object that contains the information of a newly created lab.
 * 400 Bad Request if the input json cannot be read
 * 201 Created when a lab is created successfully with given information
 */
response createLab(request req) 
{
    // Load the request body string into a JSON read value.
    json::rvalue readValueJson = json::load(req.body);

    // If there was a problem converting the body text to JSON return an error.
    // 400 Bad Request: The server cannot or will not process the request due to something
    // that is perceived to be a client error (e.g., malformed request syntax, invalid 
    // request message framing, or deceptive request routing).
    if (!readValueJson) 
        return response(400, "Invalid JSON");
    
    // Create a new Lab.
    Lab lab{readValueJson};

    // Add the new Lab to the map.
    labsMap[lab.getId()] = lab;

    // Return the create Lab as a JSON string.
    // 201 Created: The request succeeded, and a new Lab was created as a result.
    // This is typically the response sent after POST requests, or some PUT requests.
    return response(201, lab.convertToJson().dump());
}

/**
 * @brief Read a specific Lab.
 * 
 * This method retrieves a Lab identified by a unique ID.
 * 
 * @param id The unique identifier of the Lab.
 * @return The HTTP response object containing the lab of the unique ID.
 * 404 Not Found when the requested lab cannot be find
 */
response readLab(string id) 
{
    try 
    {
        // Get the Lab from the Lab map.
        Lab lab = labsMap.at(id);

        // Return the Lab as a JSON string.
        return response(lab.convertToJson().dump());
    } 
    catch (out_of_range& exception) 
    {
        // If the Lab was not found in the map return a 404 not found error.
        // 404 Not Found: The server cannot find the requested Lab.
        return response(404, "Lab Not Found");
    }
}

/**
 * @brief Read all Labs.
 * This method retrieves a Lab identified by a unique ID.
 * 
 * @param req The HTTP request object with a requested operation specified
 * There are three valid operations that a user can request: search, sort, filter
 * 1. search: searches labs with a given target name or location
 * 2. sort: sorts labs with a given target criterion
 * 3. filter: filters labs with a given minimum amount and a type of budget
 * @return The HTTP response object containing all labs that applies
 */
response readAllLabs(request req) 
{
    if (req.url_params.get("search"))
        return searchLabs(req.url_params.get("search"));

    if (req.url_params.get("sort"))
        return sortLabs(req.url_params.get("sort"));

    if (req.url_params.get("amount") && req.url_params.get("type"))
    {
        try 
        {
            float amount = stof(req.url_params.get("amount"));
            return filterLabs(req.url_params.get("type"), amount);
        } catch (invalid_argument& exception)
        {
            cerr << "Can't convert the amount to float type. Invalid argument!" << endl;
            return response(400, "Invalid request");
        }
    }

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each Lab in the map, convert the Lab to JSON and add to the write value.
    int index = 0;
    for (pair<string, Lab> keyValuePair : labsMap)
    {
        // first: gives you access to the first item in the pair.
        // second: gives you access to the second item in the pair.
        jsonWriteValue[index] = keyValuePair.second.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

/**
 * @brief Update a specific Lab.
 * This method updates the data of a Lab identified by a unique ID.
 * 
 * @param req The HTTP request object.
 * @param res The HTTP response object reference.
 * @param id The unique identifier of the Lab.
 */
void updateLab(request req, response& res, string id) 
{
    try 
    {
        // Get the Lab from the Lab map.
        Lab lab = labsMap.at(id);

        // Convert the request body to JSON.
        json::rvalue readValueJson = json::load(req.body);

        // If there was a problem converting the body text to JSON return an error.
        if (!readValueJson) 
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        // Update the Lab.
        lab.updateFromJson(readValueJson);
        labsMap[id] = lab;

        // Return the updated Lab as a JSON string.
        // 200 OK: The request succeeded.
        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(lab.convertToJson().dump());
        res.end();
    } 
    catch (out_of_range& exception) 
    {
        // If the Lab was not found in the map return a 404 not found error.
        res.code = 404;
        res.end("Lab Not Found");
    }
}

/**
 * @brief Delete a specific Lab.
 * This method deletes a Lab identified by a unique ID.
 * 
 * @param id The unique identifier of the Lab.
 * @return The HTTP response object.
 * 204 No Content when the lab is deleted successfully
 * 404 Not Found if the requested lab is not found
 */
response deleteLab(string id) 
{
    try 
    {
        // Get the Lab from the Lab map.
        Lab lab = labsMap.at(id);

        // Remove the Lab from the Lab map.
        labsMap.erase(id);

        // Return a successful code 204 which means success but no content to return.
        return response(204);
    } 
    catch (out_of_range& exception) 
    {
        // If the Lab was not found in the map return a 404 not found error.
        return response(404, "Lab Not Found");
    }
}
