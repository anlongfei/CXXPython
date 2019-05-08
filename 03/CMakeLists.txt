cmake_minimum_required(VERSION 2.8)

#2.project name，指定项目的名称，一般和项目的文件夹名称对应
PROJECT(test)

set(CMAKE_CXX_FLAGS "-O0 -std=c++11 -g -w -pthread -Wl,--export-dynamic -Wno-deprecated")

#3.head file path，头文件目录
INCLUDE_DIRECTORIES(
"${PROJECT_SOURCE_DIR}/include"
)

#4.source directory，源文件目录
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/include/gen-cpp/ GEN_SRCS)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/ TEST_SRCS)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#5.set environment variable，设置环境变量，编译用到的源文件全部都要放到这里，否则编译能够通过，但是执行的时候会出现各种问题，比如"symbol lookup error xxxxx , undefined symbol"
SET(TEST_MATH
${TEST_SRCS}
${GEN_SRCS}
)

#6.add executable file，添加要编译的可执行文件
ADD_EXECUTABLE(${PROJECT_NAME} ${TEST_MATH})
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    thrift
    python3.6m
)
