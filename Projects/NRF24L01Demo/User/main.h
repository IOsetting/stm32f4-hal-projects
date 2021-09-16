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
#define USART_GPIOx                  GPIOA
#define USART_PIN_TX                 GPIO_PIN_9
#define USART_PIN_RX                 GPIO_PIN_10
#define GPIO_AFx_USARTx              GPIO_AF7_USART1
#define RCC_USARTx_CLK_ENABLE()      __HAL_RCC_USART1_CLK_ENABLE()
#define RCC_USARTx_CLK_DISABLE()     __HAL_RCC_USART1_CLK_DISABLE()

/** SPI */
#define SPIx                         SPI1
#define SPI_GPIOx                    GPIOA
#define SPI_PIN_SCK                  GPIO_PIN_5
#define SPI_PIN_MISO                 GPIO_PIN_6
#define SPI_PIN_MOSI                 GPIO_PIN_7
#define GPIO_AFx_SPIx                GPIO_AF5_SPI1
#define RCC_SPIx_CLK_ENABLE()        __HAL_RCC_SPI1_CLK_ENABLE()
#define RCC_SPIx_CLK_DISABLE()       __HAL_RCC_SPI1_CLK_DISABLE()

/** NRF24 */
#define NRF24_MODE                   NRF24L01_modeRX
#define NRF24_GPIOx                  GPIOB
#define NRF24_PIN_IRQ                GPIO_PIN_13
#define NRF24_PIN_CE                 GPIO_PIN_14
#define NRF24_PIN_CSN                GPIO_PIN_15
#define NRF24_EXTIx_IRQx             EXTI15_10_IRQn


void Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
