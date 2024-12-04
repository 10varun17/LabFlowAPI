
/**
 * @file GenericUserAPI.cpp
 * @brief Implementation of the Generic API for RESTful services.
 *
 * This file provides the implementation for a generic API that can be
 * specialized for different types of resources in a RESTful service.
 */

#include <stdexcept>
#include "GenericUserAPI.h"
#include "Professor.h"
#include "Administrator.h"
#include "Student.h"
#include "Lab.h"
#include "labFunctions.h"
#include <regex>

using namespace std;
using namespace crow;

template<typename T> 
map<string, T> GenericUserAPI<T>::resourceMap;
extern std::map<std::string, Lab> labsMap;

/**
 * @brief Searches for resources by name.
 *
 * @tparam T The type of the resource.
 * @param searchString A string pattern to search for in resource names.
 * @return A JSON response containing matching resources.
 */
template<typename T>
response GenericUserAPI<T>::searchByName(string searchString)
{
    vector<T> found;
    for(pair<string, T> resourcePair : resourceMap)
    {
        string target = resourcePair.second.getName();
        regex pattern(searchString, regex_constants::icase);

        if (regex_search(target, pattern))
        {
            found.push_back(resourcePair.second);
        }
    }

    // Create a new JSON write value to write to the file
    json::wvalue jsonWriteValue;
    int index = 0;
    for (T resource : found)
    {
        jsonWriteValue[index] = resource.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}


// Comparator to sort pairs according to name.
struct
{
    template<typename T>
    bool operator()(pair<string, T>& a, pair<string, T>& b) 
    { 
        return a.second.getName() < b.second.getName(); 
    } 
} comparatorName;

// Comparator to sort pairs according to id.
struct
{
    template<typename T>
    bool operator()(pair<string, T>& a, pair<string, T>& b) 
    { 
        return a.second.getId() < b.second.getId(); 
    } 
} comparatorId;

/**
 * @brief Handles the GET request that includes the sort parameter for sorting users
 * 
 * @param sortString a string indicating the sorting criterion
 * @return a response object containing a JSON array of sorted T objects. 
 *         If an unsupported sortString is provided, returns the T in their original order.
*/
template<typename T>
response GenericUserAPI<T>::sortUsers(string sortString) 
{
    // Vector to store the T pairs.
    vector<pair<string, T>> objectsToSort;

    // For each string/PizzaSize pair in the pizzaSizes map.
    for (pair<string, T> resourcePair : resourceMap) 
    {
        objectsToSort.push_back(resourcePair);
    }

    if (sortString == "name")
    {
        // Sort using comparator function 
        sort(objectsToSort.begin(), objectsToSort.end(), comparatorName); 
    }

    if (sortString == "id")
    {
        // Sort using comparator function 
        sort(objectsToSort.begin(), objectsToSort.end(), comparatorId); 
    }

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each T in the vector, convert the T to JSON and add to the write value.
    int index = 0;
    for (pair<string, T> resourcePair : objectsToSort)
    {
        jsonWriteValue[index] = resourcePair.second.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

/**
 * @brief Create a new resource.
 * 
 * This method handles the creation of a new resource based on the data
 * received in the request body.
 * 
 * @param req The HTTP request object.
 * @return res The HTTP response object.
 */
template<typename T> 
response GenericUserAPI<T>::createResource(request req) 
{
    string apiKeyHeader = "Authorization";
    string expectedApiKey = "AJF328JDI83HD1";
    
    // Validate the api key in the request header.
    if (!req.headers.count(apiKeyHeader) || req.headers.find(apiKeyHeader)->second != expectedApiKey) 
    {
        return response(401);
    }

    // Load the request body string into a JSON read value.
    json::rvalue readValueJson = json::load(req.body);

    // If there was a problem converting the body text to JSON return an error.
    // 400 Bad Request: The server cannot or will not process the request due to something
    // that is perceived to be a client error (e.g., malformed request syntax, invalid 
    // request message framing, or deceptive request routing).
    if (!readValueJson) 
        return response(400, "Invalid JSON");
    
    // Create a new resource.
    T resource{readValueJson};

    // Add the new resource to the map.
    resourceMap[resource.getId()] = resource;

    // Return the create resource as a JSON string.
    // 201 Created: The request succeeded, and a new resource was created as a result.
    // This is typically the response sent after POST requests, or some PUT requests.
    return response(201, resource.convertToJson().dump());
}

/**
 * @brief Read a specific resource.
 * 
 * This method retrieves a resource identified by a unique ID.
 * 
 * @param id The unique identifier of the resource.
 * @return res The HTTP response object.
 */
template<typename T> 
response GenericUserAPI<T>::readResource(string id) 
{
    try 
    {
        // Get the resource from the resource map.
        T resource = resourceMap.at(id);

        // Return the resource as a JSON string.
        return response(resource.convertToJson().dump());
    } 
    catch (out_of_range& exception) 
    {
        // If the resource was not found in the map return a 404 not found error.
        // 404 Not Found: The server cannot find the requested resource.
        return response(404, "Resource Not Found");
    }
}

/**
 * @brief Read all resources.
 * 
 * This method retrieves a resource identified by a unique ID.
 * 
 * @return res The HTTP response object.
 */
template<typename T> 
response GenericUserAPI<T>::readAllResources(request req) 
{
    // If there is a search parameter on the request, then search by name.
    if (req.url_params.get("searchByName"))
    {
        return searchByName(req.url_params.get("searchByName"));
    }

    // If there is a search parameter on the request, then search by name.
    if (req.url_params.get("sort"))
    {
        return sortUsers(req.url_params.get("sort"));
    }

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each resource in the map, convert the resource to JSON and add to the write value.
    int index = 0;
    for (pair<string, T> keyValuePair : resourceMap)
    {
        // first: gives you access to the first item in the pair.
        // second: gives you access to the second item in the pair.
        jsonWriteValue[index] = keyValuePair.second.convertToJson();
        index++;
    }

    return response(jsonWriteValue.dump());
}

/**
 * @brief Update a specific resource.
 * 
 * This method updates the data of a resource identified by a unique ID.
 * 
 * @param req The HTTP request object.
 * @param res The HTTP response object.
 * @param id The unique identifier of the resource.
 */
template<typename T> 
void GenericUserAPI<T>::updateResource(request req, response& res, string id) 
{
    // string apiKeyHeader = "Authorization";
    // string expectedApiKey = "AJF328JDI83HD1";
    
    // // Validate the api key in the request header.
    // if (!req.headers.count(apiKeyHeader) || req.headers.find(apiKeyHeader)->second != expectedApiKey) 
    // {
    //     res.code = 401; // Unauthorized
    //     res.end("Invalid API key");
    //     return;
    // }

    try 
    {
        // Get the resource from the resource map.
        T& resource = resourceMap.at(id);

        // Convert the request body to JSON.
        json::rvalue readValueJson = json::load(req.body);

        // If there was a problem converting the body text to JSON return an error.
        if (!readValueJson) 
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        // Update the resource.
        resource.updateFromJson(readValueJson);

        // Return the updated resource as a JSON string.
        // 200 OK: The request succeeded.
        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(resource.convertToJson().dump());
        res.end();
    } 
    catch (out_of_range& exception) 
    {
        // If the resource was not found in the map return a 404 not found error.
        res.code = 404;
        res.end("Resource Not Found");
    }
}

template<> 
void GenericUserAPI<Administrator>::updateResource(request req, response& res, string id) 
{
    try 
    {
        Administrator& resource = resourceMap.at(id);

        json::rvalue readValueJson = json::load(req.body);

        if (!readValueJson) 
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        resource.updateFromJson(readValueJson);

        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(resource.convertToJson().dump());
        res.end();
    } 
    catch (std::out_of_range& exception) 
    {
        res.code = 404;
        res.end("Resource Not Found");
    }
}


/**
 * @brief Delete a specific resource.
 * 
 * This method deletes a resource identified by a unique ID.
 * 
 * @param id The unique identifier of the resource.
 * @return res The HTTP response object.
 */
template<typename T> 
response GenericUserAPI<T>::deleteResource(string id) 
{
    try 
    {
        // Get the resource from the resource map.
        T resource = resourceMap.at(id);

        // Remove the resource from the resource map.
        resourceMap.erase(id);

        // Return a successful code 204 which means success but no content to return.
        return response(204);
    } 
    catch (out_of_range& exception) 
    {
        // If the resource was not found in the map return a 404 not found error.
        return response(404, "Resource Not Found");
    }
}

// Explicit template instantiation
template class GenericUserAPI<Professor>;
template class GenericUserAPI<Student>;
template class GenericUserAPI<Administrator>;