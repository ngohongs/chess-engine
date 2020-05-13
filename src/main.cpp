#include <iostream>
#include "CApplication.h"


int main() {
    return CApplication(CInterface(std::cout, std::cin)).Run();
}
