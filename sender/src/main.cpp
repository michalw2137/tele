#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include "../include/typedef.h"

int main() {
    HANDLE port21;
    port21 = CreateFileA(R"(\\.\COM21)",                //port21 name
                        GENERIC_READ | GENERIC_WRITE, //Read/Write
                        0,                            // No Sharing
                        NULL,                         // No Security
                        OPEN_EXISTING,// Open existing port21 only
                        0,            // Non Overlapped I/O
                        NULL);        // Null for Comm Devices

    if (port21 == INVALID_HANDLE_VALUE)
        throw std::runtime_error("failed to open port");

    std::ifstream input( "../files/png.png", std::ios::binary );
    // copies all data into buffer
    std::vector<byte> buffer(std::istreambuf_iterator<char>(input), {});

    DWORD bytesWritten;
    WriteFile(port21, buffer.data(), buffer.size(), &bytesWritten, NULL);

    if (bytesWritten != buffer.size()) {
        std::cout << "bytes written: " << bytesWritten << '\n'
                    << "buffer size: " << buffer.size() << '\n';
    } else {
        std::cout << "All bytes sent";
    }


    CloseHandle(port21);
    return 0;
}
