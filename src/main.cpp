#include <iostream>
#include "CApplication.h"
#include "CInterface.h"


int main() {
    return CApplication(CInterface(std::cout, std::cin)).Run();
}
