## Linux导出终端输出结果 ##

方法一：使用script开始记录 exit退出

**方法二（推荐）：设置CRT的日志导出**

https://blog.csdn.net/quietly_brilliant/article/details/78125599

方法三(常用)：使用>重定向导出

./helllo_world >output.txt

**方法四(推荐)：使用tee 记录（-a表示append追加）**

./helllo_world |tee -a tee_output.txt