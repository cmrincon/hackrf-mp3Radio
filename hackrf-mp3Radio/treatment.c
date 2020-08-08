#include "treatment.h"


/*
AV_SAMPLE_FMT_NONE 0
AV_SAMPLE_FMT_U8	1
unsigned 8 bits

AV_SAMPLE_FMT_S16	2
signed 16 bits

AV_SAMPLE_FMT_S32	3
signed 32 bits

AV_SAMPLE_FMT_FLT	4
float

AV_SAMPLE_FMT_DBL	5
double

AV_SAMPLE_FMT_U8P	6
unsigned 8 bits, planar

AV_SAMPLE_FMT_S16P	7
signed 16 bits, planar

AV_SAMPLE_FMT_S32P	8
signed 32 bits, planar

AV_SAMPLE_FMT_FLTP	9
float, planar

AV_SAMPLE_FMT_DBLP	10
double, planar

AV_SAMPLE_FMT_S64	11
signed 64 bits

AV_SAMPLE_FMT_S64P	12
signed 64 bits, planar

AV_SAMPLE_FMT_NB	13
Number of sample formats. DO NOT USE if linking dynamically.


*/
struct dataFormat format;

void S16_to_int16(filo_ctx *buffer, AVFrame *frame)
{
	filo_push(buffer, frame->data[0], (size_t)(frame->linesize[0]));
}
void S16P_to_int16(filo_ctx *buffer, AVFrame *frame)
{
		/*uint8_t conv_data[(frame->linesize[0]) * 2];

		for (int i = 0, u = 0; i < (frame->linesize[0] - 1); i += 2)
		{
			conv_data[u++] = *(frame->data[0] + i);
			conv_data[u++] = *(frame->data[0] + i + 1);
			conv_data[u++] = *(frame->data[1] + i);
			conv_data[u++] = *(frame->data[1] + i + 1);
		}
		fifo_push(&conv_data[0], (frame->linesize[0] * 2));
		*/
	int16_t interleaved_data[(size_t) frame->linesize[0] * format.nChannels];
	int16_t *ptr_frame_data[format.nChannels];
	for (unsigned int i = 0; i < format.nChannels; i++)
		ptr_frame_data[i] = (int16_t*) frame->data[i];

	int16_t *ptr_inter_data = &interleaved_data[0];
	for (unsigned int samplesLeft = (size_t) frame->linesize[0];
			samplesLeft > 0; samplesLeft--)
	{
		for (int channel = 0; channel < format.nChannels; channel++)
			*(ptr_inter_data++) = *(ptr_frame_data[channel]++);
	}

	filo_push(buffer, (uint8_t *) &interleaved_data, ((size_t) frame->linesize[0] * format.nChannels));
}

