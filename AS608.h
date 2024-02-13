#ifndef AS608_H
#define AS608_H

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

//----

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
//----

//Define instruction codes
//----

//System Related

#define HANDSHAKE 0x17 //Handshake to test communication with module
#define SET_ADDR 0x15 //Set device address
#define SET_PARAM 0x0E //Set system parameter
#define GET_PARAM 0x1F //Read system parameter
#define GET_TEMPLATENUM 0x1D //REad current valid template number

//Fingerprint Processing

#define GEN_IMG 0x01 //Detect fingerprint and store fingerprint image
#define UP_IMG 0x0A //Upload fingerprint in buffer to computer
#define DL_IMG 0x0B //Download fingerprint image form computer
#define IMG_TO_CHAR 0x02 //Generate character file from image 
#define GEN_TMPLT 0x05 //generate a template form character buffer info
#define UP_CHAR 0x08 //Upload character file or template
#define DL_CHAR 0x09 //Download character file
#define STR_TMPLT 0x06 //Store buffer contents to flash memory
#define GET_TMPLT 0x07 //Read template from PageID in flash memeory
#define DEL_TMPLT 0x0C //Delete template from flash memory
#define PURGE_LIB 0x0D //Delete all templates in the fingerprint library
#define MATCH_TMPLT 0x03 //Match two templates
#define SEARCH 0x04 //Search for a matching template in libraray


//Other

#define GET_RNG 0x14 //Generate a random number
#define WRITE_NOTEPAD 0x18 //Write to specified page
#define READ_NOTEPAD 0x19 //REad from specified page


//Function for sending package to module
void sendDataPackage(uint8_t*, uint8_t size);

//


#endif
