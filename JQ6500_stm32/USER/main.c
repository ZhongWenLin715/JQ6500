#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "jq6500.h"

 int main(void)
 {	
    vu8 key=0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart3_init(115200);
    KEY_Init();
    JQ6500_Init();     
 	while(1)
	{
      key=KEY_Scan(0);	//得到键值
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

