# Android mk文件介绍 #

## Android JNI入门 ##
  Android.mk文件是在使用NDK编译C代码时必须的文件，Android.mk文件中描述了哪些C文件将被编译且指明了如何编译。掌握Android.mk文件的编写主要是掌握其里头将要使用的一些关键字，先来看一个简单的例子，这个例子使用的是android NDK带的

HellJni的例子。

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := hello-jni
LOCAL_SRC_FILES := hello-jni.c

include $(BUILD_SHARED_LIBRARY)

 

LOCAL_PATH 是描述所有要编译的C文件所在的根目录，这边的赋值为$(call my-dir)，代表根目录即为Android.mk所在的目录。(cbb-ai的文件结构里面在Android,mk下面没有.c文件)

 

include $(CLEAR_VARS) 代表在使用NDK编译工具时对编译环境中所用到的全局变量清零，如LOCAL_MODULE，LOCAL_SRC_FILES等，因为在一次NDK编译过程中可能会多次调用Android.mk文件，中间用到的全局变量可能是变化的。关于这个问题看了下面比较复杂的例子可能就明白了。

 

LOCAL_MODULE 是最后生成库时的名字的一部分，给其加上前缀lib和后缀.so就是生成的共享库的名字libhello-jni.so。

 

LOCAL_SRC_FILES 指明要被编译的c文件的文件名

 

include $(BUILD_SHARED_LIBRARY) 指明NDK编译时将生成一些共享库


下面来看cbb-ai里面的.mk实例

LOCAL_PATH := $(call my-dir)#代表根目录即为Android.mk所在的目录
include $(CLEAR_VARS)# 代表在使用NDK编译工具时对编译环境中所用到的全局变量清零

subdirs += $(LOCAL_PATH)/../pfc.mk#创建subdirs变量加载pfc.mk 

include $(subdirs)#使用subdirs路径下的.mk文件