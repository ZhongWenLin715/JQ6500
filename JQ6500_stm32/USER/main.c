#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "jq6500.h"

 int main(void)
 {	
    vu8 key=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart3_init(115200);
    KEY_Init();
    JQ6500_Init();     
 	while(1)
	{
      key=KEY_Scan(0);	//�õ���ֵ
	   	if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	
                    JQ6500_Next();
					break; 
				case KEY1_PRES:
                    JQ6500_Prev();
					break;
				case KEY0_PRES:
                    LoopMode(2);                    
					break;
			}
		}else delay_ms(10); 
    }	 
 }

