
#include "main.h"

extern DMA_HandleTypeDef hdma_adc2;

void HAL_MspInit(void) {

    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
}

static uint32_t HAL_RCC_ADC_CLK_ENABLED = 0;

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (hadc->Instance == ADC1) {

        HAL_RCC_ADC_CLK_ENABLED++;
        if (HAL_RCC_ADC_CLK_ENABLED == 1) {
            __HAL_RCC_ADC_CLK_ENABLE();
        }

        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    } else if (hadc->Instance == ADC2) {

        HAL_RCC_ADC_CLK_ENABLED++;
        if (HAL_RCC_ADC_CLK_ENABLED == 1) {
            __HAL_RCC_ADC_CLK_ENABLE();
        }

        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = GPIO_PIN_1;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        hdma_adc2.Instance = DMA1_Channel2;
        hdma_adc2.Init.Request = DMA_REQUEST_0;
        hdma_adc2.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_adc2.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_adc2.Init.MemInc = DMA_MINC_ENABLE;
        hdma_adc2.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
        hdma_adc2.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
        hdma_adc2.Init.Mode = DMA_CIRCULAR;
        hdma_adc2.Init.Priority = DMA_PRIORITY_LOW;
        if (HAL_DMA_Init(&hdma_adc2) != HAL_OK) {
            Error_Handler();
        }

        __HAL_LINKDMA(hadc, DMA_Handle, hdma_adc2);
    }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc) {
    if (hadc->Instance == ADC1) {

        HAL_RCC_ADC_CLK_ENABLED--;
        if (HAL_RCC_ADC_CLK_ENABLED == 0) {
            __HAL_RCC_ADC_CLK_DISABLE();
        }

        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);

    } else if (hadc->Instance == ADC2) {

        HAL_RCC_ADC_CLK_ENABLED--;
        if (HAL_RCC_ADC_CLK_ENABLED == 0) {
            __HAL_RCC_ADC_CLK_DISABLE();
        }

        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1);

        HAL_DMA_DeInit(hadc->DMA_Handle);
    }
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    if (huart->Instance == LPUART1) {

        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
        PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
            Error_Handler();
        }

        __HAL_RCC_LPUART1_CLK_ENABLE();

        __HAL_RCC_GPIOG_CLK_ENABLE();
        HAL_PWREx_EnableVddIO2();
        GPIO_InitStruct.Pin = STLK_RX_Pin | STLK_TX_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_LPUART1;
        HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

        HAL_NVIC_SetPriority(LPUART1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(LPUART1_IRQn);
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart) {
    if (huart->Instance == LPUART1) {

        __HAL_RCC_LPUART1_CLK_DISABLE();

        HAL_GPIO_DeInit(GPIOG, STLK_RX_Pin | STLK_TX_Pin);

        HAL_NVIC_DisableIRQ(LPUART1_IRQn);
    }
}

void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc) {
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    if (hrtc->Instance == RTC) {

        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
        PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
            Error_Handler();
        }

        __HAL_RCC_RTC_ENABLE();
    }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc) {
    if (hrtc->Instance == RTC) {

        __HAL_RCC_RTC_DISABLE();
    }
}

void HAL_PCD_MspInit(PCD_HandleTypeDef *hpcd) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (hpcd->Instance == USB_OTG_FS) {

        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = USB_SOF_Pin | USB_ID_Pin | USB_DM_Pin | USB_DP_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = USB_VBUS_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(USB_VBUS_GPIO_Port, &GPIO_InitStruct);

        __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

        if (__HAL_RCC_PWR_IS_CLK_DISABLED()) {
            __HAL_RCC_PWR_CLK_ENABLE();
            HAL_PWREx_EnableVddUSB();
            __HAL_RCC_PWR_CLK_DISABLE();
        } else {
            HAL_PWREx_EnableVddUSB();
        }
    }
}

void HAL_PCD_MspDeInit(PCD_HandleTypeDef *hpcd) {
    if (hpcd->Instance == USB_OTG_FS) {

        __HAL_RCC_USB_OTG_FS_CLK_DISABLE();

        HAL_GPIO_DeInit(GPIOA, USB_SOF_Pin | USB_VBUS_Pin | USB_ID_Pin | USB_DM_Pin | USB_DP_Pin);

        if (__HAL_RCC_PWR_IS_CLK_DISABLED()) {
            __HAL_RCC_PWR_CLK_ENABLE();
            HAL_PWREx_DisableVddUSB();
            __HAL_RCC_PWR_CLK_DISABLE();
        } else {
            HAL_PWREx_DisableVddUSB();
        }
    }
}
