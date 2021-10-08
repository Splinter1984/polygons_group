#! /bin/sh

if [[ $OSTYPE == "msys" ]]; then
    source_dir=$(pwd)
    current_folder=$(pwd | grep -o '[^/]*$')
    if [[ $current_folder == "script" ]]; then
        cd ../
    fi
    cmake -E make_directory build
    cd build
    cmake .. -G 'MinGW Makefiles' && mingw32-make

elif [[ `$OSTYPE` == "linux-gnu" ]]; then
    source_dir=$(pwd)
    current_folder=$(pwd | grep -o '[^/]*$')
    if [[ $current_folder == "script" ]]; then
        cd ../
    fi
    cmake -E make_directory build
    cd build && cmake .. && make

fi