/**
 * @file XMLPrinterTest.h
 * @brief Header file for class XMLPrinterTest
 * @date 18/09/2018
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

 * @details This header file contains the declaration of the class XMLPrinterTest
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef XMLPRINTERTEST_H_
#define XMLPRINTERTEST_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/
#include "XMLPrinter.h"
/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

using namespace MARTe;

/**
 * @brief Tests the XMLPrinter methods
 */
class XMLPrinterTest {
public:

    /**
     * @brief Constructor
     */
    XMLPrinterTest();

    /**
     * @brief Destructor
     */
    virtual ~XMLPrinterTest();

    /**
     * @brief Tests the PrintOpenMatrix method
     */
    bool TestPrintOpenMatrix();

    /**
     * @brief Tests the PrintCloseMatrix method
     */

    bool TestPrintCloseMatrix();

    /**
     * @brief Tests the PrintScalarSeparator method
     */
    bool TestPrintScalarSeparator();

    /**
     * @brief Tests the PrintVectorSeparator method
     */
    bool TestPrintVectorSeparator();


    /**
     * @brief Tests the PrintVariableSeparator method
     */
    bool TestPrintVariableSeparator();

    /**
     * @brief Tests the PrintBlockSeparator method
     */
    bool TestPrintBlockSeparator();

    /**
     * @brief Tests the PrintOpenVector method
     */
    bool TestPrintOpenVector();

    /**
     * @brief Tests the PrintCloseVector method
     */
    bool TestPrintCloseVector();

    /**
     * @brief Tests the PrintOpenBlock method
     */
    bool TestPrintOpenBlock();

    /**
     * @brief Tests the PrintCloseBlock method
     */
    bool TestPrintCloseBlock();

    /**
     * @brief Tests the PrintOpenAssignment method
     */
    bool TestPrintOpenAssignment();

    /**
     * @brief Tests the PrintCloseAssignment method
     */
    bool TestPrintCloseAssignment();

    /**
     * @brief Tests the PrintVariable method
     */
    bool TestPrintVariable();


};

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* XMLPRINTERTEST_H_ */