void S32_to_int32(filo_ctx *buffer, AVFrame *frame)
{
	filo_push(buffer, frame->data[0], (size_t)(frame->linesize[0]));
}
void S32P_to_int32(filo_ctx *buffer, AVFrame *frame)
{
	int32_t interleaved_data[(size_t) frame->linesize[0] * format.nChannels];
	int32_t *ptr_frame_data[format.nChannels];
	for (unsigned int i = 0; i < format.nChannels; i++)
		ptr_frame_data[i] = (int32_t *) frame->data[i];

	int32_t *ptr_inter_data = &interleaved_data[0];
	for (unsigned int samplesLeft = (size_t) frame->linesize[0];
		samplesLeft > 0; samplesLeft--)
	{
		for (unsigned int channel = 0; channel < format.nChannels; channel++)
			*(ptr_inter_data++) = *(ptr_frame_data[channel]++);
	}
	filo_push(buffer, (uint8_t *) &interleaved_data, ((size_t)frame->linesize[0] * format.nChannels));
}
void float_to_float32(filo_ctx *buffer, AVFrame *frame)
{
	filo_push(buffer, frame->data[0], (size_t) frame->linesize[0]);
}
void floatP_to_float32(filo_ctx *buffer, AVFrame *frame)
{
	float interleaved_data[(size_t) frame->linesize[0] * format.nChannels];
	float *ptr_frame_data[format.nChannels];
	for (unsigned int i = 0; i < format.nChannels; i++)
		ptr_frame_data[i] = (float *) frame->data[i];

	float *ptr_inter_data = &interleaved_data[0];
	for (unsigned int samplesLeft = (size_t) frame->linesize[0];
		samplesLeft > 0; samplesLeft--)
	{
		for (unsigned int channel = 0; channel < format.nChannels; channel++)
			*(ptr_inter_data++) = *(ptr_frame_data[channel]++);
	}
	filo_push(buffer, (uint8_t *) &interleaved_data, ((size_t) frame->linesize[0] * format.nChannels));
}
void double_to_float32(filo_ctx *buffer, AVFrame *frame)
{
	float interleaved_data[frame->linesize[0]];
	float *ptr_inter_data = (float *) &interleaved_data;
	double *ptr_frame_data = (double *) frame->data;
	for (unsigned int samplesLeft = (size_t) frame->linesize[0];
		samplesLeft > 0; samplesLeft--)
	{
			*(ptr_inter_data++) = (float) *(ptr_frame_data++);
	}
	filo_push(buffer, (uint8_t *) &interleaved_data, (size_t) frame->linesize[0]);
}
void doubleP_to_float32(filo_ctx *buffer, AVFrame *frame)
{
	float interleaved_data[(size_t) frame->linesize[0] * format.nChannels];
	double *ptr_frame_data[format.nChannels];
	for (unsigned int i = 0; i < format.nChannels; i++)
		ptr_frame_data[i] = (double *) frame->data[i];

	double *ptr_inter_data = (double *) &interleaved_data;
	for (unsigned int samplesLeft = (size_t) frame->linesize[0];
		samplesLeft > 0; samplesLeft--)
	{
		for (unsigned int channel = 0; channel < format.nChannels; channel++)
			*(ptr_inter_data++) = (float) *(ptr_frame_data[channel]++);
	}
	filo_push(buffer, (uint8_t *) &interleaved_data, ((size_t) frame->linesize[0] * format.nChannels));
}
void U8_to_uint8(filo_ctx *buffer, AVFrame *frame)
{
	filo_push(buffer, frame->data[0], (size_t) frame->linesize[0]);
}
void U8P_to_uint8(filo_ctx *buffer, AVFrame *frame)
{
	uint8_t interleaved_data[(size_t) frame->linesize[0] * format.nChannels];
	uint8_t *ptr_frame_data[format.nChannels];
	for (unsigned int i = 0; i < format.nChannels; i++)
		ptr_frame_data[i] = frame->data[i];

	uint8_t *ptr_inter_data = &interleaved_data[0];
	for (unsigned int samplesLeft = (size_t) frame->linesize[0];
		samplesLeft > 0; samplesLeft--)
	{
		for (unsigned int channel = 0; channel < format.nChannels; channel++)
			*(ptr_inter_data++) = *(ptr_frame_data[channel]++);
	}
	filo_push(buffer, &interleaved_data[0], ((size_t) frame->linesize[0] * format.nChannels));
}
void S64_to_int32(filo_ctx *buffer, AVFrame *frame)
{

}
void S64P_to_int32(filo_ctx *buffer, AVFrame *frame)
{
	
}

void (*getFormat(AVFrame *frame))(filo_ctx *, AVFrame *)
{
	format.nChannels = (unsigned int) frame->channels;
	format.sampleRate = (unsigned int) frame->sample_rate;
	void (*treatment_func)(filo_ctx *, AVFrame *);
	switch (frame->format)
	{
		case AV_SAMPLE_FMT_U8:
			treatment_func = &U8_to_uint8;
			format.format = pauint8;
			format.n_bytes = 1 * format.nChannels;
			break;
		case AV_SAMPLE_FMT_S16:
			treatment_func = &S16_to_int16;
			format.format = paint16;
			format.n_bytes = 2 * format.nChannels;
;			break;
		case AV_SAMPLE_FMT_S32:
			treatment_func = &S32_to_int32;
			format.format = paint32;
			format.n_bytes = 4 * format.nChannels;
			break;
		case AV_SAMPLE_FMT_FLT:
			treatment_func = &float_to_float32;
			format.format = pafloat32;
			format.n_bytes = 4 * format.nChannels;
			break;
		case AV_SAMPLE_FMT_DBL:
			treatment_func = &double_to_float32;
			format.format = pafloat32;
			format.n_bytes = 4 * format.nChannels;
			break;
		case AV_SAMPLE_FMT_U8P:
			treatment_func = &U8P_to_uint8;
			format.format = pauint8;
			format.n_bytes = 1 * format.nChannels;
			break;
		case AV_SAMPLE_FMT_S16P:
			treatment_func = &S16P_to_int16;
			format.format = paint16;
			format.n_bytes = 2 * format.nChannels;
			break;
		case AV_SAMPLE_FMT_S32P:
			treatment_func = &S32P_to_int32;
			format.format = paint32;
			format.n_bytes = 4 * format.nChannels;
			break;
		case AV_SAMPLE_FMT_FLTP:
			treatment_func = &floatP_to_float32;
			format.format = pafloat32;
			format.n_bytes = 4 * format.nChannels;
			break;
		case AV_SAMPLE_FMT_DBLP:
			treatment_func = &doubleP_to_float32;
			format.format = pafloat32;
			format.n_bytes = 4 * format.nChannels;
			break;
		case AV_SAMPLE_FMT_S64:
			treatment_func = &S64_to_int32;
			format.format = paint32;
			format.n_bytes = 4 * format.nChannels;
			break;
		case AV_SAMPLE_FMT_S64P:
			treatment_func = &S64P_to_int32;
			format.format = paint32;
			format.n_bytes = 4 * format.nChannels;
			break;

		default:
			break;
	}
	return treatment_func;
}