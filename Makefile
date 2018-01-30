# Public variables are stored in config.mk
include ./config.mk

#########################################################################
# Set Internal Variables						#
# May be modified to match your setup                                   #
#########################################################################
ifneq ($(V),1)
VPREFIX := @
endif
export VPREFIX

EXPORT_DIR ?= $(O)/export
INCLUDEDIR ?= /include

.PHONY: all build build-libteec-portable install copy_export \
	clean cscope clean-cscope distclean

all: build install

build-libteec-portable:
	@echo "Building libteec.a"
	@$(MAKE) --directory=libteec --no-print-directory --no-builtin-variables


build: build-libteec-portable

clean: clean-libteec-portable clean-cscope

clean-libteec-portable:
	@$(MAKE) --directory=libteec --no-print-directory clean

cscope:
	@echo "  CSCOPE"
	${VPREFIX}find ${CURDIR} -name "*.[chsS]" > cscope.files
	${VPREFIX}cscope -b -q -k

clean-cscope:
	${VPREFIX}rm -f cscope.*

# Various checkpatch targets. The ones ending with "patch" only considers the
# patch, whilst the ones ending with "file" checks the complete file.
# +-------------------------------+------------+----------------------------+
# | Target commit                 | File/Patch | Comment                    |
# +-------------------------------+------------+----------------------------+
# | checkpatch-modified-patch     | Patch      | Check local modifications  |
# +-------------------------------+------------+----------------------------+
# | checkpatch-modified-file      | File       | Check Local modifications  |
# +-------------------------------+------------+----------------------------+
# | checkpatch-last-commit-patch  | Patch      | Check against HEAD^        |
# +-------------------------------+------------+----------------------------+
# | checkpatch-last-commit-file   | File       | Check against HEAD^        |
# +-------------------------------+------------+----------------------------+
# | checkpatch-base-commit-patch  | Patch      | Against specic commit      |
# +-------------------------------+------------+----------------------------+
# | checkpatch-base-commit-file   | File       | Against specic commit      |
# +-------------------------------+------------+----------------------------+
# | checkpatch-all-files          | File       | Check all tracked files    |
# +-------------------------------+------------+----------------------------+
CHECKPATCH_IGNORE	?= --ignore NEW_TYPEDEFS --no-signoff
CHECKPATCH_STRICT	?= --strict
CHECKPATCH_ARGS		?= $(CHECKPATCH_IGNORE) $(CHECKPATCH_STRICT) --no-tree --terse
CHECKPATCH_PATCH_ARGS   := $(CHECKPATCH_ARGS) --patch
CHECKPATCH_FILE_ARGS 	:= $(CHECKPATCH_ARGS) --file --no-patch

checkpatch-pre-req:
	@echo "  CHECKPATCH"
ifndef CHECKPATCH
	$(error "Environment variable CHECKPATCH must point to Linux kernels checkpatch script")
else
ifeq (,$(wildcard ${CHECKPATCH}))
	$(error "CHECKPATCH points to the incorrect file")
endif
endif

checkpatch-modified-patch: checkpatch-pre-req
	${VPREFIX}git diff | ${CHECKPATCH} $(CHECKPATCH_PATCH_ARGS) - || true

checkpatch-modified-file: checkpatch-pre-req
	${VPREFIX}${CHECKPATCH} $(CHECKPATCH_FILE_ARGS) $(shell git diff --name-only)


checkpatch-last-commit-patch: checkpatch-pre-req
	${VPREFIX}git diff HEAD^ | ${CHECKPATCH} $(CHECKPATCH_PATCH_ARGS) - || true

checkpatch-last-commit-file: checkpatch-pre-req
	${VPREFIX}${CHECKPATCH} $(CHECKPATCH_FILE_ARGS) $(shell git diff --name-only HEAD^)


checkpatch-base-commit-patch: checkpatch-pre-req
ifndef BASE_COMMIT
	$(error "Environment variable BASE_COMMIT must contain a valid commit")
endif
	${VPREFIX}git diff $(BASE_COMMIT) | ${CHECKPATCH} $(CHECKPATCH_PATCH_ARGS) - || true

checkpatch-base-commit-file: checkpatch-pre-req
ifndef BASE_COMMIT
	$(error "Environment variable BASE_COMMIT must contain a valid commit")
endif
	${VPREFIX}${CHECKPATCH} $(CHECKPATCH_FILE_ARGS) $(shell git diff --name-only ${BASE_COMMIT})

checkpatch-all-files: checkpatch-pre-req
	${VPREFIX}${CHECKPATCH} $(CHECKPATCH_FILE_ARGS) $(shell git ls-files)
distclean: clean

