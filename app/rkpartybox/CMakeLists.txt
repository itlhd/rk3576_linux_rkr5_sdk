cmake_minimum_required(VERSION 3.8)

project(rkpartybox)

add_definitions(-g -D__EXPORTED_HEADERS__)
include_directories(
	${PROJECT_SOURCE_DIR}/app/
	${PROJECT_SOURCE_DIR}/modules/include/
	${PROJECT_SOURCE_DIR}/modules/include/os/
	${PROJECT_SOURCE_DIR}/interface/
	${PROJECT_SOURCE_DIR}/vendor/include/
	${PROJECT_SOURCE_DIR}/include/
	${PROJECT_SOURCE_DIR}/hal/include/
	${CMAKE_SYSROOT}/usr/include/rockchip/
	)

include_directories(${GLIB2_INCLUDE_DIRS})
include_directories(${DBUS_INCLUDE_DIRS})

aux_source_directory(${PROJECT_SOURCE_DIR}/app SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/modules/uac SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/modules/userial SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/modules/storage SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/modules/os/common SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/modules/os/linux SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/modules/audio SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/modules/utils SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/modules/cJSON SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/modules/slog SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/modules/trace SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/vendor/rkdemo SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/interface SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/hal SRCS)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O2")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
#install(FILES ./lib64/libasan.so.8.0.0 DESTINATION "lib" RENAME "libasan.so.8")

