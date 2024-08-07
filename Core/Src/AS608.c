#include "stm32c0xx_hal.h"
#include "stm32c0xx_hal_uart.h"
#include "AS608.h"

#include <stdlib.h>
#include <string.h>


//Function for sending package to module
void sendDataPackage(DataPackage *msg, UART_HandleTypeDef *huart)
{

    //Calculate checksum
    calculateChecksum(msg);
    
    //Calculate the package size
    uint8_t size = calculatePkgSize(msg);

    //Create an array for the data package and initialize the index
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

    HAL_UART_Transmit(huart, msgArr, size, HAL_MAX_DELAY);
}

// void assessResponse(FingerprintModule *fpModule)
// {
//     char responseMsg[];

//     switch(fpModule->resposne + 9)
// }

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

//Determine and transmit responses
void assessResponse(FingerprintModule *fpModule)
{

    if(fpModule->response == NULL)
        fpModule->response = malloc(fpModule->len_response * sizeof(uint8_t));
    else
        fpModule->response = realloc(fpModule->response, fpModule->len_response * sizeof(uint8_t));
    
    //Receive module response
    HAL_UART_Receive(fpModule->huart, fpModule->response, fpModule->len_response, HAL_MAX_DELAY);
    HAL_Delay(200);

    //Create confirmation message array
    char confMsg[60];

    //Check response and handle
    switch(*(fpModule->response + 9))
    {
        case OP_COMPLETE:
            strcpy(confMsg, "Operation Complete\r\n");
            break;
        case REC_ERR:
            strcpy(confMsg, "Error receiving package\r\n");
            break;
        case NO_FINGER:
            strcpy(confMsg, "No fingerprint on sensor\r\n");
            break;
        case ENROLL_FAIL:
            strcpy(confMsg, "Failed to enroll fingerprint\r\n");
            break;
        case BADIMG_DIS:
            strcpy(confMsg, "Character file generation fail. Overly-disorderly image\r\n");
            break;
        case BADIMG_SMALL:
            strcpy(confMsg, "Character gile generation faill. Not enough data\r\n");
            break;
        case WRONG_FP:
            strcpy(confMsg, "Fingerprint doesn't match\r\n");
            break;
        case NO_MATCH:
            strcpy(confMsg, "Could not find mathing fingerprint\r\n");
            break;
        case COMBINE_FAIL:
            strcpy(confMsg, "Failed to combine files\r\n");
            break;
        case PAGEID_OUT_OF_RANGE:
            strcpy(confMsg, "Page ID is beyond finger library\r\n");
            break;
        case TEMPLATE_READ_ERR:
            strcpy(confMsg, "Error reading template or template is invalid\r\n");
            break;
        case TEMPLATE_UPLOAD_ERR:
            strcpy(confMsg, "Error uploading template\r\n");
            break;
        case REC_UNABLE:
            strcpy(confMsg, "Unable to read the following packages\r\n");
            break;
        case IMG_UPLOAD_ERR:
            strcpy(confMsg, "Error uploading image\r\n");
            break;
        case TEMPLATE_DELETE_FAIL:
            strcpy(confMsg, "Failed to delete template\r\n");
            break;
        case LIB_CLEAR_FAIL:
            strcpy(confMsg, "Failed to clear fingerprint library\r\n");
            break;
        case IMG_GEN_FAIL: 
            strcpy(confMsg, "Failed to generate img, lack of primary img\r\n");
            break;
        case FLASH_WRITE_ERR: 
            strcpy(confMsg, "Error writing flash memory\r\n");
            break;
        case UNDEF_ERR:
            strcpy(confMsg, "No definition error\r\n");
            break;
        case INVALID_REG:
            strcpy(confMsg, "Invalid register number\r\n");
            break;
        case INVALID_REG_CONFIG:
            strcpy(confMsg, "Incorrect register configuration\r\n");
            break;
        case INVALID_PAGE_NUM:
            strcpy(confMsg, "Wrong page number\r\n");
            break;
        case COM_ERR:
            strcpy(confMsg, "Failed to operate communication port\r\n");
            break;
        default:
            strcpy(confMsg, "Unknown error. Check connections\r\n");
            break;
    }

    HAL_UART_Transmit(fpModule->huart, (uint8_t*)confMsg, sizeof(confMsg) / sizeof(char), HAL_MAX_DELAY);
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

//Function for sending handshake message
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

    //Send data to fingerprint sensor
    sendDataPackage(&handshkMsg, fpModule->huart);

    //Set reply length
    fpModule->len_response = HANDSHAKE_REPLY_LEN;

    assessResponse(fpModule);

    //Free memory used for package data
    free(handshkMsg.data);
}

