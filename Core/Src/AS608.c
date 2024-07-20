#include "stm32c0xx_hal.h"
#include "stm32c0xx_hal_uart.h"
#include "AS608.h"

#include <stdlib.h>


//Function for sending package to module
void sendDataPackage(DataPackage *msg, uint8_t size, UART_HandleTypeDef *huart)
{
    uint8_t msgArr[size];
    uint8_t arrIndex = 0;
    

    for(uint8_t i=0; i<13; i++)
    {
        if(i == 10)
        {
            for(int j=0; j<msg->len_data; j++)
                msgArr[arrIndex++] = msg->data[j];
        }
        else
            msgArr[arrIndex++] = getDataPkgElement(msg, i);
    }

    HAL_UART_Transmit(huart, &msgArr, size, HAL_MAX_DELAY);
}

//initializer for fingerprint module
void fpInit(FingerprintModule *fpModule)
{

}

//Get DataPackage elements by index
uint8_t getDataPkgElement(DataPackage *msg, uint8_t index)
{
    switch(index)
    {
        case 0:
            return msg->header[0];
            break;
        case 1:
            return msg->header[1];
            break;
        case 2:
            return msg->address[0];
            break;
        case 3:
            return msg->address[1];
            break;
        case 4:
            return msg->address[2];
            break;
        case 5:
            return msg->address[3];
            break;
        case 6:
            return msg->pid;
            break;
        case 7:
            return msg->len_pkg[0];
            break;
        case 8:
            return msg->len_pkg[1];
            break;
        case 9:
            return msg->instr_code;
            break;
        case 11:
            return msg->checksum[0];
            break;
        case 12:
            return msg->checksum[1];
            break;
        default:
            return 0;
            break;
    }
}

//Calculate the size in bytes of the data package
unsigned calculatePkgSize(DataPackage* msg)
{
    return DATAPKG_BASE_SIZE + msg->len_data; //(sizeof(msg->data) / sizeof(uint8_t));
}

//Calculates and adds checksum for data package
void calculateChecksum(DataPackage *msg)
{
    uint16_t sum = 0;

    //Add pid
    sum += msg->pid;

    //Add package length
    sum += (msg->len_pkg[0] << 8) + msg->len_pkg[1];

    //Add instruction code
    sum += msg->instr_code;

    //Add package data
    unsigned dataSize = msg->len_data;
    for(unsigned i=0U; i<dataSize; i++)
        sum += msg->data[i];


    msg->checksum[0] = (sum >> 8) & 0xFF;
    msg->checksum[1] = sum & 0xFF;
}

void sendHandshake(FingerprintModule *fpModule)
{
    //Define data package to be send
    DataPackage handshkMsg = {
        {AS608_INSTR_HEADER},
        {fpModule->address[0], fpModule->address[1], fpModule->address[2], fpModule->address[3]},
        PID_COMMAND,
        {HANDSHAKE_PKG_LEN},
        HANDSHAKE,
        NULL,
        HANDSHAKE_DATA_LEN,
        {0x00, 0x00}
    };

    //Allocate memory for data and assign data value
    handshkMsg.data = malloc(handshkMsg.len_data);
    *handshkMsg.data = 0x00;

    //Calculate checksum and add to data package
    calculateChecksum(&handshkMsg);
    unsigned msgSize = calculatePkgSize(&handshkMsg);

    //Send data to fingerprint sensor
    sendDataPackage(&handshkMsg, msgSize, fpModule->huart);

    //Allocate response memory
    if(fpModule->response == NULL)
        fpModule->response = malloc(HANDSHAKE_REPLY_LEN * sizeof(uint8_t));
    else
        fpModule->response = realloc(fpModule->response, HANDSHAKE_REPLY_LEN * sizeof(uint8_t));
    

    //Wait to receive the response message
    HAL_UART_Receive(fpModule->huart, fpModule->response, HANDSHAKE_REPLY_LEN, HAL_MAX_DELAY);
    HAL_Delay(200);
    //Set to active if handshake response was good
    if(*(fpModule->response + 9) == OP_COMPLETE)
    {
        char handshkConfirm[] = "Handshake OK\r\n";
        fpModule->active = true;
        HAL_UART_Transmit(fpModule->huart, (uint8_t*)handshkConfirm, sizeof(handshkConfirm) / sizeof(char), HAL_MAX_DELAY);
    }
    else if(*(fpModule->response + 9) == REC_ERR)
    {
        char handshkRecErr[] = "Error Receiving Package\r\n";
        fpModule->active = false;
        HAL_UART_Transmit(fpModule->huart, (uint8_t*)handshkRecErr, sizeof(handshkRecErr) / sizeof(char), HAL_MAX_DELAY);
    }
    else
    {
        char handshkComErr[] = "Couldn't operate com port\r\n";
        fpModule->active = false;
        HAL_UART_Transmit(fpModule->huart, (uint8_t*)handshkComErr, sizeof(handshkComErr) / sizeof(char), HAL_MAX_DELAY);
    }

    //Free memory used for package data
    free(handshkMsg.data);
}

