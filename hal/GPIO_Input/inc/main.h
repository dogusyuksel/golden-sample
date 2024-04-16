#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
#define MCU_IN1_Pin GPIO_PIN_7
#define MCU_IN1_GPIO_Port GPIOA
#define MCU_IN1_EXTI_IRQn EXTI9_5_IRQn
#define SENSE_LED_A_Pin GPIO_PIN_13
#define SENSE_LED_A_GPIO_Port GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
