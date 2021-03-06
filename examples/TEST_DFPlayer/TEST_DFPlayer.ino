/*
 *	TEST_DFPlayer.ino
 *	Compilation test of DFPlayer.
 *
 *	@author		Nikolai Tikhonov aka Dragon_Knight <dubki4132@mail.ru>, https://vk.com/globalzone_edev
 *	@licenses	MIT https://opensource.org/licenses/MIT
 *	@repo		https://github.com/Dragon-Knight/DFPlayer
 */

#include <DFPlayer.h>

SoftwareSerial mySerial(10, 11);
DFPlayer MP3Player(mySerial, 13);

void setup()
{
	MP3Player.Begin();
	
	MP3Player.PlayNext();
	MP3Player.PlayPrevious();
	MP3Player.PlayROOT(1000);
	MP3Player.VolumeUp();
	MP3Player.VolumeDown();
	MP3Player.SetVolume(15);
	MP3Player.SetEQ(DFPLAYER_EQUALIZER_JAZZ);
	MP3Player.PlaybackMode(3);
	MP3Player.Sleep();
	
	MP3Player.Reset();
	while(MP3Player.IsReadyReceive() == false){ }
	
	MP3Player.Play();
	MP3Player.Pause();
	MP3Player.PlayNUM(5, 100);
	MP3Player.PlayMP3(2000);
	MP3Player.PlayADVERT(2500);
	MP3Player.StopAdvert();
	MP3Player.Stop();
	MP3Player.IsBusy();
	MP3Player.IsReadyReceive();
	
	MP3Player.QueueAddTop(2111, 11, DFPLAYER_SOURSE_NONE);
	MP3Player.QueueAddTop(2112, 12, DFPLAYER_SOURSE_ROOT);
	MP3Player.QueueAddTop(2113, 13, DFPLAYER_SOURSE_NUM);
	MP3Player.QueueAddTop(2114, 14, DFPLAYER_SOURSE_MP3);
	MP3Player.QueueAddTop(2115, 15, DFPLAYER_SOURSE_ADVERT);
	MP3Player.QueueAddEnd(1111, 11, DFPLAYER_SOURSE_NONE);
	MP3Player.QueueAddEnd(1112, 12, DFPLAYER_SOURSE_ROOT);
	MP3Player.QueueAddEnd(1113, 13, DFPLAYER_SOURSE_NUM);
	MP3Player.QueueAddEnd(1114, 14, DFPLAYER_SOURSE_MP3);
	MP3Player.QueueAddEnd(1115, 15, DFPLAYER_SOURSE_ADVERT);
	MP3Player.QueueClear();
}

void loop()
{
	MP3Player.Processing();
}
