cmake_minimum_required(VERSION 3.20)
project(408_DataStructureExercises)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)

# 递归扫描当前项目目录下所有的 .cpp 文件
# 注意：这会扫描所有子目录。如果有不需要编译为独立可执行文件的辅助库文件，请不要以 .cpp 结尾，或将其排除。
file(GLOB_RECURSE CPP_FILES "*.cpp")

# 遍历找到的每一个 .cpp 文件
foreach(FILE ${CPP_FILES})
    # 获取文件名（不带扩展名），例如 "seq_list_static"
    get_filename_component(TARGET_NAME ${FILE} NAME_WE)

    # 获取文件所在的目录名，以防不同目录下有同名文件导致目标冲突
    get_filename_component(DIR_PATH ${FILE} DIRECTORY)
    get_filename_component(DIR_NAME ${DIR_PATH} NAME)

    # 拼接目标名称：目录名_文件名，例如 "ch02_linear_list_seq_list_static"
    set(FULL_TARGET_NAME "${DIR_NAME}_${TARGET_NAME}")

    # 为该文件创建一个独立的可执行目标
    add_executable(${FULL_TARGET_NAME} ${FILE}
            ch02_linear_list/seq_list_static.cpp)
endforeach()