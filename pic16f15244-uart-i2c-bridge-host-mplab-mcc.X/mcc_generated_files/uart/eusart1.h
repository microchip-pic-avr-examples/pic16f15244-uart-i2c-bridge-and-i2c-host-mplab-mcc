/**
 * EUSART1 Generated Driver API Header File
 * 
 * @file eusart1.h
 * 
 * @defgroup eusart1 EUSART1
 * 
 * @brief This file contains API prototypes and other datatypes for the Enhanced Universal Synchronous and Asynchronous Receiver Transceiver (EUSART) module.
 *
 * @version EUSART1 Driver Version 3.0.2
*/
/*
� [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef EUSART1_H
#define EUSART1_H


#include <stdbool.h>
#include <stdint.h>
/**
    @ingroup eusart1 
    @def Standard Input Output functions
    @misradeviation{@required, 21.6} This inclusion is essential for UART module to use Printf function for print the character.
*/
/* cppcheck-suppress misra-c2012-21.6 */
#include <stdio.h>
#include "../system/system.h"
#include "uart_drv_interface.h"

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif


#define UART1_interface UART1


#define UART1_Initialize     EUSART1_Initialize
#define UART1_Deinitialize   EUSART1_Deinitialize
#define UART1_Write          EUSART1_Write
#define UART1_Read           EUSART1_Read
#define UART1__IsRxReady     EUSART1_IsRxReady
#define UART1_IsTxReady      EUSART1_IsTxReady
#define UART1_IsTxDone       EUSART1_IsTxDone

#define UART1_TransmitEnable       EUSART1_TransmitEnable
#define UART1_TransmitDisable      EUSART1_TransmitDisable
#define UART1_AutoBaudSet          EUSART1_AutoBaudSet
#define UART1_AutoBaudQuery        EUSART1_AutoBaudQuery
#define UART1_BRGCountSet                (NULL)
#define UART1_BRGCountGet                (NULL)
#define UART1_BaudRateSet                (NULL)
#define UART1_BaudRateGet                (NULL)
#define UART1__AutoBaudEventEnableGet    (NULL)
#define UART1_ErrorGet             EUSART1_ErrorGet

#define UART1_TxCompleteCallbackRegister     EUSART1_TxCompleteCallbackRegister
#define UART1_RxCompleteCallbackRegister      EUSART1_RxCompleteCallbackRegister
#define UART1_TxCollisionCallbackRegister  (NULL)
#define UART1_FramingErrorCallbackRegister EUSART1_FramingErrorCallbackRegister
#define UART1_OverrunErrorCallbackRegister EUSART1_OverrunErrorCallbackRegister
#define UART1_ParityErrorCallbackRegister  (NULL)
#define UART1_EventCallbackRegister        (NULL)


/**
 @ingroup eusart1
 @struct eusart1_status_t
 @brief This is a structure defined for errors in reception of data.
 */
 /**
 * @misradeviation{@advisory,19.2}
 * The UART error status necessitates checking the bitfield and accessing the status within the group byte therefore the use of a union is essential.
 */
 /* cppcheck-suppress misra-c2012-19.2 */
typedef union {
    struct {
        uint8_t perr : 1;     /**<This is a bit field for Parity Error status*/
        uint8_t ferr : 1;     /**<This is a bit field for Framing Error status*/
        uint8_t oerr : 1;     /**<This is a bit field for Overfrun Error status*/
        uint8_t reserved : 5; /**<Reserved*/
    };
    size_t status;            /**<Group byte for status errors*/
}eusart1_status_t;





/**
 * @ingroup eusart1
 * @brief External object for eusart1_interface.
 */
extern const uart_drv_interface_t UART1;

/**
 * @ingroup eusart1
 * @brief Initializes the EUSART1 module. This routine is called
 *        only once during system initialization, before calling other APIs.
 * @param None.
 * @return None.
 */
void EUSART1_Initialize(void);

