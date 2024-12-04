
/**
 * @file experimentFunctions.cpp
 * @brief Implementation of CRUD methods for experiment management.
 *
 * This file provides the implementation for CRUD methods involving an Experiment object.
 */

#include "Experiment.h"
#include <stdexcept>
#include <regex>
#include "toLowerHelper.h"

using namespace std;
using namespace crow;

extern map<string, Experiment> experimentsMap;

/**
 * @brief Searches experiments by title or description.
 *
 * @param searchString A string to search for in titles and descriptions of experiments.
 * @return JSON response containing matching experiments.
 */
response searchExperiments(string searchString)
{
    vector<Experiment> found;
    for(pair<string, Experiment> keyValuePair : experimentsMap)
    {
        string target1 = keyValuePair.second.getTitle();
        string target2 = keyValuePair.second.getDescription();
        regex pattern(searchString, regex_constants::icase);

        if (regex_search(target1, pattern) || regex_search(target2, pattern))
            found.push_back(keyValuePair.second);
    }

    // Create a new JSON write value to write to the file
    json::wvalue jsonWriteValue;

    int index = 0;
    for (Experiment experiment : found)
    {
        jsonWriteValue[index] = experiment.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}


// Comparator to sort pairs according to id.
struct
{
    bool operator()(pair<string, Experiment>& a, pair<string, Experiment>& b) 
    { 
        return a.second.getId() < b.second.getId(); 
    } 
} comparatorId;

// Comparator to sort pairs according to cost.
struct
{
    bool operator()(pair<string, Experiment>& a, pair<string, Experiment>& b) 
    { 
        return a.second.getCost() < b.second.getCost(); 
    } 
} comparatorCost;

// Comparator to sort pairs according to start time.
struct
{
    bool operator()(pair<string, Experiment>& a, pair<string, Experiment>& b) 
    { 
        return a.second.getStartTime() < b.second.getStartTime(); 
    } 
} comparatorStartTime;

// Comparator to sort pairs according to end time.
struct
{
    bool operator()(pair<string, Experiment>& a, pair<string, Experiment>& b) 
    { 
        return a.second.getEndTime() < b.second.getEndTime(); 
    } 
} comparatorEndTime;

// Comparator to sort pairs according to number of users.
struct
{
    bool operator()(pair<string, Experiment>& a, pair<string, Experiment>& b) 
    { 
        return a.second.getUserIds().size() < b.second.getUserIds().size(); 
    } 
} comparatorNumUsers;

// Comparator to sort pairs according to number of equipments.
struct
{
    bool operator()(pair<string, Experiment>& a, pair<string, Experiment>& b) 
    { 
        return a.second.getEquipmentIds().size() < b.second.getEquipmentIds().size(); 
    } 
} comparatorNumEquipments;

// Comparator to sort pairs according to number of citations.
struct
{
    bool operator()(pair<string, Experiment>& a, pair<string, Experiment>& b) 
    { 
        return a.second.getResearchOutput().getNumCitations() < b.second.getResearchOutput().getNumCitations(); 
    } 
} comparatorNumCitations;

// Comparator to sort pairs according to number of publications.
struct
{
    bool operator()(pair<string, Experiment>& a, pair<string, Experiment>& b) 
    { 
        return a.second.getResearchOutput().getPublishedIn().size() < b.second.getResearchOutput().getPublishedIn().size(); 
    } 
} comparatorNumPublications;

/**
 * @brief Handles the GET request that includes the sort parameter for sorting users
 * 
 * @param sortString a string indicating the sorting criterion
 * @return a response object containing a JSON array of sorted T objects. 
 *         If an unsupported sortString is provided, returns the T in their original order.
*/
response sortExperiments(string sortString) 
{
    vector<pair<string, Experiment>> experimentsToSort;

    for (pair<string, Experiment> keyValuePair : experimentsMap) 
        experimentsToSort.push_back(keyValuePair);

    if (sortString == "id")
        sort(experimentsToSort.begin(), experimentsToSort.end(), comparatorId); 

    if (toLower(sortString) == "cost")
        sort(experimentsToSort.begin(), experimentsToSort.end(), comparatorCost); 

    if (toLower(sortString) == "starttime")
        sort(experimentsToSort.begin(), experimentsToSort.end(), comparatorStartTime); 

    if (toLower(sortString) == "endtime")
        sort(experimentsToSort.begin(), experimentsToSort.end(), comparatorEndTime); 

    if (toLower(sortString) == "numusers" || toLower(sortString) == "users")
        sort(experimentsToSort.begin(), experimentsToSort.end(), comparatorNumUsers); 

    if (toLower(sortString) == "numequipments" || toLower(sortString) == "equipments")
        sort(experimentsToSort.begin(), experimentsToSort.end(), comparatorNumEquipments); 

    if (toLower(sortString) == "numcitations" || toLower(sortString) == "citations")
        sort(experimentsToSort.begin(), experimentsToSort.end(), comparatorNumCitations); 

    if (toLower(sortString) == "numpublications" || toLower(sortString) == "publications")
        sort(experimentsToSort.begin(), experimentsToSort.end(), comparatorNumPublications); 

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each Experiment in the vector, convert the T to JSON and add to the write value.
    int index = 0;
    for (pair<string, Experiment> keyValuePair : experimentsToSort)
    {
        jsonWriteValue[index] = keyValuePair.second.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

response filterExperiments(string type, float number)
{
    vector<Experiment> found;

    for (pair<string, Experiment> keyValuePair : experimentsMap)
    {
        ResearchOutput output = keyValuePair.second.getResearchOutput();
        if (toLower(type) == "citations" && output.getNumCitations() >= number)
            found.push_back(keyValuePair.second);
        else if (toLower(type) == "publications" && output.getPublishedIn().size() >= number)
            found.push_back(keyValuePair.second);
    }

    // Create a new JSON write value
    json::wvalue jsonWriteValue;

    int index = 0;
    for (Experiment experiment : found)
    {
        jsonWriteValue[index] = experiment.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

response filterExperiments(bool approvalStatus)
{
    vector<Experiment> found;

    for (pair<string, Experiment> keyValuePair : experimentsMap)
    {
        if (keyValuePair.second.isApproved() == approvalStatus)
            found.push_back(keyValuePair.second);
    }

    // Create a new JSON write value
    json::wvalue jsonWriteValue;

    int index = 0;
    for (Experiment experiment : found)
    {
        jsonWriteValue[index] = experiment.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

response filterExperiments(float cost)
{
    vector<Experiment> found;

    for (pair<string, Experiment> keyValuePair : experimentsMap)
    {
        if (keyValuePair.second.getCost() >= cost)
            found.push_back(keyValuePair.second);
    }

    // Create a new JSON write value
    json::wvalue jsonWriteValue;

    int index = 0;
    for (Experiment experiment : found)
    {
        jsonWriteValue[index] = experiment.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

/**
 * @brief Create a new Experiment.
 * 
 * This method handles the creation of a new Experiment based on the data
 * received in the request body.
 * 
 * @param req The HTTP request object.
 * @return res The HTTP response object.
 */
response createExperiment(request req) 
{
    // Load the request body string into a JSON read value.
    json::rvalue readValueJson = json::load(req.body);

    // If there was a problem converting the body text to JSON return an error.
    // 400 Bad Request: The server cannot or will not process the request due to something
    // that is perceived to be a client error (e.g., malformed request syntax, invalid 
    // request message framing, or deceptive request routing).
    if (!readValueJson) 
        return response(400, "Invalid JSON");
    
    // Create a new Experiment.
    Experiment experiment{readValueJson};

    // Add the new Experiment to the map.
    experimentsMap[experiment.getId()] = experiment;

    // Return the create Experiment as a JSON string.
    // 201 Created: The request succeeded, and a new Experiment was created as a result.
    // This is typically the response sent after POST requests, or some PUT requests.
    return response(201, experiment.convertToJson().dump());
}

/**
 * @brief Read a specific Experiment.
 * 
 * This method retrieves a Experiment identified by a unique ID.
 * 
 * @param id The unique identifier of the Experiment.
 * @return res The HTTP response object.
 */
response readExperiment(string id) 
{
    try 
    {
        // Get the Experiment from the Experiment map.
        Experiment experiment = experimentsMap.at(id);

        // Return the Experiment as a JSON string.
        return response(experiment.convertToJson().dump());
    } 
    catch (out_of_range& exception) 
    {
        // If the Experiment was not found in the map return a 404 not found error.
        // 404 Not Found: The server cannot find the requested Experiment.
        return response(404, "Experiment Not Found");
    }
}

/**
 * @brief Read all Experiments.
 * 
 * This method retrieves a Experiment identified by a unique ID.
 * 
 * @return res The HTTP response object.
 */
response readAllExperiments(request req) 
{
    if (req.url_params.get("search"))
        return searchExperiments(req.url_params.get("search"));

    if (req.url_params.get("sort"))
        return sortExperiments(req.url_params.get("sort"));

    if (req.url_params.get("number") && req.url_params.get("type"))
    {
        try 
        {
            float number = stof(req.url_params.get("number"));
            return filterExperiments(req.url_params.get("type"), number);
        } catch (invalid_argument& exception)
        {
            cerr << "Can't convert the number to float type. Invalid argument!" << endl;
            return response(400, "Invalid request");
        }
    }

    if (req.url_params.get("cost"))
    {
        try 
        {
            float cost = stof(req.url_params.get("cost"));
            return filterExperiments(cost);
        } catch (invalid_argument& exception)
        {
            cerr << "Can't convert the cost to float type. Invalid argument!" << endl;
            return response(400, "Invalid request");
        }
    }

    if (req.url_params.get("isapproved"))
    {
        bool approved = false;
        if (string(req.url_params.get("isapproved")) == "TRUE" || string(req.url_params.get("isapproved")) == "true")
            approved = true;
        
        return filterExperiments(approved);
    }

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each Experiment in the map, convert the Experiment to JSON and add to the write value.
    int index = 0;
    for (pair<string, Experiment> keyValuePair : experimentsMap)
    {
        // first: gives you access to the first item in the pair.
        // second: gives you access to the second item in the pair.
        jsonWriteValue[index] = keyValuePair.second.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

/**
 * @brief Update a specific Experiment.
 * 
 * This method updates the data of a Experiment identified by a unique ID.
 * 
 * @param req The HTTP request object.
 * @param res The HTTP response object.
 * @param id The unique identifier of the Experiment.
 */
void updateExperiment(request req, response& res, string id) 
{
    try 
    {
        // Get the Experiment from the Experiment map.
        Experiment experiment = experimentsMap.at(id);

        // Convert the request body to JSON.
        json::rvalue readValueJson = json::load(req.body);

        // If there was a problem converting the body text to JSON return an error.
        if (!readValueJson) 
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        // Update the Experiment.
        experiment.updateFromJson(readValueJson);
        experimentsMap[id] = experiment;

        // Return the updated Experiment as a JSON string.
        // 200 OK: The request succeeded.
        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(experiment.convertToJson().dump());
        res.end();
    } 
    catch (out_of_range& exception) 
    {
        // If the Experiment was not found in the map return a 404 not found error.
        res.code = 404;
        res.end("Experiment Not Found");
    }
}

/**
 * @brief Delete a specific Experiment.
 * 
 * This method deletes a Experiment identified by a unique ID.
 * 
 * @param id The unique identifier of the Experiment.
 * @return res The HTTP response object.
 */
response deleteExperiment(string id) 
{
    try 
    {
        // Get the Experiment from the Experiment map.
        Experiment experiment = experimentsMap.at(id);

        // Remove the Experiment from the Experiment map.
        experimentsMap.erase(id);

        // Return a successful code 204 which means success but no content to return.
        return response(204);
    } 
    catch (out_of_range& exception) 
    {
        // If the Experiment was not found in the map return a 404 not found error.
        return response(404, "Experiment Not Found");
    }
}