#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include "../include/codes.h"

byte algebraicSum(const byte bytes[128]){
    byte sum = 0;
    for(int i=0; i<128; i++){
        sum += bytes[i];
        sum %= 256;
    }
    return sum;
}


int main() {
    bool isSuccesful;

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
    timeouts.ReadTotalTimeoutConstant = 3333;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(port, &timeouts);

    std::string fileName = "jpg.jpg";
    std::ofstream output( "../received/" + fileName, std::ios::binary );
    DWORD bytesRead = 0;
    DWORD bytesWritten = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    byte init = NAK;
    int SUM_SIZE = 1;

    byte code = 0;
    byte blockNumber = 0;
    byte complement = 255;

    byte block[128];
    byte sum;
    std::vector<byte> received;

    for (int i = 0; i < 6; i++) {
        // wysyła NAK
        isSuccesful = WriteFile(port, &init, 1, &bytesWritten, NULL);
        std::cout << "NAK sent \n";

        //wczytaj nagłówek
        ReadFile(port, &code, 1, &bytesRead, NULL);
        ReadFile(port, &blockNumber, 1, &bytesRead, NULL);
        ReadFile(port, &complement, 1, &bytesRead, NULL);

        if (code == SOH) {
            break;
        }
    }
    int number = 0;
    bool readHeader = false;
    while(code != EOT) {
        if (readHeader) {
            //wczytaj nagłówek
            ReadFile(port, &code, 1, &bytesRead, NULL);
            if (code == EOT) {
                std::cout << "eot received \n";
                break;
            }
            ReadFile(port, &blockNumber, 1, &bytesRead, NULL);
            ReadFile(port, &complement, 1, &bytesRead, NULL);
        }
        readHeader = true;

        //wczytaj blok
        ReadFile(port, block, 128, &bytesRead, NULL);
        for (int i=0; i<128; i++)
            std::cout << block[i];
        std::cout << '\n';

        //wczytaj sume kontrolna
        ReadFile(port, &sum, 1, &bytesRead, NULL);
        std::cout << "sum: " << (int)sum << '\n';

        //policz sumę kontrolna
        byte calculatedSum = algebraicSum(block);
        std::cout << "calculated: " << (int)calculatedSum << '\n';

        std::cout << "block number: " << (int)blockNumber << '\n';
        std::cout << "complement: " << (int)complement << '\n';
        std::cout << "i: " << (int)number << '\n';

        if (sum == calculatedSum
            && number == blockNumber &&
            255-blockNumber == complement
            ) {
            number++;
            isSuccesful = WriteFile(port, &ACK, 1, &bytesWritten, NULL);
            for(byte b: block) {
                received.push_back(b);
            }
            std:: cout << "code = " << (int)code << '\n';
            std:: cout << "ACK\n\n";

        } else {
            isSuccesful = WriteFile(port, &NAK, 1, &bytesWritten, NULL);
            std:: cout << "code = " << (int)code << '\n';
            std:: cout << "NACK\n\n";
        }
    }
    // wyslij ACK
    isSuccesful = WriteFile(port, &ACK, 1, &bytesWritten, NULL);

    std::cout << "\nreceived message: \n";
    for(byte b: received) {
        std::cout << b;
    }

    output.close();
    return 0;
}
