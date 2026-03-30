#include "UsbMcu.h"


//UsbMcu锁
pthread_mutex_t i_g_UsbMcuLock;
//接收UsbMcu线程ID
pthread_t g_t_RevUsbMcu_Tid;

//UsbMcu设备变量
libusb_device **g_pp_Usb_Mcu_Devs;	//pointer to pointer of device, used to retrieve a list of devices
									//指向设备指针的指针，用于检索设备列表
libusb_context *g_p_Usb_Mcu_Ctx = NULL; //a libusb session
libusb_device_handle *g_p_Usb_Mcu_Dev_handle = NULL;
//UsbMcu缓存
SUSB_MCU_BUF_T g_m_UsbMcuBuf;
//发送和接收UsbMcu命令和数据各变量
char g_i_Send_Usb_Mcu_Flag;
int g_i_Usb_Mcu_Cmd;
unsigned char g_i_Usb_Mcu_Data[30];
int g_i_Usb_Mcu_Len;
unsigned long g_i_Send_Usb_Mcu_StartTime;
char g_i_Send_Usb_Mcu_Count;
int g_i_Get_Usb_Mcu_Cmd;


//打开UsbMcu
int OpenUsbMcu()
{
    int r;				//for return values
    ssize_t cnt;		//holding number of devices in list
    r = libusb_init(&g_p_Usb_Mcu_Ctx);	//initialize a library session
    if(r < 0)
    {
        printf("Init Error \r\n");
        g_p_Usb_Mcu_Dev_handle = NULL;
        return -1;
    }

    libusb_set_debug(g_p_Usb_Mcu_Ctx, 3); //set verbosity level to 3, as suggested in the documentation
    cnt = libusb_get_device_list(g_p_Usb_Mcu_Ctx, &g_pp_Usb_Mcu_Devs); //get the list of devices
    if(cnt < 0)
    {
        printf("Get Device Error\r\n"); //there was an error
    }

    g_p_Usb_Mcu_Dev_handle = libusb_open_device_with_vid_pid(g_p_Usb_Mcu_Ctx, 0x04d9, 0xb534);

    if(g_p_Usb_Mcu_Dev_handle == NULL)
    {
        printf("Cannot open device\r\n");
        libusb_free_device_list(g_pp_Usb_Mcu_Devs, 1); //free the list, unref the devices in it
      //  libusb_exit(g_p_Usb_Mcu_Ctx);	//close the session
        g_p_Usb_Mcu_Dev_handle = NULL;
        return -2;
    }
    else
    {
        printf("Device Opened\r\n");
        libusb_free_device_list(g_pp_Usb_Mcu_Devs, 1);	//free the list, unref the devices in it
        if(libusb_kernel_driver_active(g_p_Usb_Mcu_Dev_handle, 0) == 1) { //find out if kernel driver is attached
            printf("Kernel Driver Active\r\n");

            if(libusb_detach_kernel_driver(g_p_Usb_Mcu_Dev_handle, 0) == 0) //detach it
                printf("Kernel Driver Detached!\r\n");
        }
        r = libusb_claim_interface(g_p_Usb_Mcu_Dev_handle, 0);	//claim interface 0 (the first) of device (mine had jsut 1)
        if(r < 0) {
            printf("Cannot Claim Interface\r\n");
            g_p_Usb_Mcu_Dev_handle = NULL;
            return -3;
        }
        printf("Claimed Interface\r\n");
    }
    return 0;
}


