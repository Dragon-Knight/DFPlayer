/*
 *	DFPlayerCore.h
 *	Core class of DFPlayer.
 *
 *	@author		Nikolai Tikhonov aka Dragon_Knight <dubki4132@mail.ru>, https://vk.com/globalzone_edev
 *	@licenses	MIT https://opensource.org/licenses/MIT
 *	@repo		https://github.com/Dragon-Knight/DFPlayer
 */

#ifndef DFPlayerCore_h
#define DFPlayerCore_h

#include <Arduino.h>
#include <SoftwareSerial.h>

enum DFPlayerSourse
{
	DFPLAYER_SOURSE_NONE,
	DFPLAYER_SOURSE_ROOT,
	DFPLAYER_SOURSE_NUM,
	DFPLAYER_SOURSE_MP3,
	DFPLAYER_SOURSE_ADVERT
};

enum DFPlayerEqualizer
{
	DFPLAYER_EQUALIZER_NORMAL = 0,
	DFPLAYER_EQUALIZER_POP = 1,
	DFPLAYER_EQUALIZER_ROCK = 2,
	DFPLAYER_EQUALIZER_JAZZ = 3,
	DFPLAYER_EQUALIZER_CLASSIC = 4,
	DFPLAYER_EQUALIZER_BASS = 5
};

class DFPlayerCore
{
	public:
	
		DFPlayerCore(SoftwareSerial &serial, uint8_t busyPin) : _serial(&serial), _busyPin(busyPin)
		{
			pinMode(this->_busyPin, INPUT);
			this->_cooldownTime = 0;
			
			return;
		}
		
		DFPlayerCore(SoftwareSerial &&serial, uint8_t busyPin) = delete;
		
		void Begin()
		{
			this->_serial->begin(9600);
			this->_serial->stopListening();
			this->Reset();
			
			return;
		}
		
		//////////////////// COMMANDS ////////////////////
		void PlayNext() const
		{
			this->SendData(0x01, 0x00, 0x00, 16);
			
			return;
		}
		
		void PlayPrevious() const
		{
			this->SendData(0x02, 0x00, 0x00, 16);
			
			return;
		}
		
		void PlayROOT(uint16_t track) const
		{
			this->SendData(0x03, highByte(track), lowByte(track), 16);
			
			return;
		}
		
		void VolumeUp() const
		{
			this->SendData(0x04, 0x00, 0x00, 16);
			
			return;
		}
		
		void VolumeDown() const
		{
			this->SendData(0x05, 0x00, 0x00, 16);
			
			return;
		}
		
		void SetVolume(uint8_t volume) const
		{
			this->SendData(0x06, 0x00, volume, 16);
			
			return;
		}
		
		void SetEQ(DFPlayerEqualizer eq) const
		{
			this->SendData(0x07, 0x00, (uint8_t)eq, 16);
			
			return;
		}
		
		void PlaybackMode(uint8_t mode) const		// По докам тупо повтор трека 1-3000, только откуда?
		{
			this->SendData(0x08, 0x00, mode, 16);
			
			return;
		}
		
		// 0x09
		
		void Sleep() const
		{
			this->SendData(0x0A, 0x00, 0x00, 128);
			
			return;
		}
		
		// 0x0B
		
		void Reset() const
		{
			this->SendData(0x0C, 0x00, 0x00, 1024);
			
			return;
		}
		
		void Play() const
		{
			this->SendData(0x0D, 0x00, 0x00, 16);
			
			return;
		}
		
		void Pause() const
		{
			this->SendData(0x0E, 0x00, 0x00, 16);
			
			return;
		}
		
		void PlayNUM(uint8_t folder, uint8_t track) const
		{
			this->SendData(0x0F, folder, track, 16);
			
			return;
		}
		
		// 0x10
		
		// 0x11
		
		void PlayMP3(uint16_t track) const
		{
			this->SendData(0x12, highByte(track), lowByte(track), 16);
			
			return;
		}
		
		void PlayADVERT(uint16_t track) const
		{
			this->SendData(0x13, highByte(track), lowByte(track), 16);
			
			return;
		}
		
		// 0x14
		
		void StopAdvert() const
		{
			this->SendData(0x15, 0x00, 0x00, 16);
			
			return;
		}
		
		void Stop() const
		{
			this->SendData(0x16, 0x00, 0x00, 16);
			
			return;
		}
		
		// 0x17
		
		// 0x18
		
		// 0x19
		
		// 0x1A
		//////////////////////////////////////////////////
		
		//////////////////// UTILITY ////////////////////
		void PlayBySourse(uint16_t param1, uint8_t param2, DFPlayerSourse source)
		{
			switch(source)
			{
				case DFPLAYER_SOURSE_ROOT:
				{
					this->PlayROOT(param1);
					
					break;
				}
				case DFPLAYER_SOURSE_NUM:
				{
					this->PlayNUM(param1, param2);
					
					break;
				}
				case DFPLAYER_SOURSE_MP3:
				{
					this->PlayMP3(param1);
					
					break;
				}
				case DFPLAYER_SOURSE_ADVERT:
				{
					this->PlayADVERT(param1);
					
					break;
				}
				default:
				{
					break;
				}
			}
			
			return;
		}
		
		bool IsBusy() const
		{
			return !digitalRead(this->_busyPin);
		}
		
		bool IsReadyReceive() const
		{
			return (millis() > this->_cooldownTime);
		}
		//////////////////////////////////////////////////
	
	private:
	
		void SendData(byte command, byte msb, byte lsb, uint16_t timeout)
		{
			byte data[10] = {0x7E, 0xFF, 0x06, command, 0x00, msb, lsb, 0x00, 0x00, 0xEF};
			
			uint16_t crc = 0 - (0xFF + 0x06 + command + 0x00 + msb + lsb);
			data[7] = highByte(crc);
			data[8] = lowByte(crc);
			
			this->_serial->write(data, 10);
			
			this->_cooldownTime = millis() + timeout;
			
			return;
		}
		
		SoftwareSerial *_serial;
		uint8_t _busyPin;
		uint32_t _cooldownTime;
};

#endif
