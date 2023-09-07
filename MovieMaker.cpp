#include "MovieMaker.hpp"

int MovieMaker::MakeVideo(std::string imageFolder,std::string outputPath)
{

    // 画像フォルダから画像ファイル名をソートして取得します。
    std::vector<std::string> images;
    for (const auto &file : std::filesystem::directory_iterator(imageFolder))
    {
        images.push_back(file.path());
    }
    std::sort(images.begin(), images.end());

    // 最初の画像からフレームのサイズを取得します。
    cv::Mat frame = cv::imread(images[0]);
    int height = frame.rows;
    int width = frame.cols;

    // 出力ビデオの設定を行います。FPSと解像度を指定し、ビデオファイルを作成します。
    cv::VideoWriter video(outputPath, cv::VideoWriter::fourcc('M', 'P', '4', 'V'), 24, cv::Size(width, height));

    // 画像ファイルを動画に追加します。
    for (const auto &image_path : images)
    {
        frame = cv::imread(image_path);
        video.write(frame);
    }

    // 動画の書き出しを終了
    video.release();
    std::cout << "The video has been saved as " << outputPath << std::endl;

    return 0;
}
