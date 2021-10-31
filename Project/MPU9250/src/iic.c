#include "iic.h"
#include "gd32vf103_gpio.h"
#include "gd32vf103.h"  

/*------------初始化GPIO口------------------*/ 
void iic_init()
{
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_init(GPIOB,GPIO_MODE_OUT_OD,GPIO_OSPEED_2MHZ,GPIO_PIN_6); //开漏输出
    gpio_bit_write(GPIOB,GPIO_PIN_6,1); 
    gpio_init(GPIOB,GPIO_MODE_OUT_OD,GPIO_OSPEED_2MHZ,GPIO_PIN_7); 
    gpio_bit_write(GPIOB,GPIO_PIN_7,1); 
}

/*-------------延时函数---------------------*/
void I2C_delay(void)
{	
   unsigned char i=10; //这里可以优化速度	，经测试最低到5还能写入
   while(i) 
   { 
     i--; 
   }  
}


/*--------------iic开始信号----------------*/
void I2C_Start(void)
{
	SDA_H;
	SCL_H;
	delay_1ms(1); 
	SDA_L;
	delay_1ms(1); 
	SCL_L; 
}

/*----------iic结束信号--------------------*/
void I2C_Stop(void)
{
	SCL_L;
	SDA_L;
	delay_1ms(1); 
	SCL_H;
	SDA_H;
	delay_1ms(1); 
} 

/*------------iic应答信号----------------*/
void I2C_Ack(void)
{	
	SCL_L;
	SDA_L;
	delay_1ms(1); 
	SCL_H;
	delay_1ms(1); 
	SCL_L;
}  

/*---------------iic无应答信号-----------*/
void I2C_NoAck(void)
{	
	SCL_L;
	SDA_H;
	delay_1ms(1); 
	SCL_H;
	delay_1ms(1); ;
	SCL_L;
} 

/*-------------iic等待应答--------------*/
char I2C_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	unsigned char ErrTime=0;
	SDA_H;
	delay_1ms(1); 			
	SCL_H;
	delay_1ms(1); 
	while(SDA_read)
	{
		ErrTime++;
		if(ErrTime>250)
			{
				I2C_Stop();
				return TRUE;
			}
	}
	SCL_L;
	return FALSE;
}

/*------------发送一个字节数据----------*/
void I2C_SendByte(unsigned char SendByte) //数据从高位到低位//
{
    char i=8;
    while(i--)
    {
        SCL_L;
        delay_1ms(1); 
		if (SendByte&0x80)
		 {
			SDA_H;
		 }
		  else
		  {
			SDA_L;
		  }
		 
        SendByte<<=1;
        delay_1ms(1); 
		SCL_H;
        delay_1ms(1); 
    }
    SCL_L;
}

/*------------读取一个字节数据----------*/
unsigned char I2C_ReadByte(void)  //数据从高位到低位//
{ 
    unsigned char i=8;
    unsigned char ReceiveByte=0;
    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      delay_1ms(1); 
	  SCL_H;
      I2C_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
	
} 

