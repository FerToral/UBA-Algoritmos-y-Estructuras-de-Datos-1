cmake_minimum_required(VERSION 3.13)
project(tpi)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(ENABLE_COVERAGE "Instrumentar cobertura con GCC o Clang" OFF)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencias/googletest" "${CMAKE_CURRENT_BINARY_DIR}/googletest")
include_directories("../../Dependencias/googletest/googletest/include")

set(DIR_TESTS_EN "")
file(GLOB DIR_TESTS_GRP CONFIGURE_DEPENDS "testGrupo/*.cpp")

set(SOURCE_FILES main.cpp
        auxiliares.cpp
        ejercicios.cpp)

add_executable(tpi ${SOURCE_FILES}
        ${DIR_TESTS_EN}
        ${DIR_TESTS_GRP}
        )

if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(tpi PRIVATE -g --coverage)
    target_link_options(tpi PRIVATE --coverage)
endif()

target_link_libraries(tpi gtest gtest_main)

enable_testing()
add_test(NAME tp_implementacion COMMAND tpi)
set_tests_properties(tp_implementacion PROPERTIES
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
