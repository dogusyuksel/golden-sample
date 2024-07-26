#include "canard.h"
#include "canard_stm32.h"

#include "main.h"
#include "stm32f1xx_hal.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define APP_VERSION_MAJOR 99
#define APP_VERSION_MINOR 99
#define APP_NODE_NAME "skyyu.node.demo"
#define GIT_HASH 0xBADC0FFE

#define UAVCAN_GET_NODE_INFO_DATA_TYPE_SIGNATURE 0xee468a8121c46a9e
#define UAVCAN_GET_NODE_INFO_DATA_TYPE_ID 1
#define UAVCAN_GET_NODE_INFO_RESPONSE_MAX_SIZE ((3015 + 7) / 8)

#define UAVCAN_EQUIPMENT_ESC_RAWCOMMAND_ID 1030
#define UAVCAN_EQUIPMENT_ESC_RAWCOMMAND_SIGNATURE 0x217f5c87d7ec951d
#define UAVCAN_EQUIPMENT_ESC_RAWCOMMAND_MAX_VALUE 8192

#define UNIQUE_ID_LENGTH_BYTES 16

#define UAVCAN_NODE_HEALTH_OK 0
#define UAVCAN_NODE_HEALTH_WARNING 1
#define UAVCAN_NODE_HEALTH_ERROR 2
#define UAVCAN_NODE_HEALTH_CRITICAL 3

#define UAVCAN_NODE_MODE_OPERATIONAL 0
#define UAVCAN_NODE_MODE_INITIALIZATION 1

#define UAVCAN_NODE_STATUS_MESSAGE_SIZE 7

#define UAVCAN_NODE_STATUS_MESSAGE_SIZE 7
#define UAVCAN_NODE_STATUS_DATA_TYPE_ID 341
#define UAVCAN_NODE_STATUS_DATA_TYPE_SIGNATURE 0x0f0868d0c1a7c6f1

#define UAVCAN_PROTOCOL_DEBUG_KEYVALUE_ID 16370
#define UAVCAN_PROTOCOL_DEBUG_KEYVALUE_SIGNATURE 0xe02f25d6e0c98ae0
#define UAVCAN_PROTOCOL_DEBUG_KEYVALUE_MESSAGE_SIZE 62
#define UNIQUE_ID_LENGTH_BYTES 16

#define UAVCAN_PROTOCOL_PARAM_GETSET_ID 11
#define UAVCAN_PROTOCOL_PARAM_GETSET_SIGNATURE 0xa7b622f939d1a4d5

extern UART_HandleTypeDef huart3;

typedef struct {
    uint8_t *name;
    int64_t val;
    int64_t min;
    int64_t max;
    int64_t defval;
} param_t;

void uavcanInit(void);

void showRcpwmonUart(void);

void sendCanard(void);

void receiveCanard(void);

void spinCanard(void);

void publishCanard(void);

void showRcpwmonUart(void);

void rawcmdHandleCanard(CanardRxTransfer *transfer);

void getsetHandleCanard(CanardRxTransfer *transfer);

void getNodeInfoHandleCanard(CanardRxTransfer *transfer);

uint16_t makeNodeInfoMessage(uint8_t buffer[UAVCAN_GET_NODE_INFO_RESPONSE_MAX_SIZE]);

static const uint8_t sine_wave[256] = {
    0x80, 0x83, 0x86, 0x89, 0x8C, 0x90, 0x93, 0x96, 0x99, 0x9C, 0x9F, 0xA2, 0xA5, 0xA8, 0xAB, 0xAE, 0xB1, 0xB3, 0xB6,
    0xB9, 0xBC, 0xBF, 0xC1, 0xC4, 0xC7, 0xC9, 0xCC, 0xCE, 0xD1, 0xD3, 0xD5, 0xD8, 0xDA, 0xDC, 0xDE, 0xE0, 0xE2, 0xE4,
    0xE6, 0xE8, 0xEA, 0xEB, 0xED, 0xEF, 0xF0, 0xF1, 0xF3, 0xF4, 0xF5, 0xF6, 0xF8, 0xF9, 0xFA, 0xFA, 0xFB, 0xFC, 0xFD,
    0xFD, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFD, 0xFD, 0xFC, 0xFB, 0xFA,
    0xFA, 0xF9, 0xF8, 0xF6, 0xF5, 0xF4, 0xF3, 0xF1, 0xF0, 0xEF, 0xED, 0xEB, 0xEA, 0xE8, 0xE6, 0xE4, 0xE2, 0xE0, 0xDE,
    0xDC, 0xDA, 0xD8, 0xD5, 0xD3, 0xD1, 0xCE, 0xCC, 0xC9, 0xC7, 0xC4, 0xC1, 0xBF, 0xBC, 0xB9, 0xB6, 0xB3, 0xB1, 0xAE,
    0xAB, 0xA8, 0xA5, 0xA2, 0x9F, 0x9C, 0x99, 0x96, 0x93, 0x90, 0x8C, 0x89, 0x86, 0x83, 0x80, 0x7D, 0x7A, 0x77, 0x74,
    0x70, 0x6D, 0x6A, 0x67, 0x64, 0x61, 0x5E, 0x5B, 0x58, 0x55, 0x52, 0x4F, 0x4D, 0x4A, 0x47, 0x44, 0x41, 0x3F, 0x3C,
    0x39, 0x37, 0x34, 0x32, 0x2F, 0x2D, 0x2B, 0x28, 0x26, 0x24, 0x22, 0x20, 0x1E, 0x1C, 0x1A, 0x18, 0x16, 0x15, 0x13,
    0x11, 0x10, 0x0F, 0x0D, 0x0C, 0x0B, 0x0A, 0x08, 0x07, 0x06, 0x06, 0x05, 0x04, 0x03, 0x03, 0x02, 0x02, 0x02, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03, 0x03, 0x04, 0x05, 0x06, 0x06, 0x07, 0x08, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x13, 0x15, 0x16, 0x18, 0x1A, 0x1C, 0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2B, 0x2D,
    0x2F, 0x32, 0x34, 0x37, 0x39, 0x3C, 0x3F, 0x41, 0x44, 0x47, 0x4A, 0x4D, 0x4F, 0x52, 0x55, 0x58, 0x5B, 0x5E, 0x61,
    0x64, 0x67, 0x6A, 0x6D, 0x70, 0x74, 0x77, 0x7A, 0x7D};