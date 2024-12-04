#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "User.h"

class Professor : public User
{
public:
    Professor() : User() {}
    Professor(crow::json::rvalue readValueJson);

    // Getter
    std::vector<std::string> getExperimentIds() const { return experimentIds; }

    // Setter
    void setExperimentIds(std::vector<std::string> experimentIdsInput) { experimentIds = experimentIdsInput; }

    // Override JSON methods
    crow::json::wvalue convertToJson() override;
    void updateFromJson(crow::json::rvalue readValueJson) override;

private:
    std::vector<std::string> experimentIds;
};

#endif // PROFESSOR_H