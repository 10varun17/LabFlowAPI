
/**
 * @file ResearchOutput.cpp
 * @brief Implementation of ResearchOutput class.
 * 
 * This file provides the implementation for the ResearchOutput class, which records 
 * the outputs of a research, including citations and publication details.
 */

#include "ResearchOutput.h"

using namespace crow;

/**
 * @brief Constructs a ResearchOutput object from JSON data.
 * 
 * @param readValueJson JSON object containing research output details.
 */
ResearchOutput::ResearchOutput(json::rvalue readValueJson)
{
    updateFromJson(readValueJson);
}

/**
 * @brief Converts the ResearchOutput object to a JSON representation.
 * 
 * @return A JSON object containing the research output details.
 */
json::wvalue ResearchOutput::convertToJson()
{
    json::wvalue writeJson;
    writeJson["numCitations"] = numCitations;

    // Serialize publishedIn
    std::vector<json::wvalue> publishedInArray;
    for (std::string journal : publishedIn) 
    {
        publishedInArray.push_back(journal);
    }
    writeJson["publishedIn"] = std::move(publishedInArray);

    // Serialize publishedOn
    std::vector<json::wvalue> publishedOnArray;
    for (std::string date : publishedOn) 
    {
        publishedOnArray.push_back(date);
    }
    writeJson["publishedOn"] = std::move(publishedOnArray);

    return writeJson;
}

/**
 * @brief Updates the ResearchOutput object from a JSON representation.
 * 
 * @param readValueJson JSON object containing updated research output details.
 */
void ResearchOutput::updateFromJson(json::rvalue readValueJson)
{
    numCitations = readValueJson["numCitations"].i();

    // Update publishedIn
    publishedIn.clear();
    if(readValueJson.has("publishedIn"))
    {
        for (auto& journalJson : readValueJson["publishedIn"])
        {
            publishedIn.push_back(journalJson.s());
        }
    }

    // Update publishedOn
    publishedOn.clear();
    if(readValueJson.has("publishedOn"))
    {
        for (auto& dateJson : readValueJson["publishedOn"])
        {
            publishedOn.push_back(dateJson.s());
        }
    }
}
