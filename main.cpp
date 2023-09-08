#include "MovieMaker.hpp"
#include "SoundMix.cpp"


int main()
{
	MovieMaker::MakeVideo(".\\Mov", ".\\Out\\3_2.mp4", ".\\bg\\blue.png");
	//combine_aac_audio(".\\Out\\pool.mp4", ".\\Sound\\water.wav", ".\\Out\\3_2_sound.mp4");

	return 0;
}
