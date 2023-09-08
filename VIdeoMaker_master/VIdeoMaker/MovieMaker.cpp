#include "MovieMaker.hpp"
#include "Progress.hpp"

int MovieMaker::MakeVideo(std::string imageFolder, std::string outputPath)
{
	std::vector<std::string> images;
	int count = 0;
	for (const auto& file : std::filesystem::directory_iterator(imageFolder))
	{
		images.push_back(file.path().string());

		Progress::ShowStatus(count, images.size());
		count++;
	}
	std::sort(images.begin(), images.end());

	cv::Mat frame = cv::imread(images[0]);
	int height = frame.rows;
	int width = frame.cols;

	cv::VideoWriter video(outputPath, cv::VideoWriter::fourcc('M', 'P', '4', 'V'), 24, cv::Size(width, height));

	count = 0;
	for (const auto& image_path : images)
	{
		frame = cv::imread(image_path);
		video.write(frame);

		Progress::ShowStatus(count, images.size());
		count++;
	}

	// 動画の書き出しを終了
	video.release();
	std::cout << "The video has been saved as " << outputPath << std::endl;

	return 0;
}
int MovieMaker::MakeVideo(std::string imageFolder, std::string outputPath, std::string bgPath)
{
	cv::Mat bgImg = cv::imread(bgPath, cv::IMREAD_UNCHANGED);
	// 画像フォルダから画像ファイル名をソートして取得します。
	std::vector<std::string> images;
	int count = 0;
	for (const auto& file : std::filesystem::directory_iterator(imageFolder))
	{
		images.push_back(file.path().string());
		Progress::ShowStatus(count, images.size());
		count++;
	}
	std::sort(images.begin(), images.end());

	cv::Mat frame;
	cv::Mat sizeMat = cv::imread(images[0], cv::IMREAD_UNCHANGED);

	int height = sizeMat.rows;
	int width = sizeMat.cols;

	cv::VideoWriter video(outputPath, cv::VideoWriter::fourcc('M', 'P', '4', 'V'), 24, cv::Size(width, height));

	count = 0;
	for (const auto& image_path : images)
	{
		cv::Mat overlay = cv::imread(image_path, cv::IMREAD_UNCHANGED);
		int res = AlphaOverlay(bgImg, overlay, frame);
		if (res == 0)
		{
			cv::Mat frameBGR;
			cv::cvtColor(frame, frameBGR, cv::COLOR_BGRA2BGR);
			video.write(frameBGR);
		}
		else
		{
			std::cout << "Failed to overlay image." << std::endl;
			return -1;
		}
		Progress::ShowStatus(count, images.size());
		count++;
	}
	video.release();
	std::cout << "The video has been saved as " << outputPath << std::endl;
	return 0;
}

int MovieMaker::AlphaOverlay(cv::Mat& bg, cv::Mat& overlay, cv::Mat& outImage)
{
	if (overlay.cols / overlay.rows != bg.cols / overlay.rows)
	{
		std::cout << "The aspect ratio of the overlay image and the background image are different." << std::endl;
		return -1;
	}

	cv::resize(bg, bg, cv::Size(overlay.cols, overlay.rows));

	if (overlay.channels() != 4)
	{
		std::cout << "The overlay image does not have an alpha channel." << std::endl;
		return -1;
	}




	// If the output image does not exist or has different dimensions, create a new one
	if (outImage.empty() || outImage.cols != overlay.cols || outImage.rows != overlay.rows)
	{
		outImage = cv::Mat(overlay.rows, overlay.cols, CV_8UC4);
	}

	for (int y = 0; y < overlay.rows; y++)
	{
		for (int x = 0; x < overlay.cols; x++)
		{
			cv::Vec4b overlay_vec = overlay.at<cv::Vec4b>(y, x);
			cv::Vec3b bg_vec = bg.at<cv::Vec3b>(y, x);
			double alpha = (double)overlay_vec[3] / 255.0;
			double beta = 1.0 - alpha;
			cv::Vec4b out_vec;
			out_vec[0] = bg_vec[0] * beta + overlay_vec[0] * alpha;
			out_vec[1] = bg_vec[1] * beta + overlay_vec[1] * alpha;
			out_vec[2] = bg_vec[2] * beta + overlay_vec[2] * alpha;
			out_vec[3] = 255*beta + overlay_vec[3] * alpha;
			outImage.at<cv::Vec4b>(y, x) = out_vec;
		}
	}

	return 0;
}

int MovieMaker::AddAlphaChannel(cv::Mat& image, cv::Mat& outImage)
{
	if (image.channels() != 4)
	{
		cv::cvtColor(image, image, cv::COLOR_BGR2BGRA);
		cv::Scalar alpha = cv::Scalar(255);
		cv::Mat alphaChannel = cv::Mat(image.rows, image.cols, CV_8UC1, alpha);
		std::vector<cv::Mat> imageChannels;
		cv::split(image, imageChannels);
		imageChannels.push_back(alphaChannel);
		cv::merge(imageChannels, image);
	}

	if (outImage.empty() || outImage.cols != image.cols || outImage.rows != image.rows)
	{
		outImage = cv::Mat(image.rows, image.cols, CV_8UC4);
	}

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			cv::Vec4b image_vec = image.at<cv::Vec4b>(y, x);
			cv::Vec4b out_vec;
			out_vec[0] = image_vec[0];
			out_vec[1] = image_vec[1];
			out_vec[2] = image_vec[2];
			out_vec[3] = image_vec[3];
			outImage.at<cv::Vec4b>(y, x) = out_vec;
		}
	}

	return 0;

}