message("CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
message("CMAKE_SYSROOT: ${CMAKE_SYSROOT}")

if (ENABLE_LVGL_DISPLAY)
add_definitions(-DENABLE_LCD_DISPLAY=1)
add_definitions(-DDEFAULT_HUMAN_LEVEL=15)
add_definitions(-DLV_USE_DEMO_PARTY=1)
add_definitions(-DUSE_DRM=1)
add_definitions(-DLV_COLOR_DEPTH=16)
include_directories(${PROJECT_SOURCE_DIR}/app/music_ui/)
include_directories(${PROJECT_SOURCE_DIR}/app/music_ui/lvgl)
include_directories(${CMAKE_SYSROOT}/usr/include/libdrm/)
include_directories(${CMAKE_SYSROOT}/usr/include/lvgl/)
include_directories(${CMAKE_SYSROOT}/usr/include/lvgl/lv_drivers/)
aux_source_directory(${PROJECT_SOURCE_DIR}/lvgl/ SRCS)
aux_source_directory(./app/music_ui SRCS)
aux_source_directory(./app/music_ui/lvgl SRCS)
aux_source_directory(./app/music_ui/assets SRCS)
else()
add_definitions(-DENABLE_LCD_DISPLAY=0)
add_definitions(-DDEFAULT_HUMAN_LEVEL=5)
endif()

if (ENABLE_RK_LED_EFFECT)
add_definitions(-DENABLE_RK_LED_EFFECT=1)
else()
add_definitions(-DENABLE_RK_LED_EFFECT=0)
endif()

# for linux, this is not need. may use this if rtos.
# if (ENABLE_RKCHIP_UAC)
# aux_source_directory(./modules/uac SRCS)
# endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(UDEV libudev REQUIRED)
include_directories(${UDEV_INCLUDE_DIRS})

link_directories(${PROJECT_SOURCE_DIR}/lib64/bt)
add_executable(${PROJECT_NAME} ${SRCS})

target_compile_definitions(${PROJECT_NAME} PRIVATE -D_GNU_SOURCE)
target_link_libraries(${PROJECT_NAME} ${UDEV_LIBRARIES})
target_link_libraries(${PROJECT_NAME}
	pthread m asound
)
#target_link_libraries(${PROJECT_NAME} mytest)

if (ENABLE_LVGL_DISPLAY)
target_link_libraries(${PROJECT_NAME} lvgl lv_drivers drm freetype evdev)
endif()

if(RK3308_PBOX_BTMCU)
	message("RK3308_PBOX_CORE_BOARD: building....")
	add_definitions(-DENABLE_EXT_BT_MCU=1)
	install(FILES ./hal/rockchip_coreboard/config_hal.json DESTINATION /etc/pbox  RENAME "config_hal.json")
	install(FILES ./bins/eq_drc_recorder_vendor_2chn.bin DESTINATION /etc/pbox RENAME "eq_drc_recorder.bin")
	install(FILES ./bins/rkstudio_vendor_2in6out.bin DESTINATION /etc/pbox RENAME "rkstudio.bin")
	install(FILES ./bins/config_howling_vendor.json DESTINATION /etc/pbox RENAME "config_howling.json")
	install(PROGRAMS bins/partybox_app_vendor.sh DESTINATION bin RENAME "partybox_app.sh")
	install(FILES ./bins/.usb_config_nouac DESTINATION /etc/init.d  RENAME ".usb_config")
else()
	target_link_libraries(${PROJECT_NAME} rkwifibt)
	add_definitions(-DENABLE_EXT_BT_MCU=0)
	install(FILES ./hal/rockchip_evb/config_hal.json DESTINATION /etc/pbox  RENAME "config_hal.json")
	install(FILES ./bins/eq_drc_recorder_evb_1chn.bin DESTINATION /etc/pbox RENAME "eq_drc_recorder.bin")
	install(FILES ./bins/eq_drc_recorder_evb_2chn.bin DESTINATION /etc/pbox)
	install(FILES ./bins/rkstudio_evb_2in2out.bin DESTINATION /etc/pbox RENAME "rkstudio.bin")
	install(FILES ./bins/config_howling_evb.json DESTINATION /etc/pbox RENAME "config_howling.json")
	install(PROGRAMS bins/partybox_app_evb.sh DESTINATION bin RENAME "partybox_app.sh")
	install(FILES ./bins/.usb_config DESTINATION /etc/init.d)
	install(FILES ./lib64/bt/librkwifibt.so DESTINATION "lib" RENAME "librkwifibt.so")
endif()

set(ROCKIT_FILE_LIBS
       ./lib64/librkaudio_effect_howling.so
       ./lib64/librkaudio_rhythm_effect.so
       ./lib64/libavutil.so.56
       ./lib64/libavcodec.so.58
       ./lib64/libswresample.so.3
       ./lib64/libavformat.so.58
       ./lib64/librkaudio_effect_vocal.so
       ./lib64/librkstudio_tuning.so
       ./lib64/librkstudio.so
       ./lib64/librockit.so
       ./lib64/librkaudio_effect_scene.so
       ./lib64/librkaudio_nn.so
       )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(FILES ${ROCKIT_FILE_LIBS} DESTINATION "lib")
install(FILES bins/asound.conf DESTINATION /etc)
install(FILES bins/led_effect.json DESTINATION /etc/pbox)
install(FILES bins/config_gender_detect.json DESTINATION /etc/pbox)
install(FILES bins/config_reverb_doa_detect.json DESTINATION /etc/pbox)
install(FILES bins/config_rhythm_player.json DESTINATION /etc/pbox)
install(FILES bins/config_howling_evb_nn.json DESTINATION /etc/pbox)
install(FILES bins/uac_config DESTINATION /etc/pbox)
install(FILES bins/SmileySans-Oblique.ttf DESTINATION /etc/pbox)
install(FILES bins/RK3308_vocal_separation.bin DESTINATION /etc/pbox)
install(FILES bins/RK3308_guitar_separation.bin DESTINATION /etc/pbox)
install(FILES bins/howling.bin DESTINATION /etc/pbox)

install(FILES bins/eq_drc_player.bin DESTINATION /etc/pbox)
install(FILES bins/eq_drc_player_ballad.bin DESTINATION /etc/pbox)
install(FILES bins/eq_drc_player_blues.bin DESTINATION /etc/pbox)
install(FILES bins/eq_drc_player_classical.bin DESTINATION /etc/pbox)
install(FILES bins/eq_drc_player_contry.bin DESTINATION /etc/pbox)
install(FILES bins/eq_drc_player_dance.bin DESTINATION /etc/pbox)
install(FILES bins/eq_drc_player_electronic.bin DESTINATION /etc/pbox)
install(FILES bins/eq_drc_player_jazz.bin DESTINATION /etc/pbox)
install(FILES bins/eq_drc_player_pop.bin DESTINATION /etc/pbox)
install(FILES bins/eq_drc_player_rock.bin DESTINATION /etc/pbox)
install(FILES bins/eq_drc_bass_boost.bin DESTINATION /etc/pbox)

install(FILES bins/wozai-48k2ch.pcm DESTINATION /etc/pbox)
install(FILES bins/Mono.pcm DESTINATION /etc/pbox)
install(FILES bins/Stereo.pcm DESTINATION /etc/pbox)
install(FILES bins/Widen.pcm DESTINATION /etc/pbox)
install(FILES bins/vocal_off.pcm DESTINATION /etc/pbox)
install(FILES bins/vocal_on.pcm DESTINATION /etc/pbox)
install(FILES bins/guitar_off.pcm DESTINATION /etc/pbox)
install(FILES bins/guitar_on.pcm DESTINATION /etc/pbox)
install(FILES bins/Sense.pcm DESTINATION /etc/pbox)
install(FILES bins/doa.pcm DESTINATION /etc/pbox)
install(FILES bins/antifeedback_off.pcm DESTINATION /etc/pbox)
install(FILES bins/antifeedback_on.pcm DESTINATION /etc/pbox)
install(FILES bins/zero.pcm DESTINATION /etc/pbox)
install(FILES bins/one.pcm DESTINATION /etc/pbox)
install(FILES bins/two.pcm DESTINATION /etc/pbox)
install(FILES bins/three.pcm DESTINATION /etc/pbox)
install(FILES bins/four.pcm DESTINATION /etc/pbox)
install(FILES bins/five.pcm DESTINATION /etc/pbox)

install(FILES bins/eq_offmode.pcm DESTINATION /etc/pbox)
install(FILES bins/eq_balledmode.pcm DESTINATION /etc/pbox)
install(FILES bins/eq_bluesmode.pcm DESTINATION /etc/pbox)
install(FILES bins/eq_classicmode.pcm DESTINATION /etc/pbox)
install(FILES bins/eq_countrymode.pcm DESTINATION /etc/pbox)
install(FILES bins/eq_dancemode.pcm DESTINATION /etc/pbox)
install(FILES bins/eq_elecmode.pcm DESTINATION /etc/pbox)
install(FILES bins/eq_jazzmode.pcm DESTINATION /etc/pbox)
install(FILES bins/eq_popmode.pcm DESTINATION /etc/pbox)
install(FILES bins/eq_rockmode.pcm DESTINATION /etc/pbox)
install(FILES bins/res_indoor.pcm DESTINATION /etc/pbox)
install(FILES bins/res_outdoor.pcm DESTINATION /etc/pbox)
install(FILES bins/horizon_placement.pcm DESTINATION /etc/pbox)
install(FILES bins/vertical_placement.pcm DESTINATION /etc/pbox)

install(FILES bins/pbox-factory.ini DESTINATION /etc/pbox)
install(PROGRAMS bins/S40-rkpartybox DESTINATION /etc/init.d)

add_subdirectory("test")

#add_custom_target(preprocess_uac_control ALL
#    COMMAND ${CMAKE_C_COMPILER} -E 
#		-I ${PROJECT_SOURCE_DIR}/app/
#		-I ${PROJECT_SOURCE_DIR}/modules/include/
#		-I ${PROJECT_SOURCE_DIR}/modules/include/os/
#		-I ${PROJECT_SOURCE_DIR}/interface/
#		-I ${PROJECT_SOURCE_DIR}/vendor/include/
#		-I ${PROJECT_SOURCE_DIR}/sys/
#		-I ${PROJECT_SOURCE_DIR}/include/
#		-I ${PROJECT_SOURCE_DIR}/hal/include/
#		-I ${CMAKE_SYSROOT}/usr/include/rockchip/
#		${PROJECT_SOURCE_DIR}/modules/uac/uac_control.c 
#		-o ${PROJECT_SOURCE_DIR}/modules/uac/uac_control.l
#    DEPENDS ${PROJECT_SOURCE_DIR}/modules/uac/uac_control.c
#    COMMENT "Generating preprocessed source file for uac_control.c"
#)
