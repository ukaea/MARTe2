#!/bin/bash

export GPPVERSION=$(g++ --version | grep ^g++ | sed 's/^.* //g')
#Environment by 'export' should show GPPVERSION version numbers like this
#GPPVERSION="major.middle.minor"

echo "Found g++ --version " $GPPVERSION

############################################################################
# Purpose:

# Disable three gpp Warnings if gpp version is >= 12.2.0 (as on RPI Debian 12 Bookworm)
# The gpp -Wall and -Werror options used will stop the build on these three Warnings in the M2 source:
#   -Wuninitialised   -Wformat   -Wmismatched-new-delete

# If gpp --version number is less than 12.2.0, this script puts variable BEFORE_DEBIAN_12 in environment.
# The variable BEFORE_GPP_V12P2P0 is picked up by 'make -f Makefile.rpi4' that must be called in same shell.
# See MakeDefaults folder see MakeStdLibDefs.armv8-linux 

# If BEFORE_GPP_V12P2P0 is true, 'make' will not disable the three gpp Warnings
# If BEFORE_GPP_V12P2P0 is false, 'make' disables these three gpp Warnings as needed for gpp>= 12.2.0 in Debian12 RPI build
############################################################################

IFS="$IFS." read version_major version_middle version_minor <<< $GPPVERSION
#echo $version_major
#echo $version_middle
#echo $version_minor
older_gpp=0
if [ $version_major -lt 12 ]
then
  #echo "major<12 skip my flags"
  older_gpp=1
fi
if [ $version_major -eq 12 ]
then
  if [ $version_middle -lt 2 ]
  then
    #echo "12.med<2 skip my flags"
    older_gpp=1
  fi
  if [ $version_middle -eq 2 ]
  then
    if [ $version_minor -lt 0 ]
    then
      #echo "12.2.minor<0 skip my flags"
      older_gpp=1
    fi
  fi
fi
if [ $older_gpp -eq 0 ]
then
  echo "Setting Environment Variable BEFORE_GPP_V12P2P0=0"
  export BEFORE_GPP_V12P2P0=0
fi
if [ $older_gpp -eq 1 ]
then
  echo "Setting Environment Variable BEFORE_GPP_V12P2P0=1"
  export BEFORE_GPP_V12P2P0=1
fi



