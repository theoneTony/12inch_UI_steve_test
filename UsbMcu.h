#include "libusb.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h> 
#include <string.h>

//UsbMcu通讯命令
#define HOST_CMD_SET_TIME_COUNT      0  //设置时间
#define HOST_CMD_GET_TIME_COUNT      1  //获取时间和次数
#define HOST_CMD_TAKE_PHOTO              2  //拍照
#define HOST_CMD_RECORD_VIDEO          3  //录像

//UsbMcu缓存
#define USB_MCU_MAX_TX_LEN    50  	//定义最大发送字节数
#define USB_MCU_MAX_RX_LEN    50  	//定义最大接收字节数
typedef struct SUSB_MCU_BUF_T_
{
  uint8_t REC_FLAG;
  uint16_t REC_COUNT;
//  uint8_t TX_BUF[USB_MCU_MAX_TX_LEN];	//发送缓冲
  uint8_t RX_BUF[USB_MCU_MAX_RX_LEN];	//接收缓冲
  uint16_t RX_BUF_DEAL_COUNT;
  uint8_t RX_BUF_DEAL[USB_MCU_MAX_RX_LEN];	//接收处理缓冲
}SUSB_MCU_BUF_T;

//UsbMcu锁
extern pthread_mutex_t i_g_UsbMcuLock;
//接收UsbMcu线程ID
extern pthread_t g_t_RevUsbMcu_Tid;

//UsbMcu设备变量
extern libusb_device **g_pp_Usb_Mcu_Devs;	//pointer to pointer of device, used to retrieve a list of devices
extern libusb_context *g_p_Usb_Mcu_Ctx; //a libusb session
extern libusb_device_handle *g_p_Usb_Mcu_Dev_handle;
//UsbMcu缓存
extern SUSB_MCU_BUF_T g_m_UsbMcuBuf;
//发送和接收UsbMcu命令和数据各变量
extern char g_i_Send_Usb_Mcu_Flag;
extern int g_i_Usb_Mcu_Cmd;
extern unsigned char g_i_Usb_Mcu_Data[30];
extern int g_i_Usb_Mcu_Len;
extern unsigned long g_i_Send_Usb_Mcu_StartTime;
extern char g_i_Send_Usb_Mcu_Count;
extern int g_i_Get_Usb_Mcu_Cmd;


//打开UsbMcu
extern int OpenUsbMcu();
//接收数据从UsbMcu
extern void RevDataFromUsbMcu();
//关闭UsbMcu
extern int CloseUsbMcu(int iFlag);

