/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : RttAgentInterface.h
  �� �� ��   : ����
  ��    ��   : x00312156
  ��������   : 2015��1��27��
  ����޸�   :
  ��������   : ����RTT AGENT������ģ��Ľӿڣ�������A��Errlog
  �Ľӿڣ���TLPHY�Ľӿ�

  �����б�   :
  �޸���ʷ   :
------------------------------------------------------------------------------
  1.��    ��   : 	2015��1��27��
    ��    ��   : 	x00312156
    �޸�����   : 	�����ļ�

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __RTTAGENT_INTERFACE_H__
#define __RTTAGENT_INTERFACE_H__


#ifndef LPS_RTT
#include "vos.h"
#else
#define VOS_MSG_HEADER
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define ERRLOG_STATUS_CLOSE   ( 0 )
#define ERRLOG_STATUS_OPEN    ( 1 )

#define TLPHY_ERR_LOG_CTRL_LEVEL_NULL         ( 0 )   /* ErrLog�ȼ�δ����*/
#define TLPHY_ERR_LOG_CTRL_LEVEL_CRITICAL     ( 1 )   /* ErrLog�ȼ�Ϊ���� */
#define TLPHY_ERR_LOG_CTRL_LEVEL_MAJOR        ( 2 )   /* ErrLog�ȼ�Ϊ��Ҫ */
#define TLPHY_ERR_LOG_CTRL_LEVEL_MINOR        ( 3 )   /* ErrLog�ȼ�Ϊ��Ҫ */
#define TLPHY_ERR_LOG_CTRL_LEVEL_WARNING      ( 4 )   /* ErrLog�ȼ�Ϊ��ʾ */

#define TLPHY_OM_SEND_MSG_COUNT               ( 3 )   /*TLPHYÿ�������ش�OM��Ϣ������*/
#define TLPHY_OM_SEND_CONTENT_LENGTH_IN_16BIT ( 2 )   /*TLPHY�ش�OM��Ϣ��Ϣ����*/
#define TLPHY_RTTAGENT_MSG_HEADLEN_IN_8BIT    ( 8 )   /* enMsgType+ulMsgLen ���ֽڳ���*/
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32
 ö��˵��  : TLPHY��RTT����֮�����Ϣ����
*****************************************************************************/
enum RTTAGENT_TLPHY_MSGTYPE_ENUM
{
    /* MBX ���͸�AGENT����Ϣ���� */
	MBX_TO_RTTAGENT_REQ = 0,
	/* TPHY���͸��������Ϣ���� */
	TPHY_AGENT_ERRLOG_REQ,                    /* TPHY�ϱ�Errlog���� */
	TPHY_AGENT_STORE_OM_REQ,                  /* TPHY�ϱ�OM�������� */
	TPHY_AGENT_SEND_OM_REQ,                   /* TPHY�ϱ�OM�ش����� */

	/* LPHY���͸��������Ϣ���� */
	LPHY_AGENT_ERRLOG_REQ = 32,               /* LPHY�ϱ�Errlog���� */
	LPHY_AGENT_STORE_OM_REQ,                  /* LPHY�ϱ�OM�������� */
	LPHY_AGENT_SEND_OM_REQ,                   /* LPHY�ϱ�OM�ش����� */

    /* ������RTT AGENT���͸�TLPHY����Ϣ���� */
	AGENT_TO_TLPHY_INFO_START = 63,

	AGENT_TLPHY_ERRLOG_CTRL_INFO,             /* �����͸�TLPHY ��ERRLOG���� */
	/* �����͸�TPHY ����Ϣ���� */
	AGENT_TPHY_SEND_OM_CNF,                   /* TPHY OM��Ϣ�ش�ȷ�� */

