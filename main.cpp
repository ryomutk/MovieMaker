#include "MovieMaker.hpp"
#include "SoundMix.cpp"


int main()
{
	MovieMaker::MakeVideo(".\\Mov", ".\\Out\\3_2.mp4", ".\\bg\\ƒOƒŒ[.png");
	combine_aac_audio(".\\Out\\3_2.mp4", ".\\Sound\\Shiu_3_voice_5.wav", ".\\Out\\3_2_sound.mp4");

	return 0;
}
