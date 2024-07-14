#include "AS608.h"
#include "main.h"

#include <cstring>

//Function for sending package to module
void sendDataPackage(DataPackage *msg, uint8_t size)
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

    HAL_UART_Transmit(&huart1, &msgArr, size, HAL_MAX_DELAY);
}

//initializer for fingerprint module
void fpInit()
{
    printf("Attempting connection with fingerprint module...\n\r");
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
    return DATAPKG_BASE_SIZE + (sizeof(msg->data));
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
    unsigned dataSize = sizeof(msg->data);
    for(unsigned i=0U; i<dataSize; i++)
        sum += msg->data[i];


    msg->checksum[0] = (sum >> 8) & 0xFF;
    msg->checksum[1] = sum & 0xFF;
}

uint8_t sendHandshake(FingerprintModule *fpModule)
{
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

    handshkMsg.data = malloc(msg->len_data);
    *handshkMsg.data = 0x00;

    calculateChecksum(&handshkMsg); //Calculate checksum and add to data package
    unsigned msgSize = calculatePkgSize(&handshkMsg);

    sendDataPackage(&handshkMsg, msgSize);

    uint8_t handshkReply[HANDSHAKE_REPLY_LEN];

    HAL_UART_Receive_IT(&huart1, handshkReply, HANDSHAKE_REPLY_LEN);

    free(msg->data);

    return handshkReply[9];
}