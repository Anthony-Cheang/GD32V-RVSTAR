#include "mpu9250.h"
#include "iic.h"

unsigned char dataBUF[18];       //接收数据缓存区  0-5为陀螺仪x、y、z轴高低位数据 6-11为加速度计仪x、y、z轴高低位数据 12-17为磁场计x、y、z轴高低位数据

/*---------MPU9250写入指令----------------*/
void Single_Write(unsigned char REG_Address,unsigned char REG_data)		    
{
  	 I2C_Start();
    I2C_SendByte(MPU9250_ADDRESS);   //发送设备地址+写信号
    I2C_WaitAck();
    I2C_SendByte(REG_Address);      //发送寄存器地址   
    I2C_WaitAck();	
    I2C_SendByte(REG_data);         //发送写入的数据
    I2C_WaitAck();   
    I2C_Stop();  
}

/*---------MPU9250读取数据----------------*/
unsigned char Single_Read(unsigned char REG_Address)
{  
    unsigned char REG_data;     	
	 I2C_Start();
    I2C_SendByte(MPU9250_ADDRESS); 
    I2C_WaitAck();
    I2C_SendByte(REG_Address);       
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(MPU9250_ADDRESS+1);
    I2C_WaitAck();
	 REG_data=I2C_ReadByte();
    I2C_NoAck();
    I2C_Stop();
	 return REG_data;
}	

/*---------配置MPU9250------------------*/
void mpu9250_init(void)
{
   Single_Write(PWR_MGMT_1,0x00);
	Single_Write(SMPLRT_DIV,0x07);
	Single_Write(CONFIG,0x06);
	Single_Write(GYRO_CONFIG,0x18);
   Single_Write(INTPin,0x02);
}

/******读取MPU9250测量的数据*******************/

void READ_MPU9250_MAG(void)
{ 
   Single_Write(0x37,0x02);//turn on Bypass Mode 
   delay_1ms(5);
   Single_Write(0x0A,0x01);
   delay_1ms(5);
   dataBUF[12]=Single_Read(MAG_XOUT_L);
   dataBUF[13]=Single_Read(MAG_XOUT_H);
   dataBUF[14]=Single_Read(MAG_YOUT_L);
   dataBUF[15]=Single_Read(MAG_YOUT_H);
   dataBUF[16]=Single_Read(MAG_ZOUT_L);
   dataBUF[17]=Single_Read(MAG_ZOUT_H);
  
}

/******读取MPU9250测量的温度数据*******************/
float mpu9250_temp()
{
   unsigned char dataBuf[2];
   int16_t tempdata=0;
   float temp;

   dataBuf[0]=Single_Read(TEMP_OUT_H); 
   dataBuf[1]=Single_Read(TEMP_OUT_L);
   tempdata=(tempdata|dataBuf[0])*256+dataBuf[1];
   temp=tempdata/333.87+21;

   return temp;
}

/******读取MPU9250陀螺仪测量的x轴数据*******************/
float mpu9250_gyr_x()
{
   unsigned char dataBuf[2];
   int16_t gyrdata=0;
   float gyr;

   dataBuf[0]=Single_Read(GYRO_XOUT_H); 
   dataBuf[1]=Single_Read(GYRO_XOUT_L);
   gyrdata=(gyrdata|dataBuf[0])*256+dataBuf[1];
   gyr=gyrdata/131.0;        //陀螺仪量程±2000°/s，131 LSB/（°/s）

   return gyr;
}

/******读取MPU9250陀螺仪测量的y轴数据*******************/
float mpu9250_gyr_y()
{
   unsigned char dataBuf[2];
   int16_t gyrdata=0;
   float gyr;

   dataBuf[0]=Single_Read(GYRO_YOUT_H); 
   dataBuf[1]=Single_Read(GYRO_YOUT_L);
   gyrdata=(gyrdata|dataBuf[0])*256+dataBuf[1];
   gyr=gyrdata/131.0;

   return gyr;
}

/******读取MPU9250陀螺仪测量的z轴数据*******************/
float mpu9250_gyr_z()
{
   unsigned char dataBuf[2];
   int16_t gyrdata=0;
   float gyr;

   dataBuf[0]=Single_Read(GYRO_ZOUT_H); 
   dataBuf[1]=Single_Read(GYRO_ZOUT_L);
   gyrdata=(gyrdata|dataBuf[0])*256+dataBuf[1];
   gyr=gyrdata/131.0;

   return gyr;
}

