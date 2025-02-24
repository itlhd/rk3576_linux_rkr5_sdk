/* GPL-2.0 WITH Linux-syscall-note OR Apache 2.0 */
/* Copyright (c) 2021 Fuzhou Rockchip Electronics Co., Ltd */

#ifndef INCLUDE_RT_MPI_MPI_VENC_H_
#define INCLUDE_RT_MPI_MPI_VENC_H_

#include "rk_common.h"
#include "rk_comm_video.h"
#include "rk_comm_venc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

RK_S32 RK_MPI_VENC_SetModParam(const VENC_PARAM_MOD_S *pstModParam);
RK_S32 RK_MPI_VENC_GetModParam(VENC_PARAM_MOD_S *pstModParam);
RK_S32 RK_MPI_VENC_CreateChn(VENC_CHN VeChn, const VENC_CHN_ATTR_S *pstAttr);
RK_S32 RK_MPI_VENC_DestroyChn(VENC_CHN VeChn);
RK_S32 RK_MPI_VENC_ResetChn(VENC_CHN VeChn);
RK_S32 RK_MPI_VENC_SetSceneMode(VENC_CHN VeChn, const VENC_SCENE_MODE_E enSceneMode);
RK_S32 RK_MPI_VENC_GetSceneMode(VENC_CHN VeChn, VENC_SCENE_MODE_E *penSceneMode);
RK_S32 RK_MPI_VENC_StartRecvFrame(VENC_CHN VeChn, const VENC_RECV_PIC_PARAM_S *pstRecvParam);
RK_S32 RK_MPI_VENC_StopRecvFrame(VENC_CHN VeChn);
RK_S32 RK_MPI_VENC_QueryStatus(VENC_CHN VeChn, VENC_CHN_STATUS_S *pstStatus);
RK_S32 RK_MPI_VENC_EnableSvc(VENC_CHN VeChn, RK_BOOL bEnable);
RK_S32 RK_MPI_VENC_EnableMotionDeblur(VENC_CHN VeChn, RK_BOOL bEnable);
RK_S32 RK_MPI_VENC_EnableMotionStaticSwitch(VENC_CHN VeChn, RK_BOOL bEnable);
RK_S32 RK_MPI_VENC_EnableTmvp(VENC_CHN VeChn, RK_BOOL bEnable);
RK_S32 RK_MPI_VENC_SetChnAttr(VENC_CHN VeChn, const VENC_CHN_ATTR_S *pstChnAttr);
RK_S32 RK_MPI_VENC_GetChnAttr(VENC_CHN VeChn, VENC_CHN_ATTR_S *pstChnAttr);
RK_S32 RK_MPI_VENC_SetChnBufWrapAttr(VENC_CHN VeChn, const VENC_CHN_BUF_WRAP_S *pstVencChnBufWrap);
RK_S32 RK_MPI_VENC_GetChnBufWrapAttr(VENC_CHN VeChn, VENC_CHN_BUF_WRAP_S *pstVencChnBufWrap);
RK_S32 RK_MPI_VENC_SetChnRefBufShareAttr(VENC_CHN VeChn, const VENC_CHN_REF_BUF_SHARE_S *pstVencChnRefBufShare);
RK_S32 RK_MPI_VENC_GetChnRefBufShareAttr(VENC_CHN VeChn, VENC_CHN_REF_BUF_SHARE_S *pstVencChnRefBufShare);
RK_S32 RK_MPI_VENC_SetComboAttr(VENC_CHN VeChn, VENC_COMBO_ATTR_S *pstComboAttr);
RK_S32 RK_MPI_VENC_GetComboAttr(VENC_CHN VeChn, VENC_COMBO_ATTR_S *pstComboAttr);
RK_S32 RK_MPI_VENC_EnableThumbnail(VENC_CHN VeChn);
RK_S32 RK_MPI_VENC_ThumbnailBind(VENC_CHN VeChn, VENC_CHN VeChnTb);
RK_S32 RK_MPI_VENC_ThumbnailRequest(VENC_CHN VeChn);
RK_S32 RK_MPI_VENC_SetChnParam(VENC_CHN VeChn, const VENC_CHN_PARAM_S *pstChnParam);
RK_S32 RK_MPI_VENC_GetChnParam(VENC_CHN VeChn, VENC_CHN_PARAM_S *pstChnParam);
RK_S32 RK_MPI_VENC_SendFrame(VENC_CHN VeChn, const VIDEO_FRAME_INFO_S *pstFrame, RK_S32 s32MilliSec);
RK_S32 RK_MPI_VENC_SendFrameEx(VENC_CHN VeChn, const USER_FRAME_INFO_S *pstFrame, RK_S32 s32MilliSec);
RK_S32 RK_MPI_VENC_GetStream(VENC_CHN VeChn, VENC_STREAM_S *pstStream, RK_S32 s32MilliSec);
RK_S32 RK_MPI_VENC_ReleaseStream(VENC_CHN VeChn, VENC_STREAM_S *pstStream);
RK_S32 RK_MPI_VENC_RequestIDR(VENC_CHN VeChn, RK_BOOL bInstant);
RK_S32 RK_MPI_VENC_RequestPskip(VENC_CHN VeChn, RK_S32 s32Num, RK_S32 s32Interval);
RK_S32 RK_MPI_VENC_SetRoiAttr(VENC_CHN VeChn, const VENC_ROI_ATTR_S *pstRoiAttr);
RK_S32 RK_MPI_VENC_GetRoiAttr(VENC_CHN VeChn, RK_U32 u32Index, VENC_ROI_ATTR_S *pstRoiAttr);
RK_S32 RK_MPI_VENC_SetRcParam(VENC_CHN VeChn, const VENC_RC_PARAM_S *pstRcParam);
RK_S32 RK_MPI_VENC_GetRcParam(VENC_CHN VeChn, VENC_RC_PARAM_S *pstRcParam);
RK_S32 RK_MPI_VENC_SetRcParam2(VENC_CHN VeChn, const VENC_RC_PARAM2_S *pstRcParam2);
RK_S32 RK_MPI_VENC_GetRcParam2(VENC_CHN VeChn, VENC_RC_PARAM2_S *pstRcParam2);
RK_S32 RK_MPI_VENC_SetRcParam3(VENC_CHN VeChn, const VENC_RC_PARAM3_S *pstRcParam3);
RK_S32 RK_MPI_VENC_GetRcParam3(VENC_CHN VeChn, VENC_RC_PARAM3_S *pstRcParam3);
RK_S32 RK_MPI_VENC_SetRcAdvParam(VENC_CHN VeChn, const VENC_RC_ADVPARAM_S *pstRcAdvParam);
RK_S32 RK_MPI_VENC_GetRcAdvParam(VENC_CHN VeChn, VENC_RC_ADVPARAM_S *pstRcAdvParam);
RK_S32 RK_MPI_VENC_SetFrameLostStrategy(VENC_CHN VeChn, const VENC_FRAMELOST_S *pstFrmLostParam);
RK_S32 RK_MPI_VENC_GetFrameLostStrategy(VENC_CHN VeChn, VENC_FRAMELOST_S *pstFrmLostParam);
RK_S32 RK_MPI_VENC_SetSuperFrameStrategy(VENC_CHN VeChn, const VENC_SUPERFRAME_CFG_S *pstSuperFrmParam);
RK_S32 RK_MPI_VENC_GetSuperFrameStrategy(VENC_CHN VeChn, VENC_SUPERFRAME_CFG_S *pstSuperFrmParam);
RK_S32 RK_MPI_VENC_SetIntraRefresh(VENC_CHN VeChn, const VENC_INTRA_REFRESH_S *pstIntraRefresh);
RK_S32 RK_MPI_VENC_GetIntraRefresh(VENC_CHN VeChn, VENC_INTRA_REFRESH_S *pstIntraRefresh);
RK_S32 RK_MPI_VENC_SetHierarchicalQp(VENC_CHN VeChn, const VENC_HIERARCHICAL_QP_S *pstHierarchicalQp);
RK_S32 RK_MPI_VENC_GetHierarchicalQp(VENC_CHN VeChn, VENC_HIERARCHICAL_QP_S *pstHierarchicalQp);
RK_S32 RK_MPI_VENC_SetCuPrediction(VENC_CHN VeChn, const VENC_CU_PREDICTION_S *pstCuPrediction);
RK_S32 RK_MPI_VENC_GetCuPrediction(VENC_CHN VeChn, VENC_CU_PREDICTION_S *pstCuPrediction);
RK_S32 RK_MPI_VENC_SetSkipBias(VENC_CHN VeChn, const VENC_SKIP_BIAS_S *pstSkipBias);
RK_S32 RK_MPI_VENC_GetSkipBias(VENC_CHN VeChn, VENC_SKIP_BIAS_S *pstSkipBias);
RK_S32 RK_MPI_VENC_SetDeBreathEffect(VENC_CHN VeChn, const VENC_DEBREATHEFFECT_S *pstDeBreathEffect);
RK_S32 RK_MPI_VENC_GetDeBreathEffect(VENC_CHN VeChn, VENC_DEBREATHEFFECT_S *pstDeBreathEffect);
RK_S32 RK_MPI_VENC_SetJpegParam(VENC_CHN VeChn, const VENC_JPEG_PARAM_S *pstJpegParam);
RK_S32 RK_MPI_VENC_GetJpegParam(VENC_CHN VeChn, VENC_JPEG_PARAM_S *pstJpegParam);
RK_S32 RK_MPI_VENC_GetFd(VENC_CHN VeChn);
RK_S32 RK_MPI_VENC_CloseFd(VENC_CHN VeChn);
RK_S32 RK_MPI_VENC_InsertUserData(VENC_CHN VeChn, RK_U8 *pu8Data, RK_U32 u32Len);
RK_S32 RK_MPI_VENC_SetChnRotation(VENC_CHN VeChn, ROTATION_E enRotation);
RK_S32 RK_MPI_VENC_GetChnRotation(VENC_CHN VeChn, ROTATION_E *enRotation);
RK_S32 RK_MPI_VENC_SetQpmap(VENC_CHN VeChn, const MB_BLK blk);
RK_S32 RK_MPI_VENC_GetQpmap(VENC_CHN VeChn, MB_BLK *pBlk);
RK_S32 RK_MPI_VENC_AttachMbPool(VENC_CHN VeChn, MB_POOL hMbPool);
RK_S32 RK_MPI_VENC_DetachMbPool(VENC_CHN VeChn);
RK_S32 RK_MPI_VENC_SetSliceSplit(VENC_CHN VeChn, const VENC_SLICE_SPLIT_S *pstSliceSplit);
RK_S32 RK_MPI_VENC_GetSliceSplit(VENC_CHN VeChn, VENC_SLICE_SPLIT_S *pstSliceSplit);
RK_S32 RK_MPI_VENC_SetFilter(VENC_CHN VeChn, const VENC_FILTER_S *pstFilter);
RK_S32 RK_MPI_VENC_GetFilter(VENC_CHN VeChn, VENC_FILTER_S *pstFilter);
RK_S32 RK_MPI_VENC_SetMotionDeblurStrength(VENC_CHN VeChn, const RK_U32 u32Strength);
RK_S32 RK_MPI_VENC_GetMotionDeblurStrength(VENC_CHN VeChn, RK_U32 *pu32Strength);
RK_S32 RK_MPI_VENC_SetAntiRing(VENC_CHN VeChn, const VENC_ANTI_RING_S *pstAntiRing);
RK_S32 RK_MPI_VENC_GetAntiRing(VENC_CHN VeChn, VENC_ANTI_RING_S *pstAntiRing);
RK_S32 RK_MPI_VENC_SetAntiLine(VENC_CHN VeChn, const VENC_ANTI_LINE_S *pstAntiLine);
RK_S32 RK_MPI_VENC_GetAntiLine(VENC_CHN VeChn, VENC_ANTI_LINE_S *pstAntiLine);
RK_S32 RK_MPI_VENC_SetLambda(VENC_CHN VeChn, const VENC_LAMBDA_S *pstLambda);
RK_S32 RK_MPI_VENC_GetLambda(VENC_CHN VeChn, VENC_LAMBDA_S *pstLambda);
RK_S32 RK_MPI_VENC_SetStaticWeight(VENC_CHN VeChn, const VENC_STATIC_WEIGHT_S *pstStaticWeight);
RK_S32 RK_MPI_VENC_GetStaticWeight(VENC_CHN VeChn, VENC_STATIC_WEIGHT_S *pstStaticWeight);
RK_S32 RK_MPI_VENC_SetLightChange(VENC_CHN VeChn, const VENC_LIGHT_CHANGE_S *pstLightChange);
RK_S32 RK_MPI_VENC_GetLightChange(VENC_CHN VeChn, VENC_LIGHT_CHANGE_S *pstLightChange);
RK_S32 RK_MPI_VENC_SetAntiFlick(VENC_CHN VeChn, const VENC_ANTI_FLICK_S *pstAntiFlick);
RK_S32 RK_MPI_VENC_GetAntiFlick(VENC_CHN VeChn, VENC_ANTI_FLICK_S *pstAntiFlick);

