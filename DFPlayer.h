/*
 *	DFPlayer.h
 *	Main class of DFPlayer.
 *
 *	@author		Nikolai Tikhonov aka Dragon_Knight <dubki4132@mail.ru>, https://vk.com/globalzone_edev
 *	@licenses	MIT https://opensource.org/licenses/MIT
 *	@repo		https://github.com/Dragon-Knight/DFPlayer
 */

#ifndef DFPlayer_h
#define DFPlayer_h

#include "Arduino.h"
#include "DFPlayerCore.h"

#define DFPLAYER_QUEUE_SIZE			32
#define DFPLAYER_PROCESSING_DELAY	10

struct DFPlayerQueue
{
	uint16_t param1;
	uint8_t param2;
	DFPlayerSourse source;
};

class DFPlayer : public DFPlayerCore
{
	public:
	
		DFPlayer(uint8_t TXPin, uint8_t busyPin) : DFPlayerCore(TXPin, busyPin){ }
		
		DFPlayer(SoftwareSerial &serial, uint8_t busyPin) : DFPlayerCore(serial, busyPin){ }
		
		void Processing(uint32_t currentMicroTime = millis())
		{
			if(this->_lastProcessingTime + DFPLAYER_PROCESSING_DELAY <= currentMicroTime)
			{
				this->_lastProcessingTime = currentMicroTime;
				
				if(this->_queueIndex > 0)
				{
					if(this->IsBusy() == false)
					{
						this->PlayBySourse(this->_queue[0].param1, this->_queue[0].param2, this->_queue[0].source);
						
						for(uint8_t i = 1; i < DFPLAYER_QUEUE_SIZE; ++i)
						{
							this->_queue[i - 1].param1 = this->_queue[i].param1;
							this->_queue[i - 1].param2 = this->_queue[i].param2;
							this->_queue[i - 1].source = this->_queue[i].source;
						}
						--this->_queueIndex;
					}
				}
			}
			
			return;
		}
		
		bool QueueAddTop(uint16_t param1, uint8_t param2, DFPlayerSourse source)
		{
			bool result = false;
			
			if(this->_queueIndex < DFPLAYER_QUEUE_SIZE)
			{
				for(uint8_t i = (DFPLAYER_QUEUE_SIZE - 1); i > 0; --i)
				{
					this->_queue[i - 1].param1 = this->_queue[i].param1;
					this->_queue[i - 1].param2 = this->_queue[i].param2;
					this->_queue[i - 1].source = this->_queue[i].source;
				}
				this->_queue[0].param1 = param1;
				this->_queue[0].param2 = param2;
				this->_queue[0].source = source;
				++this->_queueIndex;
				
				result = true;
			}
			
			return result;
		}
		
		bool QueueAddEnd(uint16_t param1, uint8_t param2, DFPlayerSourse source)
		{
			bool result = false;
			
			if(this->_queueIndex < DFPLAYER_QUEUE_SIZE)
			{
				this->_queue[this->_queueIndex].param1 = param1;
				this->_queue[this->_queueIndex].param2 = param2;
				this->_queue[this->_queueIndex].source = source;
				++this->_queueIndex;
				
				result = true;
			}
			
			return result;
		}
		
		void QueueClear()
		{
			for(uint8_t i = 0; i < DFPLAYER_QUEUE_SIZE; ++i)
			{
				this->_queue[this->_queueIndex].param1 = 0;
				this->_queue[this->_queueIndex].param2 = 0;
				this->_queue[this->_queueIndex].source = DFPLAYER_SOURSE_NONE;
			}
			this->_queueIndex = 0;
			
			return;
		}
	
	private:
	
		DFPlayerQueue _queue[DFPLAYER_QUEUE_SIZE];
		uint8_t _queueIndex;
		
		uint32_t _lastProcessingTime;
};

#endif
