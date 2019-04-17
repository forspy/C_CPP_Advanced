#  Android mk文件介绍详细篇二 #
一个Android.mk file用来向编译系统描述你的源代码。具体来说：该文件是GNU Makefile的一小部分，会被编译系统解析一次或多次。你可以在每一个Android.mk file中定义一个或多个模块。每个模块属下列类型之一：
  1）APK程序，一般的Android程序，编译打包生成apk文件
  2）JAVA库，java类库，编译打包生成jar文件
  3)  C\C++应用程序，可执行的C\C++应用程序
  4）C\C++静态库，编译生成C\C++静态库，并打包成.a文件
  5）C\C++共享库， 编译生成共享库（动态链接库），并打包成.so， 有且只有共享库才能被安装/复制到您的应用软件（APK）包中。
（1）先看一个简单的例子：一个简单的"hello world"，比如下面的文件：
sources/helloworld/helloworld.c 
sources/helloworld/Android.mk
相应的Android.mk文件会像下面这样：
---------- cut here ------------------

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE
:= helloworld
LOCAL_SRC_FILES := helloworld.c
include $(BUILD_SHARED_LIBRARY)
--------- cut here ------------------
      我们来解释一下这几行代码：
1，LOCAL_PATH := $(call my-dir) ，一个Android.mk file首先必须定义好LOCAL_PATH变量。它用于在开发树中查找源文件。在这个例子中，宏函数‘my-dir’, 由编译系统提供，用于返回当前路径（即包含Android.mk file文件的目录）。
2，include $( CLEAR_VARS)，CLEAR_VARS由编译系统提供（(可以在 android 安装目录下的/build/core/config.mk 文件看到其定义，为 CLEAR_VARS:= $(BUILD_SYSTEM)/clear_vars.mk)），指定让GNU MAKEFILE为你清除许多LOCAL_XXX变量（例如 LOCAL_MODULE, LOCAL_SRC_FILES, LOCAL_STATIC_LIBRARIES, 等等...),除LOCAL_PATH 。这是必要的，因为所有的编译控制文件都在同一个GNU MAKE执行环境中，所有的变量都是全局的。
3，LOCAL_MODULE := helloworld，LOCAL_MODULE变量必须定义，以标识你在Android.mk文件中描述的每个模块。名称必须是唯一的。注意编译系统会自动产生合适的前缀和后缀，换句话说，一个被命名为'foo'的共享库模块，将会生成'libfoo.so'文件（也可以直接已libxxx命名好）。
4，LOCAL_SRC_FILES := helloworld.c，LOCAL_SRC_FILES变量必须包含将要编译打包进模块中的C或C++源代码文件。注意，你不用在这里列出头文件和包含文件，因为编译系统将会自动为你找出依赖型的文件；仅仅列出直接传递给编译器的源代码文件就好。

       此处虽没用到其他常用的还有：

5，LOCAL_C_INCLUDES：可选变量，表示头文件的搜索路径。默认的头文件的搜索路径是LOCAL_PATH目录。示例：LOCAL_C_INCLUDES := sources/foo或LOCAL_C_INCLUDES := $(LOCAL_PATH)/../foo

6，TARGET_ARCH：目标 CPU平台的名字；TARGET_PLATFORM：Android.mk 解析的时候，目标 Android 平台的名字；TARGET_ARCH_ABI：暂时只支持两个 value，armeabi 和 armeabi-v7a

7，LOCAL_STATIC_LIBRARIES: 表示该模块需要使用哪些静态库，以便在编译时进行链接。

8，LOCAL_SHARED_LIBRARIES:  表示模块在运行时要依赖的共享库（动态库），在链接时就需要，以便在生成文件时嵌入其相应的信息。

9，LOCAL_LDLIBS:  编译模块时要使用的附加的链接器选项。

10，LOCAL_ARM_MODE: 默认情况下， arm目标二进制会以 thumb 的形式生成(16 位)，你可以通过设置这个变量为 arm如果你希望你的 module 是以 32 位指令的形式

