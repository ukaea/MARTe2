/**
 * @file MainGTest.cpp
 * @brief Source file for class MainGTest
 * @date 08/01/2015
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
 * the class MainGTest (public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "ErrorManagement.h"
#include "MARTe2UTest.h"
#include "Object.h"
#include "StreamString.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

void MainGTestErrorProcessFunction(const MARTe::ErrorManagement::ErrorInformation &errorInfo,
                                   const char * const errorDescription) {
    MARTe::StreamString errorCodeStr;
    MARTe::ErrorManagement::ErrorCodeToStream(errorInfo.header.errorType, errorCodeStr);
    printf("[%s - %s:%d]: %s\n", errorCodeStr.Buffer(), errorInfo.fileName, errorInfo.header.lineNumber, errorDescription);
}

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/
int main(int argc, char **argv) {
    SetErrorProcessFunction(&MainGTestErrorProcessFunction);
    bool ok = MARTe::UnitTest::PrepareTestEnvironment(argc, argv);
    if (ok) {
        ok = MARTe::UnitTest::Run();
    }
    MARTe::UnitTest::CleanTestEnvironment();
    return (ok ? 0 : -1);
}

