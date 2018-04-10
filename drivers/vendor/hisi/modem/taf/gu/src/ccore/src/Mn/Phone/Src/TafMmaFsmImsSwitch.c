

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "pslog.h"
#include "om.h"
#include "MmaMmcInterface.h"
#include "TafMmaCtx.h"
#include "TafMmaSndApp.h"
#include "TafMmaTimerMgmt.h"
#include "TafMmaSndMmc.h"
#include "TafMmaComFunc.h"
#include "TafLog.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaSndTaf.h"
#include "MmaAppLocal.h"

#if (FEATURE_IMS == FEATURE_ON)
#include "TafMmaFsmImsSwitch.h"
#include "TafMmaFsmImsSwitchTbl.h"
#include "TafMmaSndImsa.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_IMS_SWITCH_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

/*****************************************************************************
  6 ����ʵ��
*****************************************************************************/

#if (FEATURE_IMS == FEATURE_ON)

VOS_UINT32 TAF_MMA_RcvTafImsSwitchSet_ImsSwitch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU    *pstImsSwitchSet = VOS_NULL_PTR;

    pstImsSwitchSet = (TAF_MMA_IMS_SWITCH_SET_REQ_STRU*)pstMsg;

    /* ����������Ϣ */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ��IMSҵ���ܵ����� */
    if (TAF_MMA_IMS_SWITCH_SET_POWER_ON == pstImsSwitchSet->enImsSwitch)
    {
        /* ���Ϳ��������IMSA */
        TAF_MMA_SndImsaStartReq(MMA_IMSA_START_TYPE_IMS_SWITCH_ON);

        /* Ǩ��״̬���ȴ�IMSA�Ŀ����ظ� */
        TAF_MMA_FSM_SetCurrState(TAF_MMA_IMS_SWITCH_STA_WAIT_IMSA_START_CNF);

        /* ����������ʱ�� */
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_IMSA_START_CNF, TI_TAF_MMA_WAIT_IMSA_START_CNF_LEN);
    }
    else    /* �����߹ر�IMSҵ���ܵ����� */
    {
        /* ���͹ػ������IMSA */
        TAF_MMA_SndImsaStopReq(MMA_IMSA_STOP_TYPE_IMS_SWITCH_OFF);

        /* Ǩ��״̬���ȴ�IMSA�Ĺػ��ظ� */
        TAF_MMA_FSM_SetCurrState(TAF_MMA_IMS_SWITCH_STA_WAIT_IMSA_STOP_CNF);

        /* ����������ʱ�� */
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_IMSA_POWER_OFF_CNF, TI_TAF_MMA_WAIT_IMSA_POWER_OFF_CNF_LEN);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvImsaStartCnf_ImsSwitch_WaitImsaStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_IMSA_START_CNF);

    /* ��IMSΪ�ѿ��� */
    TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_ON);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ֪ͨMTC IMSA�Ŀ��ػ�״̬ */
    TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_ON);
#endif

    /* ���ϲ�ظ��ɹ� */
    TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                            TAF_ERR_NO_ERROR);

    /* ֪ͨMMC��ǰIMS�Ŀ���״̬ */
    TAF_MMA_SndMmcImsSwitchStateInd(MMA_MMC_IMS_SWITCH_STATE_ON);

    /* ֪ͨIMSA פ����Ϣ */
    TAF_MMA_SndImsaCampInfoChangeInd();

    /* ֪ͨIMSA Service Change Ind*/
    TAF_MMA_SndImsaSrvInfoNotify((MMA_MMC_SERVICE_STATUS_ENUM_UINT32)TAF_SDC_GetPsServiceStatus());

    TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_ON_SUCC);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_RcvTiWaitImsaStartCnfExpired_ImsSwitch_WaitImsaStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        vos_printf("\n*TAF_MMA_RcvTiWaitImsaStartCnfExpired_ImsSwitch_WaitImsaStartCnf\n");
    }

    /* warning��ӡ */
    TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTiWaitImsaStartCnfExpired_ImsSwitch_WaitImsaStartCnf:time expired!");

    NAS_TRACE_HIGH("Enter TAF_MMA_RcvTiWaitImsaStartCnfExpired_ImsSwitch_WaitImsaStartCnf!");

    /* ��IMSΪ�ѹػ� */
    TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_OFF);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ֪ͨMTC IMSA�Ŀ��ػ�״̬ */
    TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_OFF);
