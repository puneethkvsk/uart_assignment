# uart_assignment - Nymble

### Assignment notes:
I used a STM32H723 microcontroller. It is a single core chip. I used python script to send string data to the microcontroller @ 2400 Baud rate. Upon receiving data, I parallely stored it in the Flash memory to access it again, to echo it back to the PC, post reception of the string.

### Additional Notes:
Please find the microcontroller code I wrote in the directory: uart_assignment/uart_project/Core/Src/main.c. All code is written into a single while loop.
Please find the script I wrote in the directory : Script/main.py.

### Video details:
00:44 - Start script execution, connect to MCU, send data to MCU post connection with MCU.

00:50 - Data transmission from PC to MCU.

01:25 - Show FLASH memory to see what is stored

05:34 - Data stored in FLASH memory and ready to echo back to PC

06:25 - Data transmitted from MCU to PC via serial port

### Bugs:
1. Buffer overflow corner case issue
