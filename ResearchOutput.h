#ifndef RESEARCHOUTPUT_H
#define RESEARCHOUTPUT_H

#include <crow.h>
#include <string>

class ResearchOutput
{
public:
    // Constructors
    ResearchOutput() {}
    ResearchOutput(crow::json::rvalue readValueJson);

    // Getters
    int getNumCitations() const { return numCitations; }
    std::vector<std::string> getPublishedIn() const { return publishedIn; }
    std::vector<std::string> getpublishedOn() const { return publishedOn; }

    // Setters
    void setNumCitations(int numCitationsInput) { numCitations = numCitationsInput; }
    void setPublishedIn(std::vector<std::string> publishedInInput) { publishedIn = publishedInInput; }
    void setPublishedOn(std::vector<std::string> publishedOnInput) { publishedOn = publishedOnInput; }

    // JSON Methods
    crow::json::wvalue convertToJson();
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    int numCitations;
    std::vector<std::string> publishedIn;
    std::vector<std::string> publishedOn;
};

#endif // RESEARCHOUTPUT_H