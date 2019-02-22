#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////

void uart_init(u32 bound);
void UART2_Send_Data(u8 *buf,u8 len);

#endif


