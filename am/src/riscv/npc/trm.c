#include <am.h>
#include <klib-macros.h>
#include "../riscv.h"

extern char _heap_start;
int main(const char *args);

extern char _pmem_start;
#define PMEM_SIZE (8 * 1024 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)

Area heap = RANGE(&_heap_start, PMEM_END);
static const char mainargs[MAINARGS_MAX_LEN] = MAINARGS_PLACEHOLDER; // defined in CFLAGS

void __am_uart_init();
void putch(char ch) {
    AM_UART_TX_T tx;
    tx.data = ch;
    ioe_write(AM_UART_TX,&tx);
}

void halt(int code) {
  asm volatile("mv a0, %0; ebreak" : :"r"(code));
  while (1);
}

void _trm_init() {
  __am_uart_init();
  int ret = main(mainargs);
  halt(ret);
}
