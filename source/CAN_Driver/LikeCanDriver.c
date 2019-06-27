//build command line: gcc -g -o LikeCanDriver LikeCanDriver.c -lCanCmd -lpthread

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/select.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <signal.h>  
#include <memory.h>
#include "CAN_Driver/ICANCmd.h"

#define __countof(a)  (sizeof(a)/sizeof(a[0]))

#define  DEF_DEV_INDEX               0
#define  DEF_USE_CAN_NUM             1      // 1-使用CAN0；2-使用CAN1；3-同时使用CAN0、CAN1
#define  SendFrameNum                2      // 发送帧数
#define  RecFrameNum                 50     // 接受帧数


DWORD dwDeviceHandle;
Msg_Send SendMsg;
Msg_Rec RecMsg;
Send_Ctrl_Type Send_Control[SendFrameNum];

unsigned char receive_func()  //接收线程的处理函数
{
   uint32_t reclen = 0;
   unsigned short tWORD=0;
   CAN_DataFrame RecBuf[RecFrameNum];
   CAN_ErrorInformation err;

      if(CAN_GetReceiveCount(dwDeviceHandle,0))//缓存区有报文
      {
         reclen = CAN_ChannelReceive(dwDeviceHandle, 0, RecBuf, __countof(RecBuf), 1);
         if(reclen)//接收到报文
         {
            for ( uint32_t i = 0; i < reclen; i++ )
            {
               switch (RecBuf[i].uID)
               {
                  case 0x003:
                     RecMsg.VCM2ADAS.ADASCOMFAIL=(RecBuf[i].arryData[1] >> 1) & 0x01;
                     RecMsg.VCM2ADAS.DRIVER_OPERATE=RecBuf[i].arryData[1] & 0x01;
                     tWORD = RecBuf[i].arryData[2];
                     tWORD = (tWORD<<4) | (RecBuf[i].arryData[3]>>4);
                     RecMsg.VCM2ADAS.THCOAST = tWORD;
                     tWORD = RecBuf[i].arryData[3] & 0x0F;
                     tWORD = (tWORD<<4) | RecBuf[i].arryData[4];
                     RecMsg.VCM2ADAS.THMAX = 2*tWORD;
                     RecMsg.VCM2ADAS.VCMRefuse = (RecBuf[i].arryData[7] >> 7) & 0x01;
                     RecMsg.VCM2ADAS.OVMAX = (RecBuf[i].arryData[7] >> 6) & 0x01;
                     RecMsg.VCM2ADAS.OVCAOST =(RecBuf[i].arryData[7] >> 5) & 0x01;
                     RecMsg.VCM2ADAS.BRKRQ = (RecBuf[i].arryData[7]  >> 4) & 0x01;
                     RecMsg.VCM2ADAS.SSSTP_ACT = (RecBuf[i].arryData[7]  >> 3) & 0x01;
                     RecMsg.VCM2ADAS.fADAS_IN_CNTL = (RecBuf[i].arryData[7]  >> 2) & 0x01;
                     RecMsg.VCM2ADAS.PRUN003 = RecBuf[i].arryData[7] & 0x03;
                     break;
                  case 0x421:
                     RecMsg.VCM2CVT.ATCVT_RangeIndication = (RecBuf[i].arryData[0] >> 3 ) & 0x1F;
                     RecMsg.VCM2CVT.RGB_GearShiftRefused = (RecBuf[i].arryData[1] >> 2 ) & 0x01;
                     RecMsg.VCM2CVT.Drive_Door_Open_Buzzer = (RecBuf[i].arryData[2] >> 7 ) & 0x01;
                     RecMsg.VCM2CVT.Gear_ShiftRefuse_Buzzer = (RecBuf[i].arryData[2] >> 6 ) & 0x01;
                     RecMsg.VCM2CVT.ShBW_checkWarning = (RecBuf[i].arryData[2] >> 3 ) & 0x01;
                     RecMsg.VCM2CVT.ShBW_WarnigMessage = RecBuf[i].arryData[2] & 0x07;
                     RecMsg.VCM2CVT.Message_Counter = RecBuf[i].arryData[3] & 0x03;
                     break;
                  case 0x286:
                     RecMsg.WheelPulse.WheelSpeedPulse_RR = (RecBuf[i].arryData[0] >> 4 ) & 0x0F;
                     RecMsg.WheelPulse.WheelSpeedPulse_RL = RecBuf[i].arryData[0] & 0x0F;
                     RecMsg.WheelPulse.MessageCounterRearPulse = (RecBuf[i].arryData[1] >> 6 ) & 0x03;
                     tWORD=RecBuf[i].arryData[1]  & 0x3F;
                     tWORD=(tWORD<<1) | ((RecBuf[i].arryData[2]>>7) &0x01);
                     RecMsg.WheelPulse.WheelTop_F_L = tWORD;
                     RecMsg.WheelPulse.WheelTop_F_R = RecBuf[i].arryData[2] & 0x7f;
                     RecMsg.WheelPulse.WheelTop_R_L = RecBuf[i].arryData[3]>>1 & 0x7F;
                     tWORD = RecBuf[i].arryData[3] & 0x01;
                     RecMsg.WheelPulse.WheelTop_R_R = (RecBuf[i].arryData[4]>>2 & 0x3F) | (tWORD<<6);
                     break;
                  case 0x284:
                     tWORD = RecBuf[i].arryData[0];
                     RecMsg.WheelSpeed_F.WheelSpeed_F_R =(RecBuf[i].arryData[1]|(tWORD<<8))/24;
                     tWORD = RecBuf[i].arryData[2];
                     RecMsg.WheelSpeed_F.WheelSpeed_F_L = (RecBuf[i].arryData[3]|(tWORD<<8))/24;
                     tWORD = RecBuf[i].arryData[4];
                     RecMsg.WheelSpeed_F.VehicleSpeed_copy = (RecBuf[i].arryData[5]|(tWORD<<8))/100;
                     RecMsg.WheelSpeed_F.MessageCounterFront = RecBuf[i].arryData[6];
                     RecMsg.WheelSpeed_F.ChecksumFront = RecBuf[i].arryData[7];
                     break;
                  case 0x285:
                     tWORD = RecBuf[i].arryData[0];
                     RecMsg.WheelSpeed_R.WheelSpeed_R_R =(RecBuf[i].arryData[1]|(tWORD<<8))/24;
                     tWORD = RecBuf[i].arryData[2];
                     RecMsg.WheelSpeed_R.WheelSpeed_R_L =(RecBuf[i].arryData[3]|(tWORD<<8))/24;
                     RecMsg.WheelSpeed_R.VehicleSpeed_CVT = RecBuf[i].arryData[4];
                     RecMsg.WheelSpeed_R.MessageCounterRear = RecBuf[i].arryData[5];
                     RecMsg.WheelSpeed_R.ChecksumRear = RecBuf[i].arryData[6];
                     break;
                  case 0x60D:
                     tWORD = RecBuf[i].arryData[0];
                     RecMsg.BCM_TurnSignal.FlashingIndicatorStatus =RecBuf[i].arryData[1]>>5;
                     break;
                  case 0x05F:
                     tWORD=RecBuf[i].arryData[0];
                     tWORD=(tWORD<<8)|RecBuf[i].arryData[1];
                     RecMsg.EPS_1.EPS_SteerWheelAngle=(tWORD *0.1)-900;
                     RecMsg.EPS_1.EPS_SteerWheelRotSpd=RecBuf[i].arryData[2] *4;
                     RecMsg.EPS_1.EPS_SASFaultSts=(RecBuf[i].arryData[3] >> 3) & 0x01;
                     RecMsg.EPS_1.EPS_CalibrationSts=(RecBuf[i].arryData[3]>> 4) & 0x01;
                     RecMsg.EPS_1.EPS_SteerWheelRoSpdVaild=(RecBuf[i].arryData[3]>> 5) & 0x01;
                     RecMsg.EPS_1.EPS_SteeringAngleVaild=(RecBuf[i].arryData[3]>> 6) & 0x01;
                     RecMsg.EPS_1.EPS_DriverIntervene=(RecBuf[i].arryData[3] >> 7) & 0x01;
                     RecMsg.EPS_1.EPS_RollingCounter=RecBuf[i].arryData[6] & 0x0F;
                     RecMsg.EPS_1.EPS_CheckSum=RecBuf[i].arryData[7];
                     break;
                  case 0x173:
                     RecMsg.EPS2_PAS.EPS_FaultIndLight =(RecBuf[i].arryData[3]>>2) & 0x03;
                     RecMsg.EPS2_PAS.EPS_CAN_Fault = RecBuf[i].arryData[3] & 0x03;
                     RecMsg.EPS2_PAS.EPS_ControledMode = (RecBuf[i].arryData[4] >> 6 )& 0x03;
                     RecMsg.EPS2_PAS.EPS_2_RollingCounter = RecBuf[i].arryData[6] & 0x0F;
                     RecMsg.EPS2_PAS.EPS_2_CheckSUM =  RecBuf[i].arryData[7] ;
                     break;
                  default:
                     break;
               }
            }
         }
         else
         {
            CAN_GetErrorInfo(dwDeviceHandle, 0, &err);
            return CAN_RESULT_ERROR;
         }
      }
      else
      {

      }
      return CAN_RESULT_OK;
}

