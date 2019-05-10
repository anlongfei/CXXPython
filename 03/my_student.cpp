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
    PyObject* pModule = PyImport_ImportModule("stu_test");
    CHECK_POINT(pModule);

    // 4. 模块的字典列表
    PyObject* pDict = PyModule_GetDict(pModule);
    CHECK_POINT(pDict);

    // 5. 应用
    // 5.1 调用函数
    PyObject* pFunHi = PyDict_GetItemString(pDict, "sayhi");
    CHECK_POINT(pFunHi);
    PyObject_CallFunction(pFunHi, "s", "小明");
    // 5.2 C++2Python
        // 获取Person类
    PyObject* pClassPerson = PyDict_GetItemString(pDict, "Person");
    CHECK_POINT(pClassPerson);
        // 构造Person的实例
    PyObject* person_args = Py_BuildValue("ssi", "小明", "男", 30);
    PyObject* pInstancePerson = PyObject_CallObject(pClassPerson, person_args);
        //  调用类中函数
    PyObject_CallMethod(pClassPerson, "speak", "O", pInstancePerson); // 参考：https://blog.csdn.net/yiyouxian/article/details/51995029

        // 调用introduce函数，参数是Persion对象
    PyObject* pFunIntro = PyDict_GetItemString(pDict, "introduce");
    CHECK_POINT(pFunIntro);
    PyObject_CallFunction(pFunIntro, "O", pInstancePerson);

    // 5.3 Python2C++
    PyObject* pClassPersonFac = PyDict_GetItemString(pDict, "PersonFactory");
    CHECK_POINT(pClassPersonFac);
    PyObject* pInstancePersonFac = PyObject_CallObject(pClassPersonFac, NULL);
    CHECK_POINT(pInstancePersonFac);
    PyObject* result = PyObject_CallMethod(pClassPersonFac, "getOnPerson", "O", pInstancePersonFac);
    CHECK_POINT(result); // TODO how to deal with result, i have no idea ...

   // // 6. 结束
    Py_DECREF(pModule);
    Py_DECREF(pDict);
    Py_DECREF(pFunHi);
    Py_DECREF(pClassPerson);
    Py_DECREF(person_args);
    Py_DECREF(pInstancePerson);
    Py_DECREF(pFunIntro);
    Py_DECREF(pClassPersonFac);
    Py_DECREF(pInstancePersonFac);
    Py_DECREF(result);
    Py_Finalize();
    return 0;
}

