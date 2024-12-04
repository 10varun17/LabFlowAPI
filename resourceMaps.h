#ifndef RESOURCEMAPS_H
#define RESOURCEMAPS_H

#include <crow.h>
#include <map>
#include <string>
#include "Professor.h"
#include "Administrator.h"
#include "Student.h"
#include "Lab.h"
#include "Equipment.h"
#include "Experiment.h"
#include "FileHandlingTemplate.h"

using namespace std;
using namespace crow;

// Initialize resource maps from files
map<string, Professor> professorsMap = loadFromFile<Professor>("professors.json");
map<string, Student> studentsMap = loadFromFile<Student>("students.json");
map<string, Lab> labsMap = loadFromFile<Lab>("labs.json");
map<string, Administrator> administratorsMap = loadFromFile<Administrator>("administrators.json");
map<string, Experiment> experimentsMap = loadFromFile<Experiment>("experiments.json");
map<string, Equipment> equipmentsMap = loadFromFile<Equipment>("equipments.json");

#endif