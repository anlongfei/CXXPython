/* ====================================================
 * #   Copyright (C)2019 All rights reserved.
 * #
 * #   Author        : anlongfei
 * #   File Name     : my_student.cpp
 * #   Last Modified : 2019-06-05 14:39
 * #   Describe      :
 * #
 * # ====================================================*/

#include <iostream>
#include <python3.6m/Python.h>
#include <thrift/Thrift.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TTransport.h>
#include <thrift/transport/TBufferTransports.h>
#include "gen-cpp/stu_types.h"
using namespace std;

template <typename T>
std::string serializeToString(const T& r) {
    boost::shared_ptr<apache::thrift::transport::TMemoryBuffer> buffer(new apache::thrift::transport::TMemoryBuffer);
    boost::shared_ptr<apache::thrift::protocol::TBinaryProtocol> protocol(new apache::thrift::protocol::TBinaryProtocol(buffer));
    r.write(protocol.get());
    return buffer->getBufferAsString();
}

#define CHECK_POINT(ptr) \
    if (ptr == nullptr) { \
        std::cerr << "error !!! "<<  __FILE__ << ":" << __LINE__ << " "<< #ptr << " is nullptr !!!" << std::endl; \
        return -1; \
    }

bool py_init() {
    Py_Initialize();
    return Py_IsInitialized();

}

int main(int argc, char *argv[]) {
    // 1. 初始化python环境
    if (!py_init()) {
        std::cerr << "python init fail !!!" << std::endl;
        return -1;
    }

    PyObject *pName, *pModule;

    // 2. 导入系统模块
    if (PyRun_SimpleString("import sys") != 0) { // 导入系统模块
        std::cerr << "error !!! "<<  __FILE__ << ":" << __LINE__ << " " << "PyRun_SimpleString fail !!!" << std::endl;
        return -1;
    }

    // 3. 导入自定义模块
    if (PyRun_SimpleString("sys.path.append('./py')") != 0) { // 指定自定义calculate模块目录
        std::cerr << "error !!! "<<  __FILE__ << ":" << __LINE__ << " " << "PyRun_SimpleString fail !!!" << std::endl;
        return -1;
    }
    pModule = PyImport_ImportModule("stu_test");
    CHECK_POINT(pModule);

    // 4. 引入函数、构造参数
    PyObject *pfunc, *args, *results;
    pfunc= PyObject_GetAttrString(pModule, "print_stu"); //pModule是上一步load好的Python模块
    CHECK_POINT(pfunc);

    // ref: https://docs.python.org/3.6/extending/extending.html?highlight=py_buildvalue
    pytest::Student s1;
    s1.name = "anlongfei";
    s1.sex = "male";
    const std::string serialize_string = serializeToString(s1);
    //std::cout << "serializeToString s1 : " << serialize_string  << " size: " << serialize_string.size() << std::endl;

    //args = Py_BuildValue("s", serialize_string); //设置调用func时的输入变量，这里假设为123,456 ; 
    args = Py_BuildValue("is", 12, serialize_string.c_str());
    CHECK_POINT(args);

    // 5. 函数调用，处理结果
    //PyObject_CallFunction(pfunc, "s", args);
    //PyObject_CallFunctionObjArgs(pfunc, args); // 自定义函数调用
    PyObject_CallObject(pfunc, args); // 自定义函数调用
    //CHECK_POINT(results);
    //std::cout << PyLong_AsLong(results) << std::endl;;

    // 6. 结束
    Py_DECREF(pfunc);
    Py_Finalize();
    return 0;
}

// g++ -I./include -lpython3.6m my_student.cpp -O0 -std=c++11

