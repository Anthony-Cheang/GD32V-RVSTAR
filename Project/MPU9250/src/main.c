#include <stdio.h>
#include <stdlib.h>
#include "gd32vf103_gpio.h"
#include "gd32vf103.h"    
#include "uart.h"
#include "iic.h"
#include "mpu9250.h"


    
    
int main()
{      
    float tmp, gyr_x, gyr_y, gyr_z, acc_x, acc_y, acc_z;
    u_char data;
    iic_init();
    mpu9250_init();
    data=Single_Read(0x75);
    printf("WHO_AM_I value is %x\n",data);
    data=Single_Read(0x6b);
    printf("PWR_MGMT_1 value is %x\n",data);
    data=Single_Read(INTPin);
    printf("INPin value is %x\n",data);
    data=Single_Read_Mag(WIA);
    printf("MAG ID is %x\n",data);
    rcu_periph_clock_enable(RCU_GPIOA);//使能GPTOE时钟
    gpio_init(GPIOA,GPIO_MODE_OUT_PP,GPIO_OSPEED_2MHZ,GPIO_PIN_1); //PE12--推挽输出--速度2MHZ
    gpio_bit_write(GPIOA,GPIO_PIN_1,1); //PCE输出高电平
    
    
    while(1)
    {
        gpio_bit_reset(GPIOA,GPIO_PIN_1);
        delay_1ms (500);
        gpio_bit_set(GPIOA,GPIO_PIN_1);
        delay_1ms(500);
        tmp=mpu9250_temp();
        printf("the temp is %ddec\n",(int)(tmp*100));
        gyr_x=mpu9250_gyr_x();
        printf("gyros are x %0.2f deg/s\t",(int)gyr_x);
        gyr_y=mpu9250_gyr_y();
        printf("y % deg/s\t",(int)gyr_y);
        gyr_z=mpu9250_gyr_z();
        printf("z %d deg/s\n",(int)gyr_z);
        acc_x=mpu9250_acc_x();
        printf("accs are x %dg  \t",(int)(acc_x));
        acc_y=mpu9250_acc_y();
        printf("y %dg  \t",(int)(acc_y));
        acc_z=mpu9250_acc_z();
        printf("z %dg  \n",(int)(acc_z)); 
    }
}