#ifndef GENERIC_USER_API_H
#define GENERIC_USER_API_H

#include <crow.h>
#include <map>
#include <string>

template<typename T> 
class GenericUserAPI 
{
public:
    static std::map<std::string, T> resourceMap;
    static crow::response searchByName(std::string searchString);
    static crow::response sortUsers(std::string sortString);
    static crow::response createResource(crow::request req);
    static crow::response readResource(std::string id); 
    static crow::response readAllResources(crow::request req);
    static void updateResource(crow::request req, crow::response& res, std::string id); 
    static crow::response deleteResource(crow::request req, std::string id); 
};

// #include "GenericUserAPI.cpp"

#endif // GENERIC_USER_API_H