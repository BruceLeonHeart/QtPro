#ifndef _ICANCmd_H_
#define _ICANCmd_H_

typedef unsigned char   uint8_t;
typedef unsigned char   *puint8_t;
typedef unsigned short  uint16_t;
typedef int             int32_t;
typedef unsigned int    uint32_t;
typedef void            *pvoid_t;
typedef uint32_t        DWORD ;

#define __stdcall
#define PACKED    //__attribute__( ( packed, aligned(1) ) )

//�ӿڿ����Ͷ���
#define ACUSB_131B                  1
#define ACUSB_132B                  2
#define ACPCI_251                   3
#define ACPCI_252                   4
#define ACPCI_254                   5

#define ACNET_600                   6
#define ACNET_622                   7
#define LCPCIE_251                  8
#define LCPCIE_252                  9
#define LCMINIPCIE_251              10
#define LCMINIPCIE_252              11

#define LCUSB_131B              1
#define LCUSB_132B              2
#define LCMiniPcie_431          1
#define LCMiniPcie_432          2
#define LCPCI_252               4

#define USBCAN_1CH              13
#define USBCAN_C_1CH            14
#define USBCAN_E_1CH            15
#define USBCAN_E_2CH            16
#define MPCIeCAN_1CH            17
#define MPCIeCAN_2CH            18

//�������÷���״ֵ̬
#define	CAN_RESULT_OK               1
#define CAN_RESULT_ERROR            0

//CAN������
enum CAN_ErrorCode
{
    CAN_E_NOERROR         = 0x0000,   // û�з��ִ���
    CAN_E_OVERFLOW        = 0x0001,   // CAN�������ڲ�FIFO���
    CAN_E_ERRORALARM      = 0x0002,   // CAN���������󱨾�
    CAN_E_PASSIVE         = 0x0004,   // CAN��������������
    CAN_E_LOSE            = 0x0008,   // CAN�������ٲö�ʧ
    CAN_E_BUSERROR        = 0x0010,   // CAN���������ߴ���

    CAN_E_RCV_BUF         = 0x0020,   // dll CAN����BUF����
    CAN_E_ERR_BUF         = 0x0040,   // dll CAN������ϢBUF����

    CAN_E_DEVICEOPENED    = 0x0100,       // �豸�Ѿ���
    CAN_E_DEVICEOPEN      = 0x0200,       // ���豸����
    CAN_E_DEVICENOTOPEN   = 0x0400,       // �豸û�д�
    CAN_E_BUFFEROVERFLOW  = 0x0800,       // ���������
    CAN_E_DEVICENOTEXIST  = 0x1000,       // ���豸������
    CAN_E_LOADKERNELDLL   = 0x2000,       // װ�ض�̬��ʧ��
    CAN_E_CMDFAILED       = 0x4000,       // ִ������ʧ�ܴ�����
    CAN_E_BUFFERCREATE    = 0x8000,       // �ڴ治��
};

// �����˲�����
typedef struct tagWakeup_Config
{
    uint32_t	dwAccCode;                                              // ������
    uint32_t	dwAccMask;                                              // ������
    uint32_t	nFilter;                                                // �˲���ʽ(0��ʾδ�����˲�����-���յ�����CAN���Ķ�ͨ��USB��������,1��ʾ˫�˲�,2��ʾ���˲�,3-�رջ��ѹ���)
}PACKED Wakeup_Config, *PWakeup_Config;

enum ParamType
{
    PARAM_WAKEUP_CFG  = 0x4000,      // ���û������ò���
};

//CAN����֡����
typedef  struct  tagCAN_DataFrame {
    uint32_t	uTimeFlag;                      // ʱ���ʶ,�Խ���֡��Ч
    uint8_t	nSendType;                      // ����֡����,0-��������;1-���η���;2-�Է�����;3-�����Է�����
    uint8_t	bRemoteFlag;                    // �Ƿ���Զ��֡
    uint8_t	bExternFlag;                    // �Ƿ�����չ֡
    uint8_t	nDataLen;                       // ���ݳ���
    uint32_t	uID;                             // ����DI
    uint8_t	arryData[8];                    // ��������
}PACKED CAN_DataFrame,*PCAN_DataFrame;

