#include <am.h>
#include "../riscv.h"

void __am_audio_init() {
}

void __am_audio_config(AM_AUDIO_CONFIG_T *cfg) {
  cfg->present = false;
}

void __am_audio_ctrl(AM_AUDIO_CTRL_T *ctrl) {
}

void __am_audio_status(AM_AUDIO_STATUS_T *stat) {
  stat->count = 0;
}

void __am_audio_play(AM_AUDIO_PLAY_T *ctl) {
}
