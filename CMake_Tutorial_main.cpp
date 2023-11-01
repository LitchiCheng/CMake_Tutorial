#include <iostream>

//项目版本以及编译时间的宏定义
#include "ProjConfig.h"
//子目录lib库的头文件
#include "subDirectoryLib.h"
//利用CMakeLists的option来选择某些库
#if USE_SUB_DIRECTORY_LIB2
#include "subDirectorySharedLib.h"
#endif 
#include "subDirectoryLib3.h"

using namespace std;

int main(){
    std::cout << "CMake_Tutorial_main.cpp" << std::endl;
    //输出编译时间和项目版本
    std::cout << "Build Version:" << VER_MAJOR << "." << VER_MINOR << "." << VER_PATCH << std::endl;
    std::cout << "Build Time:" << TIMESTAMP << std::endl; 
    //调用子目录lib库的函数
    subDirectoryLibFunc();

    #ifdef USE_SUB_DIRECTORY_LIB2
    subDirectorySharedLibFunc();
    #endif 

    subDirectoryLib3Func();    

    return 0;
}