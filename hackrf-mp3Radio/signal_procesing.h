#pragma once
#include <liquid/liquid.h>
#include <complex.h>
#include <stdio.h>

typedef struct dds_ctx_t
{
	complex float *lut;
	unsigned int phase_acumulator;

}dds_ctx;

void dds_make(dds_ctx *dds);

void dds_free(dds_ctx *dds);

dds_getOutput(dds_ctx *dds, int *input, size_t inputLength);