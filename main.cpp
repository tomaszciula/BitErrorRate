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

    // TODO: Test 1
    createFile1("test1_file1.bin", 100, 0x55);
    createFile1("test1_file2.bin", 100, 0x55);

    // TODO: Test 2
    createFile1("test2_file1.bin", 100, 0x55);
    createFile1("test2_file2.bin", 100, 0x55);

    // TODO: Test 3
    // createFile1("test3_file1.bin", 400000000, 0x55);
    // createFile1("test3_file2.bin", 400000000, 0x50);

    char buffer1[100], buffer2[100];
    double count = 0.0;
    std::string s = argv[1];
    int pos = s.find("_");
    std::cout << "substring: " << s.substr(0, pos) << std::endl;

    if (s.substr(0, pos) == "test1")
    {
        std::ifstream test_file1("test1_file1.bin", std::ios::in | std::ios::binary);
        test_file1.read(buffer1, 100);
        if (!test_file1)
        {
            openLog("log.txt");
            saveLog("Test 1 plik 1 błąd otwarcia pliku");
            closeLog();
        }
        std::ifstream test_file2("test1_file2.bin", std::ios::in | std::ios::binary);
        test_file2.read(buffer2, 100);
        if (!test_file2)
        {
            openLog("log.txt");
            saveLog("Test 1 plik 2 błąd otwarcia pliku");
            closeLog();
        }
        openLog("log.txt");
        saveLog("Test 1 rozpoczęto");

        for (size_t i = 0; i < 100; i++)
        {
            count += hammingDistance(buffer1[i], buffer2[i]);
        }
        saveLog("Test 1 zakończono");
        std::string test1 = "Test 1 - BER = " + std::to_string(count / (100.0 * 8.0));
        saveLog(test1);
        closeLog();
    }

    else if (s.substr(0, pos) == "test2")

    {
        std::ifstream test_file1("test2_file1.bin", std::ios::in | std::ios::binary);
        test_file1.read(buffer1, 100);
        if (!test_file1)
        {
            openLog("log.txt");
            saveLog("Test 2 plik 1 błąd otwarcia pliku");
            closeLog();
        }
        std::ifstream test_file2("test2_file2.bin", std::ios::in | std::ios::binary);
        test_file2.read(buffer2, 100);
        if (!test_file2)
        {
            openLog("log.txt");
            saveLog("Test 2 plik 2 błąd otwarcia pliku");
            closeLog();
        }
        // Changing 10 bits
        for (size_t i = 50; i < 55; i++)
        {
            buffer2[i] = 0x77;
        }
        openLog("log.txt");
        saveLog("Test 2 rozpoczęto");
        for (size_t i = 0; i < 100; i++)
        {
            count += hammingDistance(buffer1[i], buffer2[i]);
        }
        saveLog("Test 2 zakończono");
        std::string test2 = "Test 2 - BER = " + std::to_string(count / (100.0 * 8.0));
        saveLog(test2);
        closeLog();
    }

    else

    {
        count = 0.0;
        std::ifstream test_file1("test3_file1.bin", std::ios::in | std::ios::binary);
        if (!test_file1)
        {
            openLog("log.txt");
            saveLog("Test 3 plik 1 błąd otwarcia pliku");
            closeLog();
        }
        std::ifstream test_file2("test3_file2.bin", std::ios::in | std::ios::binary);
        if (!test_file2)
        {
            openLog("log.txt");
            saveLog("Test 3 plik 2 błąd otwarcia pliku");
            closeLog();
        }
        char test3_buffer1[1], test3_buffer2[1];
        openLog("log.txt");
        saveLog("Test 3 rozpoczęto");
        int licznik = 0;
        while (!test_file1.eof())
        {

            test_file1.read(test3_buffer1, 1);
            test_file2.read(test3_buffer2, 1);
            count += hammingDistance(test3_buffer1[0], test3_buffer2[0]);
        }
        std::cout << count << std::endl;
        saveLog("Test 3 zakończono");
        std::string test3 = "Test 3 - BER = " + std::to_string(count / (400000000.0 * 8.0));
        saveLog(test3);
        closeLog();
    }
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