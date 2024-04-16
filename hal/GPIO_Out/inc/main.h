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
#define SENSE_LED_A_Pin GPIO_PIN_13
#define SENSE_LED_A_GPIO_Port GPIOB
#define SENSE_LED_B_Pin GPIO_PIN_14
#define SENSE_LED_B_GPIO_Port GPIOB
#define SENSE_LED_C_Pin GPIO_PIN_15
#define SENSE_LED_C_GPIO_Port GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
