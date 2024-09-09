/*
 * File:   application.c
 * Author: I51005
 *
 * Created on July 28, 2024, 8:02 PM
 */


#include <xc.h>
#include "stdio.h"
#include "string.h"
#include "application.h"
#include "mcc_generated_files/uart/eusart1.h"
#include "mcc_generated_files/timer/tmr0.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/i2c_host/mssp1.h"

/**
 * **********************************************************
 *  Macros definitions
 * **********************************************************
 **/
//#define _XTAL_FREQ                   (4000000)
#define DATA_LENGTH                  (2)
#define WRITE_DATA_LENGTH            (2)
#define READ_ONE_BYTE                (1)
#define READ_TWO_BYTE                (2)
#define UART_INPUT_RECEIVED          (1)
#define LENGTH                       (5)
#define CLIENT1                      ("0x0A")  //Client1 address
#define CLIENT2                      ("0x0B")  //Client2 address
#define CLIENT1_ADDRESS              (0x0A)
#define CLIENT2_ADDRESS              (0x0B)
#define SENSOR_1                     ("1")
#define SENSOR_2                     ("2")
#define SENSOR_3                     ("3")
#define SENSOR_2AND3                 ("4")
#define SET                          (1)
#define I2C_CLIENT_1                 (1)
#define I2C_CLIENT_2                 (2)
#define INPUT_RECEIVED               (1)
#define DELAY_FUNCTION()             __delay_ms(1000);

/**
 * **********************************************************
 *  File Global variables
 * **********************************************************
 **/
uint8_t readDataLength;
uint8_t dataRegisterAddress;
uint8_t clientAddress;
uint8_t dataLength;
uint8_t inputCmdBuffer;
uint8_t index;
uint8_t clientRdDataBuffer[DATA_LENGTH];
uint8_t sensor1DataRegister[DATA_LENGTH] = {0x75, 0x01};     //0x75 - Sensor Register Address, 1 - 1 byte data length
uint8_t sensor2DataRegister[DATA_LENGTH] = {0x76, 0x01};     //0x76 - Sensor Register Address, 1 - 1 byte data length
uint8_t sensor3DataRegister[DATA_LENGTH] = {0x77, 0x01};    //0x77 - Sensor Register Address, 1 - 1 byte data length   
uint8_t sensor2And3DataRegister[DATA_LENGTH] = {0x76, 0x02}; //0x76 - Sensor Register Address, 2 - 2 byte data length  
uint8_t sensorDataRdBuffer[DATA_LENGTH];
volatile uint8_t timerInterrupt_Flag;
extern volatile uint8_t eusart1RxCount;
char userInput[LENGTH];

typedef enum
{
    DISPLAY_INFORMATION,
    DISPLAY_I2C_CLIENT_INFO,
    WAIT_FOR_USER_INPUT,
    DECODE_COMMAND,
    CLIENT1_SENSOR_SELECTION,
    CLIENT2_SENSOR_SELECTION,
    SEND_I2C_SENSOR_DATA_TO_UART,
    WAIT_STATE,
}appState_t;
static appState_t applicationState = DISPLAY_INFORMATION;

/**
 * **********************************************************
 *  Function declarations
 * **********************************************************
 **/
uint8_t Eusart1_ReadInput(void);
uint8_t DecodeUartCmdForI2C_Client(char *command);
uint8_t I2C_CLient1SensorCommand(char *command);
uint8_t I2C_CLient2SensorCommand(char *command);
void I2C_ClientWriteAndRead(const uint8_t clientAddress, uint8_t *sensorDataRegister, uint8_t i2cWriteDataLength, uint8_t i2cReadDataLength);
uint8_t* IntegerToAsciConver(uint16_t num, uint8_t str[], uint16_t baseNumber);
void Reverse(uint8_t str[], uint16_t len);
void EUSART1_SendString(char *str);
void SensorInformation(void);
void DisplayI2C_ClientAddrOnUART(void);



/*******************************************************************************
 * void Application(void)
 *
 * API to run the application, this API displays i2c client and sensor information, 
 * displays input commands to be entered by the user on the terminal window
 * (used Data Visualizer)and performs I2C bidirectional communication with multiple 
 * client devices. 
 * 
 *
 * @param void 
 * @return void
 ******************************************************************************/
