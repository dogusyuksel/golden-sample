
#include "stm32f1xx_it.h"
#include "main.h"

extern CAN_HandleTypeDef hcan;
extern RTC_HandleTypeDef hrtc;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim1;

void NMI_Handler(void) {

    while (1) {
    }
}

void HardFault_Handler(void) {

    while (1) {
    }
}

void MemManage_Handler(void) {

    while (1) {
    }
}

void BusFault_Handler(void) {

    while (1) {
    }
}

void UsageFault_Handler(void) {

    while (1) {
    }
}

void DebugMon_Handler(void) {}

void RTC_IRQHandler(void) { HAL_RTCEx_RTCIRQHandler(&hrtc); }

void RCC_IRQHandler(void) {}

void USB_HP_CAN1_TX_IRQHandler(void) { HAL_CAN_IRQHandler(&hcan); }

void USB_LP_CAN1_RX0_IRQHandler(void) { HAL_CAN_IRQHandler(&hcan); }

void EXTI9_5_IRQHandler(void) { HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7); }

void TIM1_UP_IRQHandler(void) { HAL_TIM_IRQHandler(&htim1); }

void USART1_IRQHandler(void) { HAL_UART_IRQHandler(&huart1); }

void USART2_IRQHandler(void) { HAL_UART_IRQHandler(&huart2); }

void USART3_IRQHandler(void) { HAL_UART_IRQHandler(&huart3); }
