include $(AM_HOME)/scripts/isa/riscv.mk
include $(AM_HOME)/scripts/platform/cremu.mk
override CROSS_COMPILE := riscv64-unknown-elf-
COMMON_CFLAGS += -march=rv32ima_zicsr_zifencei -mabi=ilp32  	# overwrite
LDFLAGS       += -melf32lriscv                     		# overwrite