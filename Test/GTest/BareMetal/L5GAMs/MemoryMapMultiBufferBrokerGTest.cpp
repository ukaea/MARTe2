/**
 * @file MemoryMapMultiBufferBrokerGTest.cpp
 * @brief Source file for class MemoryMapMultiBufferBrokerGTest
 * @date 04/05/2018
 * @author Giuseppe Ferro
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
 * the class MemoryMapMultiBufferBrokerGTest (public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/
#include <limits.h>
#include "gtest/gtest.h"

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/
#include "MemoryMapMultiBufferBrokerTest.h"


/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/


TEST(MemoryMapMultiBufferBrokerGTest,TestConstructor) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestConstructor());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestInit) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestInit());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestInit1) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestInit1());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestCopyInputs) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestCopyInputs());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestCopyInputs_N_Times_More_Samples_Than_Buffers) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestCopyInputs_N_Times_More_Samples_Than_Buffers());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestCopyInputs_Equal_Samples_And_Buffers) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestCopyInputs_Equal_Samples_And_Buffers());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestCopyInputs_Equal_Samples_And_Buffers_NTimes) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestCopyInputs_Equal_Samples_And_Buffers_NTimes());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestCopyInputs_NoSamples) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestCopyInputs_NoSamples());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestCopyInputs_MoreBuffersThanSamples) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestCopyInputs_MoreBuffersThanSamples());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestCopyOutputs) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestCopyOutputs());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestCopyOutputs_NoSamples) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestCopyOutputs_NoSamples());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestCopyOutputs_N_Times_More_Samples_Than_Buffers) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestCopyOutputs_N_Times_More_Samples_Than_Buffers());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestCopyOutputs_Equal_Samples_And_Buffers) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestCopyOutputs_Equal_Samples_And_Buffers());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestCopyOutputs_Equal_Samples_And_Buffers_NTimes) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestCopyOutputs_Equal_Samples_And_Buffers_NTimes());
}

TEST(MemoryMapMultiBufferBrokerGTest,TestCopyOutputs_MoreBuffersThanSamples) {
    MemoryMapMultiBufferBrokerTest test;
    ASSERT_TRUE(test.TestCopyOutputs_MoreBuffersThanSamples());
}