11，LOCAL_CFLAGS:  可选的编译器选项，在编译 C 代码文件的时候使用。比如：

ifeq ($(BACKCAR_DATA_SOURCE), GPIO)
	CFLAGS += -DGPIO_ENABLE
endif
在C代码中就可以用
#ifdef GPIO_ENABLE
    *prStatu = BCWaitProtocolFromGPIO();
#endif
12，include $(call all-subdir-makefiles)：返回一个位于当前'my-dir'路径的子目录中的所有Android.mk的列表。
（2）在Android中生成本地程序或者库，这些程序和库与其所在路径没有任何关系，只和它们的Android.mk文件有关系。Android.mk和普通的Makefile有所不同，它具有统一的写法，主要包含一些系统公共的宏。在一个Android.mk中可以生成多个可执行程序、动态库和静态库。
A，编译C/C++应用程序的模板：
     #Test Exe
     LOCAL_PATH := $(call my-dir)
     include $(CLEAR_VARS)
     LOCAL_SRC_FILES:= main.c
     LOCAL_MODULE:= test_exe
     #LOCAL_C_INCLUDES :=
     #LOCAL_STATIC_LIBRARIES :=
     #LOCAL_SHARED_LIBRARIES :=
     include $(BUILD_EXECUTABLE)
BUILD_EXECUTABLE表示以一个可执行程序的方式进行编译。补充说明：include $(BUILD_PACKAGE)则是编译出一个apk，include $(BUILD_STATIC_JAVA_LIBRARY)则是编译出jar包。
B，编译静态库的模板：
     #Test Static Lib
     LOCAL_PATH := $(call my-dir)
     include $(CLEAR_VARS)
     LOCAL_SRC_FILES:= /
               helloworld.c
     LOCAL_MODULE:= libtest_static
     #LOCAL_C_INCLUDES :=
     #LOCAL_STATIC_LIBRARIES :=
     #LOCAL_SHARED_LIBRARIES :=
     include $(BUILD_STATIC_LIBRARY)
一般的和上面相似，BUILD_STATIC_LIBRARY表示编译一个静态库.a文件。静态库不会复制到的APK包中，但是能够用于编译共享库。
C，编译动态库的模板：
     #Test Shared Lib
     LOCAL_PATH := $(call my-dir)
     include $(CLEAR_VARS)
     LOCAL_SRC_FILES:= /
               helloworld.c
     LOCAL_MODULE:= libtest_shared
     TARGET_PRELINK_MODULES := false
     #LOCAL_C_INCLUDES :=
     #LOCAL_STATIC_LIBRARIES :=
     #LOCAL_SHARED_LIBRARIES :=
      include $(BUILD_SHARED_LIBRARY)
一般的和上面相似，BUILD_SHARED_LIBRARY表示编译一个动态库。
      以上三者的生成结果分别在如下，generic依具体target会变：
out/target/product/generic/obj/EXECUTABLE
out/target/product/generic/obj/STATIC_LIBRARY
out/target/product/generic/obj/SHARED_LIBRARY
      每个模块的目标文件夹分别为：
可执行程序：XXX_intermediates
静态库：      XXX_static_intermediates
动态库：      XXX_shared_intermediates
（3）另外，在Android.mk文件中，还可以指定最后的目标安装路径，用LOCAL_MODULE_PATH和LOCAL_UNSTRIPPED_PATH来指定。不同的文件系统路径用以下的宏进行选择：
TARGET_ROOT_OUT：表示根文件系统out/target/product/xxxxx/root。
TARGET_OUT：表示system文件系统out/target/product/xxxx/system。
TARGET_OUT_DATA：表示data文件系统out/target/product/xxxx/data。

TARGET_OUT_SHARED_LIBRARIES：表示out/target/product/xxxx/system/lib

TARGET_OUT_APPS：表示out/target/product/xxxx/system/app

ANDROID_PRODUCT_OUT：out/target/product/xxxx/

TARGET_OUT_JAVA_LIBRARIES：out/target/product/xxxx/system/framework

（4）Android.mk中的宏定义控制

比如一个文件夹的Android.mk如下

