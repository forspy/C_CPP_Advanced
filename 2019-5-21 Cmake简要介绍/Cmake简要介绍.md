# Cmake简要介绍 #

CMake是一个跨平台的安装（编译）工具，可以用简单的语句来描述所有平台的安装(编译过程)。他能够输出各种各样的makefile或者project文件，能测试编译器所支持的C++特性,类似UNIX下的automake。只是 CMake 的组态档取名为 CMakeLists.txt。Cmake 并不直接建构出最终的软件，而是产生标准的建构档（如 Unix 的 Makefile 或 Windows Visual C++ 的 projects/workspaces），然后再依一般的建构方式使用。这使得熟悉某个集成开发环境（IDE）的开发者可以用标准的方式建构他的软件，这种可以使用各平台的原生建构系统的能力是 CMake 和 SCons 等其他类似系统的区别之处。

CMake 可以编译源代码、制作程序库、产生适配器（wrapper）、还可以用任意的顺序建构执行档。CMake 支持 in-place 建构（二进档和源代码在同一个目录树中）和 out-of-place 建构（二进档在别的目录里），因此可以很容易从同一个源代码目录树中建构出多个二进档。CMake 也支持静态与动态程式库的建构。
“CMake”这个名字是“cross platform make”的缩写。虽然名字中含有“make”，但是CMake和Unix上常见的“make”系统是分开的，而且更为高阶。



**2、在cmake目录中新建hello_cmake.c与CMakeLists.txt文件，内容如下：**

hello_cmake.c：

    #include <stdio.h>
    
    int main() {
    printf("Hello CMake\n");
    return 0;
    }
CMakeLists.txt：

    cmake_minimum_required (VERSION 2.8)
    project (HelloCMake)
    add_executable(HelloCMake hello_cmake.c)

在linux操作系统下

    编写CMakeLists.txt配置文件。
    执行cmake命令生成makefile文件。
    执行make命令编译执行，生成最终的目标文件。
    运行最终生成的可执行文件即可，这步可选。makeinstall

**3.include：**

包含其他目录的CMakeLists.txt文件。命令格式为：

    include(<file|module> [OPTIONAL] [RESULT_VARIABLE <VAR>]
      [NO_POLICY_SCOPE])
使用示例：

	include(platform/CMakeLists.txt)

**4.ink_directories：**

指定链接器查找库的路径。命令格式为：

	link_directories(directory1 directory2 ...)

使用示例：

	link_directories(${PROJECT_SOURCE_DIR}/lib)


**5.aux_source_directory：**

查找目录中的所有源文件。命令格式为：

	aux_source_directory(<dir> <variable>)

查找指定目录dir中所有源文件的名称，并将列表存储在提供的variable中。

使用示例：

    aux_source_directory(. DIR_SRCS)
    add_executable(${APP_NAME} ${DIR_SRCS})


**6.add_library：**

使用指定的源文件给项目添加一个库。命令格式为：

	add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            source1 [source2 ...])
参数介绍：

name：

该命令调用列出的源文件来构建的库目标。对应于逻辑目标名称，在项目中必须是全局唯一的。

STATIC：

静态库，在链接其他目标时使用。

SHARED：

动态链接库，运行时加载。

MODULE：

不会被链接到其它目标中，但是可能会在运行时使用dlopen-系列的函数动态链接。

使用示例：

	add_library(HelloCMake hello_cmake.c)

示例：

 **将cJSON构建为静态库**

(1)在本地建立cJSONdemo1的目录工程，并将cJSON库源代码拷贝到目录中，并在该目录新建CMakeLists.txt文件。目录结构如下：

    cJSONdemo1  
    ├── cJSON_Utils.h  
    ├── cJSON_Utils.c  
    ├── cJSON.h
    ├── cJSON.c
    └── CMakeLists.txt 

CMakeLists.txt文件内容如下：

    cmake_minimum_required(VERSION 2.8.5)
    project(cJSON-lib)
    set(CJSON_SRC cJSON.c cJSON_Utils.c)
    add_library(cjson STATIC ${CJSON_SRC})


**7.add_executable：**

使用指定的源文件给项目添加一个可执行文件。命令格式为：

	add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               source1 [source2 ...])
参数介绍：

name：

该命令调用列出的源文件来构建的可执行目标。 对应于逻辑目标名称，在项目中必须是全局唯一的。构建的可执行文件的实际文件名是基于本机平台的约定。

WIN32：

如果给出WIN32，则在创建的目标上设置属性WIN32_EXECUTABLE。

MACOSX_BUNDLE:

如果给定MACOSX_BUNDLE，将在创建的目标上设置相应的属性。

EXCLUDE_FROM_ALL：

如果给定EXCLUDE_FROM_ALL，将在创建的目标上设置相应的属性。

source：

源码列表。

使用示例：

	add_executable(HelloCMake hello_cmake.c)

**8.target_link_libraries：**

将给定的库链接到一个目标上。命令格式为：

	target_link_libraries(<target> ... <item>... ...)

使用示例：

	target_link_libraries(luacocos2d cocos2d)

**9.set：**

将一个CMAKE变量设置为给定值。命令格式为：

	set(<variable> <value>... [PARENT_SCOPE])

使用示例：

	set(COCOS2D_ROOT ${CMAKE_SOURCE_DIR}/cocos2d)

参考文档：

https://www.cnblogs.com/alphagl/p/6280061.html