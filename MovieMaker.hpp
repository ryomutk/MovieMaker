#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>

class MovieMaker
{
    public:
        static int MakeVideo(std::string imageFolder,std::string outputPath);
};