/**
 * @ingroup eusart1
 * @brief Deinitializes and disables the EUSART1 module.
 * @param None.
 * @return None.
 */
void EUSART1_Deinitialize(void);

/**
 * @ingroup eusart1
 * @brief This API enables the EUSART1 module.     
 * @param None.
 * @return None.
 */
void EUSART1_Enable(void);

/**
 * @ingroup eusart1
 * @brief This API disables the EUSART1 module.
 * @param None.
 * @return None.
 */
void EUSART1_Disable(void);

/**
 * @ingroup eusart1
 * @brief This API enables the EUSART1 transmitter.
 *        The EUSART1 must be enabled to send the bytes over to the TX pin.
 * @param None.
 * @return None.
 */
void EUSART1_TransmitEnable(void);

/**
 * @ingroup eusart1
 * @brief This API disables the EUSART1 transmitter.
 * @param None.
 * @return None.
 */
void EUSART1_TransmitDisable(void);

/**
 * @ingroup eusart1
 * @brief This API enables the EUSART1 receiver.
 *        The EUSART1 must be enabled to receive the bytes sent by the RX pin.
 * @param None.
 * @return None.
 */
void EUSART1_ReceiveEnable(void);

/**
 * @ingroup eusart1
 * @brief This API disables the EUSART1 receiver.
 * @param None.
 * @return None.
 */
void EUSART1_ReceiveDisable(void);

/**
 * @ingroup eusart1
 * @brief This API enables the EUSART1 transmitter interrupt.
 * @param None.
 * @return None.
 */
void EUSART1_TransmitInterruptEnable(void);

/**
 * @ingroup eusart1
 * @brief This API disables the EUSART1 transmitter interrupt.
 * @param None.
 * @return None.
 */
void EUSART1_TransmitInterruptDisable(void);

/**
 * @ingroup eusart1
 * @brief This API enables the EUSART1 receiver interrupt.
 * @param None.
 * @return None.
 */
void EUSART1_ReceiveInterruptEnable(void);

/**
 * @ingroup eusart1
 * @brief This API disables the EUSART1 receiver interrupt.
 * @param None.
 * @return None.
 */
void EUSART1_ReceiveInterruptDisable(void);

/**
 * @ingroup eusart1
 * @brief This API enables the EUSART1 to send a break control. 
 * @param None.
 * @return None.
 */
void EUSART1_SendBreakControlEnable(void);

/**
 * @ingroup eusart1
 * @brief This API disables the EUSART1 send break control.
 * @param None.
 * @return None.
 */
void EUSART1_SendBreakControlDisable(void);

/**
 * @ingroup eusart1
 * @brief This API enables the EUSART1 AutoBaud Detection (ABR). 
 * @param bool enable.
 * @return None.
 */
void EUSART1_AutoBaudSet(bool enable);

/**
 * @ingroup eusart1
 * @brief This API reads the EUSART1 ABR Complete bit.
 * @param None.
 * @return bool.
 */
bool EUSART1_AutoBaudQuery(void);

/**
 * @ingroup eusart1
 * @brief This API reads the EUSART1 ABR Overflow bit.
 * @param None.
 * @return None.
 */
bool EUSART1_IsAutoBaudDetectOverflow(void);

/**
 * @ingroup eusart1
 * @brief This API resets the EUSART1 ABR Overflow bit.
 * @param None.
 * @return None.
 */
void EUSART1_AutoBaudDetectOverflowReset(void);

/**
 * @ingroup eusart1
 * @brief This API checks if the EUSART1 has received available data.
 * @param None.
 * @retval true if EUSART1 receiver FIFO has a data
 * @retval false EUSART1 receiver FIFO is empty
 */
bool EUSART1_IsRxReady(void);

/**
 * @ingroup eusart1
 * @brief This function checks if the EUSART1 transmitter is ready to accept a data byte.
 * @param None.
 * @retval true if EUSART1 transmitter FIFO has atleast 1 byte space
 * @retval false if EUSART1 transmitter FIFO is full
 */
