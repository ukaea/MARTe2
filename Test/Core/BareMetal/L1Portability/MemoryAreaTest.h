/**
 * @file MemoryAreaTest.h
 * @brief Header file for class MemoryAreaTest
 * @date 10/03/2016
 * @author Giuseppe Ferrò
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

 * @details This header file contains the declaration of the class MemoryAreaTest
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef MEMORYAREATEST_H_
#define MEMORYAREATEST_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/
#include "MemoryArea.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

using namespace MARTe;

/**
 * @brief Tests all the MemoryArea functions
 */
class MemoryAreaTest {

public:

    /**
     * @brief Tests the constructor.
     */
    bool TestConstructor();

    /**
     * @brief Tests if the function allocates the memory size passed in input.
     */
    bool TestAdd_OnlySize();

    /**
     * @brief Tests if the function allocates and copies the memory passed in input.
     */
    bool TestAdd_Element();

    /**
     * @brief Tests if the function frees the memory.
     */
    bool TestFree();

    /**
     * @brief Tests if the function returns a pointer to the begin of the memory area.
     */
    bool TestGetMemoryStart();

    /**
     * brief Tests if the function returns the size of the memory area.
     */
    bool TestGetMemorySize(uint32 size);

    /**
     * @brief Tests if the function returns the pointer to the desired position.
     */
    bool TestGetPointer();

    /**
     * @brief Tests if the function initialises the memory area correctly.
     */
    bool TestInitMemory();

    /**
     * @brief Tests if the function fails if the memory area is not empty.
     */
    bool TestInitMemoryFalse_AlreadyInit();

};

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* TEST_CORE_BAREMETAL_L1PORTABILITY_MEMORYAREATEST_H_ */

