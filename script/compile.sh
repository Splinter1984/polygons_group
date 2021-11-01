#! /bin/sh

project_dir="polygons_group"
source_dir=$(pwd)
current_folder=$(pwd | grep -o '[^/]*$')

if [[ $current_folder == "script" ]]; then
    cd ../
elif [[ $current_folder != $project_dir ]]; then
    echo -e "\033[1;31m[ERROR]\033[0m: move file \033[100m${0##*/}\033[49m to the root of the project or '$project_dir/scripts' folder "
    exit 1
fi

if [[ $OSTYPE == "msys" ]]; then
    cmake -E make_directory build
    cd build
    cmake .. -G 'MinGW Makefiles' && mingw32-make
elif [[ `$OSTYPE` == "linux-gnu" ]]; then
    cmake -E make_directory build
    cd build && cmake .. && make
fi
