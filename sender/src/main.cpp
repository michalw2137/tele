#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include "../include/typedef.h"

int main() {
    HANDLE port;
    port = CreateFileA(R"(\\.\COM21)",                //port name
                        GENERIC_READ | GENERIC_WRITE, //Read/Write
                        0,                            // No Sharing
                        NULL,                         // No Security
                        OPEN_EXISTING,// Open existing port only
                        0,            // Non Overlapped I/O
                        NULL);        // Null for Comm Devices

    if (port == INVALID_HANDLE_VALUE)
        throw std::runtime_error("failed to open port");

    //konfiguracja portu
    DCB dcbSerialParams = {0};
    GetCommState(port, &dcbSerialParams);
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    SetCommState(port, &dcbSerialParams);

    //konfiguracja timeouts
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 5000;		//in ms
    timeouts.ReadTotalTimeoutConstant = 5000;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    std::string fileName = "message.txt";
//    std::cout << "File to send: ";
//    getline(std::cin, fileName);

    std::ifstream input( "../files/" + fileName, std::ios::binary );
    // copies all data into buffer
    std::vector<byte> buffer(std::istreambuf_iterator<char>(input), {});

    DWORD bytesWritten;
    for(byte b: buffer)
        std::cout << b;
    std::cout << '\n';

    while(1)
    WriteFile(port, buffer.data(), buffer.size(), &bytesWritten, NULL);



    if (bytesWritten != buffer.size()) {
        std::cout << "bytes written: " << bytesWritten << '\n'
                    << "buffer size: " << buffer.size() << '\n';
    } else {
        std::cout << "All bytes sent";
    }


    CloseHandle(port);
    return 0;
}
