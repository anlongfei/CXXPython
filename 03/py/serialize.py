#! /usr/bin/env python
# -*- coding: utf-8 -*-

import sys
sys.path.append('../include/gen-py')

from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from pytest.ttypes import *

def serialize(th_obj):
    tmembuf = TTransport.TMemoryBuffer()
    tbinprot = TBinaryProtocol.TBinaryProtocol(tmembuf)
    th_obj.write(tbinprot)
    return tmembuf.getvalue()

def deserialize(val, th_obj_type):
    th_obj = th_obj_type()
    tmembuf = TTransport.TMemoryBuffer(val)
    tbinprot = TBinaryProtocol.TBinaryProtocol(tmembuf)
    th_obj.read(tbinprot)
    return th_obj

if __name__ == '__main__':
    stu = Student('anlongfei',"male")
    print(stu.name, stu.sex)
    val = serialize(stu)
    print(val)
    stu.name = "li"
    stu.sex = "female"
    stu2 = deserialize(val, Student)
    print(stu2.name, stu2.sex)

