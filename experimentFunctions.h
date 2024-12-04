#ifndef EXPERIMENT_FUNCTIONS_H
#define EXPERIMENT_FUNCTIONS_H

#include <crow.h>
#include <map>
#include <string>

// Functions used to handle POST, GET, PUT, and DELETE requests for the Experiment resource.
crow::response createExperiment(crow::request req);
crow::response readExperiment(std::string id);
crow::response readAllExperiments(crow::request req);
void updateExperiment(crow::request req, crow::response& res, std::string id); 
crow::response deleteExperiment(std::string id);
crow::response searchExperiments(std::string searchString);
crow::response filterExperiments(std::string type, float amount);
crow::response filterExperiments(bool approvalStatus);
crow::response filterExperiments(float cost);
crow::response sortExperiments(std::string sortString);

#endif // EXPERIMENT_FUNCTIONS_H 