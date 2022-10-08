$(info Found 4 makefiles)
USER_MAKEFILE := /home/queenie/airsdk/sdk/pc/atom.mk
USER_MAKEFILES += $(USER_MAKEFILE)
$(call user-makefile-before-include,$(USER_MAKEFILE))
include $(USER_MAKEFILE)
$(call user-makefile-after-include,$(USER_MAKEFILE))
USER_MAKEFILE := /home/queenie/airsdk/build/alchemy/targets/packages.mk
USER_MAKEFILES += $(USER_MAKEFILE)
$(call user-makefile-before-include,$(USER_MAKEFILE))
include $(USER_MAKEFILE)
$(call user-makefile-after-include,$(USER_MAKEFILE))
USER_MAKEFILE := /home/queenie/airsdk/build/alchemy/toolchains/packages.mk
USER_MAKEFILES += $(USER_MAKEFILE)
$(call user-makefile-before-include,$(USER_MAKEFILE))
include $(USER_MAKEFILE)
$(call user-makefile-after-include,$(USER_MAKEFILE))
USER_MAKEFILE := /home/queenie/airsdk/packages/airsdk-samples/hello/atom.mk
USER_MAKEFILES += $(USER_MAKEFILE)
$(call user-makefile-before-include,$(USER_MAKEFILE))
include $(USER_MAKEFILE)
$(call user-makefile-after-include,$(USER_MAKEFILE))
