/**
 * @file QueueingMessageFilterTest.cpp
 * @brief Source file for class QueueingMessageFilterTest
 * @date 9/09/2016
 * @author Andre Nneto
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
 * the class QueueingMessageFilterTest (public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/
#include "QueueingMessageFilterTest.h"

#include "CLASSMETHODREGISTER.h"
#include "ClassWithCallableMethods.h"
#include "ConfigurationDatabase.h"
#include "MessageI.h"
#include "ObjectRegistryDatabase.h"
#include "ObjectWithMessages.h"
#include "ReplyMessageCatcherMessageFilter.h"
#include "Sleep.h"
#include "Threads.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/
bool QueueingMessageFilterTest::TestDefaultConstructor() {
    using namespace MARTe;
    QueueingMessageFilter filter;
    return filter.IsPermanentFilter();
}

bool QueueingMessageFilterTest::TestConsumeMessage() {
    using namespace MARTe;
    ReferenceT<Message> msg(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    QueueingMessageFilter filter;

    bool ok = true;
    ErrorManagement::ErrorType err = filter.ConsumeMessage(msg);
    ok &= err.ErrorsCleared();
    ReferenceT<Message> msg2;
    filter.GetMessage(msg2);
    ok &= (msg == msg2);
    return ok;
}


bool QueueingMessageFilterTest::TestIsPermanentFilter() {
    using namespace MARTe;
    QueueingMessageFilter filter;
    return filter.IsPermanentFilter();
}

bool QueueingMessageFilterTest::TestGetMessage() {
    using namespace MARTe;
    ReferenceT<Message> msg(GlobalObjectsDatabase::Instance()->GetStandardHeap());
    QueueingMessageFilter filter;

    bool ok = true;
    ErrorManagement::ErrorType err = filter.ConsumeMessage(msg);
    ok &= err.ErrorsCleared();
    ReferenceT<Message> msg2;
    err = filter.GetMessage(msg2);
    ok &= err.ErrorsCleared();
    ok &= (msg == msg2);
    return ok;
}

