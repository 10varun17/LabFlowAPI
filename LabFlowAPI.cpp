
/**
 * @file LabFlowAPI.cpp
 * @brief Implementation of LabFlow API for a lab management system.
 * 
 * This file provides the implementation for LabFlow API, which manages 
 * lab resources such as equipment, experiments, and personnel.
 */

#include <crow.h>
#include <map>
#include <string>
#include "resourceMaps.h"
#include "Professor.h"
#include "Administrator.h"
#include "Student.h"
#include "Lab.h"
#include "Equipment.h"
#include "Experiment.h"
#include "GenericUserAPI.h"
#include "labFunctions.h"
#include "equipmentFunctions.h"
#include "experimentFunctions.h"
#include "FileHandlingTemplate.h"

using namespace std;
using namespace crow;

extern map<string, Professor> professorsMap;
extern map<string, Student> studentsMap;
extern map<string, Lab> labsMap;
extern map<string, Administrator> administratorsMap;
extern map<string, Experiment> experimentsMap;
extern map<string, Equipment> equipmentsMap;

/**
 * @brief Entry point for the LabFlow API application.
 * 
 * Initializes resource maps, sets up API routes using the Crow framework,
 * and runs the application.
 * 
 * @return int Exit status of the application.
 */
int main()
{
    // Create GenericUserAPIs to use in the CROW_ROUTES
    GenericUserAPI<Professor>::resourceMap = professorsMap;
    GenericUserAPI<Student>::resourceMap = studentsMap;
    GenericUserAPI<Administrator>::resourceMap = administratorsMap;

    SimpleApp app;

    // Professors API routes
    CROW_ROUTE(app, "/api/professors").methods(HTTPMethod::POST)(GenericUserAPI<Professor>::createResource);
    CROW_ROUTE(app, "/api/professors").methods(HTTPMethod::GET)(GenericUserAPI<Professor>::readAllResources);
    CROW_ROUTE(app, "/api/professors/<string>").methods(HTTPMethod::GET)(GenericUserAPI<Professor>::readResource);
    CROW_ROUTE(app, "/api/professors/<string>").methods(HTTPMethod::PUT)(GenericUserAPI<Professor>::updateResource);
    CROW_ROUTE(app, "/api/professors/<string>").methods(HTTPMethod::DELETE)(GenericUserAPI<Professor>::deleteResource);

    // Students API routes
    CROW_ROUTE(app, "/api/students").methods(HTTPMethod::POST)(GenericUserAPI<Student>::createResource);
    CROW_ROUTE(app, "/api/students").methods(HTTPMethod::GET)(GenericUserAPI<Student>::readAllResources);
    CROW_ROUTE(app, "/api/students/<string>").methods(HTTPMethod::GET)(GenericUserAPI<Student>::readResource);
    CROW_ROUTE(app, "/api/students/<string>").methods(HTTPMethod::PUT)(GenericUserAPI<Student>::updateResource);
    CROW_ROUTE(app, "/api/students/<string>").methods(HTTPMethod::DELETE)(GenericUserAPI<Student>::deleteResource);

    // Administrators API routes
    CROW_ROUTE(app, "/api/administrators").methods(HTTPMethod::POST)(GenericUserAPI<Administrator>::createResource);
    CROW_ROUTE(app, "/api/administrators").methods(HTTPMethod::GET)(GenericUserAPI<Administrator>::readAllResources);
    CROW_ROUTE(app, "/api/administrators/<string>").methods(HTTPMethod::GET)(GenericUserAPI<Administrator>::readResource);
    CROW_ROUTE(app, "/api/administrators/<string>").methods(HTTPMethod::PUT)(GenericUserAPI<Administrator>::updateResource);
    CROW_ROUTE(app, "/api/administrators/<string>").methods(HTTPMethod::DELETE)(GenericUserAPI<Administrator>::deleteResource);

    // Labs API routes
    CROW_ROUTE(app, "/api/labs").methods(HTTPMethod::POST)(createLab);
    CROW_ROUTE(app, "/api/labs").methods(HTTPMethod::GET)(readAllLabs);
    CROW_ROUTE(app, "/api/labs/<string>").methods(HTTPMethod::GET)(readLab);
    CROW_ROUTE(app, "/api/labs/<string>").methods(HTTPMethod::PUT)(updateLab);
    CROW_ROUTE(app, "/api/labs/<string>").methods(HTTPMethod::DELETE)(deleteLab);

    // Equipment API routes
    CROW_ROUTE(app, "/api/equipments").methods(HTTPMethod::POST)(createEquipment);
    CROW_ROUTE(app, "/api/equipments").methods(HTTPMethod::GET)(readAllEquipments);
    CROW_ROUTE(app, "/api/equipments/<string>").methods(HTTPMethod::GET)(readEquipment);
    CROW_ROUTE(app, "/api/equipments/<string>").methods(HTTPMethod::PUT)(updateEquipment);
    CROW_ROUTE(app, "/api/equipments/<string>").methods(HTTPMethod::DELETE)(deleteEquipment);

    // Experiments API routes
    CROW_ROUTE(app, "/api/experiments").methods(HTTPMethod::POST)(createExperiment);
    CROW_ROUTE(app, "/api/experiments").methods(HTTPMethod::GET)(readAllExperiments);
    CROW_ROUTE(app, "/api/experiments/<string>").methods(HTTPMethod::GET)(readExperiment);
    CROW_ROUTE(app, "/api/experiments/<string>").methods(HTTPMethod::PUT)(updateExperiment);
    CROW_ROUTE(app, "/api/experiments/<string>").methods(HTTPMethod::DELETE)(deleteExperiment);

    app.port(17177).run();

    // Save resources back to files
    saveToFile<Professor>(GenericUserAPI<Professor>::resourceMap, "professors.json");
    saveToFile<Student>(GenericUserAPI<Student>::resourceMap, "students.json");
    saveToFile<Administrator>(GenericUserAPI<Administrator>::resourceMap, "administrators.json");
    saveToFile<Lab>(labsMap, "labs.json");
    saveToFile<Equipment>(equipmentsMap, "equipments.json");
    saveToFile<Experiment>(experimentsMap, "experiments.json");
}
