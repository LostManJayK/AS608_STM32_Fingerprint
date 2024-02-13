#ifndef AS608_H
#define AS608_H

//Define macros for fingerprint sensor as given in datasheet

//Define fingerprint sensor instruction header. This will not change
#define AS608_INSTR_HEADER 0xEF, 0X01

//Define default fingerprint sensor address. This may be changed in your program
#define AS608_ADDRESS 0xFF, 0xFF, 0xFF, 0xFF


//Define package identifiers (PIDs) for sensor packages
//----
#define PID_COMMAND 0x01 //Command
#define PID_DATA 0x02 //Data packet
#define PID_ACK 0x07 //Acknowledge
#define PID_ENDDATA 0x08 //End data packet

//Define confirmation codes for AS608 acknowledgement packages. Each code is one byte. Refer to the datasheet for additional info
//----
#define COMPLETE 0x00 //Command execution complete
#define REC_ERR 0x01 //Error receiving package
#define NO_FINGER 0x02 //No fingerprint on sensor
#define ENROLL_FAIL 0x03//Fail to enroll fingerprint

#define BADIMG_DIS 0x06 //Character file generation fail. Overly-disorderly image
#define BADIMG_SMALL 0x07 //Character gile generation faill. Not enough data
#define WRONG_FP 0x08 //Fingerprint doesn't match
#define NO_MATCH 0x09 //Could not find mathing fingerprint
#define COMBINE_FAIL 0x0A //Failed to combine files
#define PAGEID_OUT_OF_RANGE 0x0B //Page ID is beyond finger library
#define TEMPLATE_READ_ERR 0x0C //Error reading template or template is invalid
#define TEMPLATE_UPLOAD_ERR 0x0D //Error uploading template
#define REC_UNABLE 0x0E //Unable to read the following packages
#define IMG_UPLOAD_ERR 0x0F //Error uploading image
#define TEMPLATE_DELETE_FAIL 0x10//Failed to delete template
#define LIB_CLEAR_FAIL 0x11 //Failed to clear fingerprint library

#define IMG_GEN_FAIL 0x15 //Failed to generate img, lack of primary img

#define FLASH_WRITE_ERR 0x18 //Error writing flash memory
#define UNDEF_ERR 0x19 //No definition error
#define INVALID_REG 0x1A//Invalid register number
#define INVALID_REG_CONFIG 0x1B//Incorrect register configuration
#define INVALID_PAGE_NUM 0x1C //Wrong page number
#define COM_ERR 0x1D //Failed to operate communication port


//Function for sending package to module
void sendDataPackage(uint8_t*, uint8_t size);

//


#endif
