# 最低版本
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(cmake_learn)

# 1.添加当前目录源文件
# add_executable(hello hello.cpp)

# 2.！--如果说当前目录下源文件非常多--！
# (1) 搜集当前目录下所有的源文件，并将列表储存在变量 DIR_SRCS 中
aux_source_directory(. DIR_SRCS)

add_executable(exe_name ${DIR_SRCS})

# 3.源文件和头文件分开放
# .
# ├── CMakeLists.txt
# ├── main.cpp
# ├── src/           # 存放 .cpp
# │   ├── a.cpp
# │   └── b.cpp
# └── include/       # 存放 .h
#     ├── a.h
#     └── b.h
include_directories(include)
aux_source_directory(. DIR_Main)
aux_source_directory(src DIR_Src)
add_executable(exeName ${DIR_Main} ${DIR_Src})



# 4.多个文件夹，并且每个文件夹都有头文件和源文件
# main.cpp (在根目录)
# module1/ (里面有 1.cpp 和 1.h)
# module2/ (里面有 2.cpp 和 2.h)
# --- 第一步：找源文件（存入变量） ---
aux_source_directory(. DIR_ROOT)    # 在当前目录拿到 main.cpp
aux_source_directory(module1 DIR_1) # 去module1 拿到DIR_1
aux_source_directory(module2 DIR_2) # 去module2 拿到DIR_2

# --- 第二步：设置头文件搜索路径（直接添加目录） ---
# 这样你在 main.cpp 里写 #include "1.h" 时，编译器就知道去 module1 文件夹找
include_directories(. module1 module2)

# --- 第三步：生成程序（把所有源文件变量倒出来） ---
add_executable(my_app ${DIR_ROOT} ${DIR_1} ${DIR_2})