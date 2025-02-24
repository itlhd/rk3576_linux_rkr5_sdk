################################################################################
#
# meson
#
################################################################################

MESON_VERSION = 1.3.1
MESON_SITE = https://github.com/mesonbuild/meson/releases/download/$(MESON_VERSION)
MESON_LICENSE = Apache-2.0
MESON_LICENSE_FILES = COPYING
MESON_SETUP_TYPE = setuptools

HOST_MESON_DEPENDENCIES = host-ninja

# Cleanup old files before installing
define HOST_MESON_CLEANUP
	$(RM) -r $(HOST_DIR)/lib/python$(PYTHON3_VERSION_MAJOR)/site-packages/mesonbuild
endef
HOST_MESON_PRE_INSTALL_HOOKS += HOST_MESON_CLEANUP

# Avoid interpreter shebang longer than 128 chars
define HOST_MESON_SET_INTERPRETER
	$(SED) '1s:.*:#!/usr/bin/env python3:' $(HOST_DIR)/bin/meson
endef
HOST_MESON_POST_INSTALL_HOOKS += HOST_MESON_SET_INTERPRETER

$(eval $(host-python-package))
