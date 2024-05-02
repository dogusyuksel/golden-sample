
#include "stm32l4xx_it.h"
#include "main.h"

extern DMA_HandleTypeDef hdma_adc2;
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

void DMA1_Channel2_IRQHandler(void) { HAL_DMA_IRQHandler(&hdma_adc2); }

void TIM1_UP_TIM16_IRQHandler(void) { HAL_TIM_IRQHandler(&htim1); }
