#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <cstring>
#include "../include/typedef.h"
#include "../include/codes.h"
#include <math.h>       /* floor */

void fillHeader(byte header[3], byte i) {
    header[0] = SOH;
    header[1] = i;
    header[2] = 255-i;
}

int main() {
    bool isSuccesful;
    int SUM_SIZE = 1;

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
    timeouts.ReadIntervalTimeout = 5000;        //in ms
    timeouts.ReadTotalTimeoutConstant = 5000;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    std::string fileName = "message.txt";
//    std::cout << "File to send: ";
//    getline(std::cin, fileName);
    std::ifstream input("../files/" + fileName, std::ios::binary);
    // copies all data into buffer
    std::vector<byte> buffer(std::istreambuf_iterator<char>(input), {});

    DWORD bytesWritten;
    DWORD bytesRead;

    for (byte b: buffer)
        std::cout << b;
    std::cout << '\n';

//    byte i = 0;
    byte header[3];

    // wysłanie nagłówka
//    fillHeader(header, i);
//    isSuccesful = WriteFile(port, header, 3, &bytesWritten, NULL);

    // wysłanie danych
    // pełne bloki
    byte i=0;
    while (i < floor(buffer.size() / 128)) {
        byte data[128];
        for (int ii=0; ii<128; ii++) {
            data[ii] = buffer[128*i + ii];
        }
        std::cout << (int) i << " block: \n";
        for (byte ii : data) {
            std::cout << ii;
        }
        std::cout << "\n";
        i++;
    }
    // niepełny blok
    byte bytesLeft = buffer.size() - (i * 128);
    if (bytesLeft > 0) {
        std::cout << "\nNIEPELNY BLOK \n";
        byte data[128];
        int ii = 0;
        //wpisanie pozostalych bajtow
        while (ii < bytesLeft) {
            data[ii] = buffer[128*i + ii];
            ii++;
        }
        //dopisanie zer
        while (ii < 128) {
            data[ii] = 'x';
            ii++;
        }

        std::cout << (int) i << " block: \n";
        for (byte ii : data) {
            std::cout << ii;
        }
        std::cout << "\n";
        i++;
    }
//    isSuccesful = WriteFile(port, data, 128, &bytesWritten, NULL);

    //wysłanie sumy kotrolnej
    byte sum[SUM_SIZE];

//    isSuccesful = WriteFile(port, sum, SUM_SIZE, &bytesWritten, NULL);





    CloseHandle(port);
    return 0;
}
