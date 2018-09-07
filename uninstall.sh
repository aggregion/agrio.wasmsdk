#! /bin/bash

binaries=(agrio-ranlib
          agrio-ar
          agrio-objdump
          agrio-readelf
          agrio-abigen
          agrio-wasm2wast
          agrio-wast2wasm
          agrio-pp
          agrio-cc
          agrio-cpp
          agrio-ld)

if [ -d "/usr/local/agrio.cdt" ]; then
   printf "\tDo you wish to remove this install? (requires sudo)\n"
   select yn in "Yes" "No"; do
      case $yn in
         [Yy]* )
            pushd /usr/local &> /dev/null
            rm -rf agrio.cdt
            pushd bin &> /dev/null
            for binary in ${binaries[@]}; do
               rm ${binary}
            done
            popd &> /dev/null
            break;;
         [Nn]* ) 
            printf "\tAborting uninstall\n\n"
            exit -1;;
      esac
   done
fi

if [ -d "/usr/local/agrio.wasmsdk" ]; then
   printf "\tDo you wish to remove this install? (requires sudo)\n"
   select yn in "Yes" "No"; do
      case $yn in
         [Yy]* )
            pushd /usr/local &> /dev/null
            rm -rf agrio.wasmsdk
            pushd bin &> /dev/null
            for binary in ${binaries[@]}; do
               rm ${binary}
            done
            popd &> /dev/null
            break;;

         [Nn]* ) 
            printf "\tAborting uninstall\n\n"
            exit -1;;
      esac
   done
fi
