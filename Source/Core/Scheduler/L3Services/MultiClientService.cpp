/**
 * @file MultiClientEmbeddedThread.cpp
 * @brief Source file for class MultiClientService
 * @date Sep 5, 2016
 * @author Filippo Sartori
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
 * the class MultiClientService (public, protected, and private). Be aware that some 
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include <MultiClientEmbeddedThread.h>
#include "MultiClientService.h"
#include "ReferenceT.h"

namespace MARTe {
/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

bool MultiClientService::Initialise(StructuredDataI &data) {

    ErrorManagement::ErrorType err = data.Read("MaxNumberOfThreads", maxNumberOfThreads);

    if (err.ErrorsCleared()) {
        err = data.Read("MinNumberOfThreads", minNumberOfThreads);
    }
    if (err.ErrorsCleared()) {
        err.parametersError = !data.Read("Timeout", msecTimeout);
    }
    if (err.ErrorsCleared()) {
        if (msecTimeout == 0u) {
            msecTimeout = TTInfiniteWait.GetTimeoutMSec();
        }
    }
    return err;
}

ErrorManagement::ErrorType MultiClientService::AddThread() {
    ErrorManagement::ErrorType err;
    if ((threadPool.Size() < maxNumberOfThreads) && (err.ErrorsCleared())) {
        ReferenceT<MultiClientEmbeddedThread> thread(new (NULL) MultiClientEmbeddedThread(method, *this));
        err.fatalError = !thread.IsValid();
        if (err.ErrorsCleared()) {
            thread->SetThreadNumber(threadPool.Size());
            thread->SetTimeout(msecTimeout);
            err = thread->Start();
        }
        if (err.ErrorsCleared()) {
            threadPool.Insert(thread);
        }
    }
    return err;
}

ErrorManagement::ErrorType MultiClientService::Start() {
    ErrorManagement::ErrorType err;
    err.illegalOperation = (threadPool.Size() >= minNumberOfThreads);
    uint32 n = 0u;
    while ((threadPool.Size() < minNumberOfThreads) && (err.ErrorsCleared())) {
        ReferenceT<MultiClientEmbeddedThread> thread(new (NULL) MultiClientEmbeddedThread(method, *this));
        err.fatalError = !thread.IsValid();
        if (err.ErrorsCleared()) {
            thread->SetThreadNumber(n);
            thread->SetTimeout(msecTimeout);
            err = thread->Start();
        }
        if (err.ErrorsCleared()) {
            threadPool.Insert(thread);
        }
        n++;
    }
    return err;
}

}

