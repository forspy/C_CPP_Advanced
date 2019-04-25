#include"PCMtoWAV.h"

#include <stdio.h>
#include <string.h>

int TransformPcmToWave(const char *pcmpath, int channels, int sample_rate, const char *wavepath)
{
	typedef struct WAVE_HEADER {
		char    fccID[4];       //����Ϊ"RIFF"
		unsigned int dwSize;   //�����д��WAVE��ʽ��Ƶ�Ĵ�С
		char    fccType[4];     //����Ϊ"WAVE"
	}WAVE_HEADER;

	typedef struct WAVE_FMT {
		char    fccID[4];          //����Ϊ"fmt "
		unsigned int  dwSize;     //����ΪWAVE_FMTռ���ֽ�����Ϊ16
		short wFormatTag; //�������ȣ����ΪPCM����ֵΪ 1
		short wChannels;  //��������������ͨ��=1��˫ͨ��=2
		unsigned int  dwSamplesPerSec;//����Ƶ��
		unsigned int  dwAvgBytesPerSec;/* ������(Kpbs)==dwSamplesPerSec*wChannels*uiBitsPerSample/8 */
		short wBlockAlign;//һ�δ�������ֽ�==wChannels*uiBitsPerSample/8
		short uiBitsPerSample;//ÿ���������bit����8bits=8, 16bits=16
	}WAVE_FMT;

	typedef struct WAVE_DATA {
		char    fccID[4];       //����Ϊ"data"
		unsigned int dwSize;   //��¼�洢��ԭʼ��Ƶ���ݵĳ���==NumSamples*wChannels*uiBitsPerSample/8
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
	fseek(fpout, sizeof(WAVE_HEADER), SEEK_CUR);   //1=SEEK_CUR ��������һ��ͷ
												   /* WAVE_FMT */
	memcpy(pcmFMT.fccID, "fmt ", 4);
	pcmFMT.dwSize = 16;
	pcmFMT.wFormatTag = 0x0001;
	pcmFMT.wChannels = 1;//��ͨ��
	pcmFMT.dwSamplesPerSec = 16000;//����Ƶ��(Hz)
	pcmFMT.uiBitsPerSample = 16;//ÿ��������ı�������16����

	pcmFMT.dwAvgBytesPerSec = pcmFMT.dwSamplesPerSec*pcmFMT.wChannels*pcmFMT.uiBitsPerSample / 8;

	pcmFMT.wBlockAlign = pcmFMT.wChannels*pcmFMT.uiBitsPerSample / 8;

	fwrite(&pcmFMT, sizeof(WAVE_FMT), 1, fpout);//д��ڶ���ͷ

												/* WAVE_DATA */
	memcpy(pcmDATA.fccID, "data", 4);
	pcmDATA.dwSize = 0;
	fseek(fpout, sizeof(WAVE_DATA), SEEK_CUR);//����������ͷ

	fread(&m_pcmData, sizeof(char), 1, fp);
	while (!feof(fp))
	{
		pcmDATA.dwSize += sizeof(char);
		fwrite(&m_pcmData, sizeof(char), 1, fpout);//д��
		fread(&m_pcmData, sizeof(char), 1, fp);//����
	}

	pcmHEADER.dwSize = 44 + pcmDATA.dwSize;//44��ͷ�ֽ�+pcm�ļ���С

	rewind(fpout);//����ָ��ͷ
	fwrite(&pcmHEADER, sizeof(WAVE_HEADER), 1, fpout);//д��һ��ͷ
	fseek(fpout, sizeof(WAVE_FMT), SEEK_CUR);
	fwrite(&pcmDATA, sizeof(WAVE_DATA), 1, fpout);//д������ͷ

	fclose(fp);
	fclose(fpout);

	return 0;
}