#include "Progress.hpp"
#include <iostream>

int Progress::ShowStatus(int current, int max)
{
    std::cout << "\r" << current << "/" << max << " " << current * 100 / max << "% " << std::flush;
    return 0;
}