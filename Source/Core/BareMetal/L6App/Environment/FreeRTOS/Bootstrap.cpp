/**
 * @file Bootstrap.cpp
 * @brief Source file for class Bootstrap
 * @date 04/04/2018
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
 * the class Bootstrap (public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"


/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/
#include "AdvancedErrorManagement.h"
#include "Bootstrap.h"
#include "ConfigurationDatabase.h"
#include "StructuredDataI.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/
extern void MARTe2HardwareInitialise();

extern "C" {
    SemaphoreHandle_t hwInitSem;
    void HardwarePrintf(const char8 * const msg);

    /**
    *
    */
    void PreLoader(void (*_loader)(void*)) {
        if(xSemaphoreTake(hwInitSem, portMAX_DELAY) == pdTRUE) {
            int (*loader) (MARTe::int32 argc, MARTe::char8** argv) = (int (*) (MARTe::int32 argc, MARTe::char8** argv))_loader;
            loader(0, NULL);
        }

    }
}

namespace MARTe {

//Note that some methods are implemented in FileSystem/L6App/Environment/Linux/Bootstrap.cpp

Bootstrap::Bootstrap() {

}

Bootstrap::~Bootstrap() {

}

void Bootstrap::Printf(const char8 * const msg) {
    //TODO HARDWAREPRINTF
    printf(msg);
    printf("\r\n");
}

ErrorManagement::ErrorType Bootstrap::ReadParameters(int32 argc, char8 **argv, StructuredDataI &loaderParameters) {
    //TODO finishe me
    ErrorManagement::ErrorType ret;
    ret.parametersError = !loaderParameters.Write("Loader", "RealTimeLoader");
    if (ret) {
        //ret.parametersError = !loaderParameters.Write("FirstState", "State1");
        ret.parametersError = !loaderParameters.Write("MessageDestination", "StateMachine");
        if (ret) {
            ret.parametersError = !loaderParameters.Write("MessageFunction", "START");
        }
    }
    if (ret) {
        ret.parametersError = !loaderParameters.Write("Parser", "cdb");
    }
    return ret;
}

void Bootstrap::Main(int (*loader)(int32 argc, char8** argv), int32 argc, char8** argv) {
    //TODO: Check if is acceptable this kind of approach
    hwInitSem = xSemaphoreCreateCounting(1, 0);

    if(hwInitSem != NULL) {
        MARTe2HardwareInitialise(); //Handle to initialise hardware
        BaseType_t xReturned;
        TaskHandle_t xHandle = NULL;

        //TODO CHECK Priority and stack size as parameter
        /* Create the task, storing the handle. */
        xReturned = xTaskCreate(
                        PreLoader,                     /* Function that implements the task. */
                        "Main",                             /* Text name for the task. */
                        4 * THREADS_DEFAULT_STACKSIZE,      /* Stack size in words, not bytes. */
                        (void*)loader,                      /* Parameter passed into the task. */
                        tskIDLE_PRIORITY,                   /* Priority at which the task is created. */
                        &xHandle );                         /* Used to pass out the created task's handle. */

        vTaskStartScheduler(); //Start FreeRTOS Scheduler
    }
    else {
        printf("Failure during hardware initialisation semaphore\r\n");
    }

    for(;;); //We should never reach here
}

}
