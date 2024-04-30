
#include "stm32l4xx_it.h"
#include "main.h"

extern UART_HandleTypeDef hlpuart1;
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

void SVC_Handler(void) {}

void DebugMon_Handler(void) {}

void PendSV_Handler(void) {}

void SysTick_Handler(void) {}

void TIM1_UP_TIM16_IRQHandler(void) { HAL_TIM_IRQHandler(&htim1); }

void LPUART1_IRQHandler(void) { HAL_UART_IRQHandler(&hlpuart1); }
