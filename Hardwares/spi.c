#include "spi.h"


void SPIx_Init(SPI_HandleTypeDef *hspi)
{
  hspi->Instance = SPIx;
  hspi->Init.Mode = SPI_MODE_MASTER;
  hspi->Init.Direction = SPI_DIRECTION_2LINES;
  hspi->Init.DataSize = SPI_DATASIZE_8BIT;
  hspi->Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi->Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi->Init.NSS = SPI_NSS_SOFT;
  hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi->Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi->Init.TIMode = SPI_TIMODE_DISABLE;
  hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi->Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(hspi) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_SPIx_CLK_ENABLE();
  GPIO_InitStruct.Pin = SPI_PIN_SCK|SPI_PIN_MISO|SPI_PIN_MOSI;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AFx_SPIx;
  HAL_GPIO_Init(SPI_GPIOx, &GPIO_InitStruct);
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
  RCC_SPIx_CLK_DISABLE();
  HAL_GPIO_DeInit(SPI_GPIOx, SPI_PIN_SCK|SPI_PIN_MISO|SPI_PIN_MOSI);
}
