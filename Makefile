ALLFILES = Administrator.cpp Administrator.h Budget.cpp Budget.h Equipment.cpp equipmentFunctions.cpp equipmentFunctions.h Equipment.h Experiment.cpp experimentFunctions.cpp experimentFunctions.h Experiment.h FileHandlingTemplate.cpp FileHandlingTemplate.h FunctionsTestTemplate.cpp GenericUserAPI.cpp GenericUserAPI.h Lab.cpp LabFlowAPI.cpp labFunctions.cpp labFunctions.h Lab.h Professor.cpp Professor.h ResearchOutput.cpp ResearchOutput.h Student.cpp Student.h toLowerHelper.cpp toLowerHelper.h toLowerHelperTest.cpp User.cpp User.h

# All object files
ALLOBJ = LabFlowAPI.o Professor.o Administrator.o User.o Student.o Lab.o Equipment.o Experiment.o Budget.o ResearchOutput.o GenericUserAPI.o labFunctions.o equipmentFunctions.o experimentFunctions.o toLowerHelper.o

# All class header files
CLSHEADERS = Professor.h Administrator.h Student.h Lab.h Equipment.h Experiment.h

# All functions header files
FCTHEADERS =  labFunctions.h experimentFunctions.h equipmentFunctions.h

# All header files
ALLHEADERS = LabFlowAPI.cpp $(CLSHEADERS) $(FCTHEADERS) GenericUserAPI.h FileHandlingTemplate.h 

# All resource header files
RSCHEADERS = $(CLSHEADERS) resourceMaps.h

# All unit testing executables
ALLTESTS = equipmentFunctionsTest experimentFunctionsTest labFunctionsTest toLowerHelperTest genericUserAPITest

all: LabFlowAPI static-analysis 

LabFlowAPI: $(ALLOBJ) resourceMaps.h
	g++ -lpthread $(ALLOBJ) resourceMaps.h -o LabFlowAPI

LabFlowAPI.o: $(ALLHEADERS)
	g++ -Wall -c LabFlowAPI.cpp 

User.o: User.cpp User.h 
	g++ -Wall -c User.cpp

Professor.o: Professor.cpp User.h 
	g++ -Wall -c Professor.cpp 

Student.o: Student.cpp User.h 
	g++ -Wall -c Student.cpp 

Administrator.o: Administrator.cpp User.h Lab.h
	g++ -Wall -c Administrator.cpp 

Lab.o: Lab.cpp Budget.h
	g++ -Wall -c Lab.cpp

Equipment.o: Equipment.cpp
	g++ -Wall -c Equipment.cpp

Experiment.o: Experiment.cpp ResearchOutput.h
	g++ -Wall -c Experiment.cpp

Budget.o: Budget.cpp Budget.h 
	g++ -Wall -c Budget.cpp

ResearchOutput.o: ResearchOutput.cpp ResearchOutput.h 
	g++ -Wall -c ResearchOutput.cpp

labFunctions.o: labFunctions.cpp labFunctions.h toLowerHelper.h Administrator.h
	g++ -Wall -c labFunctions.cpp

experimentFunctions.o: experimentFunctions.cpp experimentFunctions.h toLowerHelper.h
	g++ -Wall -c experimentFunctions.cpp

equipmentFunctions.o: equipmentFunctions.cpp equipmentFunctions.h 
	g++ -Wall -c equipmentFunctions.cpp

toLowerHelper.o: toLowerHelper.cpp toLowerHelper.h 
	g++ -Wall -c toLowerHelper.cpp

GenericUserAPI.o: GenericUserAPI.cpp GenericUserAPI.h Professor.h Administrator.h Student.h Lab.h labFunctions.h
	g++ -Wall -c GenericUserAPI.cpp 


# Unit testings
equipmentFunctionsTest: equipmentFunctionsTest.cpp equipmentFunctions.h
	g++ -lpthread equipmentFunctionsTest.cpp equipmentFunctions.h -o equipmentFunctionsTest 

experimentFunctionsTest: experimentFunctionsTest.cpp experimentFunctions.h
	g++ -lpthread experimentFunctionsTest.cpp experimentFunctions.h -o experimentFunctionsTest 

labFunctionsTest: labFunctionsTest.cpp labFunctions.h
	g++ -lpthread labFunctionsTest.cpp labFunctions.h -o labFunctionsTest 

toLowerHelperTest: toLowerHelperTest.cpp toLowerHelper.h
	g++ -Wall toLowerHelperTest.cpp toLowerHelper.h -o toLowerHelperTest 

genericUserAPITest: GenericUserAPITest.cpp GenericUserAPI.h
	g++ -lpthread GenericUserAPITest.cpp GenericUserAPI.h -o genericUserAPITest

run-unit-tests: $(ALLTESTS)
	./equipmentFunctionsTest
	./experimentFunctionsTest
	./labFunctionsTest
	./toLowerHelperTest
	./genericUserAPITest

static-analysis:
	cppcheck *.cpp

docs: $(ALLFILES)
	doxygen doxyfile

clean:
	rm -f *.o LabFlowAPI $(ALLTESTS)