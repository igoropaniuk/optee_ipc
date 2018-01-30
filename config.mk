#########################################################################
# Public variables                                                      #
# Developers may override these values when calling the makefile,       #
# as for example                                                        #
#       CFG_TEE_CLIENT_LOG_LEVEL=1 make                                 #
# or by declaring the variable in their environement, as for example    #
#       export CFG_TEE_CLIENT_LOG_LEVEL=1                               #
#       make                                                            #
#########################################################################

# CFG_TEE_CLIENT_LOG_LEVEL
#   Client (User Non Secure) log level
#   Supported values: 0 (no traces) to 4 (all traces)
CFG_TEE_CLIENT_LOG_LEVEL?=1
export CFG_TEE_CLIENT_LOG_LEVEL

# Default output directory.
# May be absolute, or relative to the optee_client source directory.
O               ?= out

# To be used instead of $(O) in sub-directories
OO := $(if $(filter /%,$(O)),$(O),$(CURDIR)/../$(O))

#########################################################################
# Private Values                                                        #
#########################################################################

# Check that settings are coherent.

ifdef ARM_TOOLCHAIN_DIR
ifeq ($(wildcard ${ARM_TOOLCHAIN_DIR}/bin/${ARM_GCC_PREFIX}-gcc),)
  $(error "ARM_TOOLCHAIN_DIR wrongly setup. Is ${ARM_TOOLCHAIN_DIR}")
endif
export ARM_TOOLCHAIN_DIR
export ARM_GCC_PREFIX
endif

