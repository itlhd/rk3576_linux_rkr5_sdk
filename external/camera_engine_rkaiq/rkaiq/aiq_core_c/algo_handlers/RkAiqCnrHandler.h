/*
 * Copyright (c) 2024 Rockchip Eletronics Co., Ltd.
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
#ifndef _AIQ_CNR_HANDLE_H_
#define _AIQ_CNR_HANDLE_H_

#include "aiq_algo_handler.h"

typedef AiqAlgoHandler_t AiqCnrHandler_t;

AiqAlgoHandler_t* AiqAlgoHandlerCnr_constructor(RkAiqAlgoDesComm* des, AiqCore_t* aiqCore);
#if 0
XCamReturn AiqCnrHandler_setAttrib(AiqCnrHandler_t* pHdlCnr, cnr_api_attrib_t* attr);
XCamReturn AiqCnrHandler_getAttrib(AiqCnrHandler_t* pHdlCnr, cnr_api_attrib_t* attr);
XCamReturn AiqCnrHandler_queryStatus(AiqCnrHandler_t* pHdlCnr, cnr_status_t* status);
#endif
XCamReturn AiqCnrHandler_setStrength(AiqCnrHandler_t* pHdlCnr, acnr_strength_t* strg);
XCamReturn AiqCnrHandler_getStrength(AiqCnrHandler_t* pHdlCnr, acnr_strength_t* strg);

#endif
