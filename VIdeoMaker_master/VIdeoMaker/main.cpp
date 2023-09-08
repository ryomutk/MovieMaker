#include "MovieMaker.hpp"
#include "SoundMix.cpp"


int main()
{
	MovieMaker::MakeVideo(".\\Mov\pool", ".\\Out\\pool.mp4");
	//combine_aac_audio(".\\Out\\3_2.mp4", ".\\Sound\\Shiu_3_voice_5.wav", ".\\Out\\3_2_sound.mp4");

	return 0;
}
