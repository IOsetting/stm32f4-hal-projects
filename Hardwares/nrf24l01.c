#include "nrf24l01.h"

void NRF24_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  HAL_GPIO_WritePin(NRF24_GPIOx, NRF24_PIN_CE|NRF24_PIN_CSN, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = NRF24_PIN_CE|NRF24_PIN_CSN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(NRF24_GPIOx, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = NRF24_PIN_IRQ;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(NRF24_GPIOx, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(NRF24_EXTIx_IRQx, 0, 0);
  HAL_NVIC_EnableIRQ(NRF24_EXTIx_IRQx);
}
