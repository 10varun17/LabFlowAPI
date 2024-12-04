
/**
 * @file FileHandlingTemplate.cpp
 * @brief Implementation of template methods for handling file saving and loading.
 * 
 * This file provides the implementation of generic methods to save and load data from files.
 */

#include <crow.h>
#include <fstream>
#include "FileHandlingTemplate.h"

using namespace std;
using namespace crow;

/**
 * @brief Saves data from a map to a file in JSON format.
 * 
 * @tparam T The type of the objects stored in the map.
 * @param data A map containing data to be saved.
 * @param filename The name of the file to save the data to.
 */
template <typename T>
void saveToFile(map<string, T> data, string filename)  
{
    // Open the file for writing
    ofstream file(filename);

    if (file.is_open()) 
    {
        // Create a new JSON write value to write to the file.
        json::wvalue jsonWriteValue;
        
        // For each object in the map, convert the object to JSON and add to the write value.
        int index = 0;
        for (pair<string, T> keyValuePair : data)
        {
            // first: gives you access to the first item in the pair.
            // second: gives you access to the second item in the pair.
            jsonWriteValue[index] = keyValuePair.second.convertToJson();
            index++;
        }

        // Write the JSON to the file.
        file << jsonWriteValue.dump();
        file.close();
    }
}

/**
 * @brief Loads data from a file and populates a map with the deserialized objects.
 * 
 * @tparam T The type of the objects to load into the map.
 * @param filename The name of the file to load the data from.
 * @return A map containing the loaded data.
 */
template <typename T>
map<string, T> loadFromFile(string filename) 
{
    map<string, T> data;
    
    // Open the file for reading.
    ifstream file(filename);

    if (file.is_open()) 
    {      
        // Create a stream for reading in the file.
        ostringstream stringStreamJson;

        // Read the entire JSON string.
        stringStreamJson << file.rdbuf();

        // Load the string into a JSON read value object.
        json::rvalue jsonReadValue = json::load(stringStreamJson.str());

        // Close the file.
        file.close();

        // For each item in the JSON, convert it to an object, and add it to the data map.
        for (json::rvalue item : jsonReadValue) 
        {
            T object{item};
            data[object.getId()] = object;
        }
    }
    
    return data;
}
