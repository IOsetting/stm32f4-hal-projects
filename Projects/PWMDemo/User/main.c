#include "main.h"
#include "sys.h"
#include "led.h"
#include "uart.h"
#include "pwm.h"
#include <stdio.h>

UART_HandleTypeDef huart1;
TIM_HandleTypeDef htim2;


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
  LED_Off();
  TIMx_Init(&htim2);
  
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);

  uint8_t d = 0x00, v = 0x00;
  while (1)
  {
    printf("%02X\r\n", v);
    v = (d == 0x00)? v+1 : v-1;
    if (v == 0xFF) {
      d = 0x01;
    } else if (v == 0x00) {
      d = 0x00;
    }
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, v);
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0xFF - v);
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
