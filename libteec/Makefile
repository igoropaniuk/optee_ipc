include ../flags.mk
include ../config.mk

OUT_DIR := $(OO)/libteec

.PHONY: all libteec-portable clean

all: libteec-portable
################################################################################
# Teec portable configuration
################################################################################
LIB_NAME	:= libteec.a

TEEC_SRCS	:= tee_client_api.c \
		   teec_core.c \
		   arch/arm/smc-call.S \

TEEC_SRC_DIR	:= src
TEEC_OBJ_DIR	:= $(OUT_DIR)
TEEC_OBJS 	:= $(patsubst %.c,$(TEEC_OBJ_DIR)/%.o, $(TEEC_SRCS))

TEEC_INCLUDES 	:= \
		   ${CURDIR}/include \
		   ${CURDIR}/../public \
		   ${CURDUR}/arch/arm/include \

TEEC_CFLAGS	:= $(addprefix -I, $(TEEC_INCLUDES)) $(CFLAGS) -D_GNU_SOURCE \
		   -DDEBUGLEVEL_$(CFG_TEE_CLIENT_LOG_LEVEL) \
		   -DBINARY_PREFIX=\"TEEC\"

TEEC_LFLAGS     := $(LDFLAGS)

libteec-portable: $(OUT_DIR)/$(LIB_NAME)

$(OUT_DIR)/$(LIB_NAME): $(TEEC_OBJS)
	@echo "  AR      $@"
	$(VPREFIX)$(AR) rcs $@ $+

$(TEEC_OBJ_DIR)/%.o: ${TEEC_SRC_DIR}/%.c
	$(VPREFIX)mkdir -p $(TEEC_OBJ_DIR)
	@echo "  CC      $<"
	$(VPREFIX)$(CC) $(TEEC_CFLAGS) -c $< -o $@

################################################################################
# Cleaning up configuration
################################################################################
clean:
	$(RM) $(TEEC_OBJS) $(OUT_DIR)/$(LIB_NAME)
	$(call rmdir,$(OUT_DIR))
