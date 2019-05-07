/* ====================================================
 * #   Copyright (C)2019 All rights reserved.
 * #
 * #   Author        : anlongfei
 * #   File Name     : my_add.cpp
 * #   Last Modified : 2019-06-05 14:39
 * #   Describe      :
 * #
 * # ====================================================*/

#include <iostream>
#include <python3.6m/Python.h>
using namespace std;
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
    if (!py_init()) {
        std::cerr << "python init fail !!!" << std::endl;
        return -1;
    }

    PyObject *pName, *pModule;

    if (PyRun_SimpleString("import sys") != 0) { // 导入系统模块
        std::cerr << "error !!! "<<  __FILE__ << ":" << __LINE__ << " " << "PyRun_SimpleString fail !!!" << std::endl;
        return -1;
    }

    if (PyRun_SimpleString("sys.path.append('./py')") != 0) { // 指定calculate.py所在的目录
        std::cerr << "error !!! "<<  __FILE__ << ":" << __LINE__ << " " << "PyRun_SimpleString fail !!!" << std::endl;
        return -1;
    }
    // 这种方法失败了
    //pName = PyBytes_FromString("calculate"); // 指定要导入的文件名
    //CHECK_POINT(pName);
    // pModule = PyImport_Import(pName); //将pytest.py导入模块指针pModule
    // pModule is nullptr

    pModule = PyImport_ImportModule("calculate");
    CHECK_POINT(pModule);

    PyObject *pfunc, *args, *results;
    pfunc= PyObject_GetAttrString(pModule, "my_add"); //pModule是上一步load好的Python模块
    CHECK_POINT(pfunc);

    // ref: https://docs.python.org/3.6/extending/extending.html?highlight=py_buildvalue
    args = Py_BuildValue("ii",123, 456); //设置调用func时的输入变量，这里假设为123,456 ; 
    CHECK_POINT(args);
    results= PyObject_CallObject(pfunc, args);
    CHECK_POINT(results);
    cout << PyLong_AsLong(results) << std::endl;;

    PyRun_SimpleString("print('Hello World!')");
    Py_Finalize();
    return 0;
}

// g++ -lpython3.6m my_add.cpp -O0 -std=c++11
