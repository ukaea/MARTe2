/**
 * @file Vector.h
 * @brief Header file for class Vector
 * @date 04/11/2015
 * @author Andre' Neto
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

 * @details This header file contains the declaration of the class Vector
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef VECTOR_H_
#define VECTOR_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/
#include "HeapManager.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/
namespace MARTe {

/**
 * @brief Fixed size array of values.
 * @details The Vector can allocate and manage its own memory or it can be associated
 * to an existent memory array.
 */
template<typename T>
class Vector {
public:
    /**
     * @brief Default constructor
     * @post
     *    GetNumberOfElements() == 0u &&
     *    GetDataPointer() == NULL &&
     *    IsStaticDeclared()== false
     */
    Vector();

    /**
     * @brief Constructs a new vector with size: [nOfElements]
     * @post
     *    GetNumberOfElements() == nOfElements &&
     *    GetDataPointer() != NULL &&
     *    IsStaticDeclared() == false
     */
    Vector(uint32 nOfElements);

    /**
     * @brief Constructs a new vector and associates it to an existent array with size: [nOfElements]
     * @post
     *    GetNumberOfElements() == nOfElements &&
     *    GetDataPointer() == existingArray &&
     *    IsStaticDeclared() == false
     */
    Vector(T *existingArray,
           uint32 nOfElements);

    /**
     * @brief Constructs a new matrix from a statically declared table [].
     * @param[in] source address of the statically declared table.
     * @post
     *   GetNumberOfElements() == nOfElementsStatic &&
     *   GetDataPointer() == &source[0] &&
     *   IsStaticDeclared == true
     */
    template<uint32 nOfElementsStatic>
    Vector(T (&source)[nOfElementsStatic]);

    /**
     * @brief Destructor.
     * @post
     *   If IsStaticDeclared frees \a dataPointer
     */
    ~Vector();

    /**
     * @brief Returns the element at position \a idx.
     * @param[in] idx the index of the element to retrieve.
     * @return the element at position \a idx.
     */
    T &operator [](uint32 idx);

    /**
     * @brief Gets the data pointer associated to the raw matrix data.
     * @return the data pointer associated to the raw matrix data.
     */
    inline void * GetDataPointer() const;

    /**
     * @brief Checks if GetDataPointer() is pointing at a statically allocated array memory block [].
     * @return true if GetDataPointer() is pointing at a statically allocated array memory block [].
     */
    inline bool IsStaticDeclared() const;

    /**
     * @brief Gets the number of elements in the vector.
     * @return the number of elements in the vector.
     */
    inline uint32 GetNumberOfElements();

    /**
     * @brief Performs the vector scalar product.
     * @param[in] factor is the vector to be multiplied with.
     * @param[out] result is the result of the scalar product of this vector multiplied with \a factor.
     * @return true if \a factor has the same number of elements of this vector, false otherwise.
     * @pre
     *   numberOfElements == factor.numberOfElements;
     */
    bool Product(Vector<T> factor,
                 T &result) const;

private:
    /**
     * The data pointer to the raw data.
     */
    void *dataPointer;

    /**
     * The number of elements.
     */
    uint32 numberOfElements;

    /**
     * True if this dataPointer is pointing at a statically allocated matrix memory block [][].
     */
    bool staticDeclared;

    /**
     * True if the vector is allocated internally on heap and has to be destroyed by the destructor.
     */
    bool canDestroy;
};
}

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/
namespace MARTe {

template<typename T>
Vector<T>::Vector() {
    numberOfElements = 0u;
    dataPointer = NULL_PTR(T *);
    staticDeclared = true;
    canDestroy = false;
}

template<typename T>
Vector<T>::Vector(uint32 nOfElements) {
    dataPointer = new T[nOfElements];
    numberOfElements = nOfElements;
    staticDeclared = false;
    canDestroy = true;
}

template<typename T>
Vector<T>::Vector(T *existingArray,
                  uint32 nOfElements) {
    dataPointer = existingArray;
    numberOfElements = nOfElements;
    staticDeclared = false;
    canDestroy = false;
}

template<typename T>
template<uint32 nOfElementsStatic>
Vector<T>::Vector(T (&source)[nOfElementsStatic]) {
    dataPointer = reinterpret_cast<T *>(&source[0]);
    numberOfElements = nOfElementsStatic;
    staticDeclared = true;
    canDestroy = false;
}

template<typename T>
Vector<T>::~Vector() {
    if (canDestroy) {
        delete[] reinterpret_cast<T*>(dataPointer);
    }
}

template<typename T>
T &Vector<T>::operator [](uint32 idx) {
    T* array = reinterpret_cast<T*>(dataPointer);
    return array[idx];
}

template<typename T>
inline void* Vector<T>::GetDataPointer() const {
    return dataPointer;
}

template<typename T>
inline bool Vector<T>::IsStaticDeclared() const {
    return staticDeclared;
}

template<typename T>
inline uint32 Vector<T>::GetNumberOfElements() {
    return numberOfElements;
}

template<typename T>
bool Vector<T>::Product(Vector<T> factor,
                        T &result) const {
    bool ret = (factor.numberOfElements == numberOfElements);
    if (ret) {
        result = static_cast<T>(0);
        T* array = reinterpret_cast<T*>(dataPointer);
        for (uint32 i = 0u; i < numberOfElements; i++) {
            result += array[i] * factor[i];
        }
    }
    return ret;
}

}

#endif /* VECTOR_H_ */

