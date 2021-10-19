# ZMQonPXI

Jaehyung Choi
Valero Lab
Updated October 19, 2021

Currently, the PXI can do 2-way PUB SUB with the Raspbery Pi
The problem is that this works in other Visual Studio 2019 test projects, but not within the quickDAQ project
We've tried to use the ZMQ header files and functions within the quickDAQ project
We've also tried to build the quickDAQ project within the test Visual Studio project where PUB SUB is working

# Raspberry Pi
raspi.c and raspiwrap.h are the files in the Raspberry Pi titled test.c and wrap.h
Raspberry Pi: 
Open Putty
Select Raspi-test, and click Open
Username: pi
Password: raspberry
cd zmqClient/
gcc test1.c -o test1 -lzmq
./test1

# PXI
pxitest.c and pxiwrap.h are the files in Desktop > JaehyungTesting > Test2 > Test3 > (Test3.c and wrap.h)
Open Visual Studio 2019 and open Test3.sln
Run without debugging to run the code

# Python
We have pprog.py, which is an example that uses the wrapper functions.
We have pwrap.py, which is the Python wrapper library.


