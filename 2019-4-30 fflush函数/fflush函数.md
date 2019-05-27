#fflush函数

fflush是一个计算机函数，功能是冲洗流中的信息，该函数通常用于处理磁盘文件。fflush()会强迫将缓冲区内的数据写回参数stream 指定的文件中。

函数名: fflush

功 能: 清除读写缓冲区，需要立即把输出缓冲区的数据进行物理写入时

头文件：stdio.h

原型:int fflush(FILE *stream)

其中stream是要冲洗的流

fflush()会强迫将缓冲区内的数据写回参数stream 指定的文件中. 如果参数stream 为NULL,fflush()会将所有打开的文件数据更新.


	void flush(FILE* stream)
	{
	int duphandle;
	/*flushthestream'sinternalbuffer*/
	fflush(stream);
	/*makeaduplicatefilehandle*/
	duphandle=dup(fileno(stream));
	/*closetheduplicatehandletoflushtheDOSbuffer*/
	close(duphandle);
	}