ifeq ($(strip $(TARGET_BOARD_PLATFORM_GPU)), mali400)
LOCAL_PATH := $(call my-dir)
 
ifeq ($(strip $(TARGET_BOARD_PLATFORM)),rkpx2)
ifeq ($(strip $(TARGET_PRODUCT)),rkpx2)
 
    include $(CLEAR_VARS)
    LOCAL_PREBUILT_LIBS := hwcomposer.rk30board.so
    LOCAL_MODULE_TAGS := optional
    LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
    include $(BUILD_MULTI_PREBUILT)
 
    include $(CLEAR_VARS)
    LOCAL_PREBUILT_LIBS := gralloc.rk30board.so
    LOCAL_MODULE_TAGS := optional
    LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
    include $(BUILD_MULTI_PREBUILT)
 
endif
endif
 
endif
在对应的项目.mk中配置TARGET_BOARD_PLATFORM_GPU := mali400，或者其它值，就可以起开关作用

（5）Android.mk中运行shell命令

取一个片段，如下：

ifeq ($(MTK_SENSOR_SUPPORT),yes)
LOCAL_PATH := $(call my-dir)
 
ifeq ($(CUSTOM_KERNEL_MAGNETOMETER), )
$(shell rm -f $(PRODUCT_OUT)/system/etc/permissions/android.hardware.sensor.compass.xml)
endif
ifeq ($(CUSTOM_KERNEL_ACCELEROMETER), )
$(shell rm -f $(PRODUCT_OUT)/system/etc/permissions/android.hardware.sensor.accelerometer.xml)
endif
普通的.mk一样

（6）Android.mk中 filter 和 filter-out 的用法 

举一个例子比较直观：

filter
$(filter word1 word2,$(VARIANTS))
判断变量VARIANTS中是否包含word1和 word2，如果包含就把VARIANTS中包含的word1和word2之外的过滤掉。示例：
VARIANTS := mon tue wed thu fri sat sun
DAY := $(filter sat sun,$(VARIANTS))
$(info $(DAY))
输出结果为：sat sun

filter-out
$(filter-out word1 word2,$(VARIANTS))
判断变量VARIANTS中是否包含word1和 word2，如果包含就把VARIANTS中包含的word1和word2过滤掉，其余的全部保留。示例：
VARIANTS := mon tue wed thu fri sat sun
DAY := $(filter-out sat sun,$(VARIANTS))
$(info $(DAY))
输出结果为：
mon tue wed thu fri 
=================m、mm、mmm编译命令======================

android源码目录下的build/envsetup.sh文件，描述编译的命令
- m:       Makes from the top of the tree. 
- mm:      Builds all of the modules in the current directory. 
- mmm:     Builds all of the modules in the supplied directories. 

所以要想使用这些命令，首先需要在android源码根目录执行build/envsetup.sh 脚本设置环境。
m：编译所有的模块 
mm：编译当前目录下的模块，当前目录下要有Android.mk文件 
mmm：编译指定路径下的模块，指定路径下要有Android.mk文件 

下面举个例子说明，假设我要编译android下的\hardware\libhardware_legacy\power模块，当前目录为源码根目录，方法如下： 
1、. build/envsetup.sh 
2、mmm hardware/libhardware_legacy/power/ 
或者 ： 
1、. build/envsetup.sh 
2、cd hardware/libhardware_legacy/power/ 
3、mm 

m没有试过。默认上述两个编译命令，只编译发生变化的文件。如果要编译模块的所有文件，需要-b选项，例如mm  -b或者mmm -b

      make命令，也可以用来编译。如果是include $(BUILD_PACKAGE)，用make LOCAL_PACKAGE_NAME值；如果是include $(BUILD_EXECUTABLE)或者include $(BUILD_JAVA_LIBRARY)，用make LOCAL_MODULE值（未验证）。
--------------------- 
作者：DBOY 
来源：CSDN 
原文：https://blog.csdn.net/zhandoushi1982/article/details/5316669 
版权声明：本文为博主原创文章，转载请附上博文链接！