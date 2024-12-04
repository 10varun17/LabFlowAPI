#ifndef EQUIPMENT_FUNCTIONS_H
#define EQUIPMENT_FUNCTIONS_H

#include <crow.h>
#include <map>
#include <string>

// Functions used to handle POST, GET, PUT, and DELETE requests for the Equipment resource.
crow::response createEquipment(crow::request req);
crow::response readEquipment(std::string id);
crow::response readAllEquipments(crow::request req);
void updateEquipment(crow::request req, crow::response& res, std::string id); 
crow::response deleteEquipment(std::string id);
crow::response searchEquipments(std::string searchString);
crow::response sortEquipments(std::string sortString);
crow::response filterEquipments(bool available);

#endif // EQUIPMENT_FUNCTIONS_H 