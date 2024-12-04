#ifndef BUDGET_H
#define BUDGET_H

#include <crow.h>

class Budget
{
public:
    // Constructors
    Budget() {}
    Budget(crow::json::rvalue readValueJson);

    // Getters and Setters
    float getTotalAmount() const { return totalAmount; }
    float getSpentAmount() const { return spentAmount; }
    float getRemainingAmount() const { return remainingAmount; }
    void setTotalAmount(float amount) { totalAmount = amount; }
    void setSpentAmount(float amount) { spentAmount = amount; }
    void setRemainingAmount(float amount) { remainingAmount = amount; }

    // JSON methods
    crow::json::wvalue convertToJson();
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    float totalAmount;
    float spentAmount;
    float remainingAmount;
};

#endif // BUDGET_H
