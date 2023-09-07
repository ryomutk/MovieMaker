#include "Progress.hpp"
#include <iostream>

int Progress::ShowStatus(int current, int max)
{
    std::cout << "\r" << current << "/" << max << std::flush;
    return 0;
}