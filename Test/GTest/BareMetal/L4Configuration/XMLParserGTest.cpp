/**
 * @file XMLParserGTest.cpp
 * @brief Source file for class XMLParserGTest
 * @date 10/dic/2015
 * @author pc
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
 * the class XMLParserGTest (public, protected, and private). Be aware that some 
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/


#include "XMLParserTest.h"
#include "gtest/gtest.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

TEST(XMLParserGTest,TestConstructor) {
    XMLParserTest parserTest;
    ASSERT_TRUE(parserTest.TestConstructor());
}

TEST(XMLParserGTest,TestGetGrammarInfo) {
    XMLParserTest parserTest;
    ASSERT_TRUE(parserTest.TestGetGrammarInfo());
}
TEST(XMLParserGTest,TestParseScalar) {
    XMLParserTest parserTest;
    ASSERT_TRUE(parserTest.TestParseScalar());
}

TEST(XMLParserGTest,TestParseVector) {
    XMLParserTest parserTest;
    ASSERT_TRUE(parserTest.TestParseVector());
}

TEST(XMLParserGTest,TestParseMatrix) {
    XMLParserTest parserTest;
    ASSERT_TRUE(parserTest.TestParseMatrix());
}

TEST(XMLParserGTest,TestNestedBlocks) {
    XMLParserTest parserTest;
    ASSERT_TRUE(parserTest.TestNestedBlocks());
}

TEST(XMLParserGTest,TestTypeCast_Scalar_int8) {
    XMLParserTest parserTest;
    const TypeCastTableTest<int8> table[]={
            {"<var1>(int8) 127</var1>", "var1", 127, true},
            {"<var2> (int8)-128</var2>", "var2", -128, true},
            {"<var3>(int8)0b1</var3>", "var3", 1, true},
            {"<var4>(int8)0x80</var4>", "var4", -128, true},
            {"<var5>(int8) 0xFF</var5>", "var5", -1, true},
            {"<var6>(int8) 129</var6>", "var6", 0, false},
            {0, 0, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Scalar(table));
}


TEST(XMLParserGTest,TestTypeCast_Scalar_uint8) {
    XMLParserTest parserTest;
    const TypeCastTableTest<uint8> table[]={
            {"<var1>(uint8) 127</var1>", "var1", 127, true},
            {"<var2>(uint8)255</var2>", "var2", 255, true},
            {"<var3>(uint8)0b1</var3>", "var3", 1, true},
            {"<var4>(uint8) 0xFF</var4>", "var4", 255, true},
            {"<var5>(uint8) 0x100</var5>", "var5", 0, false},
            {0, 0, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Scalar(table));
}


TEST(XMLParserGTest,TestTypeCast_Scalar_int16) {
    XMLParserTest parserTest;
    const TypeCastTableTest<int16> table[]={
            {"<var1>(int16) 32767</var1>", "var1", 32767, true},
            {"<var2> (int16)-32768</var2>", "var2", -32768, true},
            {"<var3>(int16)0b1</var3>", "var3", 1, true},
            {"<var4>(int16)0x8000</var4>", "var4", -32768, true},
            {"<var5>(int16) 0xFFFF</var5>", "var5", -1, true},
            {"<var6>(int16) 32768</var6>", "var6", 0, false},
            {0, 0, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Scalar(table));
}


TEST(XMLParserGTest,TestTypeCast_Scalar_uint16) {
    XMLParserTest parserTest;
    const TypeCastTableTest<uint16> table[]={
            {"<var1>(uint16) 32767</var1>", "var1", 32767, true},
            {"<var2>(uint16)65535</var2>", "var2", 65535, true},
            {"<var3>(uint16)0b1</var3>", "var3", 1, true},
            {"<var4>(uint16) 0xFFFF</var4>", "var4", 65535, true},
            {"<var4>(uint16) 0x10000</var4>", "var4", 0, false},
            {0, 0, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Scalar(table));
}




TEST(XMLParserGTest,TestTypeCast_Scalar_int32) {
    XMLParserTest parserTest;
    const TypeCastTableTest<int32> table[]={
            {"<var1>(int32) 2147483647</var1>", "var1", 2147483647, true},
            {"<var2>(int32)-2147483648</var2>", "var2", -2147483648, true},
            {"<var3>(int32)0b1</var3>", "var3", 1, true},
            {"<var4>(int32)0x80000000</var4>", "var4", -2147483648, true},
            {"<var5>(int32) 0xFFFFFFFF</var5>", "var5", -1, true},
            {"<var6>(int32) 2147483648</var6>", "var6", 0, false},
            {0, 0, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Scalar(table));
}


TEST(XMLParserGTest,TestTypeCast_Scalar_uint32) {
    XMLParserTest parserTest;
    const TypeCastTableTest<uint32> table[]={
            {"<var1>(uint32) 2147483647</var1>", "var1", 2147483647, true},
            {"<var2> (uint32)4294967295</var2>", "var2", 4294967295, true},
            {"<var3>(uint32)0b1</var3>", "var3", 1, true},
            {"<var4>(uint32) 0xFFFFFFFF</var4>", "var4", 4294967295, true},
            {"<var4>(uint32) 0x100000000</var4>", "var4", 0, false},
            {0, 0, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Scalar(table));
}



TEST(XMLParserGTest,TestTypeCast_Scalar_int64) {
    XMLParserTest parserTest;
    const TypeCastTableTest<int64> table[]={
            {"<var1>(int64) 9223372036854775807</var1>", "var1", (int64)9223372036854775807ul, true},
            {"<var2> (int64)-9223372036854775808</var2>", "var2", (int64)-9223372036854775808ul, true},
            {"<var3>(int64)0b1</var3>", "var3", 1, true},
            {"<var4>(int64)0x8000000000000000</var4>", "var4", (int64)-9223372036854775808ul, true},
            {"<var5>(int64) 0xFFFFFFFFFFFFFFFF</var5>", "var5", -1, true},
            {"<var6>(int64) 9223372036854775808</var6>", "var6", 0, false},
            {0, 0, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Scalar(table));
}


TEST(XMLParserGTest,TestTypeCast_Scalar_uint64) {
    XMLParserTest parserTest;
    const TypeCastTableTest<uint64> table[]={
            {"<var1>(uint64) 9223372036854775807</var1>", "var1", 9223372036854775807ul, true},
            {"<var2>(uint64)18446744073709551615</var2>", "var2", 18446744073709551615ul, true},
            {"<var3>(uint64)0b1</var3>", "var3", 1, true},
            {"<var4>(uint64) 0xFFFFFFFFFFFFFFFF</var4>", "var4", 18446744073709551615ul, true},
            {"<var4>(uint64) 0x10000000000000000</var4>", "var4", 0, false},
            {0, 0, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Scalar(table));
}


TEST(XMLParserGTest,TestTypeCast_Scalar_float32) {
    XMLParserTest parserTest;
    const TypeCastTableTest<float32> table[]={
            {"<var1>(float32) 0xFF</var1>", "var1", 255.0f, true},
            {"<var2>(float32)-340282346638528859811704183484516925440</var2>", "var2", -340282346638528859811704183484516925440.0f, true},
            {"<var3>(float32)0b1</var3>", "var3", 1.0, true},
            {"<var4>(float32) 340282346638528859811704183484516925440</var4>", "var4", 340282346638528859811704183484516925440.0f, true},
            // overflow
            {"<var4>(float32) 123E+42</var4>", "var4", 0.0f, false},
            {0, 0, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Scalar(table));
}


TEST(XMLParserGTest,TestTypeCast_Scalar_float64) {
    XMLParserTest parserTest;
    const TypeCastTableTest<float64> table[]={
            {"<var1>(float64) 0xFF</var1>", "var1", 255.0, true},
            {"<var2> (float64)-340282346638528859811704183484516925440</var2>", "var2", -340282346638528859811704183484516925440.0f, true},
            {"<var3>(float64)0b1</var3>", "var3", 1.0, true},
            {"<var4>(float64) 340282346638528859811704183484516925440</var4>", "var4", 340282346638528859811704183484516925440.0f, true},
            // overflow
            {"<var4>(float64) 123E+510</var4>", "var4", 0.0, false},
            {0, 0, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Scalar(table));
}



TEST(XMLParserGTest,TestTypeCast_Vector_int8) {
    XMLParserTest parserTest;
    const TypeCastTableTestVector<int8, 5> table[]={
            {"<var1>(int8) {127 -128 0b1, 0x80 0xFF}</var1>", "var1", {127, -128, 1 , -128, -1}, true},
            {"<var1>(int8) {127 -129 0b1, 0x80 0xFF}</var1>", "var1", {127, -128, 1 , -128, -1}, false},
            {0, 0, {0}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Vector(table));
}


TEST(XMLParserGTest,TestTypeCast_Vector_uint8) {
    XMLParserTest parserTest;
    const TypeCastTableTestVector<uint8, 4> table[]={
            {"<var1>(uint8) {127 255 0b1 0xFF}</var1>", "var1", {127, 255, 1, 255}, true},
            {"<var1>(uint8) {1 0 -1 2}</var1>", "var1", {0}, false},
            {0, 0, {0}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Vector(table));
}




TEST(XMLParserGTest,TestTypeCast_Vector_int16) {
    XMLParserTest parserTest;
    const TypeCastTableTestVector<int16, 5> table[]={
            {"<var1>(int16) {32767 -32768 0b1 0x8000 0xFFFF}</var1>", "var1", {32767,-32768,1, -32768, -1}, true},
            {"<var1>(int16) {32768 -32768 0b1 0x8000 0xFFFF}</var1>", "var1", {32767,-32768,1, -32768, -1}, false},
            {0, 0, {0}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Vector(table));
}


TEST(XMLParserGTest,TestTypeCast_Vector_uint16) {
    XMLParserTest parserTest;
    const TypeCastTableTestVector<uint16, 4> table[]={
            {"<var1>(uint16) {32767 65535 0b1 0xFFFF}</var1>", "var1", {32767, 65535, 1, 65535}, true},
            {"<var1>(uint16) {1 0 -1 2}</var1>", "var1", {0}, false},
            {0, 0, {0}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Vector(table));
}


TEST(XMLParserGTest,TestTypeCast_Vector_int32) {
    XMLParserTest parserTest;
    const TypeCastTableTestVector<int32, 5> table[]={
            {"<var1>(int32) {2147483647 -2147483648 0b1 0x80000000 0xFFFFFFFF}</var1>", "var1", {2147483647, -2147483648, 1,-2147483648, -1}, true},
            {"<var1>(int32) {2147483647 -2147483648 0b1 0x80000000 0x1FFFFFFFF}</var1>", "var1", {2147483647, -2147483648, 1,-2147483648, -1}, false},
            {0, 0, {0}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Vector(table));
}


TEST(XMLParserGTest,TestTypeCast_Vector_uint32) {
    XMLParserTest parserTest;
    const TypeCastTableTestVector<uint32, 4> table[]={
            {"<var1>(uint32) {2147483647, 4294967295 0b1 0xFFFFFFFF}</var1>", "var1", {2147483647, 4294967295, 1, 4294967295}, true},
            {"<var1>(uint32) {1 0 -1 2}</var1>", "var1", {0}, false},
            {0, 0, {0}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Vector(table));
}



TEST(XMLParserGTest,TestTypeCast_Vector_int64) {
    XMLParserTest parserTest;
    const TypeCastTableTestVector<int64, 5> table[]={
            {"<var1>(int64) {9223372036854775807 -9223372036854775808 0b1 0x8000000000000000 0xFFFFFFFFFFFFFFFF}</var1>", "var1", {(int64)9223372036854775807ul, (int64)-9223372036854775808ul,1,(int64)-9223372036854775808ul,-1}, true},
            {"<var1>(int64) {9223372036854775808 -9223372036854775808 0b1 0x8000000000000000 0xFFFFFFFFFFFFFFFF}</var1>", "var1", {(int64)9223372036854775807ul, (int64)-9223372036854775808ul,1,(int64)-9223372036854775808ul,-1}, false},
            {0, 0, {0}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Vector(table));
}


TEST(XMLParserGTest,TestTypeCast_Vector_uint64) {
    XMLParserTest parserTest;
    const TypeCastTableTestVector<uint64, 4> table[]={
            {"<var1>(uint64) {9223372036854775807 18446744073709551615 0b1 0xFFFFFFFFFFFFFFFF}</var1>", "var1", {9223372036854775807ul, 18446744073709551615ul, 1, 18446744073709551615ul}, true},
            {"<var1>(uint64) {1 0 -1 2}</var1>", "var1", {0}, false},
            {0, 0, {0}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Vector(table));
}

TEST(XMLParserGTest,TestTypeCast_Vector_float32) {
    XMLParserTest parserTest;
    const TypeCastTableTestVector<float32, 4> table[]={
            {"<var1>(float32) {0xFF -340282346638528859811704183484516925440.0 0b1 340282346638528859811704183484516925440.0}</var1>", "var1", {255.0f, -340282346638528859811704183484516925440.0f, 1.0f, 340282346638528859811704183484516925440.0f}, true},
            {"<var1>(float32) {1.2 0.01 -1.2E+42 2}</var1>", "var1", {0}, false},
            {0, 0, {0}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Vector(table));
}


TEST(XMLParserGTest,TestTypeCast_Vector_float64) {
    XMLParserTest parserTest;
    const TypeCastTableTestVector<float64, 4> table[]={
            {"<var1>(float64) {0xFF -340282346638528859811704183484516925440.0 0b1 340282346638528859811704183484516925440.0}</var1>", "var1", {255.0, -340282346638528859811704183484516925440.0, 1.0, 340282346638528859811704183484516925440.0}, true},
            {"<var1>(float64) {1.2 0.01 -1.2E+510 2}</var1>", "var1", {0}, false},
            {0, 0, {0}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Vector(table));
}


TEST(XMLParserGTest,TestTypeCast_Matrix_int8) {
    XMLParserTest parserTest;
    const TypeCastTableTestMatrix<int8, 2,3> table[]={
            {"<var1>(int8) {{127 -128 0b1} {0x80 0xFF, -1}}</var1>", "var1", {{127, -128, 1 },{ -128, -1, -1}}, true},
            {"<var1>(int8) {{127 -128 0b1} {0x180 0xFF, -1}}</var1>", "var1", {{127, -128, 1 },{ -128, -1, -1}}, false},
            {0, 0, {{0}}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Matrix(table));
}


TEST(XMLParserGTest,TestTypeCast_Matrix_uint8) {
    XMLParserTest parserTest;
    const TypeCastTableTestMatrix<uint8, 2,2> table[]={
            {"<var1>(uint8) {{127 255}{0b1 0xFF}}</var1>", "var1", {{127, 255},{1, 255}}, true},
            {"<var1>(uint8) {{127 -1}{0b1 0xFF}}</var1>", "var1", {{127, 255},{1, 255}}, false},
            {0, 0, {{0}}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Matrix(table));
}




TEST(XMLParserGTest,TestTypeCast_Matrix_int16) {
    XMLParserTest parserTest;
    const TypeCastTableTestMatrix<int16, 2,3> table[]={
            {"<var1>(int16) {{32767 -32768 0b1}{ 0x8000 0xFFFF -1}}</var1>", "var1", {{32767,-32768,1},{ -32768, -1, -1}}, true},
            {"<var1>(int16) {{32767 -32769 0b1}{ 0x8000 0xFFFF -1}}</var1>", "var1", {{32767,-32768,1},{ -32768, -1, -1}}, false},
            {0, 0, {{0}}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Matrix(table));
}


TEST(XMLParserGTest,TestTypeCast_Matrix_uint16) {
    XMLParserTest parserTest;
    const TypeCastTableTestMatrix<uint16, 2,2> table[]={
            {"<var1>(uint16) {{32767 65535}{ 0b1 0xFFFF}}</var1>", "var1", {{32767, 65535},{ 1, 65535}}, true},
            {"<var1>(uint16) {{127 1}{0b1 0x10000}}</var1>", "var1", {{127, 255},{1, 255}}, false},
            {0, 0, {{0}}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Matrix(table));
}


TEST(XMLParserGTest,TestTypeCast_Matrix_int32) {
    XMLParserTest parserTest;
    const TypeCastTableTestMatrix<int32, 2,3> table[]={
            {"<var1>(int32) {{2147483647 -2147483648 0b1}{ 0x80000000 0xFFFFFFFF -1}}</var1>", "var1", {{2147483647, -2147483648, 1},{-2147483648, -1, -1}}, true},
            {"<var1>(int32) {{2147483648 -2147483648 0b1}{ 0x80000000 0xFFFFFFFF -1}}</var1>", "var1", {{2147483647, -2147483648, 1},{-2147483648, -1, -1}}, false},
            {0, 0, {{0}}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Matrix(table));
}


TEST(XMLParserGTest,TestTypeCast_Matrix_uint32) {
    XMLParserTest parserTest;
    const TypeCastTableTestMatrix<uint32, 2,2> table[]={
            {"<var1>(uint32) {{2147483647, 4294967295 }{0b1 0xFFFFFFFF}}</var1>", "var1", {{2147483647, 4294967295},{ 1, 4294967295}}, true},
            {"<var1>(uint32) {{2147483647, 4294967296 }{0b1 0xFFFFFFFF}}</var1>", "var1", {{2147483647, 4294967295},{ 1, 4294967295}}, false},
            {0, 0, {{0}}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Matrix(table));
}



TEST(XMLParserGTest,TestTypeCast_Matrix_int64) {
    XMLParserTest parserTest;
    const TypeCastTableTestMatrix<int64, 2,3> table[]={
            {"<var1>(int64) {{9223372036854775807 -9223372036854775808 0b1}{ 0x8000000000000000 0xFFFFFFFFFFFFFFFF -1}}</var1>", "var1", {{(int64)9223372036854775807ul, (int64)-9223372036854775808ul,1},{(int64)-9223372036854775808ul,-1, -1}}, true},
            {"<var1>(int64) {{9223372036854775807 -9223372036854775808 0b1}{ 0x18000000000000000 0xFFFFFFFFFFFFFFFF -1}}</var1>", "var1", {{(int64)9223372036854775807ul, (int64)-9223372036854775808ul,1},{(int64)-9223372036854775808ul,-1, -1}}, false},
            {0, 0, {{0}}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Matrix(table));
}


TEST(XMLParserGTest,TestTypeCast_Matrix_uint64) {
    XMLParserTest parserTest;
    const TypeCastTableTestMatrix<uint64, 2,2> table[]={
            {"<var1>(uint64) {{9223372036854775807 18446744073709551615}{ 0b1 0xFFFFFFFFFFFFFFFF}}</var1>", "var1", {{9223372036854775807ul, 18446744073709551615ul},{ 1, 18446744073709551615ul}}, true},
            {"<var1>(uint64) {{9223372036854775807 18446744073709551615}{ -1 0xFFFFFFFFFFFFFFFF}}</var1>", "var1", {{9223372036854775807ul, 18446744073709551615ul},{ 1, 18446744073709551615ul}}, false},
            {0, 0, {{0}}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Matrix(table));
}

TEST(XMLParserGTest,TestTypeCast_Matrix_float32) {
    XMLParserTest parserTest;
    const TypeCastTableTestMatrix<float32, 2,2> table[]={
            {"<var1>(float32) {{0xFF -340282346638528859811704183484516925440.0}{ 0b1 340282346638528859811704183484516925440.0}}</var1>", "var1", {{255.0f, -340282346638528859811704183484516925440.0f}, {1.0f, 340282346638528859811704183484516925440.0f}}, true},
            {"<var1>(float32) {{1.2 0.01}{-1.2E+42 2}}</var1>", "var1", {{0}}, false},
            {0, 0, {{0}}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Matrix(table));
}


TEST(XMLParserGTest,TestTypeCast_Matrix_float64) {
    XMLParserTest parserTest;
    const TypeCastTableTestMatrix<float64, 2,2> table[]={
            {"<var1>(float64) {{0xFF -340282346638528859811704183484516925440.0}{ 0b1 340282346638528859811704183484516925440.0}}</var1>", "var1", {{255.0, -340282346638528859811704183484516925440.0},{ 1.0, 340282346638528859811704183484516925440.0}}, true},
            {"<var1>(float64) {{1.2 0.01}{ -1.2E+510 2}}</var1>", "var1", {{0}}, false},
            {0, 0, {{0}}, 0}
    };

    ASSERT_TRUE(parserTest.TestTypeCast_Matrix(table));
}


TEST(XMLParserGTest,TestParseErrors_empty_scalar) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "<!-- This is a comment -->\n"
            "                        <var>1</var><!-- Multiple\n"
            "                         line comment-->\n"
            "                        <block2>\n"
            "                            <var2> </var2>\n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}


TEST(XMLParserGTest,TestParseErrors_empty_vector) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>{}</var2>\n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}


TEST(XMLParserGTest,TestParseErrors_unterminated_vector) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>{ 1 2 3 </var2> \n"
            "                            <var3>5 </var3>\n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}

TEST(XMLParserGTest,TestParseErrors_mixTypes_vector) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>{ 1 2 3 \"ciao\" } </var2> \n"
            "                            <var3>5</var3> \n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}

TEST(XMLParserGTest,TestParseErrors_badCloseTerminal_vector) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>{ 1 2 3 4 )  </var2>\n"
            "                            <var3>5</var3> \n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}

TEST(XMLParserGTest,TestParseErrors_empty_matrix) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>{{}}</var2>\n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}

TEST(XMLParserGTest,TestParseErrors_badVectorOpenTerminal_matrix) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>{{1, 2} (3, 4} }</var2>\n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}


TEST(XMLParserGTest,TestParseErrors_noVectorOpenTerminal_matrix) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>{{1, 2} 3, 4} }</var2>\n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}


TEST(XMLParserGTest,TestParseErrors_badVectorCloseTerminal_matrix) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        var=1\n"
            "                        <block2>\n"
            "                            var2={{1, 2) {3, 4} }\n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}


TEST(XMLParserGTest,TestParseErrors_noVectorCloseTerminal_matrix) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>{{1, 2 {3, 4} }</var2>\n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}

TEST(XMLParserGTest,TestParseErrors_mixTypes_matrix) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>{{1, 2} {3, Hello} }</var2>\n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}


TEST(XMLParserGTest,TestParseErrors_badFormat_matrix) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>{{1, 2} {3, 4, 5} }</var2>\n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}


TEST(XMLParserGTest,TestParseErrors_typeCast_terminal_1) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>(int8} {{1,2}{3,4}}</var2>\n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}


TEST(XMLParserGTest,TestParseErrors_typeCast_terminal_2) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>(int8 3</var2>\n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}




TEST(XMLParserGTest,TestParseErrors_Too_many_CloseBlockTerminal_1) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>3</var2>\n"
            "                        </block2>\n"
            "                 </block1></block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}

TEST(XMLParserGTest,TestParseErrors_Too_many_CloseBlockTerminal_2) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>{3 2}</var2>\n"
            "                        </block2>\n"
            "                 </block1></block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}

TEST(XMLParserGTest,TestParseErrors_Too_many_CloseBlockTerminal_3) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>{{1 2}, {3,4}}</var2>\n"
            "                        </block2>\n"
            "                 </block1></block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}


TEST(XMLParserGTest,TestParseErrors_Too_many_OpenBlockTerminal) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2 block2>\n"
            "                            <var2>3</var2>\n"
            "                        </block2>\n"
            "                 </block1>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}


TEST(XMLParserGTest,TestParseErrors_Unexpected_EOF) {
    XMLParserTest parserTest;
    const char8* configString="<block1>\n"
            "                        <var>1</var>\n"
            "                        <block2>\n"
            "                            <var2>3</var2>";
    ASSERT_TRUE(parserTest.TestParseErrors(configString));
}


TEST(XMLParserGTest,TestStandardCast) {
    XMLParserTest parserTest;
    ASSERT_TRUE(parserTest.TestStandardCast());
}

