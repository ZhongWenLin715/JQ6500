#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////

void uart3_init(u32 bound);
void UART3_Send_Data(u8 *buf,u8 len);

#endif