void setAddress(FingerprintModule *fpModule, uint8_t newAddress[])
{

    //Replace address in 
    for(unsigned i=0; i<4; i++)
        fpModule->address[i] = newAddress[i];

    //Define set address data package instruction
    DataPackage setAddressMsg = {
        {AS608_INSTR_HEADER},
        {fpModule->address[0], fpModule->address[1], fpModule->address[2], fpModule->address[3]},
        PID_COMMAND, 
        {0x00, 0x07}, 
        SET_ADDR,
        NULL, 
        SETADDR_DATA_LEN, 
        {0x00, 0x00}
    };

    //Allocate memory for array holding new address
    setAddressMsg.data = malloc(SETADDR_DATA_LEN * sizeof(uint8_t));
    setAddressMsg.data[0] = newAddress[0];
    setAddressMsg.data[1] = newAddress[1];
    setAddressMsg.data[2] = newAddress[2];
    setAddressMsg.data[3] = newAddress[3];
    

    //Calculate checksum and add to message
    calculateChecksum(&setAddressMsg);

    //Calculate package size
    uint8_t msgSize = calculatePkgSize(&setAddressMsg);

    //Send the data package to the module
    sendDataPackage(&setAddressMsg, msgSize, fpModule->huart);

    if(fpModule->response == NULL)
        fpModule->response = malloc(SETADDR_REPLY_LEN * sizeof(uint8_t));
    else
        fpModule->response = realloc(fpModule->response, SETADDR_REPLY_LEN * sizeof(uint8_t));
    
    //Set dummy value
    fpModule->response[9] = 0xff;

    //Wait to receive the response message
    HAL_UART_Receive(fpModule->huart, fpModule->response, SETADDR_REPLY_LEN, HAL_MAX_DELAY);
    HAL_Delay(200);
    //Set to active if handshake response was good
    if(*(fpModule->response + 9) == OP_COMPLETE)
    {
        char setAddrConfirm[] = "New Address Set\r\n";
        fpModule->active = true;
        HAL_UART_Transmit(fpModule->huart, (uint8_t*)setAddrConfirm, sizeof(setAddrConfirm) / sizeof(char), HAL_MAX_DELAY);
    }
    else if(*(fpModule->response + 9) == REC_ERR)
    {
        char setAddrRecErr[] = "Error Receiving Package\r\n";
        fpModule->active = false;
        HAL_UART_Transmit(fpModule->huart, (uint8_t*)setAddrRecErr, sizeof(setAddrRecErr) / sizeof(char), HAL_MAX_DELAY);
    }
    else
    {
        char setAddrComErr[] = "Couldn't operate com port\r\n";
        fpModule->active = false;
        HAL_UART_Transmit(fpModule->huart, (uint8_t*)setAddrComErr, sizeof(setAddrComErr) / sizeof(char), HAL_MAX_DELAY);
    }

    //Free memory allocated for data
    free(setAddressMsg.data);

}
