# Android系统框架层次 #

## 1.Android系统框架层次。 ##

Android系统内核是基于Linux系统开发而来的，权限高度自由，源代码完全开放，是一种拓展性非常强的操作系统，免费开源，可定制，这也是迅速风靡全球的原因吧！主要使用对象是移动设备，由Google和开放手机联盟领导及开发。其内核编程语言是c/c++。android使用dalvik虚拟机制，本质上它是一个Java虚拟机。而且对于每一个APP都会创建个dalvik虚拟机，也就是一个linux进程。

## 2.android底层驱动，以及操作系统全部内核都是使用C语言和汇编语言编程开发。 ##

**但是android操作系统本身是使用Java开发，使用JNI调用本地的C语言库，由操作系统实现对底层调用。**

## 3，android应用开发，即手机app开发，使用的是Java语言，一般不会用到c/c++语言。 ##

因此，想投身手机应用开发的小伙伴们，可以直接钻研Java语言即可。

## 总结来说 ##
安卓系统也只不过是基于linux系统内核开发的一个Java虚拟机，然后在虚拟机里运行java程序。就像我们在windows电脑里安装一个虚拟机，运行其它操作系统进行软件测试一样，这个其它的操作系统就相当于安卓，然后大家开发的所有软件，在这个虚拟机里使用。这样来说，是不是感觉很容易明白它的原理了呢？

