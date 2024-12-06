# Project Design Document

## Introduction
LabFlow API supports lab mangement operations for administrators, professors, and students by providing various features such as equipment tracking, budget and expense tracking, logging research outputs, etc. It allows for users to sort, search, and filter labs, experiments, equipments, and the people associated with the lab. Overall, this system aims to improve the efficiency of lab management and support everyone involved.

## Background/Context
Laboratories are vital to academic institutions and research centres. They require extensive planning and coordination to maintain equipment, manage budget, schedule lab sessions, and record research outputs. Traditionally, lab management processes are done by manual tracking and they often have scheduling conflicts. LabFlow API addresses these issues by integrating all lab management operations into a single system that allows users to interact with lab resources according to their need. Further, the API allows the lab to have an extent to which a user can interact with the lab resources. This functionality helps improve the security of the lab.

## Stakeholders
* **Administrators:** Individuals who use this API for managing lab operations, resources, and user access. They are interested in control over budget, equipment, and user roles.
* **Professors:** Individuals who use this API to oversee experiments and ensure alignment with academic and research goals. They use this API to approve experiments and manage research outputs.
* **Students:** Individuals who can propose and do experiments in the lab but have limited access to the details of the lab resources and equipment. They can collaborate  with professors to work on an experiment.

## Functional Requirements
1. Resource Creation
    * The service shall allow administrators to create new labs via POST requests.
    * The service shall allow professors and students to create new experiments via POST requests.
    * The service shall allow administrators to create new users for the lab via POST requests.
    * The service shall allow administrators and professors to create new equipments via POST requests.
    * The service shall validate all incoming data against predefined schemas before creating a new resource.
    * The service shall return a 201 Created status code and the created resource in the response body upon successful creation.

2. Resource Retrieval
   * The service shall provide endpoints for users of any level to retrieve lists of experiments, equipments, and users in the lab via GET requests.
   * The service shall allow retrieval of detailed information for a single resource by its unique identifier.
   * The service shall return a 200 OK status code and the requested resources in the response body upon successful retrieval.

3. Resource Update
   * The service shall permit administrators, professors, and students to update existing resource entries for experiments and equipments via PUT requests.
   * The service shall validate all incoming data for updates against predefined schemas.
   * The service shall return a 200 OK status code and the updated resource in the response body upon successful update.

4. Resource Deletion
   * The service shall enable administrators and professors to delete resource entries for experiments and equipments via DELETE requests.
   * The service shall return a 204 No Content status code upon successful deletion.
   * The service shall return a 401 Unauthorized status code if an unauthorized user attempts to delete a resource.
  
5. Data Validation
   * The service shall enforce data validation rules to ensure that all resource data conforms to the expected formats, types, and constraints.
   * The service shall return a 400 Bad Request status code along with error details if validation fails.

6. Authentication and Authorization   
   * The service shall require authentication for users attempting to create, update, or delete resources.
   * The service shall authorize users based on their roles, permitting only authorized users to modify or delete resource entries.

7. Error Handling
   * The service shall implement comprehensive error handling to provide meaningful error messages and appropriate HTTP status codes to the client for all failed operations.
   * The service shall return a 404 Not Found status code when a requested resource cannot be located.
   * The service shall return a 500 Internal Server Error status code in the event of unexpected server-side errors.


## Use Case Description

#### User (Administrator, Professor, Student)
* Create (POST)
  * As a lab administrator, I want to create new user accounts to allow professors and students to access the lab.
* Read (GET)
  * As a lab administrator, I want to view a list of all users or specific user profiles to monitor and manage lab access.
  * As a professor and a student, I want to view my own user profile to ensure my details are up-to-date.
* Update (PUT)
  * As a lab administrator, I want to update user details to reflect changes in staff assignments.
* Delete (DELETE)
  * As a lab administrator, I want to remove users who are no longer part of the lab to maintain an accurate and secure user database.

#### Lab
* Create (POST)
  * As a lab administrator, I want to create new lab entries to represent different laboratories under management.
* Read (GET)
  * As a professor and a student, I want to view details of the lab to understand its resources and schedule.
  * As a lab administrator, I need to retrieve lab information to monitor capacity, budget, and overall operations.
* Update (PUT)
  * As a lab administrator, I want to update lab details (e.g., capacity, budget) to reflect changes in lab operations or policies.
* Delete (DELETE)
  * As a lab administrator, I want to remove lab entries that are no longer active to maintain an accurate database.

