# 使用CMake的最低版本号
cmake_minimum_required(VERSION 3.15)

# 内置变量
# ${PROJECT_BINARY_DIR}当前cmake构建的目录
# ${PROJECT_SOURCE_DIR}顶级CMakeLists的文件目录
# ${PROJECT_NAME}可以取到当前设置的项目名称 
# ${CMAKE_CURRENT_SOURCE_DIR}当前CMakeLists文件目录
# 调试输出
# message("current dir ${CMAKE_CURRENT_SOURCE_DIR}") cmake时输出当前信息

# 设置项目名称
#project(CMake_Tutorial)

# 设置项目名称和版本VERSION，@PROJECT_VERSION_MAJOR@被替换成1，@PROJECT_VERSION_MAJOR@被替换成0，@PROJECT_VERSION_PATCH@被替换成1
project(CMake_Tutorial VERSION 1.0.1)

# 编译的时间戳， @PROJECT_VERSION_PATCH@被替换成编译时间
string(TIMESTAMP COMPILE_TIME %Y%m%d%H%M%S)

# 版本号和编译时间戳通过*.h.in文件生成.h头文件供其他代码使用，生成目录默认cmake目录
configure_file(config.h.in ProjConfig.h)

# 指定C++标准，11就是C++11，CMAKE_CXX_STANDARD_REQUIRED为True需要再add_executable之前
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加子目录，该目录下包含库文件和源文件，多个子目录，需要多次添加，第二个参数是生成二进制的目录
# add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
add_subdirectory(subDirectoryLib)

# 添加一个选项，变量USE_SUB_DIRECTORY_LIB2默认打开，“”是描述，该变量会加载到缓存中，方便构建
option(USE_SUB_DIRECTORY_LIB2 "Use sub directory lib" ON)
# 根据选项进行
if(USE_SUB_DIRECTORY_LIB2)
    message("USE_SUB_DIRECTORY_LIB2!")
    #添加编译参数，否则程序无法读到该变量
    add_definitions(-DUSE_SUB_DIRECTORY_LIB2)
    #添加子目录
    add_subdirectory(subDirectorySharedLib) 

    # list (LENGTH <list> <output variable>) 
        # 子命令LENGTH用于读取列表长度，<output variable>为新创建的变量，用于存储列表的长度。
    # list (GET <list> <element index> [<element index> ...] <output variable>) 
        # 子命令GET用于读取列表中指定索引的的元素，可以指定多个索引，
        # <element index>为列表元素的索引，从0开始编号，索引0的元素为列表中的第一个元素；索引也可以是负数，-1表示列表的最后一个元素，-2表示列表倒数第二个元素，以此类推
        # <output variable>为新创建的变量，存储指定索引元素的返回结果，也是一个列表
    # list (JOIN <list> <glue> <output variable>) 
        # 子命令JOIN用于将列表中的元素用连接字符串连接起来组成一个字符串，注意，此时返回的结果已经不是一个列表
        # 将列表中的元素用<glue>链接起来，组成一个字符串后，返回给<output variable>变量。对于不属于列表的多个字符串的连接操作，可以使用string()命令的连接操作
    # list (SUBLIST <list> <begin> <length> <output variable>)
        # 子命令SUBLIST用于获取列表中的一部分（子列表）
        # 返回列表<list>中，从索引<begin>开始，长度为<length>的子列表。如果长度<length>为0，返回的时空列表
    # list (FIND <list> <value> <output variable>)
        # 子命令FIND用于查找列表是否存在指定的元素
        # 如果列表<list>中存在<value>，那么返回<value>在列表中的索引，如果未找到则返回-1
    # list (APPEND <list> [<element> ...])
        # 子命令APPEND用于将元素追加到列表
    # list (FILTER <list> <INCLUDE|EXCLUDE> REGEX <regular_expression>)
        # 子命令FILTER用于根据正则表达式包含或排除列表中的元素
        # 根据模式的匹配结果，将元素添加（INCLUDE选项）到列表或者从列表中排除（EXCLUDE选项）。此命令会改变原来列表的值。模式REGEX表明会对列表进行正则表达式匹配
    # list (INSERT <list> <element_index> <element> [<element> ...])
        # 子命令INSERT用于在指定位置将元素（一个或多个）插入到列表中
        # <element_index>为列表指定的位置，如果元素的位置超出列表的范围，会报错。此命令会改变原来列表的值
    # list (POP_BACK <list> [<out-var>...])
        # 子命令POP_BACK用于将列表中最后元素移除
        # <out-var>如果未指定输出变量，则仅仅是将原列表的最后一个元素移除。如果指定了输出变量，则会将最后一个元素移入到该变量，并将元素从原列表中移除
    # list还有很多其他方法，参考https://www.jianshu.com/p/89fb01752d6f

    # 将subDirectorySharedLib目录追加到EXTRA_INCLUDES列表中
    list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/subDirectorySharedLib)

    # 将subDirectorySharedLib追加到EXTRA_LIBS列表中
    list(APPEND EXTRA_LIBS subDirectorySharedLib)
    
endif()

# 添加可执行的程序，需要指定生成可执行文件的名称和相关源文件
#add_executable(${PROJECT_NAME} CMake_Tutorial_main.cpp)

# 如果有多个源文件，那么就用空格隔开
#add_executable(${PROJECT_NAME} test1.cpp test2.cpp)

# 也可以用变量来表示多个源文件
set(SRCS CMake_Tutorial_main.cpp test1.cpp test2.cpp)
add_executable(${PROJECT_NAME} ${SRCS})

add_subdirectory(${PROJECT_SOURCE_DIR}/subDirectoryLib3)

# 构建依赖于第三方库/系统库, 搜索第三方库文件thirdlib，存到FIND_LIBRARY变量中，第二个参数时库名称，第三个参数时库所在的目录
#find_library(FIND_LIBRARY thirdlib thirdlib_path)

message("EXTRA_LIBS:${EXTRA_LIBS}")
message("EXTRA_INCLUDES:${EXTRA_INCLUDES}")

# INTERFACE表示只有可执行程序需要include，PRIVATE表示只有当前的库需要include，PUBLIC表示库还是可执行程序都需要include
# 当在子目录的CMakeLists.txt中添加了INTERFACE类型的目录，顶级目录中就可以删除

# 添加目录到搜索头文件的路径列表中
target_include_directories(${PROJECT_NAME} PUBLIC
                           ${PROJECT_BINARY_DIR}
                           ${PROJECT_SOURCE_DIR}/subDirectoryLib
                           ${PROJECT_SOURCE_DIR}/subDirectoryLib3
                           ${EXTRA_INCLUDES}
                           ${thirdlib}
                           )

# 指定可执行文件要使用的库文件
target_link_libraries(${PROJECT_NAME} PUBLIC 
                            subDirectoryLib 
                            ${EXTRA_LIBS}
                            subDirectoryLib3
                            )

