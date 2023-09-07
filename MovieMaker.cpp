#include "MovieMaker.hpp"

int MovieMaker::MakeVideo(std::string &imageFolder,std::string &outputPath)
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

int MovieMaker::MakeVideo(std::string &imageFolder,std::string &outputPath, std::string &bgPath)
{
    cv::Mat bgImg = cv::imread(bgPath, cv::IMREAD_UNCHANGED);

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
        int res = AlphaOverlay(bgImg, frame, frame);
        
        if(res == 0)
        {
            video.write(frame);
        }
        else
        {
            std::cout << "Failed to overlay image." << std::endl;
            return -1;
        }
    }

    // 動画の書き出しを終了
    video.release();
    std::cout << "The video has been saved as " << outputPath << std::endl;

    return 0;
}


int MovieMaker::AlphaOverlay(cv::Mat &bg, cv::Mat &overlay, cv::Mat &outImage)
{
    if(overlay.cols/overlay.rows != bg.cols/overlay.rows)
    {
        std::cout << "The aspect ratio of the overlay image and the background image are different." << std::endl;
        return -1;
    }
    cv::resize(bg, bg, cv::Size(overlay.cols, overlay.rows));

    for(int y = 0; y < overlay.rows;y++)
    {
        for(int x = 0;x < overlay.cols;x++)
        {
            cv::Vec4b px = overlay.at<cv::Vec4b>(y, x);
            cv::Vec3b bg_px = bg.at<cv::Vec3b>(y, x);

            double alpha = px[3] / 255.0;
            double inv_alpha = 1.0 - alpha;

            cv::Vec3b result_px;
            result_px[0] = static_cast<unsigned char>(px[0] * alpha + bg_px[0] * inv_alpha);
            result_px[1] = static_cast<unsigned char>(px[1] * alpha + bg_px[1] * inv_alpha);
            result_px[2] = static_cast<unsigned char>(px[2] * alpha + bg_px[2] * inv_alpha);
            outImage.at<cv::Vec3b>(y, x) = result_px;
        }
    }

    return 0;
}

int SplitVideo(std::string &videoPath, std::string &outputFolder)
{
    //videoPathのビデオを読み込み、フレームごとに分割してoutputFolderに保存する。
    cv::VideoCapture cap(videoPath);
    if(!cap.isOpened())
    {
        std::cout << "Failed to open video file." << std::endl;
        return -1;
    }

    int frameCount = cap.get(cv::CAP_PROP_FRAME_COUNT);
    int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    cv::Mat frame;
    for(int i = 0;i < frameCount;i++)
    {
        cap >> frame;
        std::string outputPath = outputFolder + "/" + std::to_string(i) + ".png";
        cv::imwrite(outputPath, frame);
    }
    
    return 0;
}