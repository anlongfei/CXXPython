/* ====================================================
 * #   Copyright (C)2019 All rights reserved.
 * #
 * #   Author        : anlongfei
 * #   File Name     : hello.cpp
 * #   Last Modified : 2019-06-05 14:39
 * #   Describe      :
 * #
 * # ====================================================*/

#include <iostream>
#include <python3.6m/Python.h>
using namespace std;
bool py_init() {
    Py_Initialize();
    return Py_IsInitialized();

}
int main(int argc, char *argv[])
{
    if (py_init()) {
        std::cerr << "python init fail !!!" << std::endl;
        return -1;
    }
    PyRun_SimpleString("print('Hello World!')");
    Py_Finalize();
    return 0;
}

// g++ -lpython3.6m hello.cpp
