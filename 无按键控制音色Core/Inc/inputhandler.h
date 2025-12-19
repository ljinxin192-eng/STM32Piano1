#ifndef INPUTHANDLER_H
#define	INPUTHANDLER_H

#include <stdint.h>
#include "wavegener.h"

int CalcuRbKey(uint16_t inputkey);
void ChangeInNote(uint16_t inputkey,int* LEVEL);
void StateSwich(uint16_t inputkey, int* LEVEL);

#endif