//CAN��ʼ������
typedef struct tagCAN_InitConfig {
    uint8_t	bMode;                          // ����ģʽ(0��ʾ����ģʽ,1��ʾֻ��ģʽ)
    uint8_t	nBtrType;                       // λ��ʱ����ģʽ(1��ʾSJA1000,0��ʾLPC21XX)
    uint8_t       dwBtr[4];                                                // CANλ��ʱ����
    uint32_t	dwAccCode;                                              // ������
    uint32_t	dwAccMask;                                              // ������
    uint8_t	nFilter;                                                // �˲���ʽ(0��ʾδ�����˲�����,1��ʾ˫�˲�,2��ʾ���˲�)
    uint8_t       dwReserved;                     // Ԥ���ֶ�
}PACKED CAN_InitConfig,*PCAN_InitConfig;

//CAN�豸��Ϣ
typedef  struct  tagCAN_DeviceInformation {
    uint16_t	uHardWareVersion;               // Ӳ���汾
    uint16_t	uFirmWareVersion;               // �̼��汾
    uint16_t	uDriverVersion;                 // �����汾
    uint16_t	uInterfaceVersion;              // �ӿڿ�汾
    uint16_t	uInterruptNumber;               // �жϺ�
    uint8_t	    bChannelNumber;                 // �м�·CAN
    char        szSerialNumber[20];             // �豸���к�
    char        szHardWareType[40];             // Ӳ������
    char        szDescription[20];                      // �豸����
} PACKED CAN_DeviceInformation,*PCAN_DeviceInformation;

//CAN������Ϣ
typedef struct tagCAN_ErrorInformation {
    uint32_t			uErrorCode;             // ��������
    uint8_t			PassiveErrData[3];      // ������������
    uint8_t			ArLostErrData;          // �ٲô�������
} PACKED CAN_ErrorInformation,*PCAN_ErrorInformation;


typedef struct {
   float ADAS_AcceleratedSpd;
   unsigned char ADAS_Mode;
   unsigned char ADAS_TO_VCM_EN;
   unsigned char SS_Stop_Flag;
   unsigned char AEB_ACT_Flag;
   unsigned char ADAS_TO_VCM_Shift;
   unsigned char Release_Flag_TO_APA3;
   unsigned char ADAS_RollingCounter;
   unsigned char ADAS_CheckSum;
}ADAS_Send_Type;

typedef struct {
   unsigned short ADASCOMFAIL;
   unsigned char DRIVER_OPERATE;
   unsigned short THCOAST;
   unsigned short THMAX;
   unsigned char VCMRefuse;
   unsigned char OVMAX;
   unsigned char OVCAOST;
   unsigned char BRKRQ;
   unsigned char SSSTP_ACT;
   unsigned char fADAS_IN_CNTL;
   unsigned char PRUN003;
}VCM2ADAS_Rec_Type;

typedef struct {
   unsigned char ATCVT_RangeIndication;
   unsigned char RGB_GearShiftRefused;
   unsigned char Drive_Door_Open_Buzzer;
   unsigned char Gear_ShiftRefuse_Buzzer;
   unsigned char ShBW_checkWarning;
   unsigned char ShBW_WarnigMessage;
   unsigned char Message_Counter;
}VCM2CVT_Rec_Type;

typedef struct {
   unsigned char WheelSpeedPulse_RR;
   unsigned char WheelSpeedPulse_RL;
   unsigned char MessageCounterRearPulse;
   unsigned char WheelTop_F_L;
   unsigned char WheelTop_F_R;
   unsigned char WheelTop_R_L;
   unsigned char WheelTop_R_R;
}WheelPulse_Rec_Type;

typedef struct {
   float WheelSpeed_F_R;
   float WheelSpeed_F_L;
   float VehicleSpeed_copy;
   unsigned char MessageCounterFront;
   unsigned char ChecksumFront;
}WheelSpeed_F_Rec_Type;

typedef struct {
   float WheelSpeed_R_R;
   float WheelSpeed_R_L;
   unsigned char VehicleSpeed_CVT;
   unsigned char MessageCounterRear;
   unsigned char ChecksumRear;
}WheelSpeed_R_Rec_Type;

typedef struct {
   unsigned char PAS_SteerControlReq;
   float PAS_TargetSteerAngleSpeed;
   float PAS_TargetSteerAngle;
   unsigned char PAS_TargetSteerAngleValid;
   unsigned char PAS_2_RollingCounter;
   unsigned char PAS_2_CheckSUM;
}PAS2EPS_Send_Type;

typedef struct {
   float EPS_SteerWheelAngle;
   unsigned char EPS_SteerWheelRotSpd;
   unsigned char EPS_SASFaultSts;
   unsigned char EPS_CalibrationSts;
   unsigned char EPS_SteerWheelRoSpdVaild;
   unsigned char EPS_SteeringAngleVaild;
   unsigned char EPS_DriverIntervene;
   unsigned char EPS_RollingCounter;
   unsigned char EPS_CheckSum;
}EPS_1_Rec_Type;

