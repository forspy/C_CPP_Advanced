#include"PCMtoWAV.h"

#include <stdio.h>
#include <string.h>

int TransformPcmToWave(const char *pcmpath, int channels, int sample_rate, const char *wavepath)
{
	typedef struct WAVE_HEADER {
		char    fccID[4];       //内容为"RIFF"
		unsigned int dwSize;   //最后填写，WAVE格式音频的大小
		char    fccType[4];     //内容为"WAVE"
	}WAVE_HEADER;

	typedef struct WAVE_FMT {
		char    fccID[4];          //内容为"fmt "
		unsigned int  dwSize;     //内容为WAVE_FMT占的字节数，为16
		short wFormatTag; //量化精度：如果为PCM，改值为 1
		short wChannels;  //储存声道数：单通道=1，双通道=2
		unsigned int  dwSamplesPerSec;//采样频率
		unsigned int  dwAvgBytesPerSec;/* 比特率(Kpbs)==dwSamplesPerSec*wChannels*uiBitsPerSample/8 */
		short wBlockAlign;//一次处理多少字节==wChannels*uiBitsPerSample/8
		short uiBitsPerSample;//每个采样点的bit数，8bits=8, 16bits=16
	}WAVE_FMT;

	typedef struct WAVE_DATA {
		char    fccID[4];       //内容为"data"
		unsigned int dwSize;   //记录存储的原始音频数据的长度==NumSamples*wChannels*uiBitsPerSample/8
	}WAVE_DATA;

	if (channels == 2 || sample_rate == 0)
	{
		channels = 2;
		sample_rate = 44100;
	}

	WAVE_HEADER pcmHEADER;
	WAVE_FMT    pcmFMT;
	WAVE_DATA   pcmDATA;

	short m_pcmData;
	FILE *fp, *fpout;

	fp = fopen(pcmpath, "rb+");
	if (fp == NULL)
	{
		printf("Open pcm file error.\n");
		return -1;
	}
	fpout = fopen(wavepath, "wb+");
	if (fpout == NULL)
	{
		printf("Create wav file error.\n");
		return -1;
	}

	/* WAVE_HEADER */
	memcpy(pcmHEADER.fccID, "RIFF", 4);
	memcpy(pcmHEADER.fccType, "WAVE", 4);
	fseek(fpout, sizeof(WAVE_HEADER), SEEK_CUR);   //1=SEEK_CUR 先跳过第一个头
												   /* WAVE_FMT */
	memcpy(pcmFMT.fccID, "fmt ", 4);
	pcmFMT.dwSize = 16;
	pcmFMT.wFormatTag = 0x0001;
	pcmFMT.wChannels = 1;//单通道
	pcmFMT.dwSamplesPerSec = 16000;//采样频率(Hz)
	pcmFMT.uiBitsPerSample = 16;//每个采样点的比特数，16比特

	pcmFMT.dwAvgBytesPerSec = pcmFMT.dwSamplesPerSec*pcmFMT.wChannels*pcmFMT.uiBitsPerSample / 8;

	pcmFMT.wBlockAlign = pcmFMT.wChannels*pcmFMT.uiBitsPerSample / 8;

	fwrite(&pcmFMT, sizeof(WAVE_FMT), 1, fpout);//写入第二个头

												/* WAVE_DATA */
	memcpy(pcmDATA.fccID, "data", 4);
	pcmDATA.dwSize = 0;
	fseek(fpout, sizeof(WAVE_DATA), SEEK_CUR);//跳过第三个头

	fread(&m_pcmData, sizeof(char), 1, fp);
	while (!feof(fp))
	{
		pcmDATA.dwSize += sizeof(char);
		fwrite(&m_pcmData, sizeof(char), 1, fpout);//写入
		fread(&m_pcmData, sizeof(char), 1, fp);//读出
	}

	pcmHEADER.dwSize = 44 + pcmDATA.dwSize;//44个头字节+pcm文件大小

	rewind(fpout);//重新指向开头
	fwrite(&pcmHEADER, sizeof(WAVE_HEADER), 1, fpout);//写第一个头
	fseek(fpout, sizeof(WAVE_FMT), SEEK_CUR);
	fwrite(&pcmDATA, sizeof(WAVE_DATA), 1, fpout);//写第三个头

	fclose(fp);
	fclose(fpout);

	return 0;
}