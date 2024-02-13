#ifndef AS608_H
#define AS608_H

//Define macros for fingerprint sensor as given in datasheet

//Define fingerprint sensor instruction header. This will not change
#define AS608_INSTR_HEADER 0xEF, 0X01

//Define default fingerprint sensor address. This may be changed in your program
#define AS608_ADDRESS 0xFF, 0xFF, 0xFF, 0xFF


//Define package identifiers (PIDs) for sensor packages
#define PID_COMMAND 0x01 //Command
#define PID_DATA 0x02 //Data packet
#define PID_ACK 0x07 //Acknowledge
#define PID_ENDDATA 0x08 //End data packet

//Function for sending package
void sendDataPackage(uint8_t*, uint8_t size)


#endif
