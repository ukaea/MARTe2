/**
 * @file MultiClientService.h
 * @brief Header file for class MultiClientService
 * @date 05/09/2016
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

 * @details This header file contains the declaration of the class MultiClientService
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef MULTICLIENTSERVICE_H_
#define MULTICLIENTSERVICE_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "MultiThreadService.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {
/**
 *
 */
class MultiClientService: public MultiThreadService {

public:

    template<typename className>
    MultiClientService(EmbeddedServiceMethodBinderT<className> &binder);

    /**
     *
     */
    virtual ~MultiClientService() {
    }

    /**
     * TODO
     * same as object interface
     */
    virtual bool Initialise(StructuredDataI &data);

    /**
     * allows to add threads to the maxNumberOfThreads
     * called by Start
     */
    ErrorManagement::ErrorType AddThread();

    /**
     *
     */
    inline bool MoreThanEnoughThreads();

    virtual ErrorManagement::ErrorType Start();
protected:
    /**
     *
     */
    //inline bool TooManyThreads();
    /// either the available working threads or the maximum
    uint32 maxNumberOfThreads;

    uint32 minNumberOfThreads;

    /**
     *
     */
    ReferenceContainer threadPool;
};
}

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

namespace MARTe {

bool MultiClientService::MoreThanEnoughThreads() {
    return (threadPool.Size() > minNumberOfThreads);
}

template<typename className>
MultiClientService::MultiClientService(EmbeddedServiceMethodBinderT<className> &binder) :
        MultiThreadService(binder) {
    minNumberOfThreads = 0u;
    maxNumberOfThreads = 1u;
}

}
#endif /* MULTICLIENTSERVICE_H_ */

