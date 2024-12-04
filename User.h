#ifndef USER_H
#define USER_H

#include <string>
#include <crow.h>

class User
{
public:
    // Constructors
    User() {}
    User(crow::json::rvalue readValueJson);

    // Getters
    std::string getId() const { return userId; }
    std::string getName() const { return userName; }

    // Setters
    void setId(std::string userIdInput) { userId = userIdInput; }
    void setUserName(std::string userNameInput) { userName = userNameInput; }

    // JSON Methods
    virtual crow::json::wvalue convertToJson();
    virtual void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string userId;
    std::string userName;
};

#endif // USER_H
