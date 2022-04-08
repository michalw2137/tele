#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include "../include/typedef.h"
#include "../include/codes.h"

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

    std::string fileName = "jpg.jpg";
//    std::cout << "File to send: ";
//    getline(std::cin, fileName);
    std::ifstream input( "../files/" + fileName, std::ios::binary );
    // copies all data into buffer
    std::vector<byte> buffer(std::istreambuf_iterator<char>(input), {});

    DWORD bytesWritten;
    DWORD bytesRead;

    for(byte b: buffer)
        std::cout << b;
    std::cout << '\n';

//    while(1)
    WriteFile(port, buffer.data(), buffer.size(), &bytesWritten, NULL);

    byte answer;
    std::cout << "Expected: NAK = " << NAK << '\n';
    while (true) {
        ReadFile(port, &answer, sizeof(answer), &bytesRead, NULL);

        if (bytesRead == 0) {
            std::cout << "no bytes read" << '\n';
        } else {
            std::cout << " BYTES READ: " << bytesRead <<'\n';
            std::cout << answer << '\n';
        }

    }


    CloseHandle(port);
    return 0;
}