//Function for setting device address
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
        {SETADDR_PKG_LEN}, 
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

    //Send the data package to the module
    sendDataPackage(&setAddressMsg, fpModule->huart);

    //Set response length
    fpModule->len_response = SETADDR_REPLY_LEN;

    //Check response
    assessResponse(fpModule);

    //Free memory allocated for data
    free(setAddressMsg.data);
}

void setSysParam(FingerprintModule *fpModule, uint8_t paramID, uint8_t paramVal)
{
    DataPackage paramMsg = {
        {AS608_INSTR_HEADER},
        {fpModule->address[0], fpModule->address[1], fpModule->address[2], fpModule->address[3]},
        PID_COMMAND,
        {SETPARAM_PKG_LEN},
        SET_PARAM,
        NULL,
        SETPARAM_DATA_LEN,
        {0x00, 0x00}
    };


    //Allocate data memory
    paramMsg.data = malloc(SETPARAM_DATA_LEN * sizeof(uint8_t));
    *paramMsg.data = paramID;
    *(paramMsg.data+1) = paramVal;

    //Send data package
    sendDataPackage(&paramMsg, fpModule->huart);

    //Set response length
    fpModule->len_response = SETPARAM_REPLY_LEN;

    //Check response
    assessResponse(fpModule);

    //Free data package memory
    free(paramMsg.data);
}

//Set baud rate of the module (Use BAUD_VAL as defined above)
void setBaudRate(FingerprintModule* fpModule, uint8_t baudRate)
{
    if(baudRate >= 0x1 && baudRate <= 0xC)
        setSysParam(fpModule, BAUD_PARAM, baudRate);
    else
    {
        char msg[] = "Err: Invalid Baud, use defined baud ids\r\n";
        HAL_UART_Transmit(fpModule->huart, (uint8_t*)msg, sizeof(msg) / sizeof(char), HAL_MAX_DELAY);
    }
}

//Set security level of the module (Use SECLVL_VAL as defined)
void setSecurityLevel(FingerprintModule* fpModule, uint8_t secLvl)
{
    if(secLvl >= 1 && secLvl <= 5)
        setSysParam(fpModule, SECLVL_PARAM, secLvl);
    else
    {
        char msg[] = "Err: Invalid seclvl, use defined SECLVL ids\r\n";
        HAL_UART_Transmit(fpModule->huart, (uint8_t*)msg, sizeof(msg) / sizeof(char), HAL_MAX_DELAY);
    }
}

//Set max data package length (Use PACLEN_VAL as defined)
void setPacLen(FingerprintModule* fpModule, uint8_t pacLen)
{
    if(pacLen <= 3)
        setSysParam(fpModule, PACLEN_PARAM, pacLen);
    else
    {
        char msg[] = "Err: Invalid paclen, use defined PACLEN ids\r\n";
        HAL_UART_Transmit(fpModule->huart, (uint8_t*)msg, sizeof(msg) / sizeof(char), HAL_MAX_DELAY);
    }
}

//Function for accessing system parameters
void readSysParam(FingerprintModule* fpModule)
{
    DataPackage paramMsg = {
        {AS608_INSTR_HEADER},
        {fpModule->address[0], fpModule->address[1], fpModule->address[2], fpModule->address[3]},
        PID_COMMAND,
        {READPARAM_PKG_LEN},
        GET_PARAM,
        NULL,
        READPARAM_DATA_LEN,
        {0x00, 0x00}
    };

    //Send data pakcage
    sendDataPackage(&paramMsg, fpModule->huart);

    //Set response length
    fpModule->len_response = READPARAM_REPLY_LEN;

    //Check the module response
    assessResponse(fpModule);
}

//Function for reading stored templates in fpModule
void readTemplateNum(FingerprintModule *fpModule)
{
    DataPackage tmpltMsg = {
        {AS608_INSTR_HEADER},
        {fpModule->address[0], fpModule->address[1], fpModule->address[2], fpModule->address[3]},
        PID_COMMAND,
        {READTMPLTNUM_PKG_LEN},
        GET_TEMPLATENUM,
        NULL,
        READTMPLTNUM_DATA_LEN,
        {0x00, 0x00}
    };

    //Send the data package
    sendDataPackage(&tmpltMsg, fpModule->huart);

    //Set response length
    fpModule->len_response = READTMPLTNUM_REPLY_LEN;

    //Check the mdoule response
    assessResponse(fpModule);
}