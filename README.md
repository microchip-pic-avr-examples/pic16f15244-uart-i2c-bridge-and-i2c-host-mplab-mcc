<!-- Please do not change this logo with link -->

[![MCHP](images/microchip.png)](https://www.microchip.com)

# UART-I2C Bridge and I2C Host Implementation Using PIC16F15244 Microcontroller

## Introduction

Enhanced Universal Synchronous Asynchronous Receiver Transmitter (EUSART) and Inter Integrated Circuit (I2C) are  the most commonly used serial interfaces in embedded applications for communication with the external integrated circuits. Both of these serial interfaces can be used to enable communication between microcontrollers or microprocessors and also useful for interfacing IC modules supporting these serial interfaces to microcontrollers. Additionally, the EUSART interface is capable of communicating  with a terminal application on a personal computer. In some of the high-end applications, the microcontrollers, or microprocessors might fall short of USART peripheral instances or they are not supported by EUSART or I2C interface for communication with external ICs. In such applications, the PIC16F152xx family of microcontrollers can be used as a secondary microcontroller and act as an USART-I2C bridge.

This code example highlights a good use case where PIC16F152xx family microcontrollers can be used as USART-I2C bridge. It demonstrates how the user entered input commands on the PC terminal window is received by the host device through the EUSART interface. According to the input commands received, host device initiates I2C communication with the multiple client devices.

Refer to the code examples [UART-I2C Bridge Implementation: I2C Client(Client 1) Implementation Using PIC16F15244 Microcontroller](https://github.com/microchip-pic-avr-examples/pic16f15244-uart-i2c-bridge-i2c-client1-mplab-mcc) and [UART-I2C Bridge Implementation: I2C Client(Client 2) Implementation Using PIC16F15244 Microcontroller](https://github.com/microchip-pic-avr-examples/pic16f15244-uart-i2c-bridge-i2c-client2-mplab-mcc)


## Related Documentation

- [PIC16F152xx Product Family Page](https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/8-bit-mcus/pic-mcus/pic16f15244)
- [PIC16F152xx Family Code Examples on GitHub](https://github.com/orgs/microchip-pic-avr-examples/repositories?q=pic16f152&type=all&language=&sort=) 
- [PIC16F15244 MCU Family Video](https://www.youtube.com/watch?v=nHLv3Th-o-s)
- [PIC16F15244 MCU Product Page](https://www.microchip.com/wwwproducts/en/PIC16F15244?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_PIC16F15244&utm_content=pic16f15244-uart-i2c-bridge-i2c-host-mplab-mcc-github&utm_bu=MCU08)
- [Technical Brief - Using the MSSP in I2C Master mode](https://www.microchip.com/wwwappnotes/appnotes.aspx?appnote=en1001796)
- [Technical Brief – Using the MSSP in I2C Slave mode](https://www.microchip.com/wwwappnotes/appnotes.aspx?appnote=en1001796)
- [Application Note – AN3538 A Simple Water Monitoring System with I2C Communication](https://ww1.microchip.com/downloads/en/Appnotes/A-Simple-Water-Monitoring-System-with%20I2C-Communication-DS00003538A.pdf)
- [GitHub Microchip PIC Examples: UART-I2C Bridge Implementation: I2C Client(Client 1) Implementation using PIC16F15244 Microcontroller](https://github.com/microchip-pic-avr-examples/pic16f15244-uart-i2c-bridge-i2c-client1-mplab-mcc)
- [GitHub Microchip PIC Examples: UART-I2C Bridge Implementation: I2C Client(Client 2) Implementation using PIC16F15244 Microcontroller](https://github.com/microchip-pic-avr-examples/pic16f15244-uart-i2c-bridge-i2c-client2-mplab-mcc)


## Description 

In this code example, the PIC16F15244 microcontroller communicates with Data Visualizer terminal window application, running on a PC, through USART interface and receives user inputs/commands. Based on the commands received from the user, the PIC16F15244 microcontroller communicates with the I2C client devices, collects and transmits the required sensors data to the PC to display it on the terminal window. This way, the PIC16F15244 microcontroller acts as an EUART-I2C bridge to communicate with the Data Visualizer terminal window application and acts as a I2C host device to communicate with the I2C client devices.

The code example uses two I2C clients, named as client 1 and client 2, which are based on the PIC16F15244 microcontroller. Figure 1 shows the block diagram view of the application.

<p align="left">
  <img width=auto height=auto src="images/block diagram.png">
  <br>Figure 1 : Block diagram view of the application<br>
</p>

For the purpose of demonstration, pH sensor is interfaced to client 1 while temperature and capacitive soil moisture sensors are interfaced to client 2. Both the clients collects data periodically from the sensors, process the acquired data and keep the data ready to transmit to the host device over the I2C interface. 

The input commands and clients I2C address information has been displayed on the terminal window of data visualizer. The user needs to enter a client device address from where the sensor data needs to be collected. If the entered client device address is correct, then the next input command, asking the user to enter sensor information from where data needs to be collected, is displayed on the terminal window. After entering the correct sensor information, the host device establishes I2C communication with the respective client device and requests to send the processed sensor data. The client device responds back to the host request with the processed sensor data. Upon receiving the sensor data, the host device transmits data to the Data Visualizer tool through UART interface, for displaying it on the terminal window. If the user entered client address or sensor input command is incorrect, then the terminal window displays the supplied information as incorrect and requests the user to re-enter the details.

## Software Used

- [MPLAB® X IDE](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_pic16f15244&utm_content=pic16f15244-uart-i2c-bridge-i2c-host-mplab-mcc-github&utm_bu=MCU08) 6.25 or newer
- [MPLAB® XC8 Compiler](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_PIC16F15244&utm_content=pic16f15244-uart-i2c-bridge-i2c-host-mplab-mcc-github&utm_bu=MCU08) 3.00 or a newer
- [MPLAB® Code Configurator (MCC)](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_PIC16F15244&utm_content=pic16f15244-uart-i2c-bridge-i2c-host-mplab-mcc-github&utm_bu=MCU08) 5.6.2 or newer
- [Microchip PIC16F1xxxx Series Device Support](https://packs.download.microchip.com/) 1.27.418 or newer
- [Standalone Data Visualizer](https://www.microchip.com/en-us/development-tools-tools-and-software/embedded-software-center/mplab-data-visualizer?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_pic16f15244&utm_content=pic16f15244-uart-i2c-bridge-i2c-host-mplab-mcc-github&utm_bu=MCU08) 2.20.674 or newer
- MSSP MCC Melody Core 7.0.3
- TMR0 MCC Melody Core 5.1.0
- UART MCC Melody Core 1.10.2

**Note:** 

 1. Integrated MPLAB Data visualizer can also be used as a terminal window.
 2. For running this demo, the installed tool version must be same or later. This example is not tested with the previous versions.


## Hardware Used

- Curiosity Nano Base for Click boards™[AC164162](https://www.microchip.com/en-us/development-tool/AC164162?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_PIC16F15244&utm_content=pic16f15244-uart-i2c-bridge-i2c-host-mplab-mcc-github&utm_bu=MCU08)
- PIC16F15244 Curiosity Nano Evaluation Kit [EV09Z19A](https://www.microchip.com/en-us/development-tool/EV09Z19A?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_PIC16F15244&utm_content=pic16f15244-uart-i2c-bridge-i2c-host-mplab-mcc-github&utm_bu=MCU08)
- SHT AN Click [MIKROE-3984](https://www.mikroe.com/sht-an-click)
- PH Sensor [EC-4743](https://www.electronicscomp.com/analog-ph-sensor-kit-for-arduino?gclid=EAIaIQobChMIhfv3t-q58QIVu4NLBR2VKQGWEAYYAyABEgKhdPD_BwE)
- Capacitive Soil Moisture Sensor V2.0 [EC-5092](https://www.electronicscomp.com/capacitive-soil-moisture-sensor-v2?gclid=EAIaIQobChMI3YCgheq58QIVxZVLBR1PZQKPEAQYAiABEgJW9_D_BwE)

## Application Firmware:

This example is supplemented with three standalone firmware packs named as host firmware, client 1 firmware and client 2 firmware. 

The host firmware handles command line interface which allows the user to enter input commands on the terminal window of Data Visualizer. Depending on the user input commands, the host device initiates I2C communication with the relevant client devices. The host device requests the client device to send processed data of a specific sensor through I2C interface and displays the received data on the terminal window. 

The client firmware acquires the connected sensor data periodically through the Analog-to-Digital Converter (ADC) interface, and stores it at a designated location in data memory. After that, the client device enters Sleep mode. The client device wakes up from the Sleep mode only when I2C Start bit is detected or the sleep period has elapsed. If I2C Start bit is detected, the client device reads the requested sensor data from memory and sends it to the host device through the I2C interface. If the timer wait period has elapsed, then the client device measures the connected sensor data, processes and stores it at the designated location in data memory. If there is no further activity on the I2C interface for a certain period, then the client device enters the Sleep mode.

## Hardware Setup:

The PIC16F15244 Curiosity Nano evaluation kit is used to setup the host and client devices. The following figure shows the hardware setup of the application and interconnections between the host and client boards. Refer to the hardware connection details table for more information. 

<p align="left">
  <img width=auto height=auto src="images/hardware setup.png">
  <br>Figure 2 : Hardware Connection Details<br>
</p>

## Hardware Connection details:

Host microcontroller pin connection details.

| Microcontroller pin | Peripheral | Signal Description |
|:----------:|:-----------:|:---------:|	
| RB4	| I2C peripheral	        | Serial Clock	| 	
| RB6 	| I2C peripheral	        | Serial Data	|  
| RC1 	| EUSART peripheral 	        | RX            |  
| RC0 	| EUSART peripheral     	| TX	        | 


Client 1 microcontroller pin connection details

| Development board/Click board| Microcontroller pin| Peripheral| Signal description|
|:----------:|:-----------:|:---------:|:---------:|	
| PIC16F15244 Curiosity Nano board| RB4| I2C peripheral | Serial Clock	| 	
| PIC16F15244 Curiosity Nano board| RB6| I2C peripheral	| Serial Data	|  
| pH Sensor| RC4| GPIO | pH sensor output|  

	
Client 2 microcontroller pin connection details

| Development board/Click board| Pin Name| Peripheral| Signal Description|
|:----------:|:-----------:|:---------:|:---------:|	
| PIC16F15244 Curiosity Nano board| RB4| I2C peripheral | Serial Clock	| 	
| PIC16F15244 Curiosity Nano board| RB6| I2C peripheral	| Serial Data	|  
| SHT AN click| RB7| GPIO | Temperature sensor output|  
| SHT AN click| RC7| GPIO | Channel selection |
| Soil Moisture sensor| RC4| GPIO | Soil sensor output|

Steps to open Terminal window in Data Visualizer:

Use the terminal window of the standalone Data Visualizer tool to receive user input through the PC keyboard and to display the processed sensor data. Follow the below steps to open the terminal window.

1. In the Data Visualizer window, click the **Configuration** tab.
2. In the Modules section, expand External connection option and then double click Serial port.
3. From Serial Port Control Panel, select the Curiosity Virtual Com Port which is connected to the host device.
4. Check the “Open Terminal” option.
5. Check the “Add \r\n” option which allows the user to enter input command on the terminal window as shown in the figure below.
6. Click on **Connect** button and then the terminal window is opened.

<p align="left">
  <img width=auto height=auto src="images/data visualizer.png">
  <br>Figure 3 : Data Visualizer<br>
</p>

## Demo Operation:

-	Connect the hardware as shown in the Hardware Setup section . Power up the host and two client boards using micro-B USB cable
-	Load the host application firmware to the PIC16F15244 Curiosity Nano board which is connected to both clients through the I2C interface
-	Load the client 1 application firmware to the PIC16F15244 Curiosity Nano board with the pH sensor interface 
-	Load the client 2 application firmware to the PIC16F15244 Curiosity Nano with Temperature and Soil moisture sensor interface
-	Initially, the client device address and sensor information is displayed in the terminal window as shown in the figure below.

<p align="left">
  <img width=auto height=auto src="images/output1.png">
</p>

-	If the user fails to provide an input command within 15 seconds, the host displays the text "Input not received" and asks the user to enter the input command again, as shown in the figure below.

<p align="left">
  <img width=auto height=auto src="images/output2.png">
</p>

-	If an incorrect client device address is entered, then it displays the text “Error! Incorrect CLIENT Address” and asks the user to enter the input command again, as shown in the figure below. 
 
<p align="left">
  <img width=auto height=auto src="images/output3.png">
</p>

-	Enter client 1 device address “0x0A” on the terminal window as shown in the figure below.

<p align="left">
  <img width=auto height=auto src="images/output4.png">
</p>

-	After entering the client address, it displays the next input command on the terminal window. Then enter the input “1” to select the pH sensor which is interfaced to the client 1 device, as shown in the figure below.

<p align="left">
  <img width=auto height=auto src="images/output5.png">
</p>

-	The measured sensor data transmitted from the client device 1 through the I2C interface is displayed on the terminal window, as shown in the figure below. After that, the sensor information and the input commands are displayed on the terminal window again.

<p align="left">
  <img width=auto height=auto src="images/output6.png">
</p>

-	Enter client 2 device address 0x0B and check if the entered address is correct, then it displays the text “Selected Client  2” on the terminal window. The next input command is displayed and enter input "1" to select the temperature sensor which is interfaced to the client 2 device. The transmitted temperature data through the I2C interface is displayed on the terminal window, as shown in the figure below. After that, the sensor information and the input commands are displayed on the terminal window again.

<p align="left">
  <img width=auto height=auto src="images/output7.png">
</p>

-	Again, enter client 2 device address 0x0B and enter input "2" to select soil moisture sensor data which is interfaced to the client 2 device.  Transmitted  soil moisture data through I2C interface is displayed on terminal window as shown in below figure.  After that again sensor information and input commands are displayed on the terminal window.

<p align="left">
  <img width=auto height=auto src="images/output8.png">
</p>

-	After entering client 2 device address, enter input "4"  to select both sensors interfaced to the client 2 device. The data of these two sensors which is transmitted through the I2C interface is displayed on the terminal window, as shown in the figure below.

<p align="left">
  <img width=auto height=auto src="images/output9.png">
</p>

## Conclusion

Many real-time applications require the EUSART-I2C bridge to connect the microcontroller to other devices like: PC, microprocessor or the IC modules. It can also be used for the remote debug of I2C devices via an external PC or terminal program like Tera Term, Putty, etc.... This code example demonstrates the EUSART-I2C bridge implementation between PC and PIC16F152xx family of microcontrollers.






