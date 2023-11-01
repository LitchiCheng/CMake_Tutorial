# 生成库文件，subDirectoryLib库名称，subDirectoryLib.cpp所需要的源文件，默认静态库*.a
#add_library(subDirectoryLib subDirectoryLib.cpp)

# 生成动态库
# add_library(subDirectoryLib SHARED subDirectoryLib.cpp)

# 生成一个静态库包含另一个静态库，但是动态库不能再包含静态库
add_library(subDirectoryLib STATIC subDirectoryLib.cpp)

find_library(THIRD_LIB thirdlib ${PROJECT_SOURCE_DIR}/thirdLib)

target_include_directories(subDirectoryLib PRIVATE
                           ${PROJECT_SOURCE_DIR}/thirdLib
                           )
target_link_libraries(subDirectoryLib PRIVATE
                    ${THIRD_LIB}
                    )