#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <cstring>
#include "../include/typedef.h"
#include "../include/codes.h"
#include <math.h>       /* floor */

int maxBlocks;

void fillHeader(byte header[3], byte i) {
    header[0] = SOH;
    header[1] = i;
    header[2] = 255-i;
}

void splitIntoBlocks(std::vector<byte> buffer, byte blocks [][128] ) {
    int fullBlocks = (int) floor(buffer.size()/128.);

    // pełne bloki
    byte i=0;
    while (i < fullBlocks) {
        for (int ii=0; ii<128; ii++) {
            blocks[i][ii] = buffer[128*i + ii];
        }
        i++;
    }

    // niepełny blok
    byte bytesLeft = buffer.size() - (i * 128);
    if (bytesLeft > 0) {
        //wpisanie pozostalych bajtow
        int ii = 0;
        while (ii < bytesLeft) {
            blocks[i][ii] = buffer[128*i + ii];
            ii++;
        }
        //dopisanie zer
        while (ii < 128) {
            blocks[i][ii] = 'x';
            ii++;
        }
        i++;
    }
}

void printBlocks(byte blocks [][128]) {
    for (int i = 0; i<maxBlocks; i++) {
        for (int ii=0; ii<128; ii++) {
            std::cout << blocks[i][ii];
        }
        std::cout << '\n';
    }
}

byte algebraicChecksum(byte bytes[128]){
    byte sum = 0;
    for(int i=0; i<128; i++){
        sum += bytes[i];
        sum %= 256;
    }
    return sum;
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
    std::ifstream input("../files/" + fileName, std::ios::binary);
    std::vector<byte> buffer(std::istreambuf_iterator<char>(input), {});
    maxBlocks = ceil(buffer.size()/128.);

    byte blocks[maxBlocks][128];

    splitIntoBlocks(buffer, blocks);
//    printBlocks(blocks);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    DWORD bytesWritten;
    DWORD bytesRead;


    int blockNumber = 0;
    while (blockNumber < maxBlocks) {
        byte block[128];
        for(int i=0; i<128; i++) {
            block[i] = blocks[blockNumber][i];
        }

        byte header[3];
        fillHeader(header, blockNumber);

        std::cout << "BLOK nr " << blockNumber <<'\n';
        std::cout << "header: \n";
        std::cout << (int)header[0] << "_" << (int)header[1] << "_" << (int)header[2] << "\n";

        std::cout << "blok danych: \n";
        for(int i=0; i<128; i++) {
            std::cout << block[i];
        } std::cout << '\n';

        std::cout << "suma kontrolna: \n";
        std::cout << (int)algebraicChecksum(block) << "\n\n";

        blockNumber ++;
    }

    // wysłanie nagłówka
//    fillHeader(header, i);
//    isSuccesful = WriteFile(port, header, 3, &bytesWritten, NULL);


//    isSuccesful = WriteFile(port, data, 128, &bytesWritten, NULL);

    //wysłanie sumy kotrolnej
    byte sum[SUM_SIZE];

//    isSuccesful = WriteFile(port, sum, SUM_SIZE, &bytesWritten, NULL);





    CloseHandle(port);
    return 0;
}
