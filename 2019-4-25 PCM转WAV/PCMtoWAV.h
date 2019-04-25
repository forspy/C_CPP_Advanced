#ifndef _PCMtoWAV_H
#define _PCMtoWAV_H

/**
* ��PCM����ת��ΪWAVE��ʽ
* @param pcmpath       ����PCM�ļ�·��
* @param channels      PCM�ļ�ͨ����.
* @param sample_rate   PCM�ļ�����Ƶ��.
* @param wavepath      ���WAV�ļ�·��.
*/
int TransformPcmToWave(const char *pcmpath, int channels, int sample_rate, const char *wavepath);

#endif//_PCMtoWAV_H

