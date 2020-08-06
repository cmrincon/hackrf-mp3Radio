#pragma once

#include <SoapySDR/Device.h>
#include <SoapySDR/Formats.h>
#include <complex.h>
#include <stdint.h>
#include <math.h>

#define M_PI           3.14159265358979323846  /* pi */
/**
* Prepare the SDR hardware to transmit. 
* @param samRate Sample rate
* @param frequency Frequency
* @param gain Total gain.
*/
void initSDR(double sampRate, double frequency, int gain);

/**
* Free the resources and deinit the HW.
*/
void closeSDR();

/**
* Activate the stream and start transmitting. It will send the contents of the FIFO module and makes use
* of the FIFO library to pop the contents of the buffer. It stops the stream automatically.
*
*/
void send();