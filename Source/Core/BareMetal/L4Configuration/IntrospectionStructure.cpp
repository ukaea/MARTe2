/**
 * @file IntrospectionStructure.cpp
 * @brief Source file for class IntrospectionStructure
 * @date 09/11/2018
 * @author Andre Neto
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
 * the class IntrospectionStructure (public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/
#include "../L4Configuration/IntrospectionStructure.h"

#include "AdvancedErrorManagement.h"
#include "ClassRegistryItem.h"
#include "Introspection.h"
#include "StreamString.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/
namespace MARTe {

IntrospectionStructure::ClassRegistryItemConfigurationStructureLoader::ClassRegistryItemConfigurationStructureLoader(ClassProperties &cp) :
        ClassRegistryItem(cp) {
}

IntrospectionStructure::ClassRegistryItemConfigurationStructureLoader::~ClassRegistryItemConfigurationStructureLoader() {

}

}

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

namespace MARTe {
IntrospectionStructure::IntrospectionStructure() {
    entries = NULL_PTR(IntrospectionEntry **);
    criLoader = NULL_PTR(ClassRegistryItemConfigurationStructureLoader *);
    introMembers = NULL_PTR(Introspection *);
    cp = NULL_PTR(ClassProperties *);
    numberOfMembers = 0u;
    memberInfo = NULL_PTR(MemberInfo **);
}

IntrospectionStructure::~IntrospectionStructure() {
    if (entries != NULL_PTR(IntrospectionEntry **)) {
        uint32 n;
        for (n = 0u; n < (numberOfMembers + 1u); n++) {
            delete entries[n];
        }
        delete[] entries;
    }
    if (memberInfo != NULL_PTR(MemberInfo **)) {
        uint32 n;
        for (n = 0u; n < (numberOfMembers); n++) {
            delete memberInfo[n];
        }
        delete[] memberInfo;
    }
    //Deleted by the IntrospectionStructure!
    /*if (criLoader != NULL_PTR(ClassRegistryItemConfigurationStructureLoader *)) {
     delete criLoader;
     }*/
    if (introMembers != NULL_PTR(Introspection *)) {
        delete[] introMembers;
    }
    if (cp != NULL_PTR(ClassProperties *)) {
        delete cp;
    }
}

