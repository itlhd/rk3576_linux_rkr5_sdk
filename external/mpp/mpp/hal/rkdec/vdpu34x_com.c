/*
 * Copyright 2020 Rockchip Electronics Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define MODULE_TAG "vdpu34x_com"

#include <string.h>
#include <stdlib.h>

#include "mpp_log.h"
#include "mpp_buffer.h"
#include "mpp_common.h"
#include "mpp_compat_impl.h"
#include "mpp_env.h"

#include "vdpu34x_com.h"

static RK_U32 rcb_coeff[RCB_BUF_COUNT] = {
    [RCB_INTRA_ROW]     = 6,   /* RCB_INTRA_ROW_COEF */
    [RCB_TRANSD_ROW]    = 1,   /* RCB_TRANSD_ROW_COEF */
    [RCB_TRANSD_COL]    = 1,   /* RCB_TRANSD_COL_COEF */
    [RCB_STRMD_ROW]     = 3,   /* RCB_STRMD_ROW_COEF */
    [RCB_INTER_ROW]     = 6,   /* RCB_INTER_ROW_COEF */
    [RCB_INTER_COL]     = 3,   /* RCB_INTER_COL_COEF */
    [RCB_DBLK_ROW]      = 22,  /* RCB_DBLK_ROW_COEF */
    [RCB_SAO_ROW]       = 6,   /* RCB_SAO_ROW_COEF */
    [RCB_FBC_ROW]       = 11,  /* RCB_FBC_ROW_COEF */
    [RCB_FILT_COL]      = 67,  /* RCB_FILT_COL_COEF */
};

static RK_S32 update_size_offset(Vdpu34xRcbInfo *info, RK_U32 reg,
                                 RK_S32 offset, RK_S32 len, RK_S32 idx)
{
    RK_S32 buf_size = 0;

    buf_size = MPP_ALIGN(len * rcb_coeff[idx], RCB_ALLINE_SIZE);
    info[idx].reg = reg;
    info[idx].offset = offset;
    info[idx].size = buf_size;

    return buf_size;
}

RK_S32 vdpu34x_get_rcb_buf_size(Vdpu34xRcbInfo *info, RK_S32 width, RK_S32 height)
{
    RK_S32 offset = 0;

    offset += update_size_offset(info, 139, offset, width, RCB_DBLK_ROW);
    offset += update_size_offset(info, 133, offset, width, RCB_INTRA_ROW);
    offset += update_size_offset(info, 134, offset, width, RCB_TRANSD_ROW);
    offset += update_size_offset(info, 136, offset, width, RCB_STRMD_ROW);
    offset += update_size_offset(info, 137, offset, width, RCB_INTER_ROW);
    offset += update_size_offset(info, 140, offset, width, RCB_SAO_ROW);
    offset += update_size_offset(info, 141, offset, width, RCB_FBC_ROW);
    /* col rcb */
    offset += update_size_offset(info, 135, offset, height, RCB_TRANSD_COL);
    offset += update_size_offset(info, 138, offset, height, RCB_INTER_COL);
    offset += update_size_offset(info, 142, offset, height, RCB_FILT_COL);

    return offset;
}

void vdpu34x_setup_rcb(Vdpu34xRegCommonAddr *reg, MppDev dev, MppBuffer buf, Vdpu34xRcbInfo *info)
{
    RK_S32 fd = mpp_buffer_get_fd(buf);

    reg->reg139_rcb_dblk_base           = fd;
    reg->reg133_rcb_intra_base          = fd;
    reg->reg134_rcb_transd_row_base     = fd;
    reg->reg136_rcb_streamd_row_base    = fd;
    reg->reg137_rcb_inter_row_base      = fd;
    reg->reg140_rcb_sao_base            = fd;
    reg->reg141_rcb_fbc_base            = fd;
    reg->reg135_rcb_transd_col_base     = fd;
    reg->reg138_rcb_inter_col_base      = fd;
    reg->reg142_rcb_filter_col_base     = fd;

    if (info[RCB_DBLK_ROW].offset)
        mpp_dev_set_reg_offset(dev, 139, info[RCB_DBLK_ROW].offset);
    if (info[RCB_INTRA_ROW].offset)
        mpp_dev_set_reg_offset(dev, 133, info[RCB_INTRA_ROW].offset);
    if (info[RCB_TRANSD_ROW].offset)
        mpp_dev_set_reg_offset(dev, 134, info[RCB_TRANSD_ROW].offset);
    if (info[RCB_STRMD_ROW].offset)
        mpp_dev_set_reg_offset(dev, 136, info[RCB_STRMD_ROW].offset);
    if (info[RCB_INTER_ROW].offset)
        mpp_dev_set_reg_offset(dev, 137, info[RCB_INTER_ROW].offset);
    if (info[RCB_SAO_ROW].offset)
        mpp_dev_set_reg_offset(dev, 140, info[RCB_SAO_ROW].offset);
    if (info[RCB_FBC_ROW].offset)
        mpp_dev_set_reg_offset(dev, 141, info[RCB_FBC_ROW].offset);
    if (info[RCB_TRANSD_COL].offset)
        mpp_dev_set_reg_offset(dev, 135, info[RCB_TRANSD_COL].offset);
    if (info[RCB_INTER_COL].offset)
        mpp_dev_set_reg_offset(dev, 138, info[RCB_INTER_COL].offset);
    if (info[RCB_FILT_COL].offset)
        mpp_dev_set_reg_offset(dev, 142, info[RCB_FILT_COL].offset);
}

static RK_S32 vdpu34x_compare_rcb_size(const void *a, const void *b)
{
    Vdpu34xRcbInfo *p0 = (Vdpu34xRcbInfo *)a;
    Vdpu34xRcbInfo *p1 = (Vdpu34xRcbInfo *)b;

    return (p0->size > p1->size) ? -1 : 1;
}

