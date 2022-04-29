#include "pch.h"
#include "logger.cpp"

uint8_t hammingDistance(uint8_t n1, uint8_t n2);
void createFile1(const std::string name, const int count, const char value);

int main(int argc, char *argv[])
{
    std::cout << "BER Calc v1.0" << std::endl;

    openLog("log.log");
    saveLog("Program uruchomiono poprawnie");
    closeLog();

    std::cout << "argc =  : " << argc << std::endl;
    int iter = 0;
    for (iter = 0; iter < argc; iter++)
    {
        std::cout << "argv[" << iter << "] =" << argv[iter] << std::endl;
    }

    std::cout << (int)hammingDistance(0xFF, 0x01) << std::endl;
    createFile1("test1_file1.bin", 100, 0x55);
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
void createFile1(const std::string name, const int count, const char value)
{
    std::fstream f;
    f.open(name.c_str(), std::ios::binary | std::ios::out);
    for (int i = 0; i < count; i++)
    {
        f.write((char *)&value, 1);
    }
    f.close();
}