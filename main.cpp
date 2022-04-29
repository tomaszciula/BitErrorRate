#include "pch.h"
#include "logger.cpp"
#include <fstream>

uint8_t hammingDistance(uint8_t n1, uint8_t n2);
void createFile1(const std::string name, const int count, const char value);

int main(int argc, char *argv[])
{
    std::cout << "BER Calc v1.0" << std::endl;

    openLog("log.txt");
    saveLog("Program uruchomiono poprawnie");
    closeLog();

    std::cout << "argc =  : " << argc << std::endl;
    int iter = 0;
    for (iter = 0; iter < argc; iter++)
    {
        std::cout << "argv[" << iter << "] =" << argv[iter] << std::endl;
    }

    std::cout << (int)hammingDistance(0xFF, 0xFF) << std::endl;
    createFile1("test1_file1.bin", 100, 0x55);
    createFile1("test1_file2.bin", 100, 0x55);

    // TODO: Test 1

    char buffer1[100], buffer2[100];
    int count = 0;
    std::ifstream test1_file1("test1_file1.bin", std::ios::in | std::ios::binary);
    test1_file1.read(buffer1, 100);
    if (!test1_file1)
    {
        openLog("log.txt");
        saveLog("Test 1 plik 1 błąd otwarcia pliku");
        closeLog();
    }
    std::ifstream test1_file2("test1_file2.bin", std::ios::in | std::ios::binary);
    test1_file2.read(buffer2, 100);
    if (!test1_file2)
    {
        openLog("log.txt");
        saveLog("Test 1 plik 2 błąd otwarcia pliku");
        closeLog();
    }
    for (size_t i = 0; i < 100; i++)
    {
        count += hammingDistance(buffer1[i], buffer2[i]);
    }
    std::string test1 = "Test 1 - BER = " + std::to_string(count);
    openLog("log.txt");
    saveLog(test1);
    closeLog();

    //TODO: Test 2

    createFile1("test2_file1.bin", 100, 0x55);
    createFile1("test2_file2.bin", 100, 0x50);
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