	/* �����͸�LPHY ����Ϣ���� */
	AGENT_LPHY_SEND_OM_CNF,                   /* LPHY OM��Ϣ�ش�ȷ�� */
	AGENT_TLPHY_MSG_BUTT
};
typedef VOS_UINT32 RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32;

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : TPHY_ERRLOG_TAS_INFO_STRU
 �ṹ˵��  :TPHY��A��Errlog֮��Ľӿ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32         ulAntSwitchSlice;     /* TAS�л���ʱ��� */
    VOS_UINT16         usDpdtState;          /* �л����DPDT״̬��0ֱͨ��1���� */
    VOS_INT16          ssAntValuemain;       /* �л�����������߽����źŲ���ֵ */
    VOS_INT16          ssSwitchDelta;        /* �������߲���ֵDelta */
    VOS_UINT16         usBlankType;          /* �л�ʱ��״̬ */
    VOS_UINT16         usTsEn;               /* �Ƿ���TAS��Ȩ��0����Ȩ��1����Ȩ */
    VOS_UINT16         usAgentSwitchFlag;    /* �Ƿ�Ϊ�����л���0�Ǵ����У�1������ */
    VOS_UINT16         usTasState;           /* �л�ʱ��TAS״̬��HAPPY/UNHAPPY �� */
    VOS_UINT16         usReserve;            /* Ԥ�����������ֽڶ��� */
}TPHY_ERRLOG_TAS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LPHY_ERRLOG_TAS_INFO_STRU
 �ṹ˵��  :LPHY��A��Errlog֮��Ľӿ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32         ulAntSwitchSlice;      /* TAS�л���ʱ��� */
    VOS_UINT16         usDpdtState;           /* �л����DPDT״̬��0ֱͨ��1���� */
    VOS_INT16          ssAntValuemain;        /* �л�����������߽����źŲ���ֵ */
    VOS_INT16          ssSwitchDelta;         /* �������߲���ֵDelta */
    VOS_UINT16         usBlankType;           /* �л�ʱ��״̬ */
    VOS_UINT16         usTsEn;                /* �Ƿ���TAS��Ȩ��0����Ȩ��1����Ȩ */
    VOS_UINT16         usAgentSwitchFlag;     /* �Ƿ�Ϊ�����л���0�Ǵ����У�1������ */
    VOS_UINT16         usTasState;            /* �л�ʱ��TAS״̬��HAPPY/UNHAPPY �� */
    VOS_UINT16         usReserve;             /* Ԥ�����������ֽڶ��� */
}LPHY_ERRLOG_TAS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RTTAGENT_TLPHY_MSG_STRU
 �ṹ˵��  :RTT AGENT��TLPHY�Ľӿ���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;       /* ��Ϣ���� */
    VOS_UINT32                            ulMsgLen;        /* ��Ϣ���ȣcacuContent��ʵ���ֳ��� */
    VOS_UINT8                             aucContent[4];   /* ��Ϣ���� */
}RTTAGENT_TLPHY_MSG_STRU;

/*****************************************************************************
 �ṹ��    : TPHY_AGENT_ERRLOG_REQ_STRU
 �ṹ˵��  :RTT AGENT��TPHY�������л��ؼ���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32    enMsgType;        /* ��Ϣ����ΪTPHY_AGENT_ERRLOG_REQ */
    VOS_UINT32                            ulMsgLen;         /* ��Ϣ����Ϊsizeof(PHY_ERRLOG_TPHY_TAS_INFO_STRU) /2*/
    TPHY_ERRLOG_TAS_INFO_STRU             stTphyTasInfo;    /* TPHY�����л��ؼ���Ϣ */
}TPHY_AGENT_ERRLOG_REQ_STRU;


/*****************************************************************************
 �ṹ��    :LPHY_AGENT_ERRLOG_REQ_STRU
 �ṹ˵��  :RTT AGENT��TPHY�������л��ؼ���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;        /* ��Ϣ����ΪLPHY_AGENT_ERRLOG_REQ */
    VOS_UINT32                             ulMsgLen;         /* ��Ϣ����Ϊsizeof(PHY_ERRLOG_LPHY_TAS_INFO_STRU) /2*/
    LPHY_ERRLOG_TAS_INFO_STRU              stLphyTasInfo;    /* LPHY�����л��ؼ���Ϣ */
}LPHY_AGENT_ERRLOG_REQ_STRU;


/*****************************************************************************
 �ṹ��    : TLPHY_AGENT_SEND_OM_REQ_STRU
 �ṹ˵��  :RTT AGENT��TLPHY��OM�ش���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;         /* ��Ϣ����ΪTPHY_AGENT_SEND_OM_REQ��LPHY_AGENT_SEND_OM_REQ */
    VOS_UINT32                             ulMsgLen;          /* ��Ϣ����Ϊ2 */
    VOS_UINT32                             ulOmSendMsgCount;  /* �ط���OM��Ϣ���� */
}TLPHY_AGENT_SEND_OM_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AGENT_TLPHY_SEND_OM_CNF_STRU
 �ṹ˵��  :RTT AGENT��TLPHY��OM�ش���Ϣȷ�Ͻṹ��
*****************************************************************************/
typedef struct
{
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;          /* ��Ϣ����ΪAGENT_TPHY_SEND_OM_CNF��AGENT_LPHY_SEND_OM_CNF */
    VOS_UINT32                             ulMsgLen;           /* ��Ϣ����Ϊ2 */
    VOS_UINT32                             ulOmRemainMsgCount; /* ʣ���OM��Ϣ���� */
}AGENT_TLPHY_SEND_OM_CNF_STRU;

/*****************************************************************************
�ṹ��    : AGENT_TLPHY_ERRLOG_CTRL_INFO_STRU
�ṹ˵��  : RTT AGENTת����TLPHY��ERRLOG������Ϣ
*****************************************************************************/
typedef struct
{
    RTTAGENT_TLPHY_MSGTYPE_ENUM_UINT32     enMsgType;          /* ��Ϣ����ΪAGENT_TLPHY_ERRLOG_CTRL_INFO */
    VOS_UINT32                             ulMsgLen;           /* ��Ϣ����Ϊ2 */
    VOS_UINT16                             usErrLogCtrlFlag;   /* ERRLOG�򿪱�ʶ��0�رգ�1�� */
    VOS_UINT16                             usAlmLevel;         /* ERRLOG�ϱ����� */
}AGENT_TLPHY_ERRLOG_CTRL_INFO_STRU;



/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __RTTAGENT_INTERFACE_H__ */