#### Equipment
* Create (POST)
  * As a lab administrator, I want to add new equipment to the lab to ensure accurate tracking of lab resources.
  * As a professor, I want to add new equipment to the lab for research purpose.
* Read (GET)
  * As a professor and a student, I want to view available equipment to plan my experiments accordingly.
  * As a lab administrator, I need to retrieve a list of all equipments to monitor inventory and usage trends.
* Update (PUT)
  * As a lab administrator, I want to update equipment details (e.g., availability) to keep the database updated and accurate.
* Delete (DELETE)
  * As a lab administrator, I want to remove equipment that is no longer operational in the lab.

#### Experiment
* Create (POST)
  * As a professor and a student, I want to create new experiments in the lab.
* Read (GET)
  * As a professor and a student, I want to view my experiments to monitor progress and access details for analysis.
  * As a lab administrator, I need to review experiments to ensure compliance with safety protocols and resource allocation policies.
* Update (PUT)
  * As a professor and a student, I want to update experiment details (e.g., description, results, etc) to reflect ongoing
    developments or corrections in my work.
* Delete (DELETE)
  * As a professor, I want to remove experiments that are canceled or irrelevant to my research area.
  * As a lab administrator, I want to remove experiments for which the lab doesn't have sufficient funding.

## List Of Resources
* **User:** An individual who interacts with lab (administrator, professor, student)
* **Lab:** A representation of a physical laboratory space
* **Equipment:** A physical medium that represents tools and devices available in the lab
* **Experiment:** A model of an experiment
* **ResearchOutput:** A digital medium that represents experiment results and publications
* **Budget:** A digital medium that represents expenses and budget allocations associated with the lab
* **TimeSlot:**

## List of End Points
In the context of this API, `{id}` would typically be replaced by a unique identifier for the resource, such as a string or a number that uniquely identifies a user, experiment, or equipment. Moreover, `{user_type}` will be replaced by `administrators`, `professors`, or `students` because we have three different APIs for administrators, professors, and students with the same end points. 

### User (Administrator, Professor, Student)
* **POST** `/api/{user_type}`
  * **Description:** Create a new administrator, professor, or student.
  * **Request BODY:** 
    
    **Administrator**
    ```JSON
    {
      "userId": "admin_001",
      "userName": "Varun Rayamajhi",
      "labManaged":     {
        "equipmentIds": [
          "equip_001",
          "equip_002",
          "equip_003"
        ],
        "budget": {
          "remainingAmount": 35000,
          "spentAmount": 15000,
          "totalAmount": 50000
        },
        "capacity": "20",
        "location": "Jepson Hall, Room G14",
        "name": "Robotics Lab",
        "experimentIds": [
          "exp_001"
        ],
        "labId": "lab_001",
        "labAdminId": "admin_001",
        "userIds": [
          "std_001",
          "prof_001"
        ]
      }
    }
    ```


    **Professor**
    ```JSON
    {
      "userId": "prof_001",
      "userName": "Evelyn Carter",
      "experimentIds": ["exp_001"]
    }
    ```


    **Student**
    ```JSON
    {
      "userId": "std_001",
      "userName": "Matilda Róisín",
      "experimentIds": [
        "exp_001",
        "exp_004"
      ]
    }
    ```
  * **Response:** `201 Created` with the created user object in the body.
  * **Error:** `400 Bad Request` if input validation fails
  
* **GET** `/api/{user_type}`
  * **Description:** Retrieve a list of all administrators, professors, or users.
  * **Response:** `200 OK` with an array of administrator or professor or student objects in the body.
  
* **GET** `/api/{user_type}?search={searchString}`
  * **Description:** Retrieve a list of all administrators, professors, or users that have the desired `{searchString}`. Usually, the search string is the person's name.
  * **Response:** `200 OK` with an array of administrator or professor or student objects with the matching `{searchString}` in the body.
  * **Error:** `404 Not Found` if no matching object is found.

* **GET** `/api/{user_type}?sort={sortString}`
  * **Description:** Retrieve a list of all administrators, professors, or users sorted in increasing order according to `{sortString}`. `{sortString}` must be `name` or `id`.
  * **Response:** `200 OK` with an array of administrator or professor or student objects sorted according to the `{sortString}`.
  * **Error:** `400 Bad Request` if the sorting according to the given sort string is unavailable.
  
* **GET** `/api/{user_type}/{id}`
  * **Description:** Retrieve details of a specific administrator, professor, or student.
  * **Response:** `200 OK` with the administrator or professor or student object in the body.
  * **Error:** `404 Not Found` if the user doesn't exist;  `401 Unauthorized` if the user is unauthorized.

