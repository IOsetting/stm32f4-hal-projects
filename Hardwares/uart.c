#include "uart.h"

void USARTx_UART_Init(UART_HandleTypeDef *huart)
{
  huart->Instance = USARTx;
  huart->Init.BaudRate = 115200;
  huart->Init.WordLength = UART_WORDLENGTH_8B;
  huart->Init.StopBits = UART_STOPBITS_1;
  huart->Init.Parity = UART_PARITY_NONE;
  huart->Init.Mode = UART_MODE_TX_RX;
  huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart->Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(huart) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* Peripheral clock enable */
  RCC_USARTx_CLK_ENABLE();

  GPIO_InitStruct.Pin = USART_PIN_TX|USART_PIN_RX;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AFx_USARTx;
  HAL_GPIO_Init(USART_GPIOx, &GPIO_InitStruct);
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==USART1)
  {
    RCC_USARTx_CLK_DISABLE();
    HAL_GPIO_DeInit(USART_GPIOx, USART_PIN_TX|USART_PIN_RX);
  }

}
