/**
 * @file HttpObjectBrowser.cpp
 * @brief Source file for class HttpObjectBrowser
 * @date 29/10/2018
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
 * the class HttpObjectBrowser (public, protected, and private). Be aware that some 
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/
#include "AdvancedErrorManagement.h"
#include "HttpDirectoryResource.h"
#include "HttpObjectBrowser.h"
#include "HttpProtocol.h"
#include "JsonPrinter.h"
#include "ObjectRegistryDatabase.h"
#include "StreamStructuredData.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/
namespace MARTe {

HttpObjectBrowser::HttpObjectBrowser() :
        HttpDataExportI() {
    closeOnAuthFail = 1u;
}

HttpObjectBrowser::~HttpObjectBrowser() {
    root = Reference();

}

void HttpObjectBrowser::Purge(ReferenceContainer &purgeList) {
    root = Reference();
    ReferenceContainer::Purge(purgeList);
}

bool HttpObjectBrowser::Initialise(StructuredDataI &data) {
    bool ok = ReferenceContainer::Initialise(data);

    StreamString rootName;
    if (ok) {
        ok = data.Read("Root", rootName);
        if (!ok) {
            REPORT_ERROR(ErrorManagement::ParametersError, "A Root shall be specified");
        }
    }
    if (ok) {
        if (rootName.Size() == 1u) {
            if (rootName[0] == '/') {
                root = ObjectRegistryDatabase::Instance();
            }
            else if (rootName[0] == '.') {
                root = this;
            }
            else {
                REPORT_ERROR(ErrorManagement::ParametersError, "Unknown Root [%c]", rootName[0]);
            }
        }
        else {
            root = ObjectRegistryDatabase::Instance()->Find(rootName.Buffer());
            ok = root.IsValid();
            if (!ok) {
                REPORT_ERROR(ErrorManagement::ParametersError, "Invalid Root [%s]", rootName.Buffer());
            }
        }

    }
    if (ok) {
        StreamString realmStr;
        if (data.Read("Realm", realmStr)) {
            if (ok) {
                realm = Find(realmStr.Buffer());
                ok = realm.IsValid();
                if (!ok) {
                    realm = ObjectRegistryDatabase::Instance()->Find(realmStr.Buffer());
                    ok = realm.IsValid();
                }
                if (!ok) {
                    REPORT_ERROR_STATIC(ErrorManagement::ParametersError, "The specified Realm reference is not valid");
                }
            }
            else {
                REPORT_ERROR_STATIC(ErrorManagement::ParametersError, "A reference to a Realm object shall be specified");
            }
        }
        else {
            REPORT_ERROR_STATIC(ErrorManagement::Information, "No Realm specified");

        }
    }
    if (ok) {
        if (!data.Read("CloseOnAuthFail", closeOnAuthFail)) {
            closeOnAuthFail = 1u;
        }
    }
    return ok;
}

bool HttpObjectBrowser::CheckSecurity(HttpProtocol &protocol) {
    bool securityOK = true;
    if (realm.IsValid()) {
        HttpProtocol *hprotocol = dynamic_cast<HttpProtocol *>(&protocol);
        if (hprotocol != NULL_PTR(HttpProtocol *)) {
            securityOK = hprotocol->SecurityCheck(realm);
            if (!securityOK) {
                bool ok = true;
                if (!hprotocol->MoveAbsolute("OutputOptions")) {
                    ok = (hprotocol->CreateAbsolute("OutputOptions"));
                }
                if (ok) {
                    StreamString contentType = "text/html";
                    ok = hprotocol->Write("Content-Type", contentType.Buffer());
                }
                StreamString realmMsg;
                if (ok) {
                    ok = (realm->GetAuthenticationRequest(realmMsg));
                }
                if (ok) {
                    ok = hprotocol->Write("WWW-Authenticate", realmMsg.Buffer());
                }
                StreamString hstream;
                if (ok) {
                    ok = hstream.Printf("%s", "<HTML><HEAD>\n"
                                        "<TITLE>401 Authorization Required</TITLE>\n"
                                        "</HEAD><BODY>\n"
                                        "<H1>Authorization Required</H1>\n"
                                        "This server could not verify that you\n"
                                        "are authorized to access the document you\n"
                                        "requested.  Either you supplied the wrong\n"
                                        "credentials (e.g., bad password), or your\n"
                                        "browser doesn't understand how to supply\n"
                                        "the credentials required.<P>\n"
                                        "</BODY></HTML>\n");
                }
                if (ok) {
                    ok = hstream.Seek(0ULL);
                }
                if (ok) {
                    if (closeOnAuthFail > 0u) {
                        // force reissuing of a new thread
                        hprotocol->SetKeepAlive(false);
                    }
                    ok = hprotocol->WriteHeader(true, HttpDefinition::HSHCReplyAUTH, &hstream, NULL_PTR(const char8*));
                }
            }
        }
    }
    return securityOK;
}

bool HttpObjectBrowser::GetAsStructuredData(StreamStructuredDataI &data, HttpProtocol &protocol) {
    bool ok = CheckSecurity(protocol);
    if (ok) {
        Reference target = FindReference(protocol, root);
        ok = target.IsValid();
        if (ok) {
            bool isThis = (target == this);
            ReferenceT<HttpDataExportI> httpDataExportI = target;
            if ((httpDataExportI.IsValid()) && (!isThis)) {
                httpDataExportI->GetAsStructuredData(data, protocol);
            }
            else {
                ok = HttpDataExportI::GetAsStructuredData(data, protocol);
                if (ok) {
                    StreamStructuredData<JsonPrinter> *sdata = dynamic_cast<StreamStructuredData<JsonPrinter> *>(&data);
                    ok = (sdata != NULL_PTR(StreamStructuredData<JsonPrinter> *));
                    if (ok) {
                        sdata->GetPrinter()->PrintBegin();
                    }
                    if (ok) {
                        //ok = GetReferenceAsStructuredData(data, protocol, target);
                        target->ExportData(data);
                    }
                    if (ok) {
                        ok = sdata->GetPrinter()->PrintEnd();
                    }
                }
            }
        }
        //TODO Handle 404
    }
    return ok;
}

bool HttpObjectBrowser::GetAsText(StreamI &stream, HttpProtocol &protocol) {
    bool ok = CheckSecurity(protocol);
    if (ok) {
        Reference target = FindReference(protocol, root);
        ok = target.IsValid();
        if (ok) {
            bool isThis = (target == this);
            if (isThis) {
                //Check if there are any HttpDirectoryResources that could handle the request
                uint32 n;
                uint32 nObjs = Size();
                bool handled = false;
                for (n = 0u; (n < nObjs) && (!handled); n++) {
                    ReferenceT<HttpDirectoryResource> httpDirectoryResource = Get(n);
                    handled = httpDirectoryResource.IsValid();
                    if (handled) {
                        handled = httpDirectoryResource->GetAsText(stream, protocol);
                    }
                }
                if (!handled) {
                    ok = HttpDataExportI::GetAsText(stream, protocol);
                    if (ok) {
                        StreamString msg = "Resource not found.";
                        uint32 size = msg.Size();
                        ok = stream.Write(msg.Buffer(), size);
                    }
                }
            }
            else {
                ReferenceT<HttpDataExportI> httpDataExportI = target;
                if (httpDataExportI.IsValid()) {
                    httpDataExportI->GetAsText(stream, protocol);
                }
                else {
                    ok = HttpDataExportI::GetAsText(stream, protocol);
                    if (ok) {
                        StreamString msg = "Text mode not supported for this object - or object not found.";
                        uint32 size = msg.Size();
                        ok = stream.Write(msg.Buffer(), size);
                    }
                }
            }
        }
    }
    return ok;
}

CLASS_REGISTER(HttpObjectBrowser, "1.0")
}