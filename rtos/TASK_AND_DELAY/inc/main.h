/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
#define blue_button_Pin GPIO_PIN_13
#define blue_button_GPIO_Port GPIOC
#define blue_button_EXTI_IRQn EXTI15_10_IRQn
#define green_led_Pin GPIO_PIN_5
#define green_led_GPIO_Port GPIOA

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
