include $(AM_HOME)/scripts/isa/riscv.mk
include $(AM_HOME)/scripts/platform/bootloader.mk
COMMON_CFLAGS += -march=rv32ima_zicsr -mabi=ilp32 # overwrite
LDFLAGS       += -melf32lriscv                     # overwrite

AM_SRCS += riscv/npc/libgcc/unused.c
