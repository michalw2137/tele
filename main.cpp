#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

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
    // copies all data into buffer
    byte* temp;
    std::vector<byte> solution;
    DWORD bytesRead;
    std::cout<<"nasluchuje";

    while(!ReadFile(port, temp, sizeof(temp), &bytesRead, NULL));
    std::cout<<"cos sie pojawilo";
    while(ReadFile(port, temp, sizeof(temp), &bytesRead, NULL)) {
        solution.push_back(*temp);
    }
    std::cout << "bytes read: " << solution.size();

    output << solution.data();
    std::cout << solution.data();


    output.close();
    return 0;
}
