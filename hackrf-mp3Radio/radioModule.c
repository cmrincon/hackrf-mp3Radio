#include "radioModule.h"

SoapySDRDevice *sdr = NULL;
SoapySDRStream *txStream = NULL;


void initSDR(double sampRate, double frequency, int gain)
{
	size_t length;

	SoapySDRKwargs *results = SoapySDRDevice_enumerate(NULL, &length);
	sdr = SoapySDRDevice_make(&results[0]);
	SoapySDRKwargsList_clear(results, length);

	if (sdr == NULL)
	{
		printf("SoapySDRDevice_make fail: %s\n", SoapySDRDevice_lastError());
		return -3;
	}

	if (SoapySDRDevice_setSampleRate(sdr, SOAPY_SDR_TX, 0, sampRate) != 0)
	{
		printf("setSampleRate fail: %s\n", SoapySDRDevice_lastError());
	}
	if (SoapySDRDevice_setFrequency(sdr, SOAPY_SDR_TX, 0, frequency, NULL) != 0)
	{
		printf("setFrequency fail: %s\n", SoapySDRDevice_lastError());
	}
	if (SoapySDRDevice_setGainMode(sdr, SOAPY_SDR_TX, 0, false) != 0)
		printf("setGainMode fail %s\n", SoapySDRDevice_lastError());
	if (SoapySDRDevice_setGain(sdr, SOAPY_SDR_TX, 0, gain) != 0)
		printf("setGain fail %s\n", SoapySDRDevice_lastError());

	SoapySDRDevice_setupStream(sdr, &txStream, SOAPY_SDR_TX, SOAPY_SDR_CF32, NULL, 0, NULL);

	if (txStream == NULL)
	{
		printf("setupStream fail: %s\n", SoapySDRDevice_lastError());
		SoapySDRDevice_unmake(sdr);
		return -4;
	}

	return 0;


}

void closeSDR()
{
	SoapySDRDevice_closeStream(sdr, txStream);

	//cleanup device handle
	SoapySDRDevice_unmake(sdr);

}
void send() // Modification needed
{
	SoapySDRDevice_activateStream(sdr, txStream, 0, 0, 0); 

	char buff[1024];
	long long timeNs = 0; 
	int flags = 0; 


	while (true)
	{
		void *buffs[] = { buff };
		if (SoapySDRDevice_writeStream(sdr, txStream, buffs, 1024, &flags, timeNs, 1e6) < 1) 		
			printf("WriteStream error: %s\n", SoapySDRDevice_lastError());
	}

	SoapySDRDevice_deactivateStream(sdr, txStream, 0, 0); 
}