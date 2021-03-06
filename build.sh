#! /bin/bash

printf "\t=========== Building agrio.cdt ===========\n\n"

RED='\033[0;31m'
NC='\033[0m'
txtbld=$(tput bold)
bldred=${txtbld}$(tput setaf 1)
txtrst=$(tput sgr0)

export DISK_MIN=10
export TEMP_DIR="/tmp"
TEMP_DIR='/tmp'
DISK_MIN=10

unamestr=`uname`
if [[ "${unamestr}" == 'Darwin' ]]; then
   BOOST=/usr/local
   CXX_COMPILER=g++
   export ARCH="Darwin"
   bash ./scripts/agrio_build_darwin.sh
else
   OS_NAME=$( cat /etc/os-release | grep ^NAME | cut -d'=' -f2 | sed 's/\"//gI' )

   case "$OS_NAME" in
      "Amazon Linux AMI")
         export ARCH="Amazon Linux AMI"
         bash ./scripts/agrio_build_amazon.sh
         ;;
      "CentOS Linux")
         export ARCH="Centos"
         export CMAKE=${HOME}/opt/cmake/bin/cmake
         bash ./scripts/agrio_build_centos.sh
         ;;
      "elementary OS")
         export ARCH="elementary OS"
         bash ./scripts/agrio_build_ubuntu.sh
         ;;
      "Fedora")
         export ARCH="Fedora"
         bash ./scripts/agrio_build_fedora.sh
         ;;
      "Linux Mint")
         export ARCH="Linux Mint"
         bash ./scripts/agrio_build_ubuntu.sh
         ;;
      "Ubuntu")
         export ARCH="Ubuntu"
         bash ./scripts/agrio_build_ubuntu.sh
         ;;
      "Debian GNU/Linux")
         export ARCH="Debian"
	 bash ./scripts/agrio_build_ubuntu.sh
	 ;;
      *)
         printf "\\n\\tUnsupported Linux Distribution. Exiting now.\\n\\n"
         exit 1
   esac
fi

if [[ `uname` == 'Darwin' ]]; then
   FREE_MEM=`vm_stat | grep "Pages free:"`
   read -ra FREE_MEM <<< "$FREE_MEM"
   FREE_MEM=$((${FREE_MEM[2]%?}*(4096))) # free pages * page size
else
   FREE_MEM=`LANG=C free | grep "Mem:" | awk '{print $4}'`
fi

CORES_AVAIL=`getconf _NPROCESSORS_ONLN`
MEM_CORES=$(( ${FREE_MEM}/4000000 )) # 4 gigabytes per core
MEM_CORES=$(( $MEM_CORES > 0 ? $MEM_CORES : 1 ))
CORES=$(( $CORES_AVAIL < $MEM_CORES ? $CORES_AVAIL : $MEM_CORES ))

#check submodules
if [ $(( $(git submodule status --recursive | grep -c "^[+\-]") )) -gt 0 ]; then
   printf "\\n\\tgit submodules are not up to date.\\n"
   printf "\\tPlease run the command 'git submodule update --init --recursive'.\\n"
   exit 1
fi

mkdir -p build
pushd build &> /dev/null

if [ -z "$CMAKE" ]; then
  CMAKE=$( command -v cmake )
fi

"$CMAKE" -DCMAKE_INSTALL_PREFIX=/usr/local/agrio.cdt ../
if [ $? -ne 0 ]; then
   exit -1;
fi
make -j${CORES}
if [ $? -ne 0 ]; then
   exit -1;
fi
popd &> /dev/null

printf "\n\n${bldred}\t _______  _______  _______ _________ _______ \n"
printf '\t(  ___  )(  ____ \(  ____ )\__   __/(  ___  )\n'
printf '\t| (   ) || (    \/| (    )|   ) (   | (   ) |\n'
printf '\t| (___) || |      | (____)|   | |   | |   | |\n'
printf '\t|  ___  || | ____ |     __)   | |   | |   | |\n'
printf '\t| (   ) || | \_  )| (\ (      | |   | |   | |\n'
printf '\t| )   ( || (___) || ) \ \_____) (___| (___) |\n'
printf "\t|/     \\|(_______)|/   \\__/\\_______/(_______)\n\n${txtrst}"

printf "\\tFor more information:\\n"
printf "\\tAGRIO website: https://www.aggregion.com\\n"
printf "\\tAGRIO Telegram channel @ https://t.me/aggregion\\n"

