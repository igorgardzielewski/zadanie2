cmake_minimum_required(VERSION 3.15)
project(zadanie2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Attempt to locate Ice libraries (C++11 mapping + IceUtil)
find_package(Ice REQUIRED COMPONENTS Ice++11 IceUtil)

add_executable(zadanie2
    system/src/system.cpp
    # Add other .cpp files here
)

# Include and link directories for Ice
include_directories("/opt/homebrew/Cellar/ice/3.7.10/include")
link_directories("/opt/homebrew/Cellar/ice/3.7.10/lib")


# Optionally set the Slice directory (if you need to compile Slice files)
set(Ice_SLICE_DIR "/opt/homebrew/Cellar/ice/3.7.10/share/Ice-3.7.10/slice")

# RPATH settings so the runtime loader can find your libraries
set(CMAKE_BUILD_RPATH "/opt/homebrew/Cellar/ice/3.7.10/lib")
set(CMAKE_INSTALL_RPATH "/opt/homebrew/Cellar/ice/3.7.10/lib")

# Link the C++11 Ice libraries, along with iconv and bz2
target_link_libraries(zadanie2
        PRIVATE
        Ice++11
        IceUtil
        iconv
        bz2
)
