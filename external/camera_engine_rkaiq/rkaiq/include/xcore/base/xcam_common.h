/*
 * xcam_common.h - xcam common and utilities
 *
 *  Copyright (c) 2014 Intel Corporation
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
 *
 * Author: Wind Yuan <feng.yuan@intel.com>
 */

#ifndef XCAM_COMMON_H
#define XCAM_COMMON_H

#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <assert.h>
#include <math.h>
#include "xcam_defs.h"

#if defined(__linux__)
#include <pthread.h>
#endif

XCAM_BEGIN_DECLARE

typedef enum {
    XCAM_RETURN_NO_ERROR        = 0,
    XCAM_RETURN_BYPASS          = 1,

    /* errors */
    XCAM_RETURN_ERROR_FAILED    = -1,
    XCAM_RETURN_ERROR_PARAM     = -2,
    XCAM_RETURN_ERROR_MEM       = -3,
    XCAM_RETURN_ERROR_FILE      = -4,
    XCAM_RETURN_ERROR_ANALYZER  = -5,
    XCAM_RETURN_ERROR_ISP       = -6,
    XCAM_RETURN_ERROR_SENSOR    = -7,
    XCAM_RETURN_ERROR_THREAD    = -8,
    XCAM_RETURN_ERROR_IOCTL     = -9,
    XCAM_RETURN_ERROR_ORDER     = -10,
    XCAM_RETURN_ERROR_TIMEOUT   = -20,
    XCAM_RETURN_ERROR_OUTOFRANGE = -21,
    XCAM_RETURN_ERROR_UNKNOWN   = -255,
} XCamReturn;

#define xcam_malloc_type(TYPE) (TYPE*)(xcam_malloc(sizeof(TYPE)))
#define xcam_malloc_type_array(TYPE, num) (TYPE*)(xcam_malloc(sizeof(TYPE) * (num)))

#define xcam_malloc0_type(TYPE) (TYPE*)(xcam_malloc0(sizeof(TYPE)))
#define xcam_malloc0_type_array(TYPE, num) (TYPE*)(xcam_malloc0(sizeof(TYPE) * (num)))

#define xcam_mem_clear(v_stack) memset(&(v_stack), 0, sizeof(v_stack))

void * xcam_malloc (size_t size);
void * xcam_malloc0 (size_t size);

void xcam_free (void *ptr);

/*
  * return, 0 successfully
  *            else, check errno
  */
int xcam_device_ioctl (int fd, unsigned long cmd, void *arg);
const char *xcam_fourcc_to_string (uint32_t fourcc);

static inline uint32_t
xcam_ceil (uint32_t value, const uint32_t align) {
    return (value + align - 1) / align * align;
}

static inline uint32_t
xcam_around (uint32_t value, const uint32_t align) {
    return (value + align / 2) / align * align;
}

static inline uint32_t
xcam_floor (uint32_t value, const uint32_t align) {
    return value / align * align;
}

// return true or false
static inline int
xcam_ret_is_ok (XCamReturn err) {
    return err >= XCAM_RETURN_NO_ERROR;
}

//format to [0 ~ 360]
static inline float
format_angle (float angle)
{
    if (angle < 0.0f)
        angle += 360.0f;
    if (angle >= 360.0f)
        angle -= 360.0f;

    XCAM_ASSERT (angle >= 0.0f && angle < 360.0f);
    return angle;
}

static inline void xcam_to_lowercase(const char* src, char* dst) {
    for (int i = 0; src[i] != '\0'; i++)
        dst[i] = tolower((unsigned char)src[i]);
}

XCAM_END_DECLARE

#endif //XCAM_COMMON_H