//接收数据从UsbMcu
void RevDataFromUsbMcu()
{
    int size;
    int iStartFlag = 0;
    int iPos;
    int iIndex;
    int iLen;
    int iFlagFlag = 1;

    unsigned char datain[USB_MCU_MAX_RX_LEN]="\0";
    while (1)
    {
        if (g_p_Usb_Mcu_Dev_handle == NULL)
        {
            g_m_UsbMcuBuf.REC_COUNT = 0;
            iStartFlag = 0;
            usleep(20000);
            iFlagFlag = 1;
            continue;
        }

        if (iFlagFlag == 1)
        {
            usleep(2000000);
            iFlagFlag = 2;
        }

        // 向指定端点接收数据
        pthread_mutex_lock(&i_g_UsbMcuLock);
        int rr = libusb_bulk_transfer(g_p_Usb_Mcu_Dev_handle,
                0x83,
                datain,
                1024,
                &size,
                1000);
        pthread_mutex_unlock(&i_g_UsbMcuLock);
        if (rr >= 0)
        {
                for(int j=0; j<size; j++)
                {
                    //printf("usb_mcu_prn rev %x\r\n",datain[j]);

                    g_m_UsbMcuBuf.RX_BUF[g_m_UsbMcuBuf.REC_COUNT] = datain[j];
                    g_m_UsbMcuBuf.REC_COUNT++;
                    if (g_m_UsbMcuBuf.REC_COUNT >= 2 )//检测并获取数据
                    {
                        if (g_m_UsbMcuBuf.REC_COUNT >= (USB_MCU_MAX_RX_LEN-10))//不正常数据，抛弃该数据，重新接收
                        {
                            g_m_UsbMcuBuf.REC_COUNT = 0;
                            g_m_UsbMcuBuf.REC_FLAG = 0;
                            iStartFlag = 0;
                            continue;
                        }

                        if (iStartFlag == 0)//表示检测起始符号
                        {
                              if ((g_m_UsbMcuBuf.RX_BUF[g_m_UsbMcuBuf.REC_COUNT-2] == 0xAA)&&(g_m_UsbMcuBuf.RX_BUF[g_m_UsbMcuBuf.REC_COUNT-1] == 0x55))//表示检测到起始符号
                              {
                                  g_m_UsbMcuBuf.REC_FLAG = 0;
                                  iStartFlag = 1;
                              }
                        }
                        else if (iStartFlag == 1)//表示获取命令
                        {
                              iPos = 0;
                              g_m_UsbMcuBuf.RX_BUF_DEAL[iPos++] = g_m_UsbMcuBuf.RX_BUF[g_m_UsbMcuBuf.REC_COUNT - 1];
                              iStartFlag = 2;
                        }
                        else if (iStartFlag == 2)//表示获取长度
                        {
                              iLen = g_m_UsbMcuBuf.RX_BUF[g_m_UsbMcuBuf.REC_COUNT - 1];

                              if (iLen >=  (USB_MCU_MAX_RX_LEN-10))//表示不正常数据，抛弃该数据，重新接收
                              {
                                  g_m_UsbMcuBuf.REC_COUNT = 0;
                                  g_m_UsbMcuBuf.REC_FLAG = 0;
                                  iStartFlag = 0;
                              }
                              else//表示正常数据
                              {
                                  iIndex = g_m_UsbMcuBuf.REC_COUNT;
                                  g_m_UsbMcuBuf.RX_BUF_DEAL[iPos++] = iLen;
                                  iStartFlag = 3;
                                  if (iLen == 0)//表示数据获取完成
                                  {
                                      g_m_UsbMcuBuf.RX_BUF_DEAL_COUNT = 2;
                                      g_m_UsbMcuBuf.REC_COUNT = 0;
                                      g_m_UsbMcuBuf.REC_FLAG = 1;
                                      iStartFlag = 0;
                                      printf("UsbMcu Rev Data Complete\r\n");
                                  }
                              }
                        }
                        else if (iStartFlag == 3)//表示获取数据
                        {
                              if ((g_m_UsbMcuBuf.REC_COUNT - iIndex) <= iLen)
                              {
                                   g_m_UsbMcuBuf.RX_BUF_DEAL[iPos++] = g_m_UsbMcuBuf.RX_BUF[g_m_UsbMcuBuf.REC_COUNT - 1];
                                   if ((g_m_UsbMcuBuf.REC_COUNT - iIndex) == iLen)//表示数据获取完成
                                   {
                                       g_m_UsbMcuBuf.RX_BUF_DEAL_COUNT = 2 + iLen;
                                       g_m_UsbMcuBuf.REC_COUNT = 0;
                                       g_m_UsbMcuBuf.REC_FLAG = 1;
                                       iStartFlag = 0;
                                       //printf("UsbMcu Rev Data Complete\r\n");
                                   }
                              }
                        }
                    }
                }
        }

        usleep(20000);
    }
}


//关闭UsbMcu
int CloseUsbMcu(int iFlag)
{
   // pthread_mutex_lock(&i_g_UsbMcuLock);
    int r;
    r = libusb_release_interface(g_p_Usb_Mcu_Dev_handle, 0); //release the claimed interface
    if(r!=0) {
        printf("Cannot Release Interface\r\n");
        if (iFlag == 0)
        {
         //   pthread_mutex_unlock(&i_g_UsbMcuLock);
            return -1;
        }
    }
    printf("Released Interface\r\n");

    libusb_attach_kernel_driver(g_p_Usb_Mcu_Dev_handle, 0);
    libusb_close(g_p_Usb_Mcu_Dev_handle);
  //  libusb_exit(g_p_Usb_Mcu_Ctx); //close the session
    g_p_Usb_Mcu_Dev_handle = NULL;
   // pthread_mutex_unlock(&i_g_UsbMcuLock);
    return 0;
}
