#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "bre_led_model.h"
#include "bre_led_model_quantized.h"


//你好，你好吗
uint16_t i;			//定义for循环的变量

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	PWM_Init();			//PWM初始化
	
	while (1)
	{
		#if 0
		for (i = 0; i <= 100; i++)
		{
			PWM_SetCompare1(i);			//依次将定时器的CCR寄存器设置为0~100，PWM占空比逐渐增大，LED逐渐变亮
			Delay_ms(10);				//延时10ms
		}
		for (i = 0; i <= 100; i++)
		{
			PWM_SetCompare1(100 - i);	//依次将定时器的CCR寄存器设置为100~0，PWM占空比逐渐减小，LED逐渐变暗
			Delay_ms(10);				//延时10ms
		}
		#else
		OLED_ShowNum(1, 1, bre_led_model_tflite_len, 5);
		
		for (i = 0; i <= bre_led_model_tflite_len; i++)
		{
			TIM2->CCR1 = (bre_led_model_tflite[i] * 100 / 255);
			Delay_ms(1);				//延时10ms
			OLED_ShowNum(2, 1, i, 4);
			OLED_ShowNum(2, 6, (bre_led_model_tflite[i] * 100 / 255), 3);
		}
		for (i = 0; i <= bre_led_model_tflite_len; i++)
		{
			TIM2->CCR1 = bre_led_model_tflite[bre_led_model_tflite_len - i] * 100 / 255;
			Delay_ms(1);				//延时10ms
		}
		#endif
	}
}
