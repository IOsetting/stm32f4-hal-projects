#include "main.h"
#include "sys.h"
#include "led.h"
#include "uart.h"
#include "spi.h"
#include "adc.h"
#include "pwm.h"
#include "nrf24l01.h"
#include <stdio.h>
#include <string.h>

uint8_t adc_buf[32], pwm_buf[128];
uint8_t *start = pwm_buf, *end = pwm_buf, *lb = pwm_buf, *rb = (pwm_buf + 128);
uint16_t succ, err;
SPI_HandleTypeDef hspi1;
UART_HandleTypeDef huart1;
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

extern NRF24L01_bufStruct NRF24L01_rxbuff;

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
  uint8_t rxaddr[5] = {0x32, 0x4E, 0x6F, 0x64, 0x65};
  uint8_t txaddr[5] = {0x32, 0x4E, 0x6F, 0x64, 0x22};
  if (NRF24L01_config(&hspi1, txaddr, rxaddr) != HAL_OK) {
    printf("Config failed\r\n");
  } else {
    printf("Config succeeded\r\n");
  }

  NRF24L01_dumpConfig(&hspi1);
  LED_Off();
  if (NRF24_MODE == NRF24L01_modeRX)
  {
    TIMx_PWM_Init(&htim2);
    TIM3_IT_Init(&htim3);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
    HAL_TIM_Base_Start_IT(&htim3);
    while (1);
  }
  else
  {
    DMA_Init();
    ADCx_Init(&hadc1);
    HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&adc_buf, 32);    // Enable DMA transfer

    while (1)
    {
      
    }
  }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /*for (uint8_t i = 0; i < 32; i++)
  {
    printf("%02X ", adc_buf[i]);
  }
  printf("\r\n");*/
  if (NRF24L01_writeFast(&hspi1, adc_buf) != HAL_OK)
  {
    NRF24L01_resetTX(&hspi1);
    LED_On();
    LED_Off();
    err++;
  } else {
    succ++;
  }
  if (err > 255 || succ > 255)
  {
    printf("F/S: %d/%d\r\n", err, succ);
    err = 0;
    succ = 0;
  }
}

void HAL_ADC_ErrorCallback(ADC_HandleTypeDef* hadc)
{
  printf("error\r\n");
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  LED_On();
  NRF24L01_handelIrqFlag(&hspi1);
  // Move received data to audio buf
  memcpy(end, NRF24L01_rxbuff.buf, NRF24L01_PLOAD_WIDTH);
  end += NRF24L01_PLOAD_WIDTH;
  if (end == rb) end = lb;
  LED_Off();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance==TIM3)
  {
    if (start != end) {
      __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, *start);
      start++;
      if (start == rb) start = lb;
    }
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
