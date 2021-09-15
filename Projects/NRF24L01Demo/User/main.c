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
  SPIx_Init(&hspi1);
  NRF24_Init();

  while (1)
  {
    printf("Hello World\r\n");
    LED_On();
    HAL_Delay(100);
    LED_Off();
    HAL_Delay(2000);
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
