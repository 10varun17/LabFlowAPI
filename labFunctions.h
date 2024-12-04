#ifndef LAB_FUNCTIONS_H
#define LAB_FUNCTIONS_H

#include <crow.h>
#include <map>
#include <string>

// Functions used to handle POST, GET, PUT, and DELETE requests for the Lab resource.
crow::response createLab(crow::request req);
crow::response readLab(std::string id);
crow::response readAllLabs(crow::request req);
void updateLab(crow::request req, crow::response& res, std::string id); 
crow::response deleteLab(std::string id);
crow::response searchLabs(std::string searchString);
crow::response filterLabs(std::string type, float amount);
crow::response sortLabs(std::string sortString);

#endif // LAB_FUNCTIONS_H 

// sort by labid, sort by budget
// sort by numEquipments, sort by experimentIds