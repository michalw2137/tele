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
            blocks[i][ii] = '0';
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
    timeouts.ReadTotalTimeoutConstant = 3333;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    std::string fileName = "jpg.jpg";
    std::ifstream input("../files/" + fileName, std::ios::binary);
    std::vector<byte> buffer(std::istreambuf_iterator<char>(input), {});
    maxBlocks = ceil(buffer.size()/128.);

    byte blocks[maxBlocks][128];

    splitIntoBlocks(buffer, blocks);
//    printBlocks(blocks);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    DWORD bytesWritten;
    DWORD bytesRead;
    byte answer = 0;


    do {
        std::cout << "waiting for NAK \n";
        ReadFile(port, &answer, 1, &bytesRead, NULL);
    } while (answer != NAK);

    PurgeComm(port, PURGE_RXCLEAR);

    std::cout << "NAK received \n";

    int blockNumber = 0;
    while (blockNumber < maxBlocks) {
        byte header[3];
        fillHeader(header, blockNumber);

        byte block[128];
        for(int i=0; i<128; i++)
            block[i] = blocks[blockNumber][i];

        byte sum[SUM_SIZE];
        sum[0] = algebraicSum(block);

        isSuccesful = WriteFile(port, header, 3, &bytesWritten, NULL);
        if (isSuccesful)
            std::cout << blockNumber << ". header sent \n";

        isSuccesful = WriteFile(port, block, 128, &bytesWritten, NULL);
        for (int i=0; i<128; i++)
            std::cout << block[i];
        std::cout << '\n';

        if (isSuccesful)
            std::cout << blockNumber << ". block sent \n";

        isSuccesful = WriteFile(port, sum, SUM_SIZE, &bytesWritten, NULL);
        if (isSuccesful)
            std::cout << blockNumber << ". sum sent \n";

        std::cout << "\nwaiting for answer ...";
        ReadFile(port, &answer, 1, &bytesRead, NULL);
        std::cout << "\nanswer received - " << (int)answer << "\n\n";

        if (answer == ACK) {
            blockNumber ++;
        }
    }
    answer = 0;
    while(answer != ACK) {
        // wyslij EOT
        isSuccesful = WriteFile(port, &EOT, 1, &bytesWritten, NULL);
        std::cout << "EOT sent \n";

        // czekaj na ACK
        ReadFile(port, &answer, 1, &bytesRead, NULL);
    }
    std::cout << "ACK received, transmission ended \n";

    CloseHandle(port);
    return 0;
}
