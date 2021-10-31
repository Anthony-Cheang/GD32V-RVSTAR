#include "nuclei_sdk_hal.h"

void init();
bit_status get_key();

int main()
{
    init();
    while (1) 
    {
        // 按钮控制灯亮灭
        // if(get_key() == SET)
        // {
        //     gpio_bit_reset(GPIOD,GPIO_PIN_14);
        //     gpio_bit_set(GPIOD,GPIO_PIN_15);
        // }
        // if(get_key() == RESET)
        // {
        //     gpio_bit_reset(GPIOD,GPIO_PIN_15);
        //     gpio_bit_set(GPIOD,GPIO_PIN_14);
        // }

        // LED 闪烁
        gpio_bit_reset(GPIOD,GPIO_PIN_13);
        gpio_bit_set(GPIOD,GPIO_PIN_14);
        delay_1ms(100);

        gpio_bit_reset(GPIOD,GPIO_PIN_14);
        gpio_bit_set(GPIOD,GPIO_PIN_15);
        delay_1ms(100);

        gpio_bit_reset(GPIOD,GPIO_PIN_15);
        gpio_bit_set(GPIOD,GPIO_PIN_14);
        delay_1ms(100);

        gpio_bit_reset(GPIOD,GPIO_PIN_0);
        gpio_bit_set(GPIOD,GPIO_PIN_15);
        delay_1ms(100);

        gpio_bit_reset(GPIOD,GPIO_PIN_1);
        gpio_bit_set(GPIOD,GPIO_PIN_0);
        delay_1ms(100);

        gpio_bit_reset(GPIOD,GPIO_PIN_4);
        gpio_bit_set(GPIOD,GPIO_PIN_1);
        delay_1ms(100);

        gpio_bit_reset(GPIOD,GPIO_PIN_13);
        gpio_bit_set(GPIOD,GPIO_PIN_4);
        delay_1ms(100);
    } 
}

void init(){
    rcu_periph_clock_enable(RCU_GPIOD); // 使能 GPIOD 片区
    gpio_init(GPIOD,GPIO_MODE_OUT_PP,GPIO_OSPEED_2MHZ,GPIO_PIN_0    // 推挽输出
            | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_bit_write(GPIOD,GPIO_PIN_0| GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_13
            | GPIO_PIN_14 | GPIO_PIN_15,0); 
}

bit_status get_key()
{
    // 获得输入引脚的状态
    // bit_status是一个固件库定义的枚举类型
    return gpio_input_bit_get(GPIOD, GPIO_PIN_5);
}
