#include <iostream>

int MixSound(std::string &audioPath, std::string &videoPath, std::string &outputPath)
{
    // 任意のオーディオファイルをAACに変換するコマンド
    std::string audioConvertCommand =
        "ffmpeg -i " + videoPath + " -c:a aac " + audioPath + "_" + "output_audio.aac";

    // 元の動画ファイルとAACファイルを合成して新しい動画ファイルを生成するコマンド
    std::string videoCombineCommand =
        "ffmpeg -i " + videoPath + " -i " + audioPath + "_" + "output_audio.aac -c:v copy -c:a copy " + outputPath;

    // コマンドを実行
    if (system(audioConvertCommand.c_str()) != 0)
    {
        std::cerr << "Error: Failed to convert audio" << std::endl;
        return 1;
    }

    if (system(videoCombineCommand.c_str()) != 0)
    {
        std::cerr << "Error: Failed to combine video and audio" << std::endl;
        return 1;
    }

    std::cout << "Successfully combined video and audio" << std::endl;

    return 0;
}