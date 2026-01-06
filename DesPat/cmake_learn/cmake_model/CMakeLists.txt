cmake_minimum_required(VERSION 3.10)
project(SmartApp)

# 1. 定义路径变量 (这就是你之前没看懂的 set 用法)
# 使用变量后，如果 third_party 换了位置，你只改这一行就行
set(MY_LIB_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/third_party/my_lib)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 2. 搜集源文件
aux_source_directory(${SRC_DIR} SRC_FILES)
list(APPEND SRC_FILES main.cpp)

# 3. 创建执行目标
add_executable(SmartApp ${SRC_FILES})

# 4. 高阶点：Target 级配置 (不再使用全局的 include_directories)
# 我们只给 SmartApp 这个目标喂头文件
target_include_directories(SmartApp PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include     # 自己的头文件
    ${MY_LIB_ROOT}/include                  # 第三方库的头文件
)

# 5. 链接第三方库 (模拟你之前代码里的库链接)
# 告诉编译器：SmartApp 运行需要用到 my_lib 这个库
target_link_directories(SmartApp PRIVATE ${MY_LIB_ROOT}/lib)
# 下面这一句其实是写死了
target_link_libraries(SmartApp PRIVATE my_best_math_lib)