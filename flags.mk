#########################################################################
# COMMON COMPILATION FLAGS                                              #
#########################################################################

CROSS_COMPILE   ?= arm-linux-gnueabihf-
CC              ?= $(CROSS_COMPILE)gcc
AR		?= $(CROSS_COMPILE)ar

CFLAGS          := -Wall -Wbad-function-cast -Wcast-align \
		   -Werror-implicit-function-declaration \
		   -Wfloat-equal -Wformat-nonliteral -Wformat-security \
		   -Wformat=2 -Winit-self -Wmissing-declarations \
		   -Wmissing-format-attribute -Wmissing-include-dirs \
		   -Wmissing-noreturn -Wmissing-prototypes -Wnested-externs \
		   -Wpointer-arith -Wshadow -Wstrict-prototypes \
		   -Wswitch-default -Wunsafe-loop-optimizations \
		   -Wwrite-strings

#CFLAGS		+= -Wno-unused-variable -Wno-unused-function -Wextra -Werror
CFLAGS          += -c -fPIC

DEBUG      	?= 0
ifeq ($(DEBUG), 1)
CFLAGS          += -DDEBUG -O0 -g
endif


RM              := rm -f

define rmdir
if [ -d "$(1)" ] ; then rmdir --ignore-fail-on-non-empty $(1) ; fi
endef
