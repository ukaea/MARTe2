/**
 * @file PseudoCodeFunctionsTest.h
 * @brief Header file for class PseudoCodeFunctionsTest
 * @date 06/05/2020
 * @author Didac Magrinya
 *
 * @copyright Copyright 2015 F4E | European Joint Undertaking for ITER and
 * the Development of Fusion Energy ('Fusion for Energy').
 * Licensed under the EUPL, Version 1.1 or - as soon they will be approved
 * by the European Commission - subsequent versions of the EUPL (the "Licence")
 * You may not use this work except in compliance with the Licence.
 * You may obtain a copy of the Licence at: http://ec.europa.eu/idabc/eupl
 *
 * @warning Unless required by applicable law or agreed to in writing, 
 * software distributed under the Licence is distributed on an "AS IS"
 * basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the Licence permissions and limitations under the Licence.

 * @details This header file contains the declaration of the class
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef PSEUDOCODEFUNCTIONSTEST_H_
#define PSEUDOCODEFUNCTIONSTEST_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "PseudoCodeFunctions.h"
#include "PseudoCode.h"
#include "ConfigurationDatabase.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

using namespace MARTe;

/**
 * @brief Tests all the PseudoCodeFunctions functions.
 */
class PseudoCodeFunctionsTest {

public:

    /**
     * @brief Tests the default constructor.
     */
    bool TestDefaultConstructor();

    /**
     * @brief Tests types of registered functionRecords.
     */
    bool TestFunctionRecordTypes(CCString functionName, uint8 numberOfInputs, uint8 numberOfOutputs, StreamString &expectedFunctionTypes);
    bool TestFunctionRecordTypes(CCString functionName, uint8 numberOfInputs, uint8 numberOfOutputs);

    void AddFunctionsWithOnlyInputs(uint8 numberOfFunctions, StreamString typeName);

    /**
     * @brief Tests TryConsume.
     */
    bool TestTryConsume(PseudoCode::FunctionRecord &functionRecordUT, CCString inputName, StaticStack<TypeDescriptor,32> &typeStack, bool matchOutput, bool expectedRet, PseudoCode::DataMemoryAddress initialDataStackSize, PseudoCode::DataMemoryAddress expectedDataStackSize);

private:
    /**
     * @brief Checks if types provided are within types lists.
     */
    bool FindTypesInCdb(CCString &foundIndex, Vector<TypeDescriptor> &inputTypes, Vector<TypeDescriptor> &outputTypes, ConfigurationDatabase &FunctionTypesCdb);

    ConfigurationDatabase expectedFunctionTypesCdb;
};


void MockFunction(PseudoCode::Context &context);

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* PSEUDOCODEFUNCTIONSTEST_H_ */

