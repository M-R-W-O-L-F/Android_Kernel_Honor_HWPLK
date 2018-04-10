

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "pslog.h"
#include "om.h"
#include "MmaMmcInterface.h"
#include "TafMmaCtx.h"
#include "TafMmaProcNvim.h"
#include "TafLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_COM_FUNC_C

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

VOS_UINT32 TAF_MMA_UpdataVoiceDomain(
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
)
{
    /* ���û�з����仯����Ҫ���� */
    if (enVoiceDomain == TAF_SDC_GetVoiceDomain())
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE != TAF_MMA_UpdataVoiceDomainNv((VOS_UINT32)enVoiceDomain))
    {
        /* warning��ӡ */
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdataVoiceDomain: updata nv fail!");

        return VOS_FALSE;
    }

    /* ֻ����NV���³ɹ�����ܸ���ȫ�ֱ������������״̬��һ�� */
    TAF_SDC_SetVoiceDomain(enVoiceDomain);

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_UpdateLteImsSupportFlag(
    VOS_UINT8                           ucFlag
)
{
    VOS_UINT8                           ucLteImsSupportFlag;
    VOS_UINT8                           ucLteEmsSupportFlag;

    ucLteImsSupportFlag = TAF_SDC_GetLteImsSupportFlag();
    ucLteEmsSupportFlag = TAF_SDC_GetLteEmsSupportFlag();

    /* ���û�з����仯����Ҫ���� */
    if ((ucFlag != ucLteImsSupportFlag)
     || (ucFlag != ucLteEmsSupportFlag))
    {
        if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportNv(ucFlag))
        {
            /* warning��ӡ */
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateLteImsSupportFlag: updata Lte Ims support nv fail!");

            return VOS_FALSE;
        }

        TAF_SDC_SetLteImsSupportFlag(ucFlag);
        TAF_SDC_SetLteEmsSupportFlag(ucFlag);
    }

    return VOS_TRUE;
}

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



