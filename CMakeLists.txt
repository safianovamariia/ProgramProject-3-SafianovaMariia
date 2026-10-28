cmake_minimum_required(VERSION 3.20)
project(pp3 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/W3)
    add_compile_options(/EHsc)
    add_compile_options(/utf-8)
else()
    add_compile_options(-Wall)
    add_compile_options(-fexceptions)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

add_executable(CPP_PP_3
    main.cpp
)
