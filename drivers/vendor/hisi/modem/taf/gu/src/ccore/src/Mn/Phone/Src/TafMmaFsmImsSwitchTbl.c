

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "pslog.h"
#include "om.h"
#include "PsTypeDef.h"
#include "TafFsm.h"
#include "TafAppMma.h"
#include "TafMmaTimerMgmt.h"

#if (FEATURE_IMS == FEATURE_ON)
#include "TafMmaFsmImsSwitch.h"
#include "TafMmaFsmImsSwitchTbl.h"
#include "ImsaMmaInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_PHONE_MODE_TBL_C

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
TAF_FSM_DESC_STRU                       g_stTafMmaImsSwitchFsmDesc;

/**************************************************************************/
/*����״̬��������� */
/**************************************************************************/

/* TAF_MMA_IMS_SWITCH_STA_INIT ������ */
TAF_ACT_STRU        g_astTafMmaImsSwitchInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_IMS_SWITCH_SET_REQ,
                      TAF_MMA_RcvTafImsSwitchSet_ImsSwitch_Init ),

};

/* TAF_MMA_IMS_SWITCH_STA_WAIT_IMSA_START_CNF ������ */
TAF_ACT_STRU        g_astTafMmaImsSwitchWaitImsaStartCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_MMA_START_CNF,
                      TAF_MMA_RcvImsaStartCnf_ImsSwitch_WaitImsaStartCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_IMSA_START_CNF,
                      TAF_MMA_RcvTiWaitImsaStartCnfExpired_ImsSwitch_WaitImsaStartCnf ),

};

/* TAF_MMA_IMS_SWITCH_STA_WAIT_IMSA_STOP_CNF ������ */
TAF_ACT_STRU        g_astTafMmaImsSwitchWaitImsaStopCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_MMA_STOP_CNF,
                      TAF_MMA_RcvImsaStopCnf_ImsSwitch_WaitImsaStopCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_IMSA_POWER_OFF_CNF,
                      TAF_MMA_RcvTiWaitImsaStopCnfExpired_ImsSwitch_WaitImsaStopCnf ),

};

/* IMS����״̬���������Ϣ ״̬�� */
TAF_STA_STRU        g_astTafMmaImsSwitchStaTbl[]   =
{
    /* IMS����״̬���ĳ�ʼ��״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_IMS_SWITCH_STA_INIT,
                       g_astTafMmaImsSwitchInitActTbl ),

    /* �ȴ�IMSA�Ŀ����ظ�״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_IMS_SWITCH_STA_WAIT_IMSA_START_CNF,
                      g_astTafMmaImsSwitchWaitImsaStartCnfActTbl ),

    /* �ȴ�IMSA�Ĺػ��ظ�״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_IMS_SWITCH_STA_WAIT_IMSA_STOP_CNF,
                      g_astTafMmaImsSwitchWaitImsaStopCnfActTbl ),
};



VOS_UINT32 TAF_MMA_GetImsSwitchStaTblSize(VOS_VOID)
{
    return (sizeof(g_astTafMmaImsSwitchStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_FSM_DESC_STRU * TAF_MMA_GetImsSwitchFsmDescAddr(VOS_VOID)
{
    return (&g_stTafMmaImsSwitchFsmDesc);
}
#endif /* FEATURE_IMS */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



