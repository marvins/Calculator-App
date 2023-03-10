#!/bin/sh

#  Globals
DO_CLEAN=0
DO_BUILD=0
BUILD_TYPE='release'
NUM_THREADS=1

ARG_SET=0
ARG_THREADS=0

Clean_Software()
{
    echo "Cleaning Software.  Type: ${BUILD_TYPE}"

    if [ -e "${BUILD_TYPE}" ]; then
        rm -rvf "${BUILD_TYPE}"
    fi
}

Build_Software()
{
    echo "Building Software"

    mkdir -p ${BUILD_TYPE}

    cd ${BUILD_TYPE}

    if [ "${BUILD_TYPE}" = 'debug' ]; then
        CMAKE_FLAGS="${CMAKE_FLAGS} -DCMAKE_BUILD_TYPE=Debug"
    fi

    echo 'Running CMake'
    cmake ${CMAKE_FLAGS} ..
    RES="$?"
    echo "CMake result: ${RES}"
    if [ ! "$RES" = '0' ]; then
        echo "error running CMake" 
        exit ${RES}
    fi

    echo 'Running Make'
    make -j ${NUM_THREADS}
    RES="$?"
    echo "make result: ${RES}"
    if [ ! "$RES" = '0' ]; then
        echo "error running make" 
        exit ${RES}
    fi

    cd ..
}


for ARG in "$@"; do
    case $ARG in
        
        #  Clean the build
        -c)
            DO_CLEAN=1
            ;;
        
        #  Perform the build
        -m)
            DO_BUILD=1
            ;;

        #  Number threads set
        -j)
            THREADS_SET=1
            NUM_THREADS=''
            ;;

        --debug)
            BUILD_TYPE=debug
            ;;

        *)
            if [ "${THREADS_SET}" = 1 ]; then
                THREADS_SET=0
                NUM_THREADS=${ARG}
            else
                echo "error: Unsupported flag (${ARG})"
            fi

    esac
done

#  Clean
if [ "$DO_CLEAN" = '1' ]; then
    Clean_Software
fi

#  Build
if [ "${DO_BUILD}" = '1' ]; then
    Build_Software
fi
