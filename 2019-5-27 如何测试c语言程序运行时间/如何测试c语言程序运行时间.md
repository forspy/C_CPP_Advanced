# 如何测试c语言程序运行时间 #

    #include<stdio.h>
    #include<time.h>
    int main()
    {
    	clock_t start, stop;
    	void fun();
    	start = clock();
    	fun();
    	stop = clock();
    	double duration = ((double)(stop-start)) / CLK_TCK;
    	printf("%lf", duration);
    	return 0;
    }
