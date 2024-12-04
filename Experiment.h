#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <string>
#include <vector>
#include "ResearchOutput.h"

class Experiment
{
public:
    // Constructors
    Experiment() {}
    Experiment(crow::json::rvalue readValueJson);

    // Getters
    std::string getId() const { return experimentId; }
    std::string getTitle() const { return title; }
    std::string getDescription() const { return description; }
    std::string getStartTime() const { return startTime; }
    std::string getEndTime() const { return endTime; }
    std::vector<std::string> getUserIds() const { return userIds; }
    float getCost() const { return cost; }
    bool isApproved() const { return approvalStatus; }
    std::vector<std::string> getEquipmentIds() const { return equipmentIds; }
    ResearchOutput getResearchOutput() const { return researchOutput; }

    // Setters
    void setId(std::string experimentIdInput) { experimentId = experimentIdInput; }
    void setTitle(std::string titleInput) { title = titleInput; }
    void setDescription(std::string descriptionInput) { description = descriptionInput; }
    void setStartTime(std::string startTimeInput) { startTime = startTimeInput; }
    void setEndTime(std::string endTimeInput) { endTime = endTimeInput; }
    void setUserIds(std::vector<std::string> userIdsInput) { userIds = userIdsInput; }
    void setCost(float costInput) { cost = costInput; }
    void setApprovalStatus(bool approvalStatusInput) { approvalStatus = approvalStatusInput; }
    void setEquipmentIds(std::vector<std::string> equipmentIdsInput) { equipmentIds = equipmentIdsInput; }
    void setResearchOutput(ResearchOutput researchOutputInput) { researchOutput = researchOutputInput; }

    // Convert to JSON
    crow::json::wvalue convertToJson();

    // Update from JSON
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string experimentId;
    std::string title;
    std::string description;
    std::string startTime;
    std::string endTime;
    std::vector<std::string> userIds;
    float cost;
    bool approvalStatus;
    std::vector<std::string> equipmentIds;
    ResearchOutput researchOutput;
};

#endif // EXPERIMENT_H