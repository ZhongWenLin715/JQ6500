#include "usart.h"
#include "string.h"

u8 uart2_rxbuf[200];     //���ջ��� 
  
void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART2��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���1 

}
 

void UART2_Send_Data(u8 *buf,u8 len)
{
	u8 t;	
  	for(t=0;t<len;t++)		//ѭ����������
	{		   
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	  
		USART_SendData(USART2,buf[t]);
	}	
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);		
	
} 

// �����жϷ�����
void USART2_IRQHandler(void)
{
    u8 i;
    u16 uart2_count=0;
    u16 wait;
    
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{	        
		while(wait++ < 5536)	   			    
        {
            if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE))						    
            {
                USART_ClearITPendingBit(USART2,USART_IT_RXNE);	       	
                uart2_rxbuf[uart2_count++]=USART_ReceiveData(USART2); 	
                wait=0;					
            }	
        }
    }
    
    if(strncmp((char const *)(&uart2_rxbuf[0]),(char const *)"{\"flag\"",7)==0)
    {
        UART2_Send_Data("flag:",5);
        for(i=9;i<11;i++)
        UART2_Send_Data(&uart2_rxbuf[i],1);
        UART2_Send_Data(",msg:",5);
        for(i=20;i<22;i++)
        UART2_Send_Data(&uart2_rxbuf[i],1);
    }
    if(strncmp((char const *)(&uart2_rxbuf[0]),(char const *)"AABB",4)==0)
    {
        for(i=5;i<14;i++)
        UART2_Send_Data(&uart2_rxbuf[i],1);
    }
    for(i=0;i<200;i++)//��������
    uart2_rxbuf[i]=0;    
}



	