// H264
RK_S32 RK_MPI_VENC_SetH264IntraPred(VENC_CHN VeChn, const VENC_H264_INTRA_PRED_S *pstH264IntraPred);
RK_S32 RK_MPI_VENC_GetH264IntraPred(VENC_CHN VeChn, VENC_H264_INTRA_PRED_S *pstH264IntraPred);
RK_S32 RK_MPI_VENC_SetH264Trans(VENC_CHN VeChn, const VENC_H264_TRANS_S *pstH264Trans);
RK_S32 RK_MPI_VENC_GetH264Trans(VENC_CHN VeChn, VENC_H264_TRANS_S *pstH264Trans);
RK_S32 RK_MPI_VENC_SetH264Entropy(VENC_CHN VeChn, const VENC_H264_ENTROPY_S *pstH264EntropyEnc);
RK_S32 RK_MPI_VENC_GetH264Entropy(VENC_CHN VeChn, VENC_H264_ENTROPY_S *pstH264EntropyEnc);
RK_S32 RK_MPI_VENC_SetH264Dblk(VENC_CHN VeChn, const VENC_H264_DBLK_S *pstH264Dblk);
RK_S32 RK_MPI_VENC_GetH264Dblk(VENC_CHN VeChn, VENC_H264_DBLK_S *pstH264Dblk);
RK_S32 RK_MPI_VENC_SetH264Vui(VENC_CHN VeChn, const VENC_H264_VUI_S *pstH264Vui);
RK_S32 RK_MPI_VENC_GetH264Vui(VENC_CHN VeChn, VENC_H264_VUI_S *pstH264Vui);
RK_S32 RK_MPI_VENC_SetH264Qbias(VENC_CHN VeChn, const VENC_H264_QBIAS_S *pstQbias);
RK_S32 RK_MPI_VENC_GetH264Qbias(VENC_CHN VeChn, VENC_H264_QBIAS_S *pstQbias);
RK_S32 RK_MPI_VENC_SetH264Qbias2(VENC_CHN VeChn, const VENC_H264_QBIAS2_S *pstQbias);
RK_S32 RK_MPI_VENC_GetH264Qbias2(VENC_CHN VeChn, VENC_H264_QBIAS2_S *pstQbias);