#endif

    /* ����NVΪ��֧��IMSҵ�񣬷���AP��ѯ�����Ľ����MODEMά���Ĳ�һ�� */
    if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportFlag(VOS_FALSE))
    {
        /* warning��ӡ */
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateLteImsSupportFlag fail!");

    }

    /* ���ϲ�ظ�ʧ�� */
    TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_FAILURE,
                                            TAF_ERR_IMS_STACK_TIMEOUT);

    TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_ON_FAIL);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvImsaStopCnf_ImsSwitch_WaitImsaStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_IMSA_POWER_OFF_CNF);

    /* ��IMSΪ�ѹػ� */
    TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_OFF);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ֪ͨMTC IMSA�Ŀ��ػ�״̬ */
    TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_OFF);
#endif

    /* ���ϲ�ظ��ɹ� */
    TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                            TAF_ERR_NO_ERROR);

    /* ֪ͨMMC��ǰIMS�Ŀ���״̬ */
    TAF_MMA_SndMmcImsSwitchStateInd(MMA_MMC_IMS_SWITCH_STATE_OFF);

    /* ���õ�ǰIMS VOICE������ */
    TAF_SDC_SetImsVoiceAvailFlg(VOS_FALSE);

    /* ֪ͨMMC��ǰIMS voice�Ƿ���� */
    TAF_MMA_SndMmcImsVoiceCapInd(TAF_SDC_GetImsVoiceAvailFlg());

    /* ֪ͨSPM��ǰIMS VOICE�Ƿ���� */
    TAF_MMA_SndSpmImsVoiceCapInd(TAF_SDC_GetImsVoiceAvailFlg());

    TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_OFF_SUCC);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvTiWaitImsaStopCnfExpired_ImsSwitch_WaitImsaStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        vos_printf("\n*TAF_MMA_RcvTiWaitImsaStopCnfExpired_ImsSwitch_WaitImsaStopCnf\n");
    }

    /* warning��ӡ */
    TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTiWaitImsaStopCnfExpired_ImsSwitch_WaitImsaStopCnf:time expired!");

    NAS_TRACE_HIGH("Enter!");

    /* ��IMSΪ�ѹػ� */
    TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_OFF);

    /* ���ϲ�ظ�ʧ�� */
    TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_FAILURE,
                                            TAF_ERR_IMS_STACK_TIMEOUT);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ֪ͨMTC IMSA�Ŀ��ػ�״̬ */
    TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_OFF);
#endif

    /* ֪ͨMMC��ǰIMS�Ŀ���״̬ */
    TAF_MMA_SndMmcImsSwitchStateInd(MMA_MMC_IMS_SWITCH_STATE_OFF);

    /* ���õ�ǰIMS VOICE������ */
    TAF_SDC_SetImsVoiceAvailFlg(VOS_FALSE);

    /* ֪ͨMMC��ǰIMS voice�Ƿ���� */
    TAF_MMA_SndMmcImsVoiceCapInd(TAF_SDC_GetImsVoiceAvailFlg());

    /* ֪ͨSPM��ǰIMS VOICE�Ƿ���� */
    TAF_MMA_SndSpmImsVoiceCapInd(TAF_SDC_GetImsVoiceAvailFlg());

    TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_OFF_FAIL);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}
VOS_VOID TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enResult,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    VOS_UINT32                          ulEventType;
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU    *pstImsSwitchSet = VOS_NULL_PTR;

    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg = TAF_MMA_GetCurrFsmMsgAddr();
    ulEventType = pstEntryMsg->ulEventType;

    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ) == ulEventType)
    {
        pstImsSwitchSet = (TAF_MMA_IMS_SWITCH_SET_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer);

        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   enResult, enErrorCause);

    }

    return;

}

#endif /* FEATURE_IMS */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