RK_S32 vdpu34x_set_rcbinfo(MppDev dev, Vdpu34xRcbInfo *rcb_info)
{
    MppDevRcbInfoCfg rcb_cfg;
    RK_U32 i;
    /*
     * RCB_SET_BY_SIZE_SORT_MODE: by size sort
     * RCB_SET_BY_PRIORITY_MODE: by priority
     */
    Vdpu34xRcbSetMode_e set_rcb_mode = RCB_SET_BY_PRIORITY_MODE;
    RK_U32 rcb_priority[RCB_BUF_COUNT] = {
        RCB_DBLK_ROW,
        RCB_INTRA_ROW,
        RCB_SAO_ROW,
        RCB_INTER_ROW,
        RCB_FBC_ROW,
        RCB_TRANSD_ROW,
        RCB_STRMD_ROW,
        RCB_INTER_COL,
        RCB_FILT_COL,
        RCB_TRANSD_COL,
    };

    switch (set_rcb_mode) {
    case RCB_SET_BY_SIZE_SORT_MODE : {
        Vdpu34xRcbInfo info[RCB_BUF_COUNT];

        memcpy(info, rcb_info, sizeof(info));
        qsort(info, MPP_ARRAY_ELEMS(info),
              sizeof(info[0]), vdpu34x_compare_rcb_size);

        for (i = 0; i < MPP_ARRAY_ELEMS(info); i++) {
            rcb_cfg.reg_idx = info[i].reg;
            rcb_cfg.size = info[i].size;
            if (rcb_cfg.size > 0) {
                mpp_dev_ioctl(dev, MPP_DEV_RCB_INFO, &rcb_cfg);
            } else
                break;
        }
    } break;
    case RCB_SET_BY_PRIORITY_MODE : {
        Vdpu34xRcbInfo *info = rcb_info;
        RK_U32 index = 0;

        for (i = 0; i < MPP_ARRAY_ELEMS(rcb_priority); i ++) {
            index = rcb_priority[i];
            /*
             * If the inter row rcb buffer is placed in sram,
             * may conflict with other buffer in ddr,
             * will result in slower access to data and degraded decoding performance.
             * The issue will be resolved in chips after rk3588.
             */
            if (index == RCB_INTER_ROW)
                continue;

            rcb_cfg.reg_idx = info[index].reg;
            rcb_cfg.size = info[index].size;
            if (rcb_cfg.size > 0) {
                mpp_dev_ioctl(dev, MPP_DEV_RCB_INFO, &rcb_cfg);
            }
        }
    } break;
    default:
        break;
    }

    return 0;
}

void vdpu34x_setup_statistic(Vdpu34xRegCommon *com, Vdpu34xRegStatistic *sta)
{
    com->reg011.pix_range_detection_e = 1;

    memset(sta, 0, sizeof(*sta));

    sta->reg256.axi_perf_work_e = 1;
    sta->reg256.axi_perf_clr_e = 1;
    sta->reg256.axi_cnt_type = 1;

    sta->reg257.addr_align_type = 1;

    /* set hurry */
    sta->reg270.axi_rd_hurry_level = 3;
    sta->reg270.axi_wr_hurry_level = 1;
    sta->reg270.axi_wr_qos = 1;
    sta->reg270.axi_rd_qos = 3;
    sta->reg270.bus2mc_buffer_qos_level = 255;
    sta->reg271_wr_wait_cycle_qos = 0;
}

void vdpu34x_afbc_align_calc(MppBufSlots slots, MppFrame frame, RK_U32 expand)
{
    RK_U32 ver_stride = 0;
    RK_U32 img_height = mpp_frame_get_height(frame);
    RK_U32 img_width = mpp_frame_get_width(frame);
    RK_U32 hdr_stride = (*compat_ext_fbc_hdr_256_odd) ?
                        (MPP_ALIGN(img_width, 256) | 256) :
                        (MPP_ALIGN(img_width, 64));

    mpp_slots_set_prop(slots, SLOTS_HOR_ALIGN, mpp_align_64);
    mpp_slots_set_prop(slots, SLOTS_VER_ALIGN, mpp_align_16);

    mpp_frame_set_fbc_hdr_stride(frame, hdr_stride);

    ver_stride = mpp_align_16(img_height);
    if (*compat_ext_fbc_buf_size) {
        ver_stride += expand;
    }
    mpp_frame_set_ver_stride(frame, ver_stride);
}

RK_U32 vdpu34x_get_colmv_size(RK_U32 width, RK_U32 height, RK_U32 ctu_size,
                              RK_U32 colmv_bytes, RK_U32 colmv_size, RK_U32 compress)
{
    RK_U32 colmv_total_size;

    if (compress) {
        RK_U32 segment_w = (64 * colmv_size * colmv_size) / ctu_size;
        RK_U32 segment_h = ctu_size;
        RK_U32 seg_cnt_w = MPP_ALIGN(width, segment_w) / segment_w;
        RK_U32 seg_cnt_h = MPP_ALIGN(height, segment_h) / segment_h;
        RK_U32 seg_head_size = MPP_ALIGN(seg_cnt_w, 16) * seg_cnt_h;
        RK_U32 seg_payload_size = seg_cnt_w * seg_cnt_h * 64 * colmv_bytes;

        colmv_total_size = seg_head_size + seg_payload_size;
    } else {
        RK_U32 colmv_block_size_w = MPP_ALIGN(width, 64) / colmv_size;
        RK_U32 colmv_block_size_h = MPP_ALIGN(height, 64) / colmv_size;

        colmv_total_size = colmv_block_size_w * colmv_block_size_h * colmv_bytes;
    }

    return MPP_ALIGN(colmv_total_size, 128);
}