// H265
RK_S32 RK_MPI_VENC_SetH265Trans(VENC_CHN VeChn, const VENC_H265_TRANS_S *pstH265Trans);
RK_S32 RK_MPI_VENC_GetH265Trans(VENC_CHN VeChn, VENC_H265_TRANS_S *pstH265Trans);
RK_S32 RK_MPI_VENC_SetH265Entropy(VENC_CHN VeChn, const VENC_H265_ENTROPY_S *pstH265EntropyEnc);
RK_S32 RK_MPI_VENC_GetH265Entropy(VENC_CHN VeChn, VENC_H265_ENTROPY_S *pstH265EntropyEnc);
RK_S32 RK_MPI_VENC_SetH265Dblk(VENC_CHN VeChn, const VENC_H265_DBLK_S *pstH265Dblk);
RK_S32 RK_MPI_VENC_GetH265Dblk(VENC_CHN VeChn, VENC_H265_DBLK_S *pstH265Dblk);
RK_S32 RK_MPI_VENC_SetH265Sao(VENC_CHN VeChn, const VENC_H265_SAO_S *pstH265Sao);
RK_S32 RK_MPI_VENC_GetH265Sao(VENC_CHN VeChn, VENC_H265_SAO_S *pstH265Sao);
RK_S32 RK_MPI_VENC_SetH265PredUnit(VENC_CHN VeChn, const VENC_H265_PU_S *pstPredUnit);
RK_S32 RK_MPI_VENC_GetH265PredUnit(VENC_CHN VeChn, VENC_H265_PU_S *pstPredUnit);
RK_S32 RK_MPI_VENC_SetH265Vui(VENC_CHN VeChn, const VENC_H265_VUI_S *pstH265Vui);
RK_S32 RK_MPI_VENC_GetH265Vui(VENC_CHN VeChn, VENC_H265_VUI_S *pstH265Vui);
RK_S32 RK_MPI_VENC_SetH265Qbias(VENC_CHN VeChn, const VENC_H265_QBIAS_S *pstQbias);
RK_S32 RK_MPI_VENC_GetH265Qbias(VENC_CHN VeChn, VENC_H265_QBIAS_S *pstQbias);

