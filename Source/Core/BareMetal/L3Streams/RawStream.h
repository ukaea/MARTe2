/**
 * @file RawStream.h
 * @brief Header file for class RawStream
 * @date 05/10/2015
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

 * @details This header file contains the declaration of the class RawStream
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef RAWSTREAM_H_
#define RAWSTREAM_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/
#include "TimeoutType.h"
#include "AnyType.h"
#include "FormatDescriptor.h"
#include "IOBuffer.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {

/**
 * @brief
 * A more abstract version of Streamable. It is used to allow referring to streams at lower levels
 */
class RawStream {

public:

    /** @brief Default destructor */
    virtual ~RawStream() {
    }

    /**
     * @brief Pure virtual method. Reads data from the stream to a char8* buffer.
     * @param buffer is the buffer where datas must be copied.
     * @param size is the desired number of bytes to copy.
     * @param msecTimeout is the desired timeout.
     * @param complete is a flag.
     *
     * The behavior depends by derived classes implementation.
     *
     Reads data into buffer.
     As much as size byte are read,
     actual read size is returned in size. (unless complete = true)
     msecTimeout is how much the operation should last - no more - if not any (all) data read then return false
     timeout behaviour depends on class characteristics and sync mode.
     return false implies failure to comply with minimum requirements:
     timeout and complete and data read  != size
     timeout and data read == 0
     error in the stream  ==> no point to try again
     parameters error, for instance buffer = NULL
     */
    virtual bool UnbufferedRead(char8* buffer,
                                uint32 & size,
                                TimeoutType msecTimeout)=0;

    /**
     * @brief Pure virtual method. Writes from a const char8* buffer to the stream.
     * @param buffer contains the datas which must be copied on the stream.
     * @param size is the desired number of bytes to write.
     * @param msecTimeout is the desired timeout.
     * @param complete is a flag.
     *
     * The behavior depends by derived classes implementation.
     *
     UnbufferedWrite data from a buffer to the stream.
     As much as size byte are written,
     actual written size is returned in size.
     msecTimeout is how much the operation should last.
     timeout behaviour depends on class characteristics and sync mode.
     return false implies failure to comply with minimum requirements:
     timeout and complete and data written  != size
     timeout and data written == 0
     error in the stream ==> no point to try again
     parameters error, for instance buffer = NULL
     */
    virtual bool UnbufferedWrite(const char8* buffer,
                                 uint32 & size,
                                 TimeoutType msecTimeout) = 0;

    /**
     * @brief Pure virtual function. Defines if write operations can be performed on the stream.
     * @return return value depends from derived classes implementation. */
    virtual bool CanWrite() const =0;

    /**
     * @brief Pure virtual function. Defines if read operations can be performed on the stream.
     * @return return value depends from derived classes implementation. */
    virtual bool CanRead() const =0;

    /**
     * @brief Pure virtual method. Defines if seek operations can be performed on the stream.
     * @return return value depends on the derived classes implementation. */
    virtual bool CanSeek() const =0;

    /**
     * @brief Writes a character on the stream.
     * @param c is the character to write on the stream.
     * @return depends from derived classes implementation.
     *
     * Uses the derived class implementation of UnbufferedWrite function with one as size parameter,
     * then the function behavior depends from the derived class UnbufferedWrite function.*/
    inline bool PutC(const char8 c);

    /**
     * @brief Reads a character from the stream.
     * @param c is the character in return.
     * @return depends from derived classes implementation.
     *
     * Uses the derived class implementation of UnbufferedRead function with one as size parameter,
     * then the function behavior depends from the derived class UnbufferedRead function. */
    inline bool GetC(char8 &c);

    // SYNCHRONISATION INTERFACE

    /**
     * @brief Defines if operations could be blocking.
     * @return false. It means that a default stream has non blocking operations.
     *
     * Anyway since the method is virtual, it could be implemented differently in
     * the derived classes.
     *
     whether it can wait to complete operation
     or in absence of data or buffer space the
     operation terminates immediately
     msecTimeout is used to limit the blocking time
     when blocking is active. It is not used otherwise - unless
     complete is set in which case the operation is tried multiple
     times each after fixed interval (set as timeout/10 or 1ms min)
     This implies that class implementations of UnbufferedRead and UnbufferedWrite
     might have to involve a select call or something similar
     for classes light String blocking has no meaning.
     */
    virtual bool CanBlock()=0;

    /**
     * @brief Sets or unsets the blocking mode.
     * @param flag is a flag.
     * @return false. It means that by default a stream cannot set blocking mode.
     *
     * Anyway since this method is virtual it could be implemented differently
     * in the derived classes. */
    virtual bool SetBlocking(bool flag)=0;

    // RANDOM ACCESS INTERFACE

    /**
     * @brief Pure virtual method. The size of the stream.
     * @return the size of the stream depending on derived classes implementation.  */
    virtual uint64 Size() = 0;

    /**
     * @brief Pure virtual method. Moves within the stream to an absolute location.
     * @param pos is the desired absolute position.
     * @return return value depends on derived classes implementation. */
    virtual bool Seek(uint64 pos) = 0;

    /**
     * @brief Pure virtual method. Moves within the file relative to current location.
     * @param deltaPos is the gap from the current position.
     * @return return value depends on derived classes implementation. */
    virtual bool RelativeSeek(int32 deltaPos)=0;

    /**
     * @brief Pure virtual method. Returns current position.
     * @return the current position in the stream. */
    virtual uint64 Position() = 0;

    /**
     * @brief Pure virtual method. Clip the stream size to the desired value.
     * @param size is the desired size.
     * @return return value depends on the derived classes implementation. */
    virtual bool SetSize(uint64 size) = 0;

};

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

bool RawStream::PutC(const char8 c) {
    uint32 size = 1u;
    return UnbufferedWrite(&c, size, TTDefault);
}

bool RawStream::GetC(char8 &c) {
    uint32 size = 1u;
    return UnbufferedRead(&c, size, TTDefault);

}
}
#endif /* RAWSTREAM_H_ */