typedef struct {
   unsigned char FlashingIndicatorStatus;
}BCM_TurnSignal_Rec_Type;


typedef struct {
   unsigned short EPS_Steering_Failure;
}EPS_GeneralStatus_Rec_Type;

typedef struct {
   unsigned char EPS_FaultIndLight;
   unsigned char EPS_CAN_Fault;
   unsigned char EPS_ControledMode;
   unsigned char EPS_2_RollingCounter;
   unsigned char EPS_2_CheckSUM;
}EPS2_PAS_Rec_Type;

typedef struct {
   EPS_1_Rec_Type          EPS_1;
   VCM2ADAS_Rec_Type       VCM2ADAS;
   VCM2CVT_Rec_Type        VCM2CVT;
   WheelPulse_Rec_Type     WheelPulse;
   WheelSpeed_F_Rec_Type   WheelSpeed_F;
   WheelSpeed_R_Rec_Type   WheelSpeed_R;
   BCM_TurnSignal_Rec_Type BCM_TurnSignal;
   EPS2_PAS_Rec_Type       EPS2_PAS;
}Msg_Rec;

typedef struct{
   ADAS_Send_Type ADAS;
   PAS2EPS_Send_Type PAS2EPS;
}Msg_Send;

typedef struct {
   unsigned int  ID;
   unsigned int  Period;
   int  RemainedTime;
   unsigned char DataLen;
}Send_Ctrl_Type;


/**/
#ifdef __cplusplus
extern "C" {
#endif

// ���豸
uint32_t  CAN_DeviceOpen(uint32_t dwType, uint32_t dwIndex, char *pDescription);
// �ر��豸

uint32_t  CAN_DeviceClose(uint32_t dwDeviceHandle);

// ����CAN

uint32_t  CAN_ChannelStart(uint32_t dwDeviceHandle, uint32_t dwChannel, PCAN_InitConfig pInitConfig);
// ֹͣCAN

uint32_t  CAN_ChannelStop(uint32_t dwDeviceHandle, uint32_t dwChannel);

// ��ȡ�豸��Ϣ

uint32_t  CAN_GetDeviceInfo(uint32_t dwDeviceHandle, PCAN_DeviceInformation pInfo);
// ��ȡCAN������Ϣ

uint32_t  CAN_GetErrorInfo(uint32_t dwDeviceHandle, uint32_t dwChannel, PCAN_ErrorInformation pErr);

// ��EEPROM

uint32_t  CAN_ReadEEPROM(uint32_t dwDeviceHandle, uint16_t dwAddr, puint8_t pBuff, uint16_t nLen);
// дEEPROM

uint32_t  CAN_WriteEEPROM(uint32_t dwDeviceHandle, uint16_t dwAddr, puint8_t pBuff, uint16_t nLen);

// ��������

uint32_t  CAN_ChannelSend(uint32_t dwDeviceHandle, uint32_t dwChannel, PCAN_DataFrame pSend, uint32_t nCount);
// �ӽ��ջ������ж�����

uint32_t  CAN_ChannelReceive(uint32_t dwDeviceHandle, uint32_t dwChannel, PCAN_DataFrame pReceive, uint32_t nCount, int32_t nWaitTime);
// ��ȡ���ջ�����֡��

uint32_t  CAN_GetReceiveCount(uint32_t dwDeviceHandle, uint32_t dwChannel);
// ��ս��ջ�����

uint32_t  CAN_ClearReceiveBuffer(uint32_t dwDeviceHandle, uint32_t dwChannel);

//���Ĵ���

uint32_t  CAN_ReadRegister(uint32_t dwDeviceHandle, uint32_t dwChannel, uint32_t dwAddr, puint8_t pBuff, uint16_t nLen);
//д�Ĵ���

uint32_t  CAN_WriteRegister(uint32_t dwDeviceHandle, uint32_t dwChannel, uint32_t dwAddr, puint8_t pBuff, uint16_t nLen);

// ��ȡ����

uint32_t  CAN_GetParam(uint32_t dwDeviceHandle, uint32_t dwChannel, uint32_t dwParamType, pvoid_t pData);
// ���ò���

uint32_t  CAN_SetParam(uint32_t dwDeviceHandle, uint32_t dwChannel, uint32_t dwParamType, pvoid_t pData);

unsigned char receive_func();
unsigned char send_func();
unsigned char CAN_Init();
unsigned char CAN_Close();


#ifdef __cplusplus
}
#endif

#endif //_ICANCmd_H_
