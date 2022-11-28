/*
 * button.c
 *
 * Created: 11/24/2022 11:19:02 AM
 *  Author: Armin
 */ 

#include "button.h"

uint8_t ButtonManager() {
	if(PING & 0x1F){
		switch(PING & 0x1F){
			case 0x01:
				return 1;
				break;
			case 0x02:
				return 2;
				break;
			case 0x04:
				return 3;
				break;
			case 0x08:
				return 4;
				break;
			case 0x10:
				return 5;
				break;
		}
	}
	
	return 0;
}