bool IntrospectionStructure::Initialise(StructuredDataI &data) {
    bool ok = Object::Initialise(data);
    uint32 totalSize = 0u;
    const ClassRegistryItem *item = ClassRegistryDatabase::Instance()->Find(GetName());

    if (ok) {
        ok = (item == NULL_PTR(const ClassRegistryItem *));
    }
    if (ok) {
        uint32 n;
        uint32 nOfChildren = data.GetNumberOfChildren();
        for (n = 0u; (n < nOfChildren) && (ok); n++) {
            StreamString memberName = data.GetChildName(n);
            if (data.MoveRelative(memberName.Buffer())) {
                StreamString typeNameStr;
                if (ok) {
                    ok = data.Read("Type", typeNameStr);
                    if (!ok) {
                        REPORT_ERROR(ErrorManagement::ParametersError, "Member %s has no Type defined", memberName.Buffer());
                    }
                }
                uint32 numberOfDimensions = 0u;
                uint32 *numberOfElements = NULL_PTR(uint32 *);
                uint32 nd = 0u;

                if (ok) {
                    AnyType arrayDescription = data.GetType("NumberOfElements");
                    if (arrayDescription.GetDataPointer() == NULL_PTR(void *)) {
                        numberOfElements = new uint32[1u];
                        numberOfElements[0u] = 1u;
                    }
                    else {
                        numberOfDimensions = arrayDescription.GetNumberOfElements(0u);
                        if (numberOfDimensions < 2u) {
                            numberOfElements = new uint32[1u];
                            Vector<uint32> readVector(numberOfElements, numberOfDimensions);
                            if (!data.Read("NumberOfElements", readVector)) {
                                uint32 nElementsRead = 1u;
                                ok = data.Read("NumberOfElements", nElementsRead);
                                if (ok) {
                                    if (nElementsRead > 1u) {
                                        numberOfDimensions = 1u;
                                    }
                                    numberOfElements[0u] = nElementsRead;
                                }
                            }
                            if (numberOfDimensions == 1u) {
                                if (numberOfElements[0u] == 1u) {
                                    numberOfDimensions = 0u;
                                }
                            }
                        }
                        else {
                            numberOfElements = new uint32[numberOfDimensions];
                            Vector<uint32> readVector(numberOfElements, numberOfDimensions);
                            ok = data.Read("NumberOfElements", readVector);
                        }
                    }
                }
                if (ok) {
                    StreamString modifiers;
                    for (nd = 0u; nd < numberOfDimensions; nd++) {
                        modifiers.Printf("[%d]", numberOfElements[nd]);
                    }
                    uint32 z;
                    //entries is a zero terminated array
                    IntrospectionEntry **newEntries = new IntrospectionEntry *[numberOfMembers + 2u];
                    MemberInfo** newMemberInfo = new MemberInfo *[numberOfMembers + 1u];
                    for (z = 0u; z < numberOfMembers; z++) {
                        newEntries[z] = entries[z];
                        newMemberInfo[z] = memberInfo[z];
                    }
                    if (entries != NULL_PTR(IntrospectionEntry **)) {
                        delete[] entries;
                    }
                    if (memberInfo != NULL_PTR(MemberInfo **)) {
                        delete[] memberInfo;
                    }
                    entries = newEntries;
                    memberInfo = newMemberInfo;

                    uint32 memberSize = 0u;
                    TypeDescriptor td = TypeDescriptor::GetTypeDescriptorFromTypeName(typeNameStr.Buffer());
                    if (td != voidAnyType.GetTypeDescriptor()) {
                        memberSize = td.numberOfBits / 8u;
                    }
                    else {
                        const ClassRegistryItem *registeredMember = ClassRegistryDatabase::Instance()->Find(typeNameStr.Buffer());
                        if (registeredMember != NULL_PTR(const ClassRegistryItem *)) {
                            const Introspection *intro = registeredMember->GetIntrospection();
                            if (intro != NULL_PTR(const Introspection *)) {
                                memberSize = registeredMember->GetIntrospection()->GetClassSize();
                            }
                        }
                        else {
                            REPORT_ERROR(ErrorManagement::ParametersError, "Type %s is not known", typeNameStr.Buffer());
                        }
                    }
                    newMemberInfo[z] = new MemberInfo();
                    newMemberInfo[z]->memberName = memberName.Buffer();
                    newMemberInfo[z]->memberType = typeNameStr.Buffer();
                    newMemberInfo[z]->memberModifier = modifiers.Buffer();

                    uint32 totalElements = 0u;
                    for (nd = 0u; nd < numberOfDimensions; nd++) {
                        totalElements += numberOfElements[nd]; //[1][1][1] has size 3x
                    }
                    if (totalElements == 0u) {
                        totalElements = numberOfElements[0U];
                    }
                    if (totalElements == 0u) {
                        totalElements = 1u;
                    }
                    IntrospectionEntry *entry = new IntrospectionEntry(newMemberInfo[z]->memberName.Buffer(),
                                                                       newMemberInfo[z]->memberType.Buffer(),
                                                                       newMemberInfo[z]->memberModifier.Buffer(), "", memberSize,
                                                                       totalSize);
                    entries[z] = entry;
                    entries[z + 1] = NULL_PTR(IntrospectionEntry *);
                    totalSize += (memberSize * totalElements);
                    numberOfMembers++;
                }
                if (ok) {
                    ok = data.MoveToAncestor(1u);
                }
                if (numberOfElements != NULL_PTR(uint32 *)) {
                    delete[] numberOfElements;
                }
            }
        }
    }
    else {
        REPORT_ERROR(ErrorManagement::ParametersError, "Type %s is already registered", GetName());
    }
    if (ok) {
        ok = (totalSize > 0u);
        if (!ok) {
            REPORT_ERROR(ErrorManagement::ParametersError, "Type %s has no parameters", GetName());
        }
    }
    if (ok) {
        typeName.Printf("%s", GetName());
        cp = new ClassProperties(typeName.Buffer(), typeName.Buffer(), "", totalSize);
        criLoader = new ClassRegistryItemConfigurationStructureLoader(*cp);
        introMembers = new Introspection(const_cast<const IntrospectionEntry **>(entries), totalSize);
        criLoader->SetIntrospection(introMembers);
        ClassRegistryDatabase::Instance()->Add(criLoader);
        REPORT_ERROR(ErrorManagement::ParametersError, "Registering type %s ", typeName.Buffer());
    }

    return ok;
}

CLASS_REGISTER(IntrospectionStructure, "1.0");
}

