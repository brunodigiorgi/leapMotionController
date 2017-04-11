cmake_minimum_required(VERSION 2.6)
project(LMController CXX)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10)

set(tp_path "third_party")

set(test_path "test")
set(test_files
    ${test_path}/main.cpp
    ${test_path}/LMController_test.cpp
)
set(src_path "src")
set(src_files
    ${src_path}/LMController.cpp
)
set(include_path "include")
set(include_files
    ${include_path}/LMController.h
    ${tp_path}/Leap.h
    ${tp_path}/LeapMath.h
)

# Dependencies

set(ar_libgtest /usr/local/lib/libgtest.a)

# Frameworks

set(include_options
    -I${PROJECT_SOURCE_DIR}/${include_path}/
    -I${PROJECT_SOURCE_DIR}/${tp_path}/
    -I/usr/local/include)

#project compile options
set(project_compile_options
    ${include_options} -std=gnu++11 -stdlib=libc++)

# library target
# **************

# including include_files is not needed, because cmake automatically generate dependencies
# this is only needed for generating Xcode projects including header files
add_library(LMController ${src_files} ${include_files})

target_compile_options(LMController PUBLIC ${project_compile_options}) 

# test
# ****************
add_executable(LMController_test ${test_files})

find_library(dy_libLeap NAMES Leap HINTS ${PROJECT_SOURCE_DIR}/${tp_path}/)

target_compile_options(LMController_test PUBLIC ${project_compile_options} )
target_link_libraries(LMController_test 
    ${dy_libLeap}
    ${ar_libgtest}
    LMController
)

