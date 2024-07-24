
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

void Error_Handler(void);

#define LED_A_Pin GPIO_PIN_13
#define LED_A_GPIO_Port GPIOB
#define LED_B_Pin GPIO_PIN_14
#define LED_B_GPIO_Port GPIOB
#define LED_C_Pin GPIO_PIN_15
#define LED_C_GPIO_Port GPIOB
#define CS_1_Pin GPIO_PIN_6
#define CS_1_GPIO_Port GPIOB
#define CS_2_Pin GPIO_PIN_7
#define CS_2_GPIO_Port GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
