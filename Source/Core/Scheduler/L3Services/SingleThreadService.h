/**
 * @file SingleThreadService.h
 * @brief Header file for class SingleThreadService
 * @date 22/08/2016
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

 * @details This header file contains the declaration of the class SingleThreadService
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef SINGLETHREADSERVICE_H_
#define SINGLETHREADSERVICE_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "EmbeddedServiceI.h"
#include "EmbeddedThread.h"
#include "ErrorType.h"
#include "Object.h"
#include "StructuredDataI.h"
#include "Threads.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {

/**
 * @brief Associates a thread to a class method.
 * @details This class allows associating a class method in the form (MARTe::ErrorManagement::ErrorType (*)(MARTe::EmbeddedServiceI::ExecutionInfo &)) to a thread context.
 * This method will be continuously called (see Start) with the stage encoded in the Information parameter. In particular this class allows to request for a "kind" Stop of the
 * embedded thread and, if this fails, for a direct killing of the thread.
 */
class SingleThreadService: public EmbeddedServiceI {

public:

    /**
     * @brief Constructor.
     * @param[in] binder contains the function to be executed by this SingleThreadService.
     * @post
     *   GetTimeout() == TTInfiniteWait &&
     *   GetThread().GetThreadId() == 0 &&
     *   GetStatus() == OffState
     */
    SingleThreadService(EmbeddedServiceMethodBinderI &binder);

    /**
     * @brief Constructor.
     * @param[in] binder contains the function to be executed by this SingleThreadService.
     * @post
     *   GetTimeout() == TTInfiniteWait &&
     *   GetThread().GetThreadId() == 0 &&
     *   GetStatus() == OffState
     */
    template<typename className>
    SingleThreadService(EmbeddedServiceMethodBinderT<className> &binder);

    /**
     * @brief Destructor.
     * @details Calls the Stop() method.
     */
    virtual ~SingleThreadService();

    /**
     * @brief Reads the Timeout from the data input.
     * @param[in] data shall contain a parameter with name "Timeout" holding the timeout in milliseconds.
     * If "Timeout=0" => Timeout = TTInfiniteWait
     */
    virtual bool Initialise(StructuredDataI &data);

    /**
     * @brief Starts the SingleThreadService.
     * @return ErrorManagement::NoError if the thread can be successfully started.
     * @pre
     *   GetStatus() == OffState && GetThread().GetThreadId() == 0
     * @post
     *   GetStatus() != OffState && GetThread().GetThreadId() > 0
     */
    virtual ErrorManagement::ErrorType Start();

    /**
     * @brief Stops the SingleThreadService.
     * @details If the thread was not running this function does nothing.
     * If the thread is running, a stop command with timeout is issued (notice that if GetTimeout() == TTInfiniteWait) the Stop() command will block forever) .
     * If the thread was being stopped (Stop() had already been called), the thread is killed.
     * @return ErrorManagement::NoError if the thread can be successfully stopped.
     * @pre
     *   GetStatus() != OffState && GetThread().GetThreadId() != 0
     * @post
     *   GetStatus() == OffState && GetThread().GetThreadId() = 0
     */
    virtual ErrorManagement::ErrorType Stop();

    /**
     * @brief Gets the current thread status.
     * @return
     *  - OffState if the thread is not running
     *  - RunningState if the thread is being executed (i.e. calling the callback function in a loop)
     *  - StartingState if the thread is starting
     *  - TimeoutStartingState if the thread has timed-out while starting
     *  - StoppingState is the thread is stopping
     *  - TimeoutStoppingState if the thread has timed-out while stopping
     *  - KillingState if the thread is being killed
     *  - TimeoutKillingState if the thread has timed-out while being killed
     */
    States GetStatus();

    /**
     * @brief Sets the maximum time to execute a state change.
     * @param[in] msecTimeout the maximum time in milliseconds to execute a state change.
     */
    void SetTimeout(TimeoutType msecTimeoutIn);

    /**
     * @brief Gets the maximum time to execute a state change.
     * @return the maximum time to execute a state change.
     */
    TimeoutType GetTimeout() const;

    /**
     * @brief Gets the embedded thread.
     * @return the embedded thread.
     */
    const EmbeddedThread &GetThread();

    /**
     * @brief Gets the thread unique number (with-in the context of a pool).
     * @return the thread unique number (with-in the context of a pool).
     */
    uint16 GetThreadNumber() const;

    /**
     * @brief Sets the thread unique number (with-in the context of a pool).
     * @param[in] numberIn the thread unique number (with-in the context of a pool).
     */
    void SetThreadNumber(uint16 threadNumberIn);

protected:
    /**
     * Maximum absolute time to execute a state change.
     * maxCommandCompletionHRT = HighResolutionTimer::Counter32 + timeoutHRT
     */
    uint32 maxCommandCompletionHRT;

    /**
     * The timeout in high resolution counts.
     */
    int32 timeoutHRT;

    /**
     * The maximum time to execute a state change.
     */
    TimeoutType msecTimeout;

    /**
     * The embedded thread.
     */
    EmbeddedThread embeddedThread;
};

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

template<typename className>
SingleThreadService::SingleThreadService(EmbeddedServiceMethodBinderT<className> &binder) :
        EmbeddedServiceI(),
        embeddedThread(binder) {
    maxCommandCompletionHRT = 0;
    timeoutHRT = -1;
    SetTimeout(TTInfiniteWait);
}

}
#endif /* SINGLETHREADSERVICE_H_ */

