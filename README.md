# uart_assignment
## Nymble

Please find the microcontroller code I wrote in the directory: uart_assignment/Core/Src/main.c
Please find the script I wrote in the directory : Script/main.py

Assignment notes:
I used a STM32H723 microcontroller. It is a single core chip.I used python script to send string data to the microcontroller @ 2400 Baud rate. Upon receiving data, I parallely stored it in the Flash memory to access it again, to echo it back to the PC, post receiving of the string

Bugs:
1. Flash data storage does not work in real time.
2. Buffer overflow corner case issue.
