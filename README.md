# CXXPython
Embedding Python in CXX


参考：
C++调用Python的API总结（跟python3.6有diff）：https://zhuanlan.zhihu.com/p/25888215
Embedding Python in Another Application：https://docs.python.org/3.6/extending/embedding.html
C++ 调用Python3：https://www.jianshu.com/p/c82fd490ca22
中文参考:https://docs.python.org/zh-cn/3.6/extending/extending.html

安装：
查看源：yum search python3 | grep devel
安装：sudo yum install python36-devel

源码：
源代码：https://github.com/python/cpython
头文件路径：/usr/include/python3.6m路径找头文件。

示例：
api参考：https://docs.python.org/3.6/c-api/index.html
具体实现参考github源码或者头文件
一个实例：https://github.com/anlongfei/CXXPython/tree/master/02
