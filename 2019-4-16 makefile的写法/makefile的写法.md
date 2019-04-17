# makefile的写法 #
include头文件的写法

    INC_PATH += $(CURDIR) $(CURDIR)/../include/ \
    			$(CURDIR)/../../../10-common/include/system \
    			$(CURDIR)/../../../10-common/include/foundation \
    			$(CURDIR)/../../../10-common/include/protocol \
其中INC_PATH就表示头文件路径

修改之后：

    INC_PATH += $(CURDIR) $(CURDIR)/../include/ \
    			$(CURDIR)/../../../10-common/include/system \
    			$(CURDIR)/../../../10-common/include/foundation \
    			$(CURDIR)/../../../10-common/include/protocol \
    ##下面测试加载头文件（注意注意，这一行要删去）
    			$(CURDIR)/../../../10-common/include/cbb_ai \

这样就会去找这些路径文件夹下的头文件

## 使用**`make -f makefile_linux_d`**进行makefile的脚本运行 ##