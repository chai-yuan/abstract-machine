AM_SRCS := riscv/cremu/start.S \
           riscv/cremu/trm.c \
           riscv/cremu/ioe.c \
           riscv/cremu/timer.c \
           riscv/cremu/input.c \
           riscv/cremu/gpu.c \
           riscv/cremu/uart.c \
           riscv/cremu/cte.c \
           riscv/cremu/audio.c \
           riscv/cremu/trap.S \
           platform/dummy/vme.c \
           platform/dummy/mpe.c

CFLAGS    += -fdata-sections -ffunction-sections
LDSCRIPTS += $(AM_HOME)/scripts/linker.ld
LDFLAGS   += --defsym=_pmem_start=0x80000000 --defsym=_entry_offset=0x0
LDFLAGS   += --gc-sections -e _start

MAINARGS_MAX_LEN = 64
MAINARGS_PLACEHOLDER = The insert-arg rule in Makefile will insert mainargs here.
CFLAGS += -DMAINARGS_MAX_LEN=$(MAINARGS_MAX_LEN) -DMAINARGS_PLACEHOLDER=\""$(MAINARGS_PLACEHOLDER)"\"

CREMUFLAGS += --bin=$(IMAGE).bin --machine=nemu

insert-arg: image
	@python $(AM_HOME)/tools/insert-arg.py $(IMAGE).bin $(MAINARGS_MAX_LEN) "$(MAINARGS_PLACEHOLDER)" "$(mainargs)"

image: image-dep
	@$(OBJDUMP) -d $(IMAGE).elf > $(IMAGE).txt
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -S --set-section-flags .bss=alloc,contents -O binary $(IMAGE).elf $(IMAGE).bin

run: insert-arg
	echo "TODO: add command here to run simulation $(IMAGE)"
	$(MAKE) -C $(CREMU_HOME) run ARGS="$(CREMUFLAGS)"

.PHONY: insert-arg
