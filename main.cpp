#include "pch.h"

uint8_t hammingDistance(uint8_t n1, uint8_t n2);

int main(int argc, char * argv[])
{
    std::cout << "BER Calc v1.0" << std::endl;
    std::cout << "argc =  : " << argc << std::endl; 
    int iter = 0;
    for (iter = 0; iter < argc; iter++) {
        std::cout << "argv[" << iter << "] =" << argv[iter] << std::endl;
    }

    std::cout << (int)hammingDistance(0xFF, 0x11) << std::endl;

    return 0;
}

uint8_t hammingDistance(uint8_t n1, uint8_t n2)
{
    uint8_t x = n1 ^ n2; // XOR
    uint8_t setBits = 0;
    while (x > 0)
    {
        setBits += x & 1;
        x >>= 1;
    }
    return setBits;
}