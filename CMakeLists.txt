cmake_minimum_required(VERSION 3.16)
project(408_DataStructureExercises)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 公共头文件目录
include_directories(${CMAKE_SOURCE_DIR}/common)

# 递归扫描当前项目目录下所有的 .cpp 文件（排除 common 目录下的辅助文件）
file(GLOB_RECURSE CPP_FILES
    "ch*/*.cpp"
)

# 遍历找到的每一个 .cpp 文件，为每个文件创建独立可执行目标
foreach(FILE ${CPP_FILES})
    # 获取文件名（不带扩展名），例如 "seq_list_static"
    get_filename_component(TARGET_NAME ${FILE} NAME_WE)

    # 获取文件所在的目录名，以防不同目录下有同名文件导致目标冲突
    get_filename_component(DIR_PATH ${FILE} DIRECTORY)
    get_filename_component(DIR_NAME ${DIR_PATH} NAME)

    # 拼接目标名称：目录名_文件名，例如 "ch02_linear_list_seq_list_static"
    set(FULL_TARGET_NAME "${DIR_NAME}_${TARGET_NAME}")

    # 为该文件创建一个独立的可执行目标（每个 .cpp 自包含 main 函数）
    add_executable(${FULL_TARGET_NAME} ${FILE})

    # 为 CLion 的 "Run" 按钮设置默认启动项提示
    # 可执行文件输出到 build/bin 下，方便查找
    set_target_properties(${FULL_TARGET_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endforeach()
