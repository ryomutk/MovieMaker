#include "MovieMaker.hpp"


int main()
{   
    std::string imageFolder = "./images";
    std::string outputPath = "./output.mp4";

    MovieMaker::SplitVideo(outputPath, imageFolder);
    return 0;
}