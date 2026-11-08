#指定cmake最小版本
cmake_minimum_required(VERSION 2.8)

#定义工程名字，也可以包含语言
project(HELLOWORLD)

#添加可执行程序  编译main.cpp生成main
add_executable(helloworld main.cpp)

