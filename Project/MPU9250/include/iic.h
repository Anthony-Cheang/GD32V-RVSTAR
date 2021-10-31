#ifndef __IIC_H__
#define __IIC_H__
#include "gd32vf103.h"
#include "gd32vf103_gpio.h"
/*IIC通信采用使用GPIO口模拟时序的方法实现*/
/*IIC端口输出输入定义*/
/*这两个IO口需要上拉*/
#define SCL_H         gpio_bit_set(GPIOB,GPIO_PIN_6)
#define SCL_L         gpio_bit_reset(GPIOB,GPIO_PIN_6)
   
#define SDA_H         gpio_bit_set(GPIOB,GPIO_PIN_7)
#define SDA_L         gpio_bit_reset(GPIOB,GPIO_PIN_7)

/*此处直接读取此处IO口的输入值而不用修改IO口模式配置*/
#define SCL_read        gpio_input_bit_get(GPIOB,GPIO_PIN_6)  //将模拟IIC时序的GPIO口设置为开漏输出
#define SDA_read        gpio_input_bit_get(GPIOB,GPIO_PIN_7)


/*模拟IIC时序函数声明*/
void iic_init();
void I2C_delay(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NoAck(void);
char I2C_WaitAck(void);
void I2C_SendByte(unsigned char SendByte);
unsigned char I2C_ReadByte(void);




#endif