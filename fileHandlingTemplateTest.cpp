#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "FileHandlingTemplate.h"
#include "Equipment.h"
#include <string>

TEST_CASE("Saving to a file and loading from a file.") 
{
    // Load a resources to read.
    map<string, Equipment> EquipmentsMap;
    EquipmentsMap["1"] = Equipment{json::load(R"({"equipmentId":"\"equip_001\"","name":"\"Muon Detector\"","description":"\"A particle detector that can identify and observe the by-products of cosmic ray particles\"","available":true})")};
    EquipmentsMap["2"] = Equipment{json::load(R"({"equipmentId":"\"equip_002\"","name":"\"Cloud Chamber\"","description":"\"a device that visualizes the paths of charged particles, like alpha and beta particles, by creating visible tracks of condensation in a supersaturated vapor\"","available":false})")};

    // Perform the action
    saveToFile<Equipment>(EquipmentsMap, "fileHandlingTemplateTest.json");
    map<string, Equipment> EquipmentsMapLoaded = loadFromFile<Equipment>("fileHandlingTemplateTest.json");

    // Check the results
    CHECK(EquipmentsMap.size() == EquipmentsMapLoaded.size()); // Ensure saved and loaded map are the same size.

    string id1 = EquipmentsMap.at("1").getId();
    CHECK(EquipmentsMap.at("1").getId() == EquipmentsMapLoaded.at(id1).getId());
    CHECK(EquipmentsMap.at("1").getName() == EquipmentsMapLoaded.at(id1).getName());
    CHECK(EquipmentsMap.at("1").getDescription() == EquipmentsMapLoaded.at(id1).getDescription());
    CHECK(EquipmentsMap.at("1").isAvailable() == EquipmentsMapLoaded.at(id1).isAvailable());

    string id2 = EquipmentsMap.at("2").getId();
    CHECK(EquipmentsMap.at("2").getId() == EquipmentsMapLoaded.at(id2).getId());
    CHECK(EquipmentsMap.at("2").getName() == EquipmentsMapLoaded.at(id2).getName());
    CHECK(EquipmentsMap.at("2").getDescription() == EquipmentsMapLoaded.at(id2).getDescription());
    CHECK(EquipmentsMap.at("2").isAvailable() == EquipmentsMapLoaded.at(id2).isAvailable());
}