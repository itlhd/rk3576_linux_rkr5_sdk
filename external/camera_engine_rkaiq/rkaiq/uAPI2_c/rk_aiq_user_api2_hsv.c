/*
 * Copyright (c) 2019-2022 Rockchip Eletronics Co., Ltd.
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

#include "newStruct/hsv/include/hsv_algo_api.h"
#include "uAPI2/rk_aiq_user_api2_hsv.h"
#include "aiq_core_c/algo_handlers/RkAiqHsvHandler.h"
#include "uAPI2_c/rk_aiq_user_api2_common.h"

RKAIQ_BEGIN_DECLARE

#ifdef RK_SIMULATOR_HW
#define CHECK_USER_API_ENABLE
#endif

XCamReturn
rk_aiq_user_api2_hsv_SetAttrib(const rk_aiq_sys_ctx_t* sys_ctx, hsv_api_attrib_t* attr)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    CHECK_USER_API_ENABLE2(sys_ctx);
    CHECK_USER_API_ENABLE(RK_AIQ_ALGO_TYPE_AHSV);
    RKAIQ_API_SMART_LOCK(sys_ctx);

	rk_aiq_sys_ctx_array_t ctx_array = rk_aiq_user_api2_common_getSysCtxArray(sys_ctx);

	int type = RESULT_TYPE_HSV_PARAM;
	int man_param_size = sizeof(hsv_param_t);
	int aut_param_size = sizeof(hsv_param_auto_t);

	for (int i = 0; i < ctx_array.num; i++) {
		if (attr->opMode == RK_AIQ_OP_MODE_MANUAL || attr->opMode == RK_AIQ_OP_MODE_AUTO) {
			ret = rk_aiq_user_api2_common_processParams(ctx_array.ctx[i], true,
					&attr->opMode, &attr->en, &attr->bypass,
					type, man_param_size, &attr->stMan, aut_param_size, &attr->stAuto);
		} else {
			ret = XCAM_RETURN_ERROR_FAILED;
			LOGE_AHSV("wrong mode %d !", attr->opMode);
		}
	}

	return ret;
}

XCamReturn
rk_aiq_user_api2_hsv_GetAttrib(const rk_aiq_sys_ctx_t* sys_ctx, hsv_api_attrib_t* attr)
{
    CHECK_USER_API_ENABLE2(sys_ctx);
    CHECK_USER_API_ENABLE(RK_AIQ_ALGO_TYPE_AHSV);
    RKAIQ_API_SMART_LOCK(sys_ctx);

	const rk_aiq_sys_ctx_t* ctx = rk_aiq_user_api2_common_getSysCtx(sys_ctx);

	int type = RESULT_TYPE_HSV_PARAM;
	int man_param_size = sizeof(hsv_param_t);
	int aut_param_size = sizeof(hsv_param_auto_t);

    return rk_aiq_user_api2_common_processParams(ctx, false,
				&attr->opMode, &attr->en, &attr->bypass,
				type, man_param_size, &attr->stMan, aut_param_size, &attr->stAuto);
}

XCamReturn
rk_aiq_user_api2_hsv_QueryStatus(const rk_aiq_sys_ctx_t* sys_ctx, hsv_status_t* status)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    CHECK_USER_API_ENABLE2(sys_ctx);
    CHECK_USER_API_ENABLE(RK_AIQ_ALGO_TYPE_AHSV);
    RKAIQ_API_SMART_LOCK(sys_ctx);

	const rk_aiq_sys_ctx_t* ctx = rk_aiq_user_api2_common_getSysCtx(sys_ctx);

	AiqAlgoHandler_t* algo_handle =
		ctx->_analyzer->mAlgoHandleMaps[RK_AIQ_ALGO_TYPE_AHSV];

	if (algo_handle) {
		ret = AiqAlgoHandler_queryStatus_common(algo_handle,
				&status->opMode, &status->en, &status->bypass, &status->stMan);
		if (status->opMode == RK_AIQ_OP_MODE_AUTO)
            AiqHsvHandler_queryahsvStatus((AiqHsvHandler_t*)algo_handle, &status->ahsvStatus);
	}

	return ret;
}

static XCamReturn check_hsv_param(ahsv_hsvCalib_t* calibdb){
    int tblAll_len = calibdb->sw_hsvCfg_tblAll_len;
    for (int i = 0;i < tblAll_len;i++) {
        int lut0_mode = calibdb->tableAll[i].meshGain.lut1d0.hw_hsvT_lut1d_mode == 3? 1:calibdb->tableAll[i].meshGain.lut1d0.hw_hsvT_lut1d_mode;
        int lut1_mode = calibdb->tableAll[i].meshGain.lut1d1.hw_hsvT_lut1d_mode == 3? 1:calibdb->tableAll[i].meshGain.lut1d1.hw_hsvT_lut1d_mode;
        int lut2_mode = calibdb->tableAll[i].meshGain.lut2d.hw_hsvT_lut2d_mode / 2;
        if (lut0_mode == lut1_mode || lut1_mode == lut2_mode || lut2_mode == lut0_mode) {
            LOGE("HSV config failed, hsv.calibdb is invaild. Three output channels of hsv lut must be different."
                "Please configure by hsv.calibdb.tableAll.meshGain.");
            return XCAM_RETURN_ERROR_FAILED;
        }
    }
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
rk_aiq_user_api2_hsv_SetCalib(const rk_aiq_sys_ctx_t* sys_ctx, ahsv_hsvCalib_t* calib)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    CHECK_USER_API_ENABLE2(sys_ctx);
    CHECK_USER_API_ENABLE(RK_AIQ_ALGO_TYPE_AHSV);
    RKAIQ_API_SMART_LOCK(sys_ctx);

    if (check_hsv_param(calib) != XCAM_RETURN_NO_ERROR) {
        return XCAM_RETURN_ERROR_FAILED;
    }
    rk_aiq_sys_ctx_array_t ctx_array = rk_aiq_user_api2_common_getSysCtxArray(sys_ctx);

    for (int i = 0; i < ctx_array.num; i++) {
        AiqAlgoHandler_t* algo_handle =
		    ctx_array.ctx[i]->_analyzer->mAlgoHandleMaps[RK_AIQ_ALGO_TYPE_AHSV];
        if (algo_handle) {
            ret = AiqHsvHandler_setCalib((AiqHsvHandler_t*)algo_handle, calib);
        } else {
            ret = XCAM_RETURN_ERROR_FAILED;
            LOGE_AHSV("ctx[%d]: SetCalib failed!", i);
        }
    }

    return ret;
}

XCamReturn
rk_aiq_user_api2_hsv_GetCalib(const rk_aiq_sys_ctx_t* sys_ctx, ahsv_hsvCalib_t* calib)
{
    CHECK_USER_API_ENABLE2(sys_ctx);
    CHECK_USER_API_ENABLE(RK_AIQ_ALGO_TYPE_AHSV);
    RKAIQ_API_SMART_LOCK(sys_ctx);

	const rk_aiq_sys_ctx_t* ctx = rk_aiq_user_api2_common_getSysCtx(sys_ctx);
    AiqAlgoHandler_t* algo_handle =
		ctx->_analyzer->mAlgoHandleMaps[RK_AIQ_ALGO_TYPE_AHSV];

	if (algo_handle) 
        return AiqHsvHandler_getCalib((AiqHsvHandler_t*)algo_handle, calib);
    else {
        LOGE_AHSV("GetCalib failed!");
        return XCAM_RETURN_ERROR_FAILED;
    }
        
}

RKAIQ_END_DECLARE
