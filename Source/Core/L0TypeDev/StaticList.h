/**
 * @file StaticList.h
 * @brief Header file for class StaticList
 * @date 14/09/2015
 * @author Ivan Herrero
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

 * @details This header file contains the declaration of the class StaticList
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef STATICLIST_H_
#define STATICLIST_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "StaticListHolder.h"
#include "GeneralDefinitions.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace Lists {

/**
 * @brief This template class is a ADT for an unbounded list which allows
 * adding, inserting, removing and peeking elements at arbitrary positions
 * in a range from 0 onwards.
 *
 * @details This class is the template version of the class StaticListHolder,
 * parameterising the elementType and listAllocationGranularity. Thus, the
 * instantiation of the template class determines automatically the size of
 * the element type and sets the allocation granularity for all the instances.
 *
 * @see Lists::StaticListHolder
 */
template<typename elementType, uint32 listAllocationGranularity = 10>
class StaticList {
public:

    /**
     * @brief Default constructor
     */
    StaticList();

    /**
     * @brief StaticListHolder::GetElementSize()
     */
    uint32 GetElementSize(void) const;

    /**
     * @brief StaticListHolder::GetAllocationGranularity()
     */
    uint32 GetAllocationGranularity(void) const;

    /**
     * @brief StaticListHolder::GetSize()
     */
    uint32 GetSize(void) const;

    /**
     * @brief StaticListHolder::GetCapacity()
     */
    uint32 GetCapacity(void) const;

    /**
     * @brief StaticListHolder::GetMaxCapacity()
     */
    uint32 GetMaxCapacity(void) const;

    /**
     * @brief StaticListHolder::Peek()
     */
    bool Peek(const uint32 position,
              elementType &value) const;

    /**
     * @brief StaticListHolder::Add()
     */
    bool Add(const elementType &value);

    /**
     * @brief StaticListHolder::Insert()
     */
    bool Insert(const uint32 position,
             const elementType &value);

    /**
     * @brief StaticListHolder::Remove()
     */
    bool Remove(const uint32 position);

    /**
     * @brief StaticListHolder::Extract()
     */
    bool Extract(const uint32 position,
                 elementType &value);

private:

    /**
     * @brief The instance of StaticListHolder to which the implementation is delegated.
     */
    StaticListHolder slh;

};

}

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

namespace Lists {

template<typename elementType, uint32 listAllocationGranularity>
StaticList<elementType, listAllocationGranularity>::StaticList() :
    slh(sizeof(elementType), listAllocationGranularity) {
}

template<typename elementType, uint32 listAllocationGranularity>
uint32 StaticList<elementType, listAllocationGranularity>::GetElementSize(void) const {
    return slh.GetElementSize(); /* sizeof(elementType); */
}

template<typename elementType, uint32 listAllocationGranularity>
uint32 StaticList<elementType, listAllocationGranularity>::GetAllocationGranularity(void) const {
    return slh.GetAllocationGranularity(); /* listAllocationGranularity; */
}

template<typename elementType, uint32 listAllocationGranularity>
uint32 StaticList<elementType, listAllocationGranularity>::GetSize(void) const {
    return slh.GetSize();
}

template<typename elementType, uint32 listAllocationGranularity>
uint32 StaticList<elementType, listAllocationGranularity>::GetCapacity(void) const {
    return slh.GetCapacity();
}

template<typename elementType, uint32 listAllocationGranularity>
uint32 StaticList<elementType, listAllocationGranularity>::GetMaxCapacity(void) const {
    return slh.GetMaxCapacity();
}

template<typename elementType, uint32 listAllocationGranularity>
bool StaticList<elementType, listAllocationGranularity>::Peek(const uint32 position,
                                                              elementType &value) const {
    return slh.Peek(position, static_cast<void *>(&value));
}

template<typename elementType, uint32 listAllocationGranularity>
bool StaticList<elementType, listAllocationGranularity>::Add(const elementType &value) {
    return slh.Add(static_cast<const void *>(&value));
}

template<typename elementType, uint32 listAllocationGranularity>
bool StaticList<elementType, listAllocationGranularity>::Insert(const uint32 position,
                                                             const elementType &value) {
    return slh.Insert(position, static_cast<const void *>(&value));
}

template<typename elementType, uint32 listAllocationGranularity>
bool StaticList<elementType, listAllocationGranularity>::Remove(const uint32 position) {
    return slh.Remove(position);
}

template<typename elementType, uint32 listAllocationGranularity>
bool StaticList<elementType, listAllocationGranularity>::Extract(const uint32 position,
                                                                 elementType &value) {
    return slh.Extract(position, static_cast<void *>(&value));
}

}

#endif /* STATICLIST_H_ */

