#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include "../include/codes.h"

int main() {
    HANDLE port;
    port = CreateFileA(R"(\\.\COM37)",                //port name
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
    SetCommTimeouts(port, &timeouts);

    std::string fileName = "test.txt";
//    std::cout << "Name to save received file under: ";
//    getline(std::cin, fileName);
    std::ofstream output( "../received/" + fileName, std::ios::binary );
    DWORD bytesRead = 0;
    DWORD bytesWritten = 0;

    byte startConnection;
    if (true) {
        startConnection = NAK;
    } else {
        startConnection = C;
    }

    int SIZE = 0;
    if (true) {
        SIZE = 128 + 3;
    } else {
        SIZE = 128 + 4;
    }
    byte answer[SIZE];

    for (int i = 0; i < 60; i++){
        bool isSuccesful = WriteFile(port, &NAK, 1, &bytesWritten, NULL);
        std::cout << "poczatek wczytywania \n";
        ReadFile(port, answer, SIZE, &bytesRead, NULL);
        std::cout << "koniec wczytywania \n";
        if (bytesRead == 0) {
            std::cout << "no bytes read" << '\n';
        } else {
            std::cout << " BYTES READ: " << bytesRead <<'\n';
            std::cout << answer << '\n';
        }
        Sleep(10 * 1000);
    }


    output.close();
    return 0;
}