void Application(void)
{
    uint8_t *transmitBuffer;
    uint8_t baseValue = 10;
    uint8_t string[12];
    uint8_t bytesLength = 0;
    uint8_t decodeUartCmdBuffer = 0;
    uint8_t uartCmdReceived = 0;
    switch(applicationState)
    {
        case DISPLAY_INFORMATION:
            __delay_ms(100);
            SensorInformation();
            applicationState = DISPLAY_I2C_CLIENT_INFO;
            break;
        case DISPLAY_I2C_CLIENT_INFO:
            DisplayI2C_ClientAddrOnUART();
            Timer0_Start();
            applicationState = WAIT_FOR_USER_INPUT;
            break;
        case WAIT_FOR_USER_INPUT:
            uartCmdReceived = Eusart1_ReadInput();
            if(uartCmdReceived == INPUT_RECEIVED)
            {
                applicationState = DECODE_COMMAND;
                uartCmdReceived = 0;
            }
            else if(timerInterrupt_Flag == SET)
            {
                EUSART1_SendString("Input not received\n");
                timerInterrupt_Flag = 0;
                applicationState = DISPLAY_I2C_CLIENT_INFO;   
            }
            break;
        case DECODE_COMMAND:
            decodeUartCmdBuffer  = DecodeUartCmdForI2C_Client(userInput);
            memset(userInput, 0 , sizeof(userInput)); // to clear the user input with value 0
            if(decodeUartCmdBuffer  == I2C_CLIENT_1)
            {
                applicationState = CLIENT1_SENSOR_SELECTION;
            }
            else if(decodeUartCmdBuffer  == I2C_CLIENT_2)
            {
                applicationState = CLIENT2_SENSOR_SELECTION;
            }
            else
            {
                applicationState = DISPLAY_I2C_CLIENT_INFO;
            } 
            decodeUartCmdBuffer = 0;
            break;
        case CLIENT1_SENSOR_SELECTION:
            uartCmdReceived = Eusart1_ReadInput();
            if(uartCmdReceived == INPUT_RECEIVED)
            { 
                inputCmdBuffer = I2C_CLient1SensorCommand(userInput); 
                dataLength = inputCmdBuffer;
                if(inputCmdBuffer)
                {
                    applicationState = SEND_I2C_SENSOR_DATA_TO_UART;  
                }
                else
                {
                    applicationState = DISPLAY_I2C_CLIENT_INFO;
                }
                memset(userInput, 0 , sizeof(userInput));
                uartCmdReceived = 0;
            }
            else if(timerInterrupt_Flag == SET)
            {
                EUSART1_SendString("Input not received\n");
                timerInterrupt_Flag = 0;
                applicationState = DISPLAY_I2C_CLIENT_INFO;   
            }
            break;
        case CLIENT2_SENSOR_SELECTION:
            uartCmdReceived = Eusart1_ReadInput();
            if(uartCmdReceived == INPUT_RECEIVED)
            {
                inputCmdBuffer = I2C_CLient2SensorCommand(userInput);
                dataLength = inputCmdBuffer;
                if(inputCmdBuffer)
                {
                    
                    applicationState = SEND_I2C_SENSOR_DATA_TO_UART; 
                }
                else
                {
                    applicationState = DISPLAY_I2C_CLIENT_INFO;
                }
                uartCmdReceived = 0;
                memset(userInput, 0 , sizeof(userInput[0]));
            }
            else if(timerInterrupt_Flag == SET)
            {
                EUSART1_SendString("Input not received\n");
                timerInterrupt_Flag = 0;
                applicationState = DISPLAY_I2C_CLIENT_INFO;   
            }
            break;
        case SEND_I2C_SENSOR_DATA_TO_UART:
            I2C_ClientWriteAndRead(clientAddress,dataRegisterAddress,WRITE_DATA_LENGTH ,readDataLength );
            for(uint8_t index = 0;index < dataLength;index++)
            {
                *clientRdDataBuffer = sensorDataRdBuffer[index];
                transmitBuffer = IntegerToAsciConver(*clientRdDataBuffer,string, baseValue);
                EUSART1_SendString((char*)(transmitBuffer));    
                EUSART1_SendString("\t");
            }  
            memset(sensorDataRdBuffer, 0 , sizeof(sensorDataRdBuffer));
            inputCmdBuffer = 0;
            dataLength = 0;
            applicationState = WAIT_STATE;
        case WAIT_STATE:
            __delay_ms(1000);
            applicationState = DISPLAY_INFORMATION;
            break;
        default:
            break;
    }
}

/*******************************************************************************
 * void EUSART1_SendString(char *str)
 *
 * API to transmit a sequence of characters on terminal window 
 * 
 *
 * @param *str - to send sequence of characters
 * @return void
 ******************************************************************************/
