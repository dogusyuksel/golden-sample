#include "25LC512.h"

static SPI_HandleTypeDef *hspi_eeprom;
static GPIO_TypeDef *GPIOx_Port_eeprom;
static uint16_t GPIO_Pin_eeprom;

void MC25LC512_Initilize(SPI_HandleTypeDef *hspi_, GPIO_TypeDef *GPIOx_, uint16_t GPIO_Pin_) {
    hspi_eeprom = hspi_;
    GPIOx_Port_eeprom = GPIOx_;
    GPIO_Pin_eeprom = GPIO_Pin_;

    MC25LC512_CS(EEPROM_CS_PIN_SET); // Reset The spi Chip //Reset means Enable
    MC25LC512_ReleaseDeepPowerDownMode();
    MC25LC512_ReadStatusRegister();
    MC25LC512_WriteEnableOrDisable(EEPROM_Enable);
}

void MC25LC512_CS(unsigned char CS_Status) {

    // For Cs of the EEprom
    if (CS_Status == EEPROM_CS_PIN_RESET) {
        // Zero reset the Chip
        HAL_GPIO_WritePin(GPIOx_Port_eeprom, GPIO_Pin_eeprom, GPIO_PIN_RESET);
        HAL_Delay(5);
        // DAC8760_SetSPIEnablePin(5,'R');
    } else { // One Set the chip
        HAL_GPIO_WritePin(GPIOx_Port_eeprom, GPIO_Pin_eeprom, GPIO_PIN_SET);
        HAL_Delay(5);
        //		DAC8760_SetSPIEnablePin(5,'S');
    }
}

void MC25LC512_WriteEnableOrDisable(unsigned char EnableOrDisable) {
    unsigned char SendOneByte = 0;
    MC25LC512_CS(EEPROM_CS_PIN_RESET); // Reset The spi Chip //Reset means Enable

    if (EnableOrDisable == EEPROM_Enable) {
        SendOneByte = MC25LCxxx_SPI_WREN;
    } else {
        SendOneByte = MC25LCxxx_SPI_WRDI;
    }
    HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200);
    MC25LC512_CS(EEPROM_CS_PIN_SET); // Set The spi Chip //Set means Disable
}

unsigned char MC25LC512_ReleaseDeepPowerDownMode(void) {

    unsigned char SendOneByte;
    uint8_t RecieveByteOfReleaseDeepPowerMode = 0;
    SendOneByte = MC25LCxxx_SPI_RDID;

    MC25LC512_CS(EEPROM_CS_PIN_RESET); // Reset The spi Chip //Reset means Enable

    HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200);

    HAL_SPI_Receive(hspi_eeprom, &RecieveByteOfReleaseDeepPowerMode, 1, 200); // Address of Manufaturer id High
    HAL_SPI_Receive(hspi_eeprom, &RecieveByteOfReleaseDeepPowerMode, 1, 200); // Address of Manufaturer id Low
    HAL_SPI_Receive(hspi_eeprom, &RecieveByteOfReleaseDeepPowerMode, 1, 200); // Manufaturer id

    MC25LC512_CS(EEPROM_CS_PIN_SET); // Set The spi Chip //Set means Disable

    return RecieveByteOfReleaseDeepPowerMode;
}

void MC25LC512_Write(uint16_t AddresOfData, unsigned char *WriteArrayOfEEProm, unsigned short SizeOfArray) {

    unsigned char SendOneByte;
    MC25LC512_CS(EEPROM_CS_PIN_RESET); // Reset The spi Chip //Reset means Enable
    HAL_Delay(1);
    SendOneByte = MC25LCxxx_SPI_WRITE;
    HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200);
    SendOneByte = AddresOfData >> 8;
    HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200); // High byte of address
    SendOneByte = AddresOfData & 0x00FF;
    HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200); // Low byte of address
    //
    HAL_SPI_Transmit(hspi_eeprom, WriteArrayOfEEProm, SizeOfArray, SizeOfArray * 50);
    HAL_Delay(4);
    MC25LC512_CS(EEPROM_CS_PIN_SET); // Reset The spi Chip //Reset means Enable
    MC25LC512_WriteEnableOrDisable(EEPROM_Enable);
}

// void MC25LC512_Write(uint16_t AddresOfData, unsigned short *WriteArrayOfEEProm, unsigned short sizeOfArray) {

//     unsigned char SendOneByte;

//     unsigned short i = 0, j = 0;
//     unsigned char tmpArrayForSend[2];
//     MC25LC512_CS(EEPROM_CS_PIN_RESET); // Reset The spi Chip //Reset means Enable
//     HAL_Delay(1);
//     SendOneByte = MC25LCxxx_SPI_WRITE;
//     HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200);
//     SendOneByte = AddresOfData >> 8;
//     HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200); // High byte of address
//     SendOneByte = AddresOfData & 0x00FF;
//     HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200); // Low byte of address
//     ////
//     for (j = 0; j < sizeOfArray; j++) {
//         for (i = 0; i < 2; i++)
//             tmpArrayForSend[i] = (((WriteArrayOfEEProm[j]) >> ((1 - i) * 8)) & 0x000000FF);
//         HAL_SPI_Transmit(hspi_eeprom, tmpArrayForSend, 2, 50);
//     }
//     HAL_Delay(4);
//     MC25LC512_CS(EEPROM_CS_PIN_SET); // Reset The spi Chip //Reset means Enable
//     MC25LC512_WriteEnableOrDisable(EEPROM_Enable);
// }

// void MC25LC512_Write(uint16_t AddresOfData, unsigned int *WriteArrayOfEEProm, unsigned short sizeOfArray) {

//     unsigned char SendOneByte;

