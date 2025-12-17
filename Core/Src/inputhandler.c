#include "inputhandler.h"
#include "gpio.h"
#include "usart.h"
#include <string.h>
#include "wavegener.h"
#include <stdio.h>

uint16_t state = 0;

void StateSwich(uint16_t inputkey, int* LEVEL){
	if(inputkey == FK4_Pin)
	{
		state = (state == 2)? 0 : (state+1) ;
	}
	if(inputkey == FK2_Pin)
	{
		state = 0;
		*LEVEL = 0;
	}
	
	switch (state){
			case 0:
				if(inputkey == FK1_Pin)  *LEVEL += 1;
				else if(inputkey == FK3_Pin)  *LEVEL -= 1;
				break;
				
			case 1:
				break;

			case 2:
				break;
		}

}
int CalcuRbKey(uint16_t inputkey)
{
	int RbKey = 0;
	
	switch(inputkey){
		case NK1_Pin: RbKey = 60;
			break;
		case NK2_Pin: RbKey = 61;							//C4#
			break;
		case NK3_Pin: RbKey = 62;							//D4
			break;
		case NK4_Pin: RbKey = 63;							//D4#
			break;
		case NK5_Pin: RbKey = 64;							//E4
			break;
		case NK6_Pin: RbKey = 65;							//F4
			break;
		case NK7_Pin: RbKey = 66;							//F4#
			break;
		case NK8_Pin: RbKey = 67;							//G4
			break;
		case NK9_Pin: RbKey = 68;							//G4#
			break;
		case NK10_Pin: RbKey = 69;							//A4
			break;
		case NK11_Pin: RbKey = 70;							//A4#
			break;
		case NK12_Pin: RbKey = 71;							//B4
			break;
	}
	
	return RbKey;
}

void ChangeInNote(uint16_t inputkey, int* LEVEL)
{
	int AbKey = 0;
	int RbKey = 0;
	
	RbKey = CalcuRbKey(inputkey);

	AbKey = (*LEVEL) * 12 + RbKey;
	
	char message[64];
  snprintf(message, sizeof(message),
		"[INFO] The Note %d Has Been Triggered.\r\n", AbKey);

	HAL_UART_Transmit(&huart3, (uint8_t*)message, strlen(message), 100);
	NoteOn(AbKey);
}