void EUSART1_SendString(char *str)
{
    for(uint8_t index = 0; index < strlen(str); index++)
    {
       while(0 == PIR1bits.TX1IF)
        {

        }
        
        EUSART1_Write(str[index]);
    }
}

/*******************************************************************************
 * uint8_t DecodeUartCmdForI2C_Client(char *command)
 *
 * API to decode the uart input command ,to check whether user entered correct 
 * client address or not.
 * 
 *
 * @param *command - user input is passed
 * @return if user entered input matches,then returns 1 for client 1 address match 
 * and returns 2 for client 2 address match
 ******************************************************************************/
uint8_t DecodeUartCmdForI2C_Client(char *command)
{
    uint8_t cmdFlag = 0;
    if(strcmp(command,CLIENT1) == 0)
    {
        EUSART1_SendString("Selected Client 1\n");
        EUSART1_SendString("Enter '1' to measure pH\n");
        Timer0_Start();
        cmdFlag = 1; 
    }
    else if(strcmp(command,CLIENT2)== 0)
    {
        EUSART1_SendString("Selected Client 2\n");
        EUSART1_SendString("Enter '2' to measure Temperature, '3' to measure Soil moisture, '4' to measure both sensors\n");
        Timer0_Start();
        cmdFlag = 2;
    }
    else
    {   
        EUSART1_SendString("Error! Incorrect CLIENT Address\n");
        cmdFlag = 0;
    }
    return (cmdFlag);
}

/*******************************************************************************
 * uint8_t Eusart1_ReadInput(void)
 *
 * API to receive the user input from the terminal window of data visualizer
 * 
 *
 * @param void 
 * @return 1 if input is received from the terminal window
 ******************************************************************************/
uint8_t Eusart1_ReadInput(void)
{
    uint8_t readFlag = 0 ;
    uint8_t inputStr;
    if(eusart1RxCount!=0)
    {
        Timer0_Stop();
        inputStr = EUSART1_Read();
        if(inputStr != '\n' && inputStr != '\r')
        {
            userInput[index++] = inputStr;
        }  
            
        if(inputStr == '\n')
        {
            userInput[index] = '\0';  //Null character is added to indicate the end of the string
            index = 0;
            readFlag  = UART_INPUT_RECEIVED;
        }
    }
    else
    {
        readFlag  = 0;
    }
    return (readFlag);
}

/*******************************************************************************
 * void SensorInformation(void)
 *
 * API to display information about I2C host and sensors connected to 
 * the client devices.
 * 
 *
 * @param void 
 * @return void
 ******************************************************************************/
void SensorInformation(void)
{
    EUSART1_SendString("\n\nTwo I2C Clients are connected to I2C Host\n");
    EUSART1_SendString("pH Sensor is connected to I2C Client1\n");
    EUSART1_SendString("Temperature Sensor and Soil Moisture Sensor are connected to I2C Client2\n");
}

/*******************************************************************************
 * void DisplayI2C_ClientAddrOnUART(void)
 *
 * API to display I2C Client address on terminal window of data visualizer and 
 * asks user to enter client address needs to be connected.
 *
 * 
 *
 * @param void 
 * @return void
 ******************************************************************************/
void DisplayI2C_ClientAddrOnUART(void)
{
    EUSART1_SendString("\nEnter '0x0A' address to connect I2C_Client1 or '0x0B' address to connect I2C_Client2\n");
}

/*******************************************************************************
 * uint8_t I2C_CLient1Command(char *command)
 *
 * API to check whether the user entered sensor input command is  correct or 
 * wrong. If correct then input command and sensor data register 
 * location address is transmitted to the client device through i2c interface.
 * 
 *
 * @param *command - user input is passed
 * @return update dataLength flag and return 1 if user input is  matched 
 ******************************************************************************/
uint8_t I2C_CLient1SensorCommand(char *command)
{
    uint8_t dataLengthFlag = 0;
  
    if(strcmp(command,SENSOR_1)== 0)
    {
        EUSART1_SendString("pH is : ");
        clientAddress = CLIENT1_ADDRESS;
        readDataLength = READ_ONE_BYTE;
        dataRegisterAddress = (uint8_t)sensor1DataRegister;
        dataLengthFlag = 1;
    }
    else
    {
        EUSART1_SendString("Error! Incorrect Client 1 Command\n");
        dataLengthFlag = 0;
    }
    return (dataLengthFlag);
}

