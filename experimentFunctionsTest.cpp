/**
 * @file experimentFunctionsTest.cpp
 * @brief provides unit testing for experimentFunctions.cpp
 * However, it covers not only experimentFunctions.cpp but also labFunctions.cpp, equipmentFunctions.cpp, and genericUserAPI.cpp since they work the same.
 * We chose experimentFunctions.cpp to test since all the functions in the other implementation files are a subset of the functions that experimentFunctionsTest.cpp has.
 * Therefore, we acheive 100% coverage through this along side with the other two test files.
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "experimentFunctions.h"
#include "Experiment.h"
// #include "http_request.h"

using namespace std;
using namespace crow;

map<string, Experiment> experimentsMap;

TEST_CASE("Post: Creating a new Experiment resource") 
{
    // Setup resource map to be empty before the test
    experimentsMap.clear();
    request req;

    SUBCASE("401: authetication failed")
    {
        response res = createExperiment(req);
        CHECK(res.code == 401);
    }

    SUBCASE("400: request with an invalid json")
    {
        // Setup request object
        req.body = R"({invalid_json})"; 
        req.headers.insert({"Authorization", "PHYS17"});

        // Perform the action
        response res = createExperiment(req);

        // Check the results
        CHECK(res.code == 400); // Check that the response code is 400
        CHECK("Invalid JSON" == res.body); // Validate the reponse body
    }

    SUBCASE("201: created successfully")
    {
        // Setup request object
        req.headers.insert({"Authorization", "PHYS17"});
        req.body = R"({"equipmentIds":["equip_001","equip_002"],"userIds":["std_001","prof_001"],"approvalStatus":true,"cost":1500.0,"researchOutput":{"publishedOn":["2024-10-29","2025-04-17"],"publishedIn":["Multi-agent robotics journal","Jorunal of Robotics"],"numCitations":4980},"endTime":"2025-10-12_17:00","startTime":"2024-10-10_09:00","description":"An experiment to form a triangle with a group of three robots","title":"Shape formation in multi-agent robotics","experimentId":"exp_001"})"; 

        // Perform the action
        response res = createExperiment(req);

        // Check the results
        string id1 = "exp_001";
        CHECK(res.code == 201); // Check that the response code is 201 Created
        CHECK(res.body == req.body); // Validate the reponse body
        CHECK(experimentsMap.size() == 1); // Ensure the resource was added to the map
        CHECK(experimentsMap.at(id1).getId() == id1); // Validate the resource content
        // CHECK(experimentsMap.at(id1).getGenre() == "Rock"); // Validate the resource content
    }
}

TEST_CASE("Read: Reading a list of experiment resources / a single experiment resource")
{
    // Setup resource map
    request req;
    req.headers.insert({"Authorization", "PHYS17"});

    req.body = R"({"experimentId":"exp_002","title":"Double Slit Experiment","description":"A recreation of the famous double-slit experiment in Quantum Mechanics Lab","startTime":"","endTime":"","researchOutput":{"numCitations":0,"publishedIn":[],"publishedOn":[]},"cost":3000.0,"approvalStatus":false,"userIds":["std_002","std_003","prof_002"],"equipmentIds":["equip_005"]})"; 
    createExperiment(req);
    
    req.body = R"({"equipmentIds":["equip_006","equip_007"],"userIds":["std_003","std_004","prof_003","prof_004"],"approvalStatus":true,"cost":2000.0,"researchOutput":{"publishedOn":["2025-02-10","2025-06-05"],"publishedIn":["Journal of Material Science","Mechanical Engineering Research"],"numCitations":1250},"endTime":"2025-01-15_16:00","startTime":"2024-12-15_10:00","description":"An experiment to study stress-strain behavior of metals under load","title":"Stress Analysis of Metallic Materials","experimentId":"exp_003"})";
    createExperiment(req);
    
    req.body = R"({"equipmentIds":["equip_006","equip_008","equip_009"],"userIds":["std_005","std_001","std_003","prof_004"],"approvalStatus":true,"cost":1800.0,"researchOutput":{"publishedOn":["2025-03-15","2025-07-20"],"publishedIn":["International Journal of Fluid Mechanics","Hydraulic Engineering Studies"],"numCitations":980},"endTime":"2025-02-01_18:00","startTime":"2024-12-20_08:30","description":"Analyzing pressure drops and flow rates in pipe systems","title":"Fluid Flow in Pipe Networks","experimentId":"exp_004"})";
    createExperiment(req);
    // Now there are four experiment objects

    SUBCASE("404: Not found")
    {
        response res = readExperiment(req, "exp_999");
        CHECK(res.code == 404);
    }

    // Covers readExperiment
    SUBCASE("Reading an experiment by an ID")
    {
        string id4 = "exp_004";
        response res = readExperiment(req, id4);
        CHECK(res.body == experimentsMap.at(id4).convertToJson().dump());
        CHECK(res.code == 200);
    }

    // Covers readAllExperiments
    SUBCASE("Reading all experiments")
    {
        response res = readAllExperiments(req);
        string expectedResult = R"([{"equipmentIds":["equip_001","equip_002"],"userIds":["std_001","prof_001"],"approvalStatus":true,"cost":1500.0,"researchOutput":{"publishedOn":["2024-10-29","2025-04-17"],"publishedIn":["Multi-agent robotics journal","Jorunal of Robotics"],"numCitations":4980},"endTime":"2025-10-12_17:00","startTime":"2024-10-10_09:00","description":"An experiment to form a triangle with a group of three robots","title":"Shape formation in multi-agent robotics","experimentId":"exp_001"},{"experimentId":"exp_002","title":"Double Slit Experiment","description":"A recreation of the famous double-slit experiment in Quantum Mechanics Lab","startTime":"","endTime":"","researchOutput":{"numCitations":0,"publishedIn":[],"publishedOn":[]},"cost":3000.0,"approvalStatus":false,"userIds":["std_002","std_003","prof_002"],"equipmentIds":["equip_005"]},{"equipmentIds":["equip_006","equip_007"],"userIds":["std_003","std_004","prof_003","prof_004"],"approvalStatus":true,"cost":2000.0,"researchOutput":{"publishedOn":["2025-02-10","2025-06-05"],"publishedIn":["Journal of Material Science","Mechanical Engineering Research"],"numCitations":1250},"endTime":"2025-01-15_16:00","startTime":"2024-12-15_10:00","description":"An experiment to study stress-strain behavior of metals under load","title":"Stress Analysis of Metallic Materials","experimentId":"exp_003"},{"equipmentIds":["equip_006","equip_008","equip_009"],"userIds":["std_005","std_001","std_003","prof_004"],"approvalStatus":true,"cost":1800.0,"researchOutput":{"publishedOn":["2025-03-15","2025-07-20"],"publishedIn":["International Journal of Fluid Mechanics","Hydraulic Engineering Studies"],"numCitations":980},"endTime":"2025-02-01_18:00","startTime":"2024-12-20_08:30","description":"Analyzing pressure drops and flow rates in pipe systems","title":"Fluid Flow in Pipe Networks","experimentId":"exp_004"}])";
        CHECK(res.body == expectedResult);
        CHECK(res.code == 200);
    }

    // Covers readAllExperiments and searchExperiments
    SUBCASE("Reading all experiments by search string (using searchExperiments)")
    {
        req.url_params = query_string("?search=experiment");
        response res = readAllExperiments(req);
        string expectedResult = R"([{"equipmentIds":["equip_001","equip_002"],"userIds":["std_001","prof_001"],"approvalStatus":true,"cost":1500.0,"researchOutput":{"publishedOn":["2024-10-29","2025-04-17"],"publishedIn":["Multi-agent robotics journal","Jorunal of Robotics"],"numCitations":4980},"endTime":"2025-10-12_17:00","startTime":"2024-10-10_09:00","description":"An experiment to form a triangle with a group of three robots","title":"Shape formation in multi-agent robotics","experimentId":"exp_001"},{"experimentId":"exp_002","title":"Double Slit Experiment","description":"A recreation of the famous double-slit experiment in Quantum Mechanics Lab","startTime":"","endTime":"","researchOutput":{"numCitations":0,"publishedIn":[],"publishedOn":[]},"cost":3000.0,"approvalStatus":false,"userIds":["std_002","std_003","prof_002"],"equipmentIds":["equip_005"]},{"equipmentIds":["equip_006","equip_007"],"userIds":["std_003","std_004","prof_003","prof_004"],"approvalStatus":true,"cost":2000.0,"researchOutput":{"publishedOn":["2025-02-10","2025-06-05"],"publishedIn":["Journal of Material Science","Mechanical Engineering Research"],"numCitations":1250},"endTime":"2025-01-15_16:00","startTime":"2024-12-15_10:00","description":"An experiment to study stress-strain behavior of metals under load","title":"Stress Analysis of Metallic Materials","experimentId":"exp_003"}])";
        CHECK(res.body == expectedResult);
        CHECK(res.code == 200);
    }

    // Covers readAllExperiments and sortExperiments(string sortString)
    SUBCASE("Reading all experiments sorted by cost (sortExperiments(string sortString))")
    {
        req.url_params = query_string("?sort=cost");
        response res = readAllExperiments(req);
        string expectedResult = R"([{"equipmentIds":["equip_001","equip_002"],"userIds":["std_001","prof_001"],"approvalStatus":true,"cost":1500.0,"researchOutput":{"publishedOn":["2024-10-29","2025-04-17"],"publishedIn":["Multi-agent robotics journal","Jorunal of Robotics"],"numCitations":4980},"endTime":"2025-10-12_17:00","startTime":"2024-10-10_09:00","description":"An experiment to form a triangle with a group of three robots","title":"Shape formation in multi-agent robotics","experimentId":"exp_001"},{"experimentId":"exp_004","title":"Fluid Flow in Pipe Networks","description":"Analyzing pressure drops and flow rates in pipe systems","startTime":"2024-12-20_08:30","endTime":"2025-02-01_18:00","researchOutput":{"numCitations":980,"publishedIn":["International Journal of Fluid Mechanics","Hydraulic Engineering Studies"],"publishedOn":["2025-03-15","2025-07-20"]},"cost":1800.0,"approvalStatus":true,"userIds":["std_005","std_001","std_003","prof_004"],"equipmentIds":["equip_006","equip_008","equip_009"]},{"equipmentIds":["equip_006","equip_007"],"userIds":["std_003","std_004","prof_003","prof_004"],"approvalStatus":true,"cost":2000.0,"researchOutput":{"publishedOn":["2025-02-10","2025-06-05"],"publishedIn":["Journal of Material Science","Mechanical Engineering Research"],"numCitations":1250},"endTime":"2025-01-15_16:00","startTime":"2024-12-15_10:00","description":"An experiment to study stress-strain behavior of metals under load","title":"Stress Analysis of Metallic Materials","experimentId":"exp_003"},{"equipmentIds":["equip_005"],"userIds":["std_002","std_003","prof_002"],"approvalStatus":false,"cost":3000.0,"researchOutput":{"publishedOn":[],"publishedIn":[],"numCitations":0},"endTime":"","startTime":"","description":"A recreation of the famous double-slit experiment in Quantum Mechanics Lab","title":"Double Slit Experiment","experimentId":"exp_002"}])";
        CHECK(res.body == expectedResult);
        CHECK(res.code == 200);
    }

    // Covers readAllExperiments and filterExperiments(bool approvalStatus)
    SUBCASE("Reading all experiments filtered by approval status (using searchExperiments(bool approvalStatus))")
    {
        req.url_params = query_string("?type=isapproved&isapproved=TRUE");
        response res = readAllExperiments(req);
        string expectedResult = R"([{"equipmentIds":["equip_001","equip_002"],"userIds":["std_001","prof_001"],"approvalStatus":true,"cost":1500.0,"researchOutput":{"publishedOn":["2024-10-29","2025-04-17"],"publishedIn":["Multi-agent robotics journal","Jorunal of Robotics"],"numCitations":4980},"endTime":"2025-10-12_17:00","startTime":"2024-10-10_09:00","description":"An experiment to form a triangle with a group of three robots","title":"Shape formation in multi-agent robotics","experimentId":"exp_001"},{"experimentId":"exp_003","title":"Stress Analysis of Metallic Materials","description":"An experiment to study stress-strain behavior of metals under load","startTime":"2024-12-15_10:00","endTime":"2025-01-15_16:00","researchOutput":{"numCitations":1250,"publishedIn":["Journal of Material Science","Mechanical Engineering Research"],"publishedOn":["2025-02-10","2025-06-05"]},"cost":2000.0,"approvalStatus":true,"userIds":["std_003","std_004","prof_003","prof_004"],"equipmentIds":["equip_006","equip_007"]},{"equipmentIds":["equip_006","equip_008","equip_009"],"userIds":["std_005","std_001","std_003","prof_004"],"approvalStatus":true,"cost":1800.0,"researchOutput":{"publishedOn":["2025-03-15","2025-07-20"],"publishedIn":["International Journal of Fluid Mechanics","Hydraulic Engineering Studies"],"numCitations":980},"endTime":"2025-02-01_18:00","startTime":"2024-12-20_08:30","description":"Analyzing pressure drops and flow rates in pipe systems","title":"Fluid Flow in Pipe Networks","experimentId":"exp_004"}])";
        CHECK(res.body == expectedResult);
        CHECK(res.code == 200);
    }

    // Covers readAllExperiments and filterExperiments(std::string type, float amount)
    SUBCASE("Reading all experiments filtered by sortString (using filterExperiments(std::string type, float amount))")
    {
        req.url_params = query_string("?type=citations&number=2000");
        response res = readAllExperiments(req);
        string expectedResult = R"([{"equipmentIds":["equip_001","equip_002"],"userIds":["std_001","prof_001"],"approvalStatus":true,"cost":1500.0,"researchOutput":{"publishedOn":["2024-10-29","2025-04-17"],"publishedIn":["Multi-agent robotics journal","Jorunal of Robotics"],"numCitations":4980},"endTime":"2025-10-12_17:00","startTime":"2024-10-10_09:00","description":"An experiment to form a triangle with a group of three robots","title":"Shape formation in multi-agent robotics","experimentId":"exp_001"}])";
        CHECK(res.body == expectedResult);
        CHECK(res.code == 200);
    }

    // Covers readAllExperiments and filterExperiments(float cost)
    SUBCASE("Reading all experiments filtered by sort string (using filterExperiments(float cost))")
    {
        req.url_params = query_string("?cost=2000");
        response res = readAllExperiments(req);
        string expectedResult = R"([{"experimentId":"exp_002","title":"Double Slit Experiment","description":"A recreation of the famous double-slit experiment in Quantum Mechanics Lab","startTime":"","endTime":"","researchOutput":{"numCitations":0,"publishedIn":[],"publishedOn":[]},"cost":3000.0,"approvalStatus":false,"userIds":["std_002","std_003","prof_002"],"equipmentIds":["equip_005"]},{"equipmentIds":["equip_006","equip_007"],"userIds":["std_003","std_004","prof_003","prof_004"],"approvalStatus":true,"cost":2000.0,"researchOutput":{"publishedOn":["2025-02-10","2025-06-05"],"publishedIn":["Journal of Material Science","Mechanical Engineering Research"],"numCitations":1250},"endTime":"2025-01-15_16:00","startTime":"2024-12-15_10:00","description":"An experiment to study stress-strain behavior of metals under load","title":"Stress Analysis of Metallic Materials","experimentId":"exp_003"}])";
        CHECK(res.body == expectedResult);
        CHECK(res.code == 200);
    }

    // Covers readAllExperiments and filterExperiments(float cost)
    SUBCASE("Reading all experiments filtered by an invalid sort string returns 400 (using filterExperiments(float cost))")
    {
        req.url_params = query_string("?cost=invalid");
        response res = readAllExperiments(req);
        CHECK(res.code == 400);
    }
}

TEST_CASE("Update: change an existing lab")
{
    request req;
    string id1 = "exp_001";
    string idNotFound = "exp_999";

    SUBCASE("401: authetication failed")
    {
        response res;
        updateExperiment(req, res, id1);
        CHECK(res.code == 401);
    }

    req.headers.insert({"Authorization", "PHYS17"});

    SUBCASE("400: invalid JSON")
    {
        req.body = R"({invalid_json})"; 
        response res;
        updateExperiment(req, res, id1);
        CHECK(res.code == 400);
    }

    SUBCASE("404: Experiment Found")
    {
        response res;
        updateExperiment(req, res, idNotFound);
        CHECK(res.code == 404);
    }

    SUBCASE("200: successfully updated")
    {
        response res;
        string newExperiment1 = R"({"equipmentIds":["equip_001"],"userIds":["std_001","prof_001"],"approvalStatus":false,"cost":1500.0,"researchOutput":{"publishedOn":["2024-10-29","2025-04-17"],"publishedIn":["Multi-agent robotics journal","Jorunal of Robotics"],"numCitations":4980},"endTime":"2025-10-12_17:00","startTime":"2024-10-10_09:00","description":"An experiment to form a triangle with a group of three robots","title":"Shape formation in multi-agent robotics","experimentId":"exp_001"})";

        req.body = newExperiment1;
        updateExperiment(req, res, id1);

        CHECK(res.code == 200);
        CHECK(readExperiment(req, id1).body == newExperiment1);
    }
}

TEST_CASE("Delete: delete an existing lab")
{
    request req;
    string id1 = "exp_001";
    string idNotFound = "exp_999";

    SUBCASE("401: authetication failed")
    {
        response res =deleteExperiment(req, id1);
        CHECK(res.code == 401);
    }

    req.headers.insert({"Authorization", "PHYS17"});

    SUBCASE("404: Experiment Found")
    {
        response res = deleteExperiment(req, idNotFound);
        CHECK(res.code == 404);
    }

    SUBCASE("204: successfully deleted")
    {
        response res = deleteExperiment(req, id1);

        CHECK(res.code == 204);
        CHECK(experimentsMap.size() == 3);
    }
}