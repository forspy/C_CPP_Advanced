#fprintf的功能

fprintf(目标buff，格式，源buff)

示例1：

	 fprintf(FSPOINTER, "%s", STRBUFF);

示例2：
	
	fprintf(in, "Can not open inputfile.\n");

示例3：

    fprintf(err_output_file, "get sdk failed for %s\n", err_msg.c_str());

其中err_msg为string类型 .c_str()获得其首地址(buff)