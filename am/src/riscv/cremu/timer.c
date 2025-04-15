#include <am.h>
#include "../riscv.h"

#define RTC_ADDR 0x0200bff8

void __am_timer_init() {
}

void __am_timer_config(AM_TIMER_CONFIG_T *cfg) { cfg->present = true; cfg->has_rtc = true; }

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uptime->us = inq(RTC_ADDR);
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