bool EUSART1_IsTxReady(void);

/**
 * @ingroup eusart1
 * @brief This function returns the status of Transmit Shift Register (TSR).
 * @param None.
 * @retval true if Data completely shifted out from the TSR
 * @retval false if Data is present in Transmit FIFO and/or in TSR
 */
bool EUSART1_IsTxDone(void);

/**
 * @ingroup eusart1
 * @brief This function receives the error status of the last read byte.
 * @param None.
 * @return Status of the last read byte. See eusart1_status_t struct for more details.
 */
size_t EUSART1_ErrorGet(void);

/**
 * @ingroup eusart1
 * @brief This function reads the 8 bits from the FIFO register receiver.
 * @pre The transfer status must be checked to see if the receiver is not empty
 *      before calling this function. Verify the EUSART1_IsRxReady(), before calling this API.
 * @param None.
 * @return 8-bit data from RX FIFO register.
 */
uint8_t EUSART1_Read(void);

/**
 * @ingroup eusart1
 * @brief This function writes a byte of data to the transmitter FIFO register.
 * @pre The transfer status must be checked to see if the transmitter is ready to accept a byte
 *      before calling this function. Verify the EUSART1_IsTxReady() before calling this API.
 * @param txData  - Data byte to write to the TX FIFO.
 * @return None.
 */
void EUSART1_Write(uint8_t txData);

/**
 * @ingroup eusart1
 * @brief This API registers the function to be called upon framing error.
 * @param callbackHandler - a function pointer which will be called upon framing error condition.
 * @return None.
 */
void EUSART1_FramingErrorCallbackRegister(void (* callbackHandler)(void));

/**
 * @ingroup eusart1
 * @brief This API registers the function to be called upon overrun error.
 * @param callbackHandler - a function pointer which will be called upon overrun error condition.
 * @return None.
 */
void EUSART1_OverrunErrorCallbackRegister(void (* callbackHandler)(void));

/**
 * @ingroup eusart1
 * @brief This indicates the function that will be called upon transmit interrupt.
 * @pre Initialize the EUSART1 module with transmit interrupt enabled
 * @param None.
 * @return None.
 */
extern void (*EUSART1_TxInterruptHandler)(void);

/**
 * @ingroup eusart1
 * @brief This API registers the function to be called upon after data has been successfully transmitted.
 * @param callbackHandler - a function pointer which will be called upon transmitter interrupt condition.
 * @return None.
 */
void EUSART1_TxCompleteCallbackRegister(void (* callbackHandler)(void));

/**
 * @ingroup eusart1
 * @brief This ISR function is called upon transmitter interrupt.
 * @param void.
 * @return None.
 */
void EUSART1_TransmitISR(void);

/**
 * @ingroup eusart1
 * @brief This indicates the function that will be called upon receive interrupt.
 * @pre Initialize the EUSART1 module with receive interrupt enabled
 * @param None.
 * @return None.
 */
extern void (*EUSART1_RxInterruptHandler)(void);
/**
 * @ingroup eusart1
 * @brief This API registers the function to be called upon after data has been successfully received.
 * @param callbackHandler - a function pointer which will be called upon receiver interrupt condition.
 * @return None.
 */
void EUSART1_RxCompleteCallbackRegister(void (* callbackHandler)(void));

/**
 * @ingroup eusart1
 * @brief This ISR function is called upon receiver interrupt.
 * @param void.
 * @return None.
 */
void EUSART1_ReceiveISR(void);

/**
 * @ingroup eusart1
 * @brief This function used to printf support for reads the 8 bits from the FIFO register receiver.
 * @param None.
 * @return 8-bit data from RX FIFO register.
 */
int getch(void);

/**
 * @ingroup eusart1
 * @brief This function used to printf support for writes a byte of data to the transmitter FIFO register.
 * @param txData  - Data byte to write to the TX FIFO.
 * @return None.
 */
void putch(char txData);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // EUSART1_H
