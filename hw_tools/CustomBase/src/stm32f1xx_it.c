
#include "main.h"
#include "stm32f1xx_it.h"

extern ADC_HandleTypeDef hadc2;
extern CAN_HandleTypeDef hcan;
extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim1;

void NMI_Handler(void)
{

   while (1)
  {
  }
}

void HardFault_Handler(void)
{

  while (1)
  {
  }
}

void MemManage_Handler(void)
{

  while (1)
  {
  }
}

void BusFault_Handler(void)
{

  while (1)
  {
  }
}

void UsageFault_Handler(void)
{

  while (1)
  {
  }
}

void SVC_Handler(void)
{

}

void DebugMon_Handler(void)
{

}

void PendSV_Handler(void)
{

}

void SysTick_Handler(void)
{

}

void ADC1_2_IRQHandler(void)
{

  HAL_ADC_IRQHandler(&hadc2);

}

void USB_HP_CAN1_TX_IRQHandler(void)
{

  HAL_CAN_IRQHandler(&hcan);

}

void USB_LP_CAN1_RX0_IRQHandler(void)
{

  HAL_CAN_IRQHandler(&hcan);

}

void CAN1_RX1_IRQHandler(void)
{

  HAL_CAN_IRQHandler(&hcan);

}

void CAN1_SCE_IRQHandler(void)
{

  HAL_CAN_IRQHandler(&hcan);

}

void TIM1_UP_IRQHandler(void)
{

  HAL_TIM_IRQHandler(&htim1);

}

void I2C1_EV_IRQHandler(void)
{

  HAL_I2C_EV_IRQHandler(&hi2c1);

}

void I2C1_ER_IRQHandler(void)
{

  HAL_I2C_ER_IRQHandler(&hi2c1);

}

void SPI1_IRQHandler(void)
{

  HAL_SPI_IRQHandler(&hspi1);

}

void USART1_IRQHandler(void)
{

  HAL_UART_IRQHandler(&huart1);

}

void USART2_IRQHandler(void)
{

  HAL_UART_IRQHandler(&huart2);

}

void USART3_IRQHandler(void)
{

  HAL_UART_IRQHandler(&huart3);

}

