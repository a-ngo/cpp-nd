# cpp-nd
Udacity C++ nanodegree

## Part One

- Lecture one
- Project 1: Open Street Map Route Planner
    - install IO2D
    ```
    sudo apt update
    sudo apt install build-essential
    sudo apt install cmake
    sudo apt install libcairo2-dev
    sudo apt install libgraphicsmagick1-dev
    sudo apt install libpng-dev

    git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
    cd P0267_RefImpl
    mkdir Debug
    cd Debug
    cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" ..
    cmake --build .
    sudo make install # this will copy the necessary files at places where Cmake can find them
    ```