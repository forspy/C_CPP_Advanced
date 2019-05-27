String 类的方法

1.先说c_str()，它返回const char*类型，不能修改指向的内容（**但是可以强制类型转换成char*类型**），并且实际上返回string内部那个数组的首地址的一个指针，并且数组末尾有'\0'

例如：

	    fprintf(err_output_file, "get sdk failed for %s\n", err_msg.c_str());

	其中err_msg为string类型 .c_str()获得其首地址(buff)

2.data()和c_str()的区别就在返回的指针所指的数组最后带不带'\0'，这由编译器决定。一般data()返回的char* 类型不带'\0'