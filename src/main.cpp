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

#define CRC16 0x8005

WORD crcSum(const byte bytes[128]) {
    uint16_t out = 0;
    int bits_read = 0, bit_flag;
    int size = 128;
    while(size > 0)
    {
        bit_flag = out >> 15;
        /* Get next bit: */
        out <<= 1;
        out |= (*bytes >> bits_read) & 1; // item a) work from the least significant bits
        /* Increment bit counter: */
        bits_read++;
        if(bits_read > 7)
        {
            bits_read = 0;
            bytes++;
            size--;
        }
        /* Cycle check: */
        if(bit_flag)
            out ^= CRC16;
    }
    // item b) "push out" the last 16 bits
    int i;
    for (i = 0; i < 16; ++i) {
        bit_flag = out >> 15;
        out <<= 1;
        if(bit_flag)
            out ^= CRC16;
    }
    // item c) reverse the bits
    uint16_t crc = 0;
    i = 0x8000;
    int j = 0x0001;
    for (; i != 0; i >>=1, j <<= 1) {
        if (i & out) crc |= j;
    }

    return crc;
}

int main() {
    bool isSuccesful;

    HANDLE port;
    port = CreateFileA(R"(\\.\COM1)",                //port name
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


    bool crcSumChoice;
    byte init = NAK;
    int SUM_SIZE = 1;

    byte code = 0;
    byte blockNumber = 0;
    byte complement = 255;

    byte block[128];
    std::vector<byte> received;


    std::cout << "Use algebraic sum (0) or CRC sum (1)?";
    std::cin >> crcSumChoice;
    if(crcSumChoice) {
        init = C;
        SUM_SIZE = 2;
    }
    else {
        init = NAK;
        SUM_SIZE = 1;
    }

    for (int i = 0; i < 6; i++) {
        // wysyła NAK
        isSuccesful = WriteFile(port, &init, 1, &bytesWritten, NULL);
        std::cout << "init sent \n";

        //wczytaj nagłówek
        ReadFile(port, &code, 1, &bytesRead, NULL);
        ReadFile(port, &blockNumber, 1, &bytesRead, NULL);
        ReadFile(port, &complement, 1, &bytesRead, NULL);

        if(crcSumChoice) {
            if (code == C) {
                break;
            }
        }
        else {
            if (code == SOH) {
                break;
            }
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
        byte sumA;
        WORD sumC;
        byte temp[2];
        if(crcSumChoice) {
            ReadFile(port, &temp, SUM_SIZE, &bytesRead, NULL);
            sumC = ((uint16_t)temp[0] << 8) | temp[1];
            std::cout << "read CRC sum: " << (int)(sumC) << '\n';
        } else {
            ReadFile(port, &sumA, SUM_SIZE, &bytesRead, NULL);
            std::cout << "read algebraic sum: " << (int)sumA << '\n';
        }


        //policz sumę kontrolna
        byte calculatedSumA;
        WORD calculatedSumC;
        if(crcSumChoice) {
            calculatedSumC = crcSum(block);
            std::cout << "calculated crc: " << (int) calculatedSumC << '\n';
        } else {
            calculatedSumA = algebraicSum(block);
            std::cout << "calculated algebraic: " << (int) calculatedSumA << '\n';
        }

        std::cout << "block number: " << (int)blockNumber << '\n';
        std::cout << "complement: " << (int)complement << '\n';
        std::cout << "i: " << (int)number << '\n';
        if(crcSumChoice){
            if (sumC == calculatedSumC
                && number == blockNumber &&
                255 - blockNumber == complement
                    ) {
                number++;
                isSuccesful = WriteFile(port, &ACK, 1, &bytesWritten, NULL);
                for (byte b: block) {
                    received.push_back(b);
                }
                std::cout << "code = " << (int) code << '\n';
                std::cout << "ACK\n\n";

            } else {
                isSuccesful = WriteFile(port, &NAK, 1, &bytesWritten, NULL);
                std::cout << "code = " << (int) code << '\n';
                std::cout << "NACK\n\n";
            }
        } else {
            if (sumA == calculatedSumA
                && number == blockNumber &&
                255 - blockNumber == complement
                    ) {
                number++;
                isSuccesful = WriteFile(port, &ACK, 1, &bytesWritten, NULL);
                for (byte b: block) {
                    received.push_back(b);
                }
                std::cout << "code = " << (int) code << '\n';
                std::cout << "ACK\n\n";

            } else {
                isSuccesful = WriteFile(port, &NAK, 1, &bytesWritten, NULL);
                std::cout << "code = " << (int) code << '\n';
                std::cout << "NACK\n\n";
            }
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