// H264&H265 common
RK_S32 RK_MPI_VENC_SetRefParam(VENC_CHN VeChn, const VENC_REF_PARAM_S *pstRefParam);
RK_S32 RK_MPI_VENC_GetRefParam(VENC_CHN VeChn, VENC_REF_PARAM_S *pstRefParam);
RK_S32 RK_MPI_VENC_SetH265Qbias(VENC_CHN VeChn, const VENC_H265_QBIAS_S *pstQbias);
RK_S32 RK_MPI_VENC_GetH265Qbias(VENC_CHN VeChn, VENC_H265_QBIAS_S *pstQbias);
RK_S32 RK_MPI_VENC_SetH265Qbias2(VENC_CHN VeChn, const VENC_H265_QBIAS2_S *pstQbias);
RK_S32 RK_MPI_VENC_GetH265Qbias2(VENC_CHN VeChn, VENC_H265_QBIAS2_S *pstQbias);
RK_S32 RK_MPI_VENC_SetH265CuDqp(VENC_CHN VeChn, const VENC_H265_CU_DQP_S *pstCuDqp);
RK_S32 RK_MPI_VENC_GetH265CuDqp(VENC_CHN VeChn, VENC_H265_CU_DQP_S *pstCuDqp);

// MJPEG
RK_S32 RK_MPI_VENC_SetMjpegParam(VENC_CHN VeChn, const VENC_MJPEG_PARAM_S *pstMjpegParam);
RK_S32 RK_MPI_VENC_GetMjpegParam(VENC_CHN VeChn, VENC_MJPEG_PARAM_S *pstMjpegParam);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  // INCLUDE_RT_MPI_MPI_VENC_H_

