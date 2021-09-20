#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

/** LED */
#define LED_PIN                      GPIO_PIN_13
#define LED_GPIO_PORT                GPIOC

/** UART */
#define USARTx                       USART1
#define USART_PIN_TX                 GPIO_PIN_9
#define USART_PIN_RX                 GPIO_PIN_10
#define USART_GPIOx                  GPIOA
#define GPIO_AFx_USARTx              GPIO_AF7_USART1
#define RCC_USARTx_CLK_ENABLE()      __HAL_RCC_USART1_CLK_ENABLE()
#define RCC_USARTx_CLK_DISABLE()     __HAL_RCC_USART1_CLK_DISABLE()

/** TIM PWM */
#define PWM_TIMx                     TIM2
#define PWM_GPIOx_CH1                GPIOA
#define PWM_PIN_CH1                  GPIO_PIN_15
#define PWM_GPIOx_CH2                GPIOB
#define PWM_PIN_CH2                  GPIO_PIN_3
#define PWM_GPIO_AFx_TIMx            GPIO_AF1_TIM2


void Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
