#include <iostream>
#include <stdint.h>

#include "HighPrecision.h"

int main(void) {
    HighPrecision a = 10, b = -100;
    HighPrecision c = a + b;
    std::cout << c << std::endl;
    c++;
    std::cout << c << std::endl;
    hpabs(c);
    std::cout << c << std::endl;

    return 0;
}