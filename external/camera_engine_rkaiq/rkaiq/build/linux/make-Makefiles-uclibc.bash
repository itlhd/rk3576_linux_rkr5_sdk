#!/bin/bash
# Run this from within a bash shell
# x86_64 is for simulation do not enable RK platform
export AIQ_BUILD_HOST_DIR=/data/project_codes/arm-rockchip830-linux-uclibcgnueabihf
if [ "${RKAIQ_TARGET_SOC}" == "rv1103b" ];then
	export AIQ_BUILD_HOST_DIR=/data/project_codes/arm-rockchip830-linux-uclibcgnueabihf-rv1103b
	echo "${AIQ_BUILD_HOST_DIR}"
fi
export AIQ_BUILD_TOOLCHAIN_TRIPLE=arm-rockchip830-linux-uclibcgnueabihf
export AIQ_BUILD_SYSROOT=sysroot
export AIQ_BUILD_ARCH=arm
TOOLCHAIN_FILE=$(pwd)/../../cmake/toolchains/gcc.cmake
OUTPUT=$(pwd)/output/${AIQ_BUILD_ARCH}
SOURCE_PATH=$OUTPUT/../../../../

mkdir -p $OUTPUT
pushd $OUTPUT

cmake -G "Ninja" \
    -DCMAKE_BUILD_TYPE=MinSizeRel \
    -DRKAIQ_TARGET_SOC=${RKAIQ_TARGET_SOC} \
    -DARCH=${AIQ_BUILD_ARCH} \
    -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE \
    -DRKAIQ_BUILD_BINARY_IQ=ON \
    -DCMAKE_SKIP_RPATH=TRUE \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=YES \
    -DISP_HW_VERSION=${ISP_HW_VERSION} \
    -DCMAKE_INSTALL_PREFIX="installed" \
    $SOURCE_PATH \
&& ninja -j$(nproc) \
&& ninja install

status_code=$?

popd

exit $status_code
