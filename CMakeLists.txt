cmake_minimum_required(VERSION 3.26)
project(allocator)

set(CMAKE_CXX_STANDARD 17)

add_executable(allocator main.cpp
        allocator.cpp
        template.cpp
        fullSpecialize.cpp
        sharedPtr.cpp
        minimum.cpp
        minimum.cpp
        flatten.cpp
        scopedPtr.cpp
        proxy.cpp
        array.cpp
        templateMethods.cpp
        Any.cpp)
