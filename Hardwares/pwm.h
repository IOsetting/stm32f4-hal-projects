#ifndef __PWM_H
#define __PWM_H

#include "main.h"

void TIMx_PWM_Init(TIM_HandleTypeDef *htim);
void TIM3_IT_Init(TIM_HandleTypeDef *htim);

#endif /* __PWM_H */