/*******************************************************************************
 * uint8_t I2C_CLient2Command(char *command)
 *
 * API to check whether the user entered sensor input command is  correct or 
 * wrong. If correct then input command and sensor data register 
 * location address is transmitted to the client device through i2c interface.
 * 
 *
 * @param *command - user input is passed,
 * @return update dataLength flag and return values if user input is matched
 ******************************************************************************/
uint8_t I2C_CLient2SensorCommand(char *command)
{
    uint8_t dataLengthFlag = 0;
   
    if(strcmp(command,SENSOR_2)== 0)
    {
        EUSART1_SendString("Temperature in \260C: "); 
        clientAddress = CLIENT2_ADDRESS;
        readDataLength = READ_ONE_BYTE;
        dataRegisterAddress = (uint8_t)sensor2DataRegister;
        dataLengthFlag = 1; 
    }
    else if(strcmp(command,SENSOR_3)== 0)
    {
        EUSART1_SendString("Soil Moisture in \045: ");
        clientAddress = CLIENT2_ADDRESS;
        readDataLength = READ_ONE_BYTE;
        dataRegisterAddress = (uint8_t)sensor3DataRegister;
        dataLengthFlag = 1;  
    }
    else if(strcmp(command,SENSOR_2AND3)== 0)
    {
        EUSART1_SendString("Temperature in \260C and Soil Moisture in \045: ");
        clientAddress = CLIENT2_ADDRESS;
        readDataLength = READ_TWO_BYTE;
        dataRegisterAddress = (uint8_t)sensor2And3DataRegister;
        dataLengthFlag = 2;
    }
    else
    {
        EUSART1_SendString("Error! Incorrect Client 2 command\n");
        dataLengthFlag = 0;
    }
    
    return (dataLengthFlag);
}

/*******************************************************************************
 * uint8_t* IntegerToAsciConver(uint16_t num, uint8_t str[], uint16_t baseNumber)
 *
 * API to convert integer value into corresponding ASCII value
 * 
 * 
 *
 * @param num, str[], baseNumber
 * @return value converted to ASCII form
 ******************************************************************************/
uint8_t* IntegerToAsciConver(uint16_t num, uint8_t str[], uint16_t baseNumber)
{
    uint16_t index = 0;
    uint16_t rem;
   
    /* A zero is same "0" string in all base */
    if (num == 0) {
        str[index] = '0';
        str[index + 1] = '\0';
        return str;
    }
  
    while (num != 0) {
        rem = num % baseNumber;
        str[index++] = (uint8_t)(rem > 9)? (uint8_t)(rem-10) + 'A' :(uint8_t)rem + '0';
        num = num/baseNumber;
    }
  
    str[index] = '\0';
    Reverse(str, index);
  
    return str;
}

/*******************************************************************************
 * void Reverse(uint8_t str[], uint16_t len)
 *
 * API to reverse the string
 * 
 * 
 *
 * @param str[], len 
 * @return void
 ******************************************************************************/
void Reverse(uint8_t str[], uint16_t len)
{
    uint16_t  start, end;
    uint8_t temp;
    for(start=0, end=len-1; start < end; start++, end--) {
        temp = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = temp;
    }
}

/*******************************************************************************
 * void I2C_ClientWriteAndRead(const uint8_t clientAddress, uint8_t *sensorDataRegister, uint8_t i2cWriteDataLength, uint8_t i2cReadDataLength)
 *
 * API to perform I2C Write and Read operation
 * 
 * 
 *
 * @param clientAddress,*sensorDataRegister,i2cWriteDataLength, i2cReadDataLength
 * @return void       
 ******************************************************************************/
void I2C_ClientWriteAndRead(const uint8_t clientAddress, uint8_t *sensorDataRegister, uint8_t i2cWriteDataLength, uint8_t i2cReadDataLength)
{
    bool retState;
    retState = I2C1_Write(clientAddress,sensorDataRegister,i2cWriteDataLength); 
    if (retState)
    {
        while (I2C1_IsBusy());
    }
    DELAY_FUNCTION();
    retState = I2C1_Read(clientAddress,sensorDataRdBuffer,i2cReadDataLength);  
    if (retState)
    {
        while (I2C1_IsBusy());
    }
}

/*******************************************************************************
 * void TimerInterruptHandler(void)
 *
 * API to handle timer interrupt, which generates interrupt for every 15sec.
 * 
 * 
 *
 * @param void 
 * @return void
 ******************************************************************************/
void TimerInterruptHandler(void)
{
    timerInterrupt_Flag = 1;
}