/******读取MPU9250加速度计测量的x轴数据*******************/
float mpu9250_acc_x()
{
   unsigned char dataBuf[2];
   int16_t accdata=0;
   float acc;

   dataBuf[0]=Single_Read(ACCEL_XOUT_H); 
   dataBuf[1]=Single_Read(ACCEL_XOUT_L);
   accdata=(accdata|dataBuf[0])*256+dataBuf[1];
   acc=accdata/1.6384;      //加速度计量程±2g，16384 LSB/g

   return acc;
}

/******读取MPU9250加速度计测量的y轴数据*******************/
float mpu9250_acc_y()
{
   unsigned char dataBuf[2];
   int16_t accdata=0;
   float acc;

   dataBuf[0]=Single_Read(ACCEL_YOUT_H); 
   dataBuf[1]=Single_Read(ACCEL_YOUT_L);
   accdata=(accdata|dataBuf[0])*256+dataBuf[1];
   acc=accdata/1.6384;      //加速度计量程±2g，16384 LSB/g

   return acc;
}

/******读取MPU9250加速度计测量的z轴数据*******************/
float mpu9250_acc_z()
{
   unsigned char dataBuf[2];
   int16_t accdata=0;
   float acc;

   dataBuf[0]=Single_Read(ACCEL_ZOUT_H); 
   dataBuf[1]=Single_Read(ACCEL_ZOUT_L);
   accdata=(accdata|dataBuf[0])*256+dataBuf[1];
   acc=accdata/1.6384;      //加速度计量程±2g，16384 LSB/g

   return acc;
}


/*-----------------------------以下为磁力计AK8963------------------------------------------*/
/*---------AK8963写入指令----------------*/
void Single_Write_Mag(unsigned char REG_Address,unsigned char REG_data)		    
{
  	 I2C_Start();
    I2C_SendByte(MAG_ADREES);       //发送设备地址+写信号
    I2C_WaitAck();
    I2C_SendByte(REG_Address);      //发送寄存器地址   
    I2C_WaitAck();	
    I2C_SendByte(REG_data);         //发送写入的数据
    I2C_WaitAck();   
    I2C_Stop();  
}

/*---------AK8963读取数据----------------*/
unsigned char Single_Read_Mag(unsigned char REG_Address)
{  
    unsigned char REG_data;     	
	 I2C_Start();
    I2C_SendByte(MAG_ADREES); 
    I2C_WaitAck();
    I2C_SendByte(REG_Address);       
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(MAG_ADREES+1);
    I2C_WaitAck();
	 REG_data=I2C_ReadByte();
    I2C_WaitAck();
    I2C_Stop();
	 return REG_data;
}	

/*--------------读数据--------------------------*/
float mpu9250_mag_x()
{
   unsigned char dataBuf[2];
   int16_t magdata=0;
   float mag;

   Single_Write(INTPin,0x02);
   Single_Write_Mag(CNTL1,0x01);
   dataBuf[0]=Single_Read_Mag(MAG_XOUT_H); 
   dataBuf[1]=Single_Read_Mag(MAG_XOUT_L);
   magdata=(magdata|dataBuf[0])*256+dataBuf[1];
   mag=magdata*0.6;      //磁力计量程4800uT，0.6uT/LSB

   return mag;
}

float mpu9250_mag_y()
{
   unsigned char dataBuf[2];
   int16_t magdata=0;
   float mag;

   Single_Write(INTPin,0x02);
   Single_Write_Mag(CNTL1,0x01);
   dataBuf[0]=Single_Read_Mag(MAG_YOUT_H); 
   dataBuf[1]=Single_Read_Mag(MAG_YOUT_L);
   magdata=(magdata|dataBuf[0])*256+dataBuf[1];
   mag=magdata*0.6;      //磁力计量程4800uT，0.6uT/LSB

   return mag;
}

float mpu9250_mag_z()
{
   unsigned char dataBuf[2];
   int16_t magdata=0;
   float mag;

   Single_Write(INTPin,0x02);
   Single_Write_Mag(CNTL1,0x01);
   dataBuf[0]=Single_Read_Mag(MAG_ZOUT_H); 
   dataBuf[1]=Single_Read_Mag(MAG_ZOUT_L);
   magdata=(magdata|dataBuf[0])*256+dataBuf[1];
   mag=magdata*0.6;      //磁力计量程4800uT，0.6uT/LSB

   return mag;
}
