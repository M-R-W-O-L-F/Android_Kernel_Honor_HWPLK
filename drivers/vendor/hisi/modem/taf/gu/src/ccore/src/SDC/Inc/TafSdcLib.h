
#ifndef _TAF_SDC_LIB_H_
#define _TAF_SDC_LIB_H_
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "TafSdcCtx.h"

#include "TafOamInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define PRE_SECOND_TO_TICK                      (100)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
#define TAF_SDC_GET_CURC_RPT_CTRL_STATUS_MAP_TBL_PTR()    (&g_aenTafSdcCurcRptCmdTable[0])
#define TAF_SDC_GET_CURC_RPT_CTRL_STATUS_MAP_TBL_SIZE()   (sizeof(g_aenTafSdcCurcRptCmdTable)/sizeof(TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8))

#define TAF_SDC_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_PTR()    (&g_aenTafSdcUnsolicitedRptCmdTable[0])
#define TAF_SDC_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_SIZE()   (sizeof(g_aenTafSdcUnsolicitedRptCmdTable)/sizeof(TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8))

#define TAF_SDC_MIN(n1,n2)                                  (((n1) > (n2)) ? (n2):(n1))


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU
 �ṹ˵��  :TAF��g_stTafSdcCtx�е�NETWORK/APPNETWORK��Ϣ��ά�ɲ�

 �޸ļ�¼  :
  1.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    TAF_SDC_NETWORK_INFO_STRU           stNetworkInfo;                          
    TAF_SDC_APPNETWORK_INFO             stAppNetworkInfo;
}TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 OM_TraceMsgHook(VOS_VOID* pMsg);

VOS_UINT32  TAF_SDC_IsPlatformRatSupported(
    TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8                    enSpecRat
);

VOS_UINT32  TAF_SDC_IsPlatformSupportLte( VOS_VOID );

VOS_UINT32  TAF_SDC_IsPlatformSupportUtran( VOS_VOID );
VOS_UINT32  TAF_SDC_IsPlatformSupportUtranFdd( VOS_VOID );
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT32  TAF_SDC_IsPlatformSupportUtranTdd( VOS_VOID );
#endif

VOS_UINT32  TAF_SDC_IsPlatformSupportGsm( VOS_VOID );

VOS_UINT32 TAF_SDC_CheckRptCmdStatus(
    VOS_UINT8                                  *pRptCfg,
    TAF_SDC_CMD_RPT_CTRL_TYPE_ENUM_UINT8        enRptCtrlType,
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            enRptCmdIndex
);
VOS_UINT32 TAF_SDC_UpdateRptCmdStatus(
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            enRptCmdIndex,
    VOS_UINT32                                  ulRptCmdStatus
);

VOS_UINT32 TAF_SDC_ConvertOamSendPid(
    VOS_UINT32                          ulConvertedSendPid
);

VOS_UINT32 TAF_SDC_GetCsSrvExistFlg(VOS_VOID);



VOS_UINT32 TAF_SDC_GetImsSupportFlag(VOS_VOID);

#if (FEATURE_ON == FEATURE_PTM)
VOS_UINT32 TAF_SDC_IsErrLogNeedRecord(VOS_UINT16 usLevel);
#endif

VOS_UINT32  TAF_CalcTime(
                VOS_UINT32  ulFirTime,
                VOS_UINT32  ulSecTime,
                VOS_UINT32 *pulTotalTime
);

VOS_UINT32 TAF_SDC_IsUsimStausValid(VOS_VOID);


#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 TAF_SDC_IsImsVoiceSupportedInUE(VOS_VOID);
VOS_UINT32 TAF_SDC_IsImsVoiceSupportedInNW(VOS_VOID);
#endif

VOS_VOID TAF_SDC_PlmnId2Bcd(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
);

VOS_UINT32 TAF_SDC_IsConfigCLInterWork(VOS_VOID);

VOS_UINT32 TAF_SDC_IsLteOnlyMode(
    TAF_SDC_RAT_PRIO_STRU              *pstRatOrder
);

VOS_UINT32 TAF_SDC_IsCsNormalService(VOS_VOID);

VOS_UINT32 TAF_SDC_IsImsSrvExist(VOID);


VOS_UINT8 TAF_SDC_IsCurrentNormalServiceStatus(void);

VOS_UINT8 TAF_SDC_IsCurrentNormalRegStatus(void);

VOS_VOID TAF_MMA_UpdateRoamFlag(
    TAF_SDC_REG_STATUS_ENUM_UINT8      enRegState
);

VOS_UINT32 TAF_SDC_IsAppSepcDomainRegStaChg(
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enCnDomainId,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState
);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafSdcLib.h */
