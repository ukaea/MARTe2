/**
 * @file DoubleBufferedStream.cpp
 * @brief Source file for class DoubleBufferedStream
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
 * the class DoubleBufferedStream (public, protected, and private). Be aware that some 
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "DoubleBufferedStream.h"
#include "ErrorManagement.h"
#include "StringHelper.h"
/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

namespace MARTe {

DoubleBufferedStream::DoubleBufferedStream() :
        BufferedStream(),
        readBuffer(this),
        writeBuffer(this) {
    timeout = TTDefault;
}

DoubleBufferedStream::DoubleBufferedStream(const TimeoutType &msecTimeout) :
        BufferedStream(),
        readBuffer(this, msecTimeout),
        writeBuffer(this, msecTimeout) {
    timeout = msecTimeout;
}

DoubleBufferedStream::~DoubleBufferedStream() {

    if (!writeBuffer.Flush()) {
        //TODO
    }
}

bool DoubleBufferedStream::SetBufferSize(uint32 readBufferSize,
                                         uint32 writeBufferSize) {

    bool ret = true;
    // minimum size = 8
    if (readBufferSize < 8u) {
        readBufferSize = 8u;
    }
    if (writeBufferSize < 8u) {
        writeBufferSize = 8u;
    }

    // do not allocate if not necessary
    if (!CanRead()) {
        readBufferSize = 0u;
    }
    if (!CanWrite()) {
        writeBufferSize = 0u;
    }

    // dump any data in the write Queue
    if (Flush()) {

        // adjust readBufferSize
        if (!readBuffer.SetBufferSize(readBufferSize)) {
            //TODO
        }

        // adjust writeBufferSize
        if (!writeBuffer.SetBufferSize(writeBufferSize)) {
            //TODO
        }
    }
    else {
        ret = false;
    }

    return ret;
}
/*lint -e{1536} [MISRA C++ Rule 9-3-1], [MISRA C++ Rule 9-3-2]. Justification: BufferedStream must have the access to the final buffers.*/
IOBuffer * DoubleBufferedStream::GetInputBuffer() {
    return &readBuffer;
}

/*lint -e{1536} [MISRA C++ Rule 9-3-1], [MISRA C++ Rule 9-3-2]. Justification: BufferedStream must have the access to the final buffers.*/
IOBuffer * DoubleBufferedStream::GetOutputBuffer() {

    return &writeBuffer;
}

bool DoubleBufferedStream::Read(char8 * const bufferIn,
                                uint32 & size) {

    bool ret = true;

    // check whether we have a buffer
    if (readBuffer.BufferSize() > 0u) {

        // read from buffer first
        uint32 toRead = size;

        // try once
        if (!readBuffer.Read(&bufferIn[0], size)) {
            //TODO
        }

        if (size != toRead) {
            // partial only so continue

            // adjust toRead
            toRead -= size;

            // decide whether to use the buffer again or just to read directly
            if ((toRead * 4u) < readBuffer.MaxUsableAmount()) {
                if (!readBuffer.Refill()) {
                    ret = false;
                }

                else {

                    if (!readBuffer.Read(&bufferIn[size], toRead)) {
                        //TODO
                    }
                    size += toRead;

                    // should have completed
                    // as our buffer is at least 4x the need
                }

            }
            else {
                // if needed read directly from stream
                if (!UnbufferedRead(&bufferIn[size], toRead, timeout)) {
                    ret = false;
                }
                else {
                    size += toRead;
                }
            }
        }
    }

    // if needed read directly from stream
    return (ret) ? (UnbufferedRead(&bufferIn[0], size, timeout)) : (false);
}

/** Write data from a buffer to the stream. As much as size byte are written, actual size
 is returned in size. msecTimeout is how much the operation should last.
 timeout behaviour is class specific. I.E. sockets with blocking activated wait forever
 when noWait is used .... */
bool DoubleBufferedStream::Write(const char8* const bufferIn,
                                 uint32 & size) {

    bool ret = true;
    // buffering active?
    if (writeBuffer.BufferSize() > 0u) {
        // separate input and output size

        uint32 toWrite = size;
        // check available buffer size versus write size
        // if size is comparable to buffer size there
        // is no reason to use the buffering mechanism
        if (writeBuffer.MaxUsableAmount() > (4u * size)) {

            // try writing the buffer
            if (!writeBuffer.Write(&bufferIn[0], size)) {
                //TODO
            }

            // all done! space available!
            if (size != toWrite) {
                // make space
                if (!writeBuffer.Flush()) {
                    ret = false;
                }
                else {
                    toWrite -= size;
                    uint32 leftToWrite = toWrite;

                    // try writing the buffer
                    if (!writeBuffer.Write(&bufferIn[size], leftToWrite)) {
                        //TODO
                    }

                    size += leftToWrite;

                    // should have been able to fill in it!!!
                    if (leftToWrite != toWrite) {
                        ret = false;
                    }
                }
            }
        }
        else {
            // write the buffer so far
            if (!writeBuffer.Flush()) {
                ret = false;
            }
        }

    }
    return (ret) ? (UnbufferedWrite(&bufferIn[0], size, timeout)) : (false);

}

/** The size of the stream */
uint64 DoubleBufferedStream::Size() {
    return UnbufferedSize();
}

/** Moves within the file to an absolute location */
bool DoubleBufferedStream::Seek(const uint64 pos) {
    return UnbufferedSeek(pos);
}

/** Moves within the file relative to current location */
bool DoubleBufferedStream::RelativeSeek(const int32 deltaPos) {
    return UnbufferedRelativeSeek(deltaPos);
}

/** Returns current position */
uint64 DoubleBufferedStream::Position() {
    return UnbufferedPosition();
}

/** Clip the stream size to a specified point */
bool DoubleBufferedStream::SetSize(const uint64 size) {
    return UnbufferedSetSize(size);
}

}