* **PUT** `/api/users/{id}`
  * **Description:** Update an existing administrator or professor or student.
  * **Request BODY:** 
    
    **Administrator**
    ```JSON
    {
      "userId": "admin_001",
      "userName": "Varun Rayamajhi",
      "labManaged":     {
        "equipmentIds": [
          "equip_001",
          "equip_002",
          "equip_003"
        ],
        "budget": {
          "remainingAmount": 35000,
          "spentAmount": 15000,
          "totalAmount": 50000
        },
        "capacity": "20",
        "location": "Jepson Hall, Room G14",
        "name": "Robotics Lab",
        "experimentIds": [
          "exp_001"
        ],
        "labId": "lab_001",
        "labAdminId": "admin_001",
        "userIds": [
          "std_001",
          "prof_001"
        ]
      }
    }
    ```


    **Professor**
    ```JSON
    {
      "userId": "prof_001",
      "userName": "Evelyn Carter",
      "experimentIds": ["exp_001"]
    }
    ```


    **Student**
    ```JSON
    {
      "userId": "std_001",
      "userName": "Matilda Róisín",
      "experimentIds": [
        "exp_001",
        "exp_004"
      ]
    }
    ```
  * **Response:** `200 OK` with the updated administrator, professor, or student object in the body.
  * **Error:** `400 Not Found` if the user doesn't exist; `400 Bad Request` if input validation fails; `401 Unauthorized` if the user is unauthorized.

* **DELETE** `/api/{user_type}/{id}`
  * **Description:** Delete a specific administrator, professor, or student.
  * **Response:** `404 No Content`.
  * **Error:** `404 Not Found` if the user doesn't exist; `401 Unauthorized` if the user is unauthorized.

### Lab
* **POST** `/api/labs`
  * **Description:** Create a new lab.
  * **Request BODY:**
    ```JSON
    {
      "labId": "lab_002",
      "labAdminId" : "admin_002",
      "userIds": [
        "std_002",
        "std_003",
        "prof_002"
      ],
      "experimentIds": [
        "exp_002"
      ],
      "name": "Quantum Mechanics Lab",
      "location": "Gottwald, Room D209",
      "capacity": "15",
      "budget": {
        "totalAmount": 75000,
        "spentAmount": 30000,
        "remainingAmount": 45000
      },
      "equipmentIds": [
        "equip_004",
        "equip_005"
      ]
    }
    ```
  * **Response:** `201 Created` with the created lab object in the body.
  * **Error:** `400 Bad Request` if input validation fails.
  
* **GET** `/api/labs`
  * **Description:** Retrieve a list of all labs.
  * **Response:** `200 OK` with an array of lab objects in the body.

* **GET** `/api/labs/?search={searchString}`
  * **Description:** Retrieve a list of all labs according to the given `{searchString}`. This string is usually the name or the location of the lab.
  * **Response:** `200 OK` with an array of lab objects in the body.
  * **Error:** `404 Not Found` if no matching lab is found.

* **GET** `/api/labs/?sort={sortString}`
  * **Description:** Retrieve a list of all labs sorted in increasing order according to `{sortString}`. `{sortString}` must be `name`, `id`, `totalamount`, `remainingamount`, `spentamount`, `numexperiments`, or `numequipments`.
  * **Response:** `200 OK` with an array of lab objects in the body.
  * **Error:** `400 Bad Request` if the sorting according to the given sort string is unavailable.

* **GET** `/api/labs/?type={filterType}&amount={amount}`
  * **Description:** Retrieve a list of filtered labs according to given filter type and amount. `{filterType}` must be `totalamount` or `remainingamount`, or `spentamount`. `{amount}` must be a string convertable to float. Example usage: retrieving labs whose budget has total amount greater than 5000.
  * **Response:** `200 OK` with an array of lab objects in the body.
  * **Error:** `400 Bad Request` if the filterType is not available or the amount isn't convertable to float type; `404 Not Found` if the desired lab is not found.

* **GET** `/api/labs/{id}`
  * **Description:** Retrieve details of a specific lab.
  * **Response:** `200 OK` with the specific lab object in the body.
  * **Error:** `401 Unauthorized` if the user is unauthorized; `404 Not Found` if the lab doesn't exist.

