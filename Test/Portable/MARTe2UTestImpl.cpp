#include "AdvancedErrorManagement.h"
#include "CompilerTypes.h"
#include "MARTe2UTestMacros.h"

using namespace MARTe;

TestMarkerInterface::TestMarkerInterface(const char* suiteName, const char* testName) {
	this->testName = (char*)testName;
	this->suiteName = (char*)suiteName;
}

TestFramework::TestFramework() {
	statsPassedTests = 0;
	statsFailedTests = 0;
	statsTotalTests = 0;
}

void TestFramework::Add(TestMarkerInterface* miInstance) {
	testHolderDataStructure.Add(miInstance);
	statsTotalTests++;
}

void TestFramework::Run() {
	TestMarkerInterface* currentTest = NULL;
	uint32 dsSize = testHolderDataStructure.GetSize();
	for(uint32 i = 0; i < dsSize; i++) {
		currentTest = testHolderDataStructure[i];
		REPORT_ERROR_STATIC(ErrorManagement::Information, "Running test %d/%d |%s|.|%s|", (i+1), statsTotalTests, currentTest->suiteName, currentTest->testName);
		currentTest->Test();
		if(currentTest->testResult) {
			passedHolderDataStructure.Add(currentTest);
			statsPassedTests++;
		}
		else {
			failedHolderDataStructure.Add(currentTest);
			statsFailedTests++;
		}
	}
}

void TestFramework::Clean() {
	failedHolderDataStructure.Clean();
	passedHolderDataStructure.Clean();
	testHolderDataStructure.Clean();

    statsPassedTests = 0;
	statsFailedTests = 0;
	statsTotalTests = 0;
}

void TestFramework::PrintResults() {
	MARTe::uint32 failedSize = failedHolderDataStructure.GetSize();

	for(MARTe::uint32 i = 0; i < failedSize; i++) {
		REPORT_ERROR_STATIC(ErrorManagement::FatalError, "Failed |%s|.|%s|", failedHolderDataStructure[i]->suiteName, failedHolderDataStructure[i]->testName);
	}
	
	REPORT_ERROR_STATIC(ErrorManagement::Information, "Stats:\r\n----------------------");
	REPORT_ERROR_STATIC(ErrorManagement::Information, "Total/Passed/Failed = %d/%d/%d", statsTotalTests, statsPassedTests, statsFailedTests);
}

TestFramework& TestFramework::Instance() {
	static TestFramework instance;
	return instance;
}

Bootstrapper::Bootstrapper(TestMarkerInterface* inFun) {
	TestFramework::Instance().Add(inFun);
}