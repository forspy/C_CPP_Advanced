#标准错误输出stderr


    FILE *err_output_file = stderr;//标准错误输出

一般结合fprintf

	fprintf(err_output_file, "get sdk failed for %s\n", err_msg.c_str());

stderr一般输出到屏幕

0就是stdin 1就是stdout 2就是strerr

stdout -- 标准输出设备 (printf("..")) 同 stdout。

stderr -- 标准错误输出设备

两者默认向屏幕输出。
但如果用转向标准输出到磁盘文件，则可看出两者区别。stdout输出到磁盘文件，stderr在屏幕。

用法：

fprintf(stderr, "Can't open it!\n");

fprintf(stdout, "Can't open it!\n");