unsigned char send_func()
{
   unsigned char tByte;
   unsigned short tWORD;
   CAN_DataFrame SendBuf;
   CAN_ErrorInformation err;

   //发送包头填充
   SendBuf.uTimeFlag=0;      // 发送忽略时间戳
   SendBuf.nSendType = 0;    // 0-正常发送;1-单次发送;2-自发自收;3-单次自发自收
   SendBuf.bRemoteFlag = 0;  // 0-数据帧；1-远程帧
   SendBuf.bExternFlag = 0;  // 0-标准帧；1-扩展帧

  for(int i=0;i<SendFrameNum;i++)
  {
     Send_Control[i].RemainedTime-=10;
     if(Send_Control[i].RemainedTime<=0)
     {
        Send_Control[i].RemainedTime=Send_Control[i].Period;
        SendBuf.uID = Send_Control[i].ID;
        SendBuf.nDataLen=Send_Control[i].DataLen;   //DLC
        switch (Send_Control[i].ID)
        {
        case 0x005 ://ADAS发送内容填充
              tWORD=(SendMsg.ADAS.ADAS_AcceleratedSpd+10)*1000;
              SendBuf.arryData[0] = tWORD>>8;
              SendBuf.arryData[1] = tWORD;
//               printf("tWORD=%d,SendBuf[0]=%d,SendBuf[1]=%d\n",tWORD,SendBuf.arryData[0] ,SendBuf.arryData[1] );
              tByte=(SendMsg.ADAS.ADAS_Mode & 0x01)<<7;
              tByte|=(SendMsg.ADAS.ADAS_TO_VCM_EN & 0x01)<<6;
              tByte|=(SendMsg.ADAS.SS_Stop_Flag & 0x01)<<5;
              tByte|=(SendMsg.ADAS.AEB_ACT_Flag & 0x01)<<4;
              tByte|=(SendMsg.ADAS.ADAS_TO_VCM_Shift& 0x07)<<1;
              SendBuf.arryData[2] = tByte;

              tByte=(SendMsg.ADAS.Release_Flag_TO_APA3 & 0x01<<7);
              if(SendMsg.ADAS.ADAS_RollingCounter<=14)
              SendMsg.ADAS.ADAS_RollingCounter++;
              else
              SendMsg.ADAS.ADAS_RollingCounter=0;
              tByte|=(SendMsg.ADAS.ADAS_RollingCounter & 0x0F);
              SendBuf.arryData[3] = tByte;
              SendBuf.arryData[4] =((SendBuf.uID&0xFF)+((SendBuf.uID&0xF00)>>8)+SendBuf.arryData[0]+SendBuf.arryData[1]+SendBuf.arryData[2]+SendBuf.arryData[3])&0xFF;
              SendBuf.arryData[5]=0;
              SendBuf.arryData[6]=0;
              SendBuf.arryData[7]=0;
           break;
        case 0x0B7:
              SendBuf.arryData[0] = (SendMsg.PAS2EPS.PAS_SteerControlReq & 0x03)<<4;
              tWORD=SendMsg.PAS2EPS.PAS_TargetSteerAngleSpeed*10;
              SendBuf.arryData[1] = tWORD>>8;
              SendBuf.arryData[2] = tWORD;
              SendBuf.arryData[3] = 0;
              tWORD=(SendMsg.PAS2EPS.PAS_TargetSteerAngle+780)*10;
              SendBuf.arryData[4] = tWORD>>8;
              SendBuf.arryData[5] = tWORD;

              tByte=(SendMsg.PAS2EPS.PAS_TargetSteerAngleValid & 0x01)<<7;
              if(SendMsg.PAS2EPS.PAS_2_RollingCounter<=14)
              SendMsg.PAS2EPS.PAS_2_RollingCounter++;
              else
              SendMsg.PAS2EPS.PAS_2_RollingCounter=0;
              tByte|=(SendMsg.PAS2EPS.PAS_2_RollingCounter & 0x0F);
              SendBuf.arryData[6] = tByte;
              SendBuf.arryData[7] =((SendBuf.uID&0xFF)+((SendBuf.uID&0xF00)>>8)+SendBuf.arryData[0]+SendBuf.arryData[1]+SendBuf.arryData[2]+SendBuf.arryData[3]+SendBuf.arryData[4]+SendBuf.arryData[5]+SendBuf.arryData[6]+SendBuf.arryData[7])&0xFF;
           break;
        default:
           break;
        }
        if(CAN_ChannelSend(dwDeviceHandle, 0, &SendBuf,1)!=1)
        {
           CAN_GetErrorInfo(dwDeviceHandle, 0, &err);//no use
           return CAN_RESULT_ERROR;
        }
     }
     else
     {
         //do nothing
     }
  }
  return CAN_RESULT_OK;
}


