#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <crow.h>
#include <string>

class Equipment
{
public:
    // Constructors
    Equipment() {}
    Equipment(crow::json::rvalue readValueJson);

    // Getters
    std::string getId() const { return equipmentId; }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    bool isAvailable() const { return available; }

    // Setters
    void setId(std::string equipmentIdInput) { equipmentId = equipmentIdInput; }
    void setName(std::string nameInput) { name = nameInput; }
    void setDescription(std::string descriptionInput) { description = descriptionInput; }
    void setAvailability(bool availabilityInput) { available = availabilityInput; }

    // JSON Methods
    crow::json::wvalue convertToJson();
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string equipmentId;
    std::string name;
    std::string description;
    bool available;
};

#endif // EQUIPMENT_H
