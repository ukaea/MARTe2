/**
 * @file StreamMemoryReference.cpp
 * @brief Source file for class StreamMemoryReference
 * @date 06/10/2015
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

 * @details This source file contains the definition of all the methods for
 * the class StreamMemoryReference (public, protected, and private). Be aware that some 
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "StreamMemoryReference.h"
#include "AdvancedErrorManagement.h"
/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

namespace MARTe {

StreamMemoryReference::StreamMemoryReference() :
        BufferedStream(),
        buffer() {

}

StreamMemoryReference::StreamMemoryReference(char8 * const bufferIn,
                                             const uint32 bufferSize) :
        BufferedStream() {
    if (this->buffer.SetBufferReferencedMemory(bufferIn, bufferSize, 0u)) {
        //TODO
    }
}

StreamMemoryReference::StreamMemoryReference(const char8 * const bufferIn,
                                             const uint32 bufferSize) :
        BufferedStream() {
    if (!this->buffer.SetBufferReadOnlyReferencedMemory(bufferIn, bufferSize, 0u)) {
        //TODO
    }
    if (!this->buffer.SetUsedSize(bufferSize)) {
        //TODO
    }
}

StreamMemoryReference::~StreamMemoryReference() {
}

StreamMemoryReference::operator AnyType() {
    AnyType at(Buffer());
    return at;
}

/*lint -e{1536} [MISRA C++ Rule 9-3-1], [MISRA C++ Rule 9-3-2]. Justification: BufferedStream must have the access to the final buffers.*/
IOBuffer *StreamMemoryReference::GetInputBuffer() {
    return &buffer;
}

/*lint -e{1536} [MISRA C++ Rule 9-3-1], [MISRA C++ Rule 9-3-2]. Justification: BufferedStream must have the access to the final buffers.*/
IOBuffer *StreamMemoryReference::GetOutputBuffer() {
    return &buffer;
}

bool StreamMemoryReference::Read(char8* const bufferIn,
                                 uint32 & size) {
    return this->buffer.Read(&bufferIn[0], size);
}

bool StreamMemoryReference::Write(const char8* const bufferIn,
                                  uint32 & size) {
    return this->buffer.Write(&bufferIn[0], size);

}

bool StreamMemoryReference::CanWrite() const {
    bool cond1 = (buffer.BufferReference() != NULL);
    bool cond2 = buffer.CanWrite();
    return (cond1) && (cond2);
};

bool StreamMemoryReference::CanRead() const {
    return (buffer.Buffer() != NULL);
};

/** The size of the stream */
uint64 StreamMemoryReference::Size() {
    return buffer.UsedSize();
}

bool StreamMemoryReference::SetSize(const uint64 size) {

    if (!buffer.SetUsedSize(static_cast<uint32>(size))) {
        //TODO
    }
    return true;
}

bool StreamMemoryReference::Seek(const uint64 pos) {
    uint32 usedSize = buffer.UsedSize();
    bool ret = true;
    if (pos > usedSize) {
//REPORT_ERROR_PARAMETERS(ParametersError,"pos=%i out of range=[0-%i] , moving to end of stream",pos,usedSize)
        if (!buffer.Seek(usedSize)) {
            //TODO
        }
        ret = false;
    }

    return (ret) ? (buffer.Seek(static_cast<uint32>(pos))) : (false);
}

/** Moves within the file relative to current location */
bool StreamMemoryReference::RelativeSeek(const int32 deltaPos) {
    return buffer.RelativeSeek(deltaPos);
}

/** Returns current position */
uint64 StreamMemoryReference::Position() {
    return buffer.Position();
}

/** can you move the pointer */
bool StreamMemoryReference::CanSeek() const {
    return true;
}

/*lint -e{715} [MISRA C++ Rule 0-1-11]. Justification: This implementation does not requires input arguments.*/
bool StreamMemoryReference::UnbufferedWrite(const char8 * const bufferIn,
                                            uint32 & size,
                                            const TimeoutType &msecTimeout) {
    return false;
}

/*lint -e{715} [MISRA C++ Rule 0-1-11]. Justification: This implementation does not requires input arguments.*/
bool StreamMemoryReference::UnbufferedRead(char8 * const bufferIn,
                                           uint32 & size,
                                           const TimeoutType &msecTimeout) {
    return false;
}

uint64 StreamMemoryReference::UnbufferedSize() {
    return 0u;
}

/*lint -e{715} [MISRA C++ Rule 0-1-11]. Justification: This implementation does not requires input arguments.*/
bool StreamMemoryReference::UnbufferedSeek(const uint64 pos) {
    return false;
}

/*lint -e{715} [MISRA C++ Rule 0-1-11]. Justification: This implementation does not requires input arguments.*/
bool StreamMemoryReference::UnbufferedRelativeSeek(const int32 deltaPos) {
    return false;
}

uint64 StreamMemoryReference::UnbufferedPosition() {
    return 0u;
}

/*lint -e{715} [MISRA C++ Rule 0-1-11]. Justification: This implementation does not requires input arguments.*/
bool StreamMemoryReference::UnbufferedSetSize(const uint64 size) {
    return false;
}

}