unsigned char CAN_Init()
{
   CAN_InitConfig config;
   // 打开设备
   if ( (dwDeviceHandle = CAN_DeviceOpen(ACUSB_132B, DEF_DEV_INDEX, 0)) == 0 ) {
      CAN_Close();
   }
   // 启动CAN通道
   config.dwAccCode = 0;
   config.dwAccMask = 0xffffffff;
   config.nFilter  = 0;             // 滤波方式(0表示未设置滤波功能,1表示双滤波,2表示单滤波)
   config.bMode    = 0;             // 工作模式(0表示正常模式,1表示只听模式)
   config.nBtrType = 1;             // 位定时参数模式(1表示SJA1000,0表示LPC21XX)
   config.dwBtr[0] = 0x00;          // BTR0   0014 -1M 0016-800K 001C-500K 011C-250K 031C-12K 041C-100K 091C-50K 181C-20K 311C-10K BFFF-5K
   config.dwBtr[1] = 0x1c;          // BTR1
   config.dwBtr[2] = 0;
   config.dwBtr[3] = 0;

   if ( CAN_ChannelStart(dwDeviceHandle, 0, &config) != CAN_RESULT_OK ) {
      CAN_Close();
   }

   //ADAS发送周期设置
   Send_Control[0].ID=0x005;
   Send_Control[0].DataLen=5;
   Send_Control[0].Period=10;
   Send_Control[0].RemainedTime=10;
   //PAS2EPS 发送周期设置
   Send_Control[1].ID=0x0B7;
   Send_Control[1].DataLen=8;
   Send_Control[1].Period=10;
   Send_Control[1].RemainedTime=10;

   memset(&SendMsg,0,sizeof (SendMsg));
   memset(&RecMsg,0,sizeof (RecMsg));
   return CAN_RESULT_OK;
}

   unsigned char CAN_Close()
   {
       if(dwDeviceHandle)
       {
           CAN_ChannelStop(dwDeviceHandle, 0);
           CAN_DeviceClose(dwDeviceHandle);
           return 1;
       }
       else
       {
           return 0;
       }
   }
