#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <crow.h>
#include "User.h"
#include "Lab.h"
#include <string>
#include <vector>

class Administrator : public User
{
public:
    Administrator() : User(), labManaged(nullptr) {}
    Administrator(crow::json::rvalue& readValueJson);

    // Getter
    Lab* getLabManaged() const { return labManaged; }

    // Setter
    void setLabManaged(Lab* labInput) { labManaged = labInput; }

    // Override JSON methods
    crow::json::wvalue convertToJson() override;
    void updateFromJson(crow::json::rvalue readValueJson) override;

private:
    Lab* labManaged;
};

#endif // ADMINISTRATOR_H