//     unsigned short i = 0, j = 0;
//     unsigned char tmpArrayForSend[4];
//     MC25LC512_CS(EEPROM_CS_PIN_RESET); // Reset The spi Chip //Reset means Enable
//     HAL_Delay(1);
//     SendOneByte = MC25LCxxx_SPI_WRITE;
//     HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200);
//     SendOneByte = AddresOfData >> 8;
//     HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200); // High byte of address
//     SendOneByte = AddresOfData & 0x00FF;
//     HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200); // Low byte of address
//     ////
//     for (j = 0; j < sizeOfArray; j++) {
//         for (i = 0; i < 4; i++)
//             tmpArrayForSend[i] = (((WriteArrayOfEEProm[j]) >> ((3 - i) * 8)) & 0x000000FF);
//         HAL_SPI_Transmit(hspi_eeprom, tmpArrayForSend, 4, 50);
//     }
//     HAL_Delay(4);
//     MC25LC512_CS(EEPROM_CS_PIN_SET); // Reset The spi Chip //Reset means Enable
//     MC25LC512_WriteEnableOrDisable(EEPROM_Enable);
// }

unsigned char MC25LC512_ReadStatusRegister(void) {

    unsigned char SendOneByte = 0;
    unsigned char ReceiveOneByte;
    SendOneByte = MC25LCxxx_SPI_RDSR;
    MC25LC512_CS(EEPROM_CS_PIN_RESET); // Reset The spi Chip //Reset means Enable
    HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200);
    HAL_SPI_Receive(hspi_eeprom, &ReceiveOneByte, 1, 200); // Address of Manufaturer id High
    MC25LC512_CS(EEPROM_CS_PIN_SET);                       // Set The spi Chip //Set means Disable
    return ReceiveOneByte;
}

unsigned char MC25LC512_Read(uint16_t AddresOfData, unsigned char *DataArrayOfEEProm, unsigned short SizeOfArray) {

    unsigned char SendOneByte;
    //	uint8_t RecieveByteFromEEProm[1];
    MC25LC512_CS(EEPROM_CS_PIN_RESET); // Reset The spi Chip //Reset means Enable
    HAL_Delay(1);
    SendOneByte = MC25LCxxx_SPI_READ; // Config the Device
    HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200);

    SendOneByte = AddresOfData >> 8;
    HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200); // High byte of address
    SendOneByte = AddresOfData & 0x00FF;
    HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200); // Low byte of address

    HAL_SPI_Receive(hspi_eeprom, DataArrayOfEEProm, SizeOfArray,
                    SizeOfArray * 30); // Receive Amount of  Data from EEPROM

    MC25LC512_CS(EEPROM_CS_PIN_SET); // Reset The spi Chip //Reset means Enable
    HAL_Delay(1);
    return 0;
}

// unsigned char MC25LC512_Read(uint16_t AddresOfData, unsigned short *DataArrayOfEEProm,
//                                      unsigned short SizeOfArray) {
//     unsigned char SendOneByte;
//     unsigned char ucDataArrayOfEEProm[2];
//     unsigned short i = 0;
//     //	uint8_t RecieveByteFromEEProm[1];
//     MC25LC512_CS(EEPROM_CS_PIN_RESET); // Reset The spi Chip //Reset means Enable
//     HAL_Delay(1);
//     SendOneByte = MC25LCxxx_SPI_READ; // Config the Device
//     HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200);

//     SendOneByte = AddresOfData >> 8;
//     HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200); // High byte of address
//     SendOneByte = AddresOfData & 0x00FF;
//     HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200); // Low byte of address

//     for (i = 0; i < SizeOfArray; i++) {

//         HAL_SPI_Receive(hspi_eeprom, ucDataArrayOfEEProm, 2, 150); // Receive Amount of  Data from EEPROM
//         DataArrayOfEEProm[i] =
//             (unsigned short)((unsigned char)(ucDataArrayOfEEProm[0]) << 8 | (unsigned char)(ucDataArrayOfEEProm[1]));
//     }
//     MC25LC512_CS(EEPROM_CS_PIN_SET); // Reset The spi Chip //Reset means Enable
//     HAL_Delay(1);
//     return 0;
// }

// unsigned char MC25LC512_Read(uint16_t AddresOfData, unsigned int *DataArrayOfEEProm,
//                                      unsigned short SizeOfArray) {
//     unsigned char SendOneByte;
//     unsigned char ucDataArrayOfEEProm[4];
//     unsigned short i = 0;
//     //	uint8_t RecieveByteFromEEProm[1];
//     MC25LC512_CS(EEPROM_CS_PIN_RESET); // Reset The spi Chip //Reset means Enable
//     HAL_Delay(1);
//     SendOneByte = MC25LCxxx_SPI_READ; // Config the Device
//     HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200);

//     SendOneByte = AddresOfData >> 8;
//     HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200); // High byte of address
//     SendOneByte = AddresOfData & 0x00FF;
//     HAL_SPI_Transmit(hspi_eeprom, &SendOneByte, 1, 200); // Low byte of address

//     for (i = 0; i < SizeOfArray; i++) {

//         HAL_SPI_Receive(hspi_eeprom, ucDataArrayOfEEProm, 4, 150); // Receive Amount of  Data from EEPROM
//         DataArrayOfEEProm[i] =
//             (unsigned int)((unsigned char)(ucDataArrayOfEEProm[0]) << 24 |
//                            (unsigned char)(ucDataArrayOfEEProm[1]) << 16 |
//                            (unsigned char)(ucDataArrayOfEEProm[2]) << 8 | (unsigned char)(ucDataArrayOfEEProm[3]));
//     }
//     MC25LC512_CS(EEPROM_CS_PIN_SET); // Reset The spi Chip //Reset means Enable
//     HAL_Delay(1);
//     return 0;
// }