* **PUT** `/api/labs/{id}`
  * **Description:** Update an existing lab.
  * **Request BODY:**
    ```JSON
    {
      "labId": "lab_002",
      "labAdminId" : "admin_002",
      "userIds": [
        "std_002",
        "std_003",
        "prof_002"
      ],
      "experimentIds": [
        "exp_002"
      ],
      "name": "Quantum Mechanics Lab",
      "location": "Gottwald, Room D209",
      "capacity": "15",
      "budget": {
        "totalAmount": 75000,
        "spentAmount": 30000,
        "remainingAmount": 45000
      },
      "equipmentIds": [
        "equip_004",
        "equip_005"
      ]
    }
    ```
  * **Response:** `200 OK` with the updated lab object in the body.
  * **Error:** `404 Not Found` if the lab doesn't exist; `400 Bad Request` if input validation fails; `401 Unauthorized` if the user is unauthorized.

* **DELETE** `/api/labs/{id}`
  * **Description:** Delete a specific lab.
  * **Response:** `204 No Content`
  * **Error:** `404 Not Found` if the lab doesn't exist; `401 Unauthorized` if the user is unauthorized.
  
### Experiment
* **POST** `/api/experiments`
  * **Description:** Create a new experiment.
  * **Request BODY:** 
    ```JSON
    {
      "experimentId": "exp_001",
      "title": "Shape formation in multi-agent robotics",
      "description": "An experiment to form a triangle with a group of three robots",
      "startTime": "2024-10-10_09:00",
      "endTime": "2025-10-12_17:00",
      "researchOutput": {
        "numCitations": 4980,
        "publishedIn": [
          "Multi-agent robotics journal",
          "Jorunal of Robotics"
        ],
        "publishedOn": [
          "2024-10-29",
          "2025-04-17"
        ]
      },
      "cost": 1500,
      "approvalStatus": true,
      "userIds": [
        "std_001",
        "prof_001"
      ],
      "equipmentIds": [
        "equip_001",
        "equip_002"
      ]
    }
    ```
  * **Response:** `201 Created` with the created experiment object in the body.
  
* **GET** `/api/experiments`
  * **Description:** Retrieve a list of all experiments.
  * **Response:** `200 OK` with an array of experiment objects in the body.
  
* **GET** `/api/experiments/?search={searchString}`
  * **Description:** Retrieve a list of all experiments according to the given `{searchString}`. This string is usually a keyword related to the experiment.
  * **Response:** `200 OK` with an array of experiment objects in the body.
  * **Error:** `404 Not Found` if no matching experiment is found.

* **GET** `/api/experiments/?sort={sortString}`
  * **Description:** Retrieve a list of all experiments sorted in increasing order according to `{sortString}`. `{sortString}` must be `id`, `cost`, `starttime`, `endtime`, `numusers`, `numequipments`, `numcitations`, or `numpublications`.
  * **Response:** `200 OK` with an array of experiment objects in the body.
  * **Error:** `400 Bad Request` if the sorting according to the given sort string is unavailable.

* **GET** `/api/experiments/?type={filterType}&number={number}`
  * **Description:** Retrieve a list of filtered experiments according to given filter type and number. `{filterType}` must be `citations` or `publications`. `{number}` must be a string convertable to float. Example usage: retrieving experiments with citations greater than 300.
  * **Response:** `200 OK` with an array of experiment objects in the body.
  * **Error:** `400 Bad Request` if the filterType is not available or the number isn't convertable to float type; `404 Not Found` if the desired experiment is not found.

* **GET** `/api/experiments/?cost={cost}`
  * **Description:** Retrieve a list of experiments according to their costs. `{cost}` must be a string convertable to float. Example usage: retrieving experiments with cost greater than 3000.
  * **Response:** `200 OK` with an array of experiment objects in the body.
  * **Error:** `400 Bad Request` if the cost isn't convertable to float type; `404 Not Found` if the desired experiment is not found.

* **GET** `/api/experiments/?isapproved={approvalStatus}`
  * **Description:** Retrieve a list of experiments according to their approval status. If `{approvalStatus}` is `TRUE` or `true`, then approved experiments will be retrieved else experiments with no approval will be retrieved. 
  * **Response:** `200 OK` with an array of experiment objects in the body.
  * **Error:** `404 Not Found` if the desired experiment is not found.
  
* **GET** `/api/experiments/{id}`
  * **Description:** Retrieve details of a specific experiment.
  * **Response:** `200 OK` with the experiment object in the body.
  * **Error:** `404 Not Found` if the experiment doesn't exist.

