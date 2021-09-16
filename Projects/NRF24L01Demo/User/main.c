#include "main.h"
#include "sys.h"
#include "led.h"
#include "uart.h"
#include "spi.h"
#include "nrf24l01.h"
#include <stdio.h>

SPI_HandleTypeDef hspi1;
UART_HandleTypeDef huart1;

static void GLOBAL_GPIO_Init(void)
{
  /* All GPIO CLK of this project are initialized here */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
}

int main(void)
{
  HAL_Init();
  SystemClock_Config_HSE_25MHz();
  GLOBAL_GPIO_Init();

  USARTx_UART_Init(&huart1);
  LED_Init();
  NRF24L01_Init();
  SPIx_Init(&hspi1);

  if (NRF24L01_initCheck(&hspi1) != HAL_OK) {
    printf("Check failed\r\n");
  } else {
    printf("Check succeeded\r\n");
  }

  if (NRF24L01_config(&hspi1) != HAL_OK) {
    printf("Config failed\r\n");
  } else {
    printf("Config succeeded\r\n");
  }

  uint8_t tmp[] = {
            0x1F, 0x80, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
            0x21, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x28,
            0x31, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x38,
            0x41, 0x12, 0x13, 0x14, 0x15, 0x16, 0x37, 0x48};
  uint8_t txaddr[5] = {0x32, 0x4E, 0x6F, 0x64, 0x65};
  uint8_t rxaddr[5] = {0xF2, 0xF3, 0xF4, 0xF5, 0xF6};
  NRF24L01_txMode(&hspi1, txaddr);
  NRF24L01_dumpConfig(&hspi1);
  LED_Off();
  uint16_t succ, err;

  while (1)
  {
    if (NRF24L01_writeFast(&hspi1, tmp) != HAL_OK) {
      NRF24L01_resetTX(&hspi1);
      err++;
    } else {
      succ++;
    }
    if (err > 255 || succ > 255) {
      printf("F/S: %d/%d\r\n", err, succ);
      err = 0;
      succ = 0;
    }
    HAL_Delay(10);
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1);
}

int fputc(int ch, FILE* stream)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
