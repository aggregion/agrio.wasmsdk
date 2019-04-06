#! /bin/bash

NAME=$1
CDT_PREFIX=${PREFIX}/${SUBPREFIX}
mkdir -p ${PREFIX}/bin/
mkdir -p ${PREFIX}/lib/cmake/${PROJECT}
mkdir -p ${CDT_PREFIX}/bin 
mkdir -p ${CDT_PREFIX}/include
mkdir -p ${CDT_PREFIX}/lib/cmake/${PROJECT}
mkdir -p ${CDT_PREFIX}/cmake
mkdir -p ${CDT_PREFIX}/scripts
mkdir -p ${CDT_PREFIX}/licenses

#echo "${PREFIX} ** ${SUBPREFIX} ** ${CDT_PREFIX}"

# install binaries 
cp -R ${BUILD_DIR}/bin/* ${CDT_PREFIX}/bin 
cp -R ${BUILD_DIR}/licenses/* ${CDT_PREFIX}/licenses

# install cmake modules
sed "s/_PREFIX_/\/${SPREFIX}/g" ${BUILD_DIR}/modules/AgrioCDTMacrosPackage.cmake &> ${CDT_PREFIX}/lib/cmake/${PROJECT}/AgrioCDTMacros.cmake
sed "s/_PREFIX_/\/${SPREFIX}/g" ${BUILD_DIR}/modules/AgrioWasmToolchainPackage.cmake &> ${CDT_PREFIX}/lib/cmake/${PROJECT}/AgrioWasmToolchain.cmake
sed "s/_PREFIX_/\/${SPREFIX}\/${SSUBPREFIX}/g" ${BUILD_DIR}/modules/${PROJECT}-config.cmake.package &> ${CDT_PREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake

# install scripts
cp -R ${BUILD_DIR}/scripts/* ${CDT_PREFIX}/scripts 

# install misc.
cp ${BUILD_DIR}/agrio.imports ${CDT_PREFIX}

# install wasm includes
cp -R ${BUILD_DIR}/include/* ${CDT_PREFIX}/include

# install wasm libs
cp ${BUILD_DIR}/lib/*.a ${CDT_PREFIX}/lib

# make symlinks
pushd ${PREFIX}/lib/cmake/${PROJECT} &> /dev/null
ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake ${PROJECT}-config.cmake
ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/AgrioWasmToolchain.cmake AgrioWasmToolchain.cmake
ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/AgrioCDTMacros.cmake AgrioCDTMacros.cmake
popd &> /dev/null

create_symlink() {
   pushd ${PREFIX}/bin &> /dev/null
   ln -sf ../${SUBPREFIX}/bin/$1 $2
   popd &> /dev/null
}

create_symlink "agrio-cc agrio-cc"
create_symlink "agrio-cpp agrio-cpp"
create_symlink "agrio-ld agrio-ld"
create_symlink "agrio-pp agrio-pp"
create_symlink "agrio-init agrio-init"
create_symlink "agrio-abigen agrio-abigen"
create_symlink "agrio-wasm2wast agrio-wasm2wast"
create_symlink "agrio-wast2wasm agrio-wast2wasm"

tar -cvzf $NAME ./${PREFIX}/*
rm -r ${PREFIX}
