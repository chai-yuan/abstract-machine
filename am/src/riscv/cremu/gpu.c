#include <am.h>
#include "../riscv.h"
#include "stdio.h"
#include "string.h"

#define VRAM_ADDR 0x40000000
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void __am_gpu_init() {
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = SCREEN_WIDTH, .height = SCREEN_HEIGHT,
    .vmemsz = SCREEN_WIDTH * SCREEN_HEIGHT * 4
  };
}

typedef uint32_t pixel_t;

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
    if (ctl == NULL || ctl->pixels == NULL) return;
    if (ctl->w <= 0 || ctl->h <= 0) return;
    
    pixel_t *src = (pixel_t *)ctl->pixels;
    volatile pixel_t *dst = (pixel_t *)VRAM_ADDR + ctl->y * SCREEN_WIDTH + ctl->x;
    for (int y = 0; y < ctl->h; y++) {
        memcpy((void *)(dst + y * SCREEN_WIDTH), src + y * ctl->w, ctl->w * sizeof(pixel_t));
    }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
