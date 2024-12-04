#ifndef LAB_H
#define LAB_H

#include <crow.h>
#include <string>
#include <vector>
#include "Budget.h"

class Lab
{
public:
    // Constructors
    Lab() {}
    Lab(crow::json::rvalue readValueJson);

    // Getters
    std::string getId() const { return labId; }
    std::string getLabAdminId() const { return labAdminId; }
    std::string getName() const { return name; }
    std::string getLocation() const { return location; }
    std::string getCapacity() const { return capacity; }
    Budget getBudget() const { return budget; }
    std::vector<std::string> getUserIds() const { return userIds; }
    std::vector<std::string> getEquipmentIds() const { return equipmentIds; }
    std::vector<std::string> getExperimentIds() const { return experimentIds; }

    // Setters
    void setId(std::string labIdInput) { labId = labIdInput; }
    void setLabAdminId(std::string labAdminIdInput) { labId = labAdminIdInput; }
    void setName(std::string nameInput) { name = nameInput; }
    void setLocation(std::string locationInput) { location = locationInput; }
    void setCapacity(std::string capacityInput) { capacity = capacityInput; }
    void setBudget(Budget budgetInput) { budget = budgetInput; }
    void setUserIds(std::vector<std::string> userIdsInput) { userIds = userIdsInput; }
    void setEquipmentIds(std::vector<std::string> equipmentIdsInput) { equipmentIds = equipmentIdsInput; }
    void setExperimentIds(std::vector<std::string> experimentIdsInput) { experimentIds = experimentIdsInput; }

    // Convert to JSON.
    crow::json::wvalue convertToJson();

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string labId;
    std::string labAdminId;
    std::string name;
    std::string location;
    std::string capacity;
    Budget budget;
    std::vector<std::string> userIds;
    std::vector<std::string> equipmentIds;
    std::vector<std::string> experimentIds;
};

#endif // LAB_H