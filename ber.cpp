#include "pch.h"

int main(int argc, char * argv[])
{
    std::cout << "BER Calc v1.0" << std::endl;
    std::cout << "argc =  : " << argc << std::endl; 
    int iter = 0;
    for (iter = 0; iter < argc; iter++) {
        std::cout << "argv[" << iter << "] =" << argv[iter] << std::endl;
    }

    return 0;
}