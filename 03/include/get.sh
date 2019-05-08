#!/bin/bash
rm -rf gen*
thrift -r --gen cpp stu.thrift
thrift -r --gen py stu.thrift
