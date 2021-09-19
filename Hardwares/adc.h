#ifndef __ADC_H
#define __ADC_H

#include "main.h"

void ADCx_Init(ADC_HandleTypeDef *hadc);
void DMA_Init(void);
void DMA2_Stream4_IRQHandler(void);

#endif /* __ADC_H */
