#include"PCMtoWAV.h"

#include <stdio.h>
#include <string.h>


int main()
{
	TransformPcmToWave("./16k.pcm", 1, 16000, "./16kpcm_to_wav.wav");
	return 0;
}