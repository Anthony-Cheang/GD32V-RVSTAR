#ifndef __MPU9250_H__
#define __MPU9250_H__
#include "gd32vf103.h"
#include "gd32vf103_gpio.h"

// 定义MPU9250地址   
#define MPU9250_ADDRESS 0XD0   // 此时AD0=0，AD0=1时，0xD2
// 定义磁力计地址
#define MAG_ADREES      0X18   // MPU9250内部集成了AK8963磁力计，此为磁力计器件地址


// 定义磁力计内部寄存器地址
/*****************************************************************************************************/
#define WIA             0x00    // 设备ID寄存器，默认值0x48（只读） 
#define CNTL1           0x0A    // 控制寄存器  设置磁力计分辨率以及工作模式，典型值：0x01 14位分辨率，单次测量

#define	MAG_XOUT_H		0x04    // 磁力计测量寄存器  x轴高八位
#define	MAG_XOUT_L		0x03    // 磁力计测量寄存器  x轴低八位
#define	MAG_YOUT_H		0x06    // 磁力计测量寄存器  y轴高八位
#define	MAG_XOUT_L		0x05    // 磁力计测量寄存器  y轴低八位
#define	MAG_ZOUT_H		0x08    // 磁力计测量寄存器  z轴高八位
#define	MAG_ZOUT_L		0x07    // 磁力计测量寄存器  z轴低八位

// 定义MPU9250内部寄存器地址
/******************************************************************************************************/
#define	PWR_MGMT_1		0x6B	// 电源管理寄存器               典型值：0x01(正常启用)
#define	WHO_AM_I		0x75	// 设备识别寄存器               默认数值0x71，只读
#define	SMPLRT_DIV		0x19	// 采样率分频寄存器             陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	// 配置寄存器                  配制数字低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	// 陀螺仪配置寄存器             陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	// 加速度计配置寄存器           加速度计自检、测量范围及高通滤波频率，典型值：0x00(不自检，2G，5Hz)
#define	ACCEL_CONFIG2	0x1D	// 加速度计配置寄存器2          加速计低通滤波频率 ，典型值：0x00
#define INTPin          0x37    // 内部引脚/旁路使能配置        开启旁路模式，从而读取磁力计数值，典型值：0x02

#define	ACCEL_XOUT_H	0x3B    // 加速度计测量数据寄存器       x轴 高八位
#define	ACCEL_XOUT_L	0x3C    // 加速度计测量数据寄存器       x轴 低八位
#define	ACCEL_YOUT_H	0x3D    // 加速度计测量数据寄存器       y轴 高八位
#define	ACCEL_YOUT_L	0x3E    // 加速度计测量数据寄存器       y轴 低八位
#define	ACCEL_ZOUT_H	0x3F    // 加速度计测量数据寄存器       z轴 高八位
#define	ACCEL_ZOUT_L	0x40    // 加速度计测量数据寄存器       z轴 低八位

#define	TEMP_OUT_H		0x41    // 温度数据寄存器               高八位
#define	TEMP_OUT_L		0x42    // 温度数据寄存器               低八位  

#define	GYRO_XOUT_H		0x43    // 陀螺仪测量寄存器             x轴高八位
#define	GYRO_XOUT_L		0x44	// 陀螺仪测量寄存器             x轴低八位
#define	GYRO_YOUT_H		0x45    // 陀螺仪测量寄存器             y轴高八位
#define	GYRO_YOUT_L		0x46    // 陀螺仪测量寄存器             y轴低八位
#define	GYRO_ZOUT_H		0x47    // 陀螺仪测量寄存器             x轴高八位
#define	GYRO_ZOUT_L		0x48    // 陀螺仪测量寄存器             x轴低八位

#define MAG_XOUT_L		0x03
#define MAG_XOUT_H		0x04
#define MAG_YOUT_L		0x05
#define MAG_YOUT_H		0x06
#define MAG_ZOUT_L		0x07
#define MAG_ZOUT_H		0x08

void Single_Write(unsigned char REG_Address,unsigned char REG_data);
unsigned char Single_Read(unsigned char REG_Address);
void mpu9250_init(void);
float mpu9250_temp();
float mpu9250_gyr_x();
float mpu9250_gyr_y();
float mpu9250_gyr_z();
float mpu9250_acc_x();
float mpu9250_acc_y();
float mpu9250_acc_z();

void Single_Write_Mag(unsigned char REG_Address,unsigned char REG_data);
unsigned char Single_Read_Mag(unsigned char REG_Address);
float mpu9250_mag_x();
float mpu9250_mag_y();
float mpu9250_mag_z();

#endif