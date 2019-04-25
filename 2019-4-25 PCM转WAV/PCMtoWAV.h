#ifndef _PCMtoWAV_H
#define _PCMtoWAV_H

/**
* 将PCM数据转化为WAVE格式
* @param pcmpath       输入PCM文件路径
* @param channels      PCM文件通道数.
* @param sample_rate   PCM文件采样频率.
* @param wavepath      输出WAV文件路径.
*/
int TransformPcmToWave(const char *pcmpath, int channels, int sample_rate, const char *wavepath);

#endif//_PCMtoWAV_H

