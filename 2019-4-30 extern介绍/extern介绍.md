#extern介绍

extern是计算机语言中的一个关键字，可置于变量或者函数前，以表示变量或者函数的定义在别的文件中。提示编译器遇到此变量或函数时，在其它模块中寻找其定义，另外，extern也可用来进行链接指定。

    //external.cpp  --- external variables , compile with support.cpp
    #include <iostream>
    using namespace std;
    double warming = 0.3; // warming defined .
    void update(double dt);
    void local();
    //第一个const防止字符串被修改，第二个const确保数组中每个指针始终指向它最初指向的字符串。
    const char * const months[12] =
    {
    	"January","February","March","April","May",
    	"June","July","August","September","October",
    	"November","December"
    };
    int main(int argc, char** argv) {  //使用全局变量
    	cout << "Global warming is " << warming << "degress.\n";
    	update(0.1); //call function to change warming
    	cout << "Global warming is " << warming << "degress.\n";
    	local(); //call function with local warming
    	cout << "Global warming is " << warming << "degress.\n";
    	return 0;
    }


在其他文件中使用extern 修饰变量

    //support.cpp ---- use external varibales . compile with external.cpp
    #include <iostream>
    using std::cout;
    extern double warming; //use warming another file
    void update(double dt);
    void local();
    
    void update(double dt) {
    	extern double warming; //extern 使用全局文件共享的变量warming
    	warming += dt;
    	cout << "Updataing global warming to " << warming << "degress.\n";
    }
    
    void local() {
    	//定义一个局部的自动变量warming，在函数内屏蔽全局文件共享的warming
    	double warming = 0.8;
    	cout << "Local warming = " << warming << "degress.\n";
    	cout << "But global warming = " << ::warming << "degress.\n";
    	//使用C++作用域解析符访问全局共享的warming，而不是函数内定义的自动变量warming。
    }


因为extern 修饰的变量作用于该文件，extern的原理很简单，就是告诉编译器：“你现在编译的文件中，
有一个标识符虽然没有在本文件中定义，但是它是在别的文件中定义的全局变量，你要放行！”
比如：

    //A.cpp
    extern int i;
    int main()
    {
    i=100;//试图使用B中定义的全局变量
    }
    //B.cpp
    int i;
    区别于static 将变量声明为静态全局变量，只能在模块内部使用，如果声明了static后，尽管主文件中声明了extern也调用不到
    */
    #endif

extern 修饰的变量也可以从封装的lib静态库或者dll动态库中调取