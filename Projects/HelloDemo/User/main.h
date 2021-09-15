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

void Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