* **PUT** `/api/experiments/{id}`
  * **Description:** Update an existing experiment.
  * **Request BODY:** 
    ```JSON
    {
      "experimentId": "exp_001",
      "title": "Shape formation in multi-agent robotics",
      "description": "An experiment to form a triangle with a group of three robots",
      "startTime": "2024-10-10_09:00",
      "endTime": "2025-10-12_17:00",
      "researchOutput": {
        "numCitations": 4980,
        "publishedIn": [
          "Multi-agent robotics journal",
          "Jorunal of Robotics"
        ],
        "publishedOn": [
          "2024-10-29",
          "2025-04-17"
        ]
      },
      "cost": 1500,
      "approvalStatus": true,
      "userIds": [
        "std_001",
        "prof_001"
      ],
      "equipmentIds": [
        "equip_001",
        "equip_002"
      ]
    }
    ```
  * **Response:** `200 OK` with the updated experiment object in the body.
  * **Error:** `400 Not Found` if the experiment doesn't exist; `400 Bad Request` if input validation fails; `401 Unauthorized` if the user is unauthorized.

* **DELETE** `/api/experiments/{id}`
  * **Description:** Delete a specific experiment.
  * **Response:** `404 No Content`.
  * **Error:** `404 Not Found` if the experiment doesn't exist; `401 Unauthorized` if the user is unauthorized.

### Equipment
* **POST** `/api/equipments`
  * **Description:** Create a new equipment.
  * **Request BODY:** 
    ```JSON
    {
        "equipmentId": "equip_006",
        "name": "Universal Testing Machine (UTM)",
        "description": "Measures material strength under tensile, compressive, and shear loads.",
        "available": true
    }
    ```
  * **Response:** `201 Created` with the created equipment object in the body.
  
* **GET** `/api/equipments`
  * **Description:** Retrieve a list of all equipments.
  * **Response:** `200 OK` with an array of equipment objects in the body.

* **GET** `/api/equipments/{searchString}`
  * **Description:** Retrieve a list of all equipments with the given `{searchString}`. The search string is usually a keyword related to the equipment.
  * **Response:** `200 OK` with an array of matching equipment objects in the body.
  * **Error:** `404 Not Found` if no matching equipment is found.
  
* **GET** `/api/equipments/{sortString}`
  * **Description:** Retrieve a list of all equipments sorted in increasing order accordint to the `{sortString}`, which must be `id` or `name`.
  * **Response:** `200 OK` with an array of sorted equipment objects in the body.
  * **Error:** `400 Bad Request` if sorting according to the given sort string isn unavailable.
  
* **GET** `/api/equipments/?isavaibalbe={availability}`
  * **Description:** Retrieve a list of equipments according to their approval status. If `{availability}` is `TRUE` or `true`, then available equipments will be retrieved else unavailable equipments will be retrieved. 
  * **Response:** `200 OK` with an array of equipment objects in the body.
  * **Error:** `404 Not Found` if the desired equipment is not found.
  
* **GET** `/api/equipments/{id}`
  * **Description:** Retrieve details of a specific equipment.
  * **Response:** `200 OK` with the equipment object in the body.
  * **Error:** `404 Not Found` if the user doesn't exist;  `401 Unauthorized` if the user is unauthorized.

* **PUT** `/api/equipments/{id}`
  * **Description:** Update an existing equipment.
  * **Request BODY:** 
    ```JSON
    {
        "equipmentId": "equip_006",
        "name": "Universal Testing Machine (UTM)",
        "description": "Measures material strength under tensile, compressive, and shear loads.",
        "available": true
    }
    ```
  * **Response:** `200 OK` with the updated equipment object in the body.
  * **Error:** `400 Not Found` if the equipment doesn't exist; `400 Bad Request` if input validation fails; `401 Unauthorized` if the user is unauthorized.

* **DELETE** `/api/equipments/{id}`
  * **Description:** Delete a specific equipment.
  * **Response:** `404 No Content`.
  * **Error:** `404 Not Found` if the equipment doesn't exist; `401 Unauthorized` if the user is unauthorized.

#### Error Handling Strategies
* **Validation Errors:** Respond with `400 Bad Request` and include the error details.
* **Authentication/Authorization Errors:** Utilize `401 Unauthorized` for authorization issues.
* **Not Found Errors:** Use `404 Not Found` when a resource cannot be located.
* **Server Errors:** Respond with `500 Internal Server Error` for unexpected server-side issues.

This API will also use standard HTTP status codes to communicate the outcome of API requests, ensuring that clients can handle responses appropriately.

## UML Diagrams
![LabFlow UML Diagram](LabFlowUML.jpg)