# Building on RPI4 Debian 12 Bookworm with gpp version 12.2.0

The new gpp version caused the following steps to build MARTe2.
Source the shell script in the MARTe2 folder i.e. "source check_gpp_version.sh"
The script should say "Found g++ --version 12.2.0" (or higher)
Because of the 'source' command, the script should also have made an Environment Variable BEFORE_GPP_V12P2P0=0
The 'make' command for MARTe2 and MARTe2-Components must be called from this same instance of the shell, not a new one, to preserve the environment variable BEFORE_GPP_V12P2P0
This environment variable causes MakeStdLibDefs.armv8-linux to disable some new warnings as follows.
If BEFORE_GPP_V12P2P0 is 0, MakeStdLibDefs.armv8-linux disregards three new types of compiler warnings which stop build
on g++ 12.2.0 (warnings stop the build because -Werror is set).
If BEFORE_GPP_V12P2P0 is 1, the original line in MakeStdLibDefs.armv8-linux is applied (in case builds on older g++ were somehow affected by the above modification)
Apart from the above, note this MARTe2 repo's makefiles contain a minor fix as libGTEST was not being built for armv8. 


# MARTe2

The MARTe software framework is a C++ modular and multi-platform framework for the development of real-time control system applications. 

- [User documentation](https://vcis.f4e.europa.eu/marte2-docs/master/html/)
- [API documentation](https://vcis-jenkins.f4e.europa.eu/job/MARTe2-docs-master/doxygen/annotated.html)
- [Components](https://vcis-gitlab.f4e.europa.eu/aneto/MARTe2-components) 

- [Source-code](https://vcis-gitlab.f4e.europa.eu/aneto/MARTe2)
- [Integration](https://vcis-jenkins.f4e.europa.eu/job/MARTe2)

## License

Copyright 2015 F4E | European Joint Undertaking for ITER and the Development of Fusion Energy ('Fusion for Energy').
Licensed under the EUPL, Version 1.1 or - as soon they will be approved by the European Commission - subsequent versions of the EUPL (the "Licence"). You may not use this work except in compliance with the Licence. You may obtain a copy of the Licence at: http://ec.europa.eu/idabc/eupl

Unless required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence permissions and limitations under the Licence.
