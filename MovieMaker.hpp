#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>

class MovieMaker
{
    public:
        static int MakeVideo(std::string &imageFolder,std::string &outputPath);
        static int MakeVideo(std::string &imageFolder,std::string &outputPath, std::string &bgPath);
        static int AlphaOverlay(cv::Mat &image, cv::Mat &mask, cv::Mat &outImage);  

        static int SplitVideo(std::string &videoPath, std::string &outputFolder); 
};