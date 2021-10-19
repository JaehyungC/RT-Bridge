# ZMQonPXI

Jaehyung Choi<br>
Valero Lab<br>
Updated October 19, 2021<br>

Currently, the PXI can do 2-way PUB SUB with the Raspbery Pi<br>
The problem is that this works in other Visual Studio 2019 test projects, but not within the quickDAQ project<br>
We've tried to use the ZMQ header files and functions within the quickDAQ project<br>
We've also tried to build the quickDAQ project within the test Visual Studio project where PUB SUB is working<br>

# Raspberry Pi
raspi.c and raspiwrap.h are the files in the Raspberry Pi titled test.c and wrap.h<br>
Raspberry Pi:<br>
Open Putty<br>
Select Raspi-test, and click Open<br>
Username: pi<br>
Password: raspberry<br>
cd zmqClient/<br>
gcc test1.c -o test1 -lzmq<br>
./test1<br>

# PXI
pxitest.c and pxiwrap.h are the files in Desktop > JaehyungTesting > Test2 > Test3 > (Test3.c and wrap.h)<br>
Open Visual Studio 2019 and open Test3.sln<br>
Run without debugging to run the code<br>

# Python
We have pprog.py, which is an example that uses the wrapper functions.<br>
We have pwrap.py, which is the Python wrapper library.<br>


