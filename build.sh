#!/bin/bash

checkabortfailed()
{
    if [ $1 -eq 0 ]
    then
      echo "INFO: Step finished successfully"
    else
      echo "ERROR: An error occurred. aborting..."
      exit 1
    fi
}

get_cur_dir() {
    SOURCE="${BASH_SOURCE[0]}"

    # resolve $SOURCE until the file is no longer a symlink
    while [ -h "$SOURCE" ]; do
      DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
      SOURCE="$(readlink "$SOURCE")"
      # if $SOURCE was a relative symlink, we need to resolve it relative to
      # the path where the symlink file was located
      [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE"
    done
    DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
}

get_cur_dir

#######################################################################
## parameters to collect from the user
## 1. OS (Ubuntu, Windows)
## 2. Build Type (Debug, Release)
#######################################################################
BUILD_TYPE="release"
TARGET_OS="ubuntu"
unamestr=`uname`
if [[ "$unamestr" == 'Linux' ]]; then
   TARGET_OS="ubuntu"
elif [[ "$unamestr" == *"MINGW"* ]]; then
   TARGET_OS="windows"
fi

usage() { echo "Usage: $0 [-b <debug/release> ] [-t <ubuntu/windows>]" 1>&2; exit 1; }

while getopts ":b:t:" o; do
    case "${o}" in
        b)
			BUILD_TYPE="${OPTARG}"
            ;;
        t)
			TARGET_OS="${OPTARG}"
            ;;
        *)
            usage
            ;;
    esac
done

BUILD_DIR="${DIR}/build-${TARGET_OS}-${BUILD_TYPE}"
echo "TARGET_OS=[${TARGET_OS}]"
echo "BUILD_TYPE=[${BUILD_TYPE}]"

################################################
echo "Remove old builds"
rm -rf ${BUILD_DIR}
mkdir -p ${BUILD_DIR}

################################################
# Case 1: Standalone build with inidividual dependencies
################################################
if [ "${TARGET_OS}" == "ubuntu" ]
then
  pushd ${BUILD_DIR}
	echo "INFO: Build for [${TARGET_OS}]"
	cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
           -DGLFW_DIR=${GLFW_DIR} \
	checkabortfailed $?

  echo "INFO: Count number of CPU cores on this machine"
  CPU_CORES_COUNT=`grep -c ^processor /proc/cpuinfo`
  echo "INFO: There are [${CPU_CORES_COUNT}] processor cores in this machine"

	echo "INFO: Build project"
	make -j${CPU_CORES_COUNT}
	checkabortfailed $?

  ## make install
	echo "INFO: make install the project"
	make install
	checkabortfailed $?
  sync

  popd

elif [ "${TARGET_OS}" == "windows" ]
then
    pushd ${BUILD_DIR}
    CPU_CORES_COUNT=${NUMBER_OF_PROCESSORS}

    echo "Build for ${TARGET_OS}"
    ##cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -G "Visual Studio 14 2015 Win64" ..
    cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -G "Visual Studio 15 2017 Win64" ..
    checkabortfailed $?

    echo "Add MSBuild to path"
    ##export PATH="C:\Program Files (x86)\MSBuild\14.0\Bin":$PATH
    export PATH="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin":$PATH
    MSBuild.exe *.sln /maxcpucount:${CPU_CORES_COUNT}
    checkabortfailed $?

    popd
else
	echo "ERROR: unsupported OS ${TARGET_OS}"
	exit 1
fi
