#include "main.h"
#include "sys.h"
#include "led.h"
#include "uart.h"
#include "adc.h"
#include <stdio.h>

uint16_t ADC_Value[2];

UART_HandleTypeDef huart1;
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

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
  SystemClock_Config_HSE_84MHz();
  GLOBAL_GPIO_Init();

  USARTx_UART_Init(&huart1);
  LED_Init();
  DMA_Init();
  ADCx_Init(&hadc1);
  HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_Value, 2);    // Enable DMA transfer

  LED_Off();
  while (1)
  {
    printf("%d %d\r\n", //  %d %d
      ADC_Value[0], ADC_Value[1]); // , ADC_Value[2], ADC_Value[3]
    HAL_Delay(100);
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
