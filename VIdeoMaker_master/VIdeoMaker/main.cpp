#include "MovieMaker.hpp"
#include "SoundMix.cpp"


int main()
{
	MovieMaker::MakeVideo(".\\Sequences\\pool", ".\\Out\\pool.mp4");
	MovieMaker::MakeVideo(".\\Sequences\\azuki", ".\\Out\\azuki.mp4", ".\\bg\\box.png");
	//combine_aac_audio(".\\Out\\3_2.mp4", ".\\Sound\\Shiu_3_voice_5.wav", ".\\Out\\3_2_sound.mp4");

	return 0;
}
