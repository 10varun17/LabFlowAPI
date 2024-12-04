#ifndef STUDENT_H
#define STUDENT_H

#include <crow.h>
#include "User.h"
#include <string>
#include <vector>

class Student : public User
{
public:
    Student() : User() {}
    Student(crow::json::rvalue readValueJson);

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

#endif // STUDENT_H