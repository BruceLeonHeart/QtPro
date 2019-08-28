cmake_minimum_required(VERSION 2.8)

project(ALGS)
add_executable(${PROJECT_NAME} "chinesenum.cpp")
#add_executable(${PROJECT_NAME} "funtest.cpp")
#add_executable(${PROJECT_NAME} "main.cpp")
#搜索所有文件并存储在变量中
aux_source_directory(. SRC_LIST)
