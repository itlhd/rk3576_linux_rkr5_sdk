/**
 * @file lv_demo_music_main.h
 *
 */

#ifndef LV_DEMO_MUSIC_MAIN_H
#define LV_DEMO_MUSIC_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_music.h"
#if LV_USE_DEMO_PARTY

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t * _lv_demo_music_main_create(lv_obj_t * parent);
void _lv_demo_music_play(uint32_t id);
void _lv_demo_music_stop(void);
void _lv_demo_music_resume(void);
void _lv_demo_music_pause(void);
void _lv_demo_music_album_next(bool next);
void _lv_demo_music_update_track_info(uint32_t id);
void _lv_demo_music_destroy(void);
/**********************
 *      MACROS
 **********************/
#endif /*LV_USE_DEMO_PARTY*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DEMO_MUSIC_MAIN_H*/
