#!/bin/bash
# ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : anlongfei
#   Email         : 在 vimrc 文件中添加 let g:file_copyright_email = 'your email'
#   File Name     : build.sh
#   Last Modified : 2019-05-07 22:59
#   Describe      :
#
# ====================================================
cd include
sh get.sh
cd -
mkdir -p build
cd build && \
    cmake .. && \
    make -j8
