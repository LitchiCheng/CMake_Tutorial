# 生成库文件，subDirectoryLib库名称，subDirectoryLib.cpp所需要的源文件，默认静态库*.a
#add_library(subDirectoryLib subDirectoryLib.cpp)

# 生成动态库
add_library(subDirectoryLib3 SHARED subDirectoryLib3.cpp)

# 生成静态库
#add_library(subDirectoryLib STATIC subDirectoryLib.cpp)