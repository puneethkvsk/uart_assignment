import serial
from serial.tools import list_ports
import time
import os
import platform

PORT_NAME_0 = "/dev/ttyUSB0"
PORT_NAME_1 = "/dev/ttyUSB1"

port_list = []

microcontroller = None
name = None
conn = None

data_to_send = "Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for predicting that the next banking crisis would be triggered by MSME lending, saying postmortem is easier than taking action when it was required. Rajan, who had as the chief economist at IMF warned of impending financial crisis of 2008, in a note to a parliamentary committee warned against ambitious credit targets and loan waivers, saying that they could be the sources of next banking crisis. Government should focus on sources of the next crisis, not just the last one. In particular, government should refrain from setting ambitious credit targets or waiving loans. Credit targets are sometimes achieved by abandoning appropriate due diligence, creating the environment for future NPAs,\" Rajan said in the note.\" Both MUDRA loans as well as the Kisan Credit Card, while popular, have to be examined more closely for potential credit risk. Rajan, who was RBI governor for three years till September 2016, is currently."
# data_to_send = "`qweRTYuIoPAsdFgHjKlZzXcvBnMmNxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZpXcVvBnNmMxBvCtDfuGyHjKkLlZ"

data_received = ""

com_ports = serial.tools.list_ports.comports(include_links=True)
for i in com_ports:
    port_list.append(i.device)
print(port_list)

for i in range(len(port_list)):
    if (port_list[i] == PORT_NAME_0) or (port_list[i] == PORT_NAME_1):
        conn = serial.Serial(port_list[i], 2400, timeout=1)
        if conn == None:
            print("Serial port connection error")
        else:
            print("Serial connection to ", str(port_list[i]), " successful")
        time.sleep(2)

        while data_received == "":
            data_received = conn.readline().decode('utf-8').rstrip()
        if data_received == "Start":
            print("Communicating with MCU...")

        conn.flush()
        conn.flushInput()

        # conn.flush()
        # conn.flushInput()
        # conn.close()
    # else:
    #     print("PORT_NAME defined not found in serial list")

if conn != None:
    print("Transmitting data...")
    # data_to_send = str(input("Enter string: "))
    conn.write(data_to_send.encode())
    # time.sleep(10)
    print("Data Sent: ", data_to_send)
    data_received = ""
    while data_received == "":
        data_received = conn.readline().decode('utf-8').rstrip()
    print("Data Received: ", data_received)
    # if data_received == data_to_send:
    #     print("Data Received: ", data_to_send)

