/**
 * @file ConfigurationLoaderHashCRCGTest.cpp
 * @brief Source file for class ConfigurationLoaderHashCRCGTest
 * @date 16/02/2022
 * @author Andre Neto
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

 * @details This source file contains the definition of all the methods for
 * the class ConfigurationLoaderHashCRCGTest (public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/
#include "MARTe2UTest.h"

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/
#include "ConfigurationLoaderHashCRCTest.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/
TEST(BareMetal_L6App_ConfigurationLoaderHashCRCGTest,TestConstructor) {
    ConfigurationLoaderHashCRCTest test;
    ASSERT_TRUE(test.TestConstructor());
}

TEST(BareMetal_L6App_ConfigurationLoaderHashCRCGTest,TestGetSeed) {
    ConfigurationLoaderHashCRCTest test;
    ASSERT_TRUE(test.TestGetSeed());
}

TEST(BareMetal_L6App_ConfigurationLoaderHashCRCGTest,TestComputeHash) {
    ConfigurationLoaderHashCRCTest test;
    ASSERT_TRUE(test.TestComputeHash());
}

TEST(BareMetal_L6App_ConfigurationLoaderHashCRCGTest,TestInitialise) {
    ConfigurationLoaderHashCRCTest test;
    ASSERT_TRUE(test.TestInitialise());
}

TEST(BareMetal_L6App_ConfigurationLoaderHashCRCGTest,TestInitialise_NoKey) {
    ConfigurationLoaderHashCRCTest test;
    ASSERT_TRUE(test.TestInitialise_NoKey());
}
