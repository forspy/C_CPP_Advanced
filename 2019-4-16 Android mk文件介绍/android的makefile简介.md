# android的makefile简介 #

android是什么就不用说了，android自从开源以来，就受到很多人的追捧。当然，一部人追捧它是因为它是Google开发的。对一个程序员来说，一个系统值不值得追捧得要拿代码来说话。我这里并不打算分析android的代码，而是android的makefile，我想通过分析andorid的makefile来告诉大家如何写makefile。

对于一个程序新手而言，好的IDE是他们追捧的对象。但当他接触的代码多了之后，就会逐渐发现IDE不够用了，因为有好多东西用IDE是不好做的，例如自动编译，测试，版本控制，编译定制等。这跟政治课上的一句话有点像：资本主义开始的时候是促进生产力发展的，但到了后来又成了阻碍生产力发展的因素了。如果一个程序不能摆脱IDE的限制（不是不用，而是要有选择的用），那么他就很难提高。要知道，IDE和makefile代表了两种不同的思想：IDE强调的是简化计算机与用户的交互；而makefile体现的是自动化。

对于一个一开始就接触linux的人来说，makefile可能是比较容易学的（熟能生巧），对于一个一开始就接触Windows的人来说，makefile就不太好学，这主要是应该很多时候会不自觉地去用Visual Studio（Visual Studio是个好东西，特别是它的调试）。不知道大叫有没有这个的感觉：一个人如果先接触c，再接触java会比较容易点；如果一个人先接触java，再接触c，就会比较反感c。

这个先引用一下百度百科对makefile的一些描述：

一个工程中的源文件不计数，其按类型、功能、模块分别放在若干个目录中，makefile定义了一系列的规则来指定，哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至于进行更复杂的功能操作，因为 makefile就像一个Shell脚本一样，其中也可以执行操作系统的命令。

makefile带来的好处就是——“自动化编译”，一旦写好，只需要一个make命令，整个工程完全自动编译，极大的提高了软件开发的效率。make是一个命令工具，是一个解释makefile中指令的命令工具，一般来说，大多数的IDE都有这个命令，比如：Delphi的make，Visual C++的nmake，Linux下GNU的make。可见，makefile都成为了一种在工程方面的编译方法。

Make工具最主要也是最基本的功能就是通过makefile文件来描述源程序之间的相互关系并自动维护编译工作。而makefile 文件需要按照某种语法进行编写，文件中需要说明如何编译各个源文件并连接生成可执行文件，并要求定义源文件之间的依赖关系。makefile 文件是许多编译器--包括 Windows NT 下的编译器--维护编译信息的常用方法，只是在集成开发环境中，用户通过友好的界面修改 makefile 文件而已。

对于android而言，android使用的是GNU的make，因此它的makefile格式也是GNU的makefile格式。现在网络上关于makefile最好的文档就是陈皓的《跟我一起写makefile》，这份文档对makefile进行了详细的介绍，因此推荐大家先看这份文档（电子版可以到http://pipi.googlecode.com/files/How%20to%20Write%20makefile.pdf下载，陈皓的blog在http://blog.csdn.net/haoel）。

android最顶层的目录结构如下：

    . 
    |-- Makefile        （全局的Makefile） 
    |-- bionic          （Bionic含义为仿生，这里面是一些基础的库的源代码） 
    |-- bootloader      （引导加载器） 
    |-- build           （build目录中的内容不是目标所用的代码，而是编译和配置所需要的脚本和工具） 
    |-- dalvik          （JAVA虚拟机） 
    |-- development     （程序开发所需要的模板和工具） 
    |-- external        （目标机器使用的一些库） 
    |-- frameworks      （应用程序的框架层） 
    |-- hardware        （与硬件相关的库） 
    |-- kernel          （Linux2.6的源代码） 
    |-- packages        （Android的各种应用程序） 
    |-- prebuilt        （Android在各种平台下编译的预置脚本） 
    |-- recovery        （与目标的恢复功能相关） 
    `-- system          （Android的底层的一些库）
    