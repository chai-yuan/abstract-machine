#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

#define PRINT_SIZE_MAX 1024

int printf(const char *fmt, ...) {
    char buf[PRINT_SIZE_MAX];
    va_list ap;
    va_start(ap, fmt);
    int retval = vsprintf(buf, fmt, ap);
    va_end(ap);
    putstr(buf);
    return retval;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
    return vsnprintf(out, PRINT_SIZE_MAX, fmt, ap);
}

int sprintf(char *out, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int result = vsprintf(out, fmt, ap);
    va_end(ap);
    return result;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int result = vsnprintf(out, n, fmt, ap);
    va_end(ap);
    return result;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
    char *p = out;
    const char *fmt_ptr = fmt;
    size_t remaining = n;

    while (*fmt_ptr && remaining > 1) {
        if (*fmt_ptr == '%') {
            fmt_ptr++;
            switch (*fmt_ptr) {
                case 'd': {
                    int num = va_arg(ap, int);
                    char buffer[16]; // 假设整数最多16位
                    char *num_ptr = buffer;
                    int is_negative = 0;

                    if (num < 0) {
                        is_negative = 1;
                        num = -num;
                    }

                    do {
                        *num_ptr++ = '0' + (num % 10);
                        num /= 10;
                    } while (num > 0);

                    if (is_negative) {
                        *num_ptr++ = '-';
                    }

                    // 反转数字字符串
                    char *start = buffer;
                    char *end = num_ptr - 1;
                    while (start < end) {
                        char tmp = *start;
                        *start = *end;
                        *end = tmp;
                        start++;
                        end--;
                    }

                    // 复制到输出缓冲区
                    size_t len = num_ptr - buffer;
                    if (len >= remaining) {
                        len = remaining - 1;
                    }
                    memcpy(p, buffer, len);
                    p += len;
                    remaining -= len;
                    break;
                }
                case 's': {
                    const char *str = va_arg(ap, const char *);
                    size_t len = strlen(str);
                    if (len >= remaining) {
                        len = remaining - 1;
                    }
                    memcpy(p, str, len);
                    p += len;
                    remaining -= len;
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(ap, int);
                    if (remaining > 1) {
                        *p++ = c;
                        remaining--;
                    }
                    break;
                }
                case 'x': {
                    unsigned int num = va_arg(ap, unsigned int);
                    char buffer[16]; // 假设十六进制数最多16位
                    char *num_ptr = buffer;

                    do {
                        int digit = num % 16;
                        *num_ptr++ = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
                        num /= 16;
                    } while (num > 0);

                    // 反转十六进制字符串
                    char *start = buffer;
                    char *end = num_ptr - 1;
                    while (start < end) {
                        char tmp = *start;
                        *start = *end;
                        *end = tmp;
                        start++;
                        end--;
                    }

                    // 复制到输出缓冲区
                    size_t len = num_ptr - buffer;
                    if (len >= remaining) {
                        len = remaining - 1;
                    }
                    memcpy(p, buffer, len);
                    p += len;
                    remaining -= len;
                    break;
                }
                case '%': {
                    if (remaining > 1) {
                        *p++ = '%';
                        remaining--;
                    }
                    break;
                }
                default: {
                    // 不支持的格式说明符，直接复制到输出
                    if (remaining > 1) {
                        *p++ = '%';
                        remaining--;
                    }
                    if (remaining > 1) {
                        *p++ = *fmt_ptr;
                        remaining--;
                    }
                    break;
                }
            }
            fmt_ptr++;
        } else {
            *p++ = *fmt_ptr++;
            remaining--;
        }
    }

    // 确保字符串以 null 结尾
    if (n > 0) {
        *p = '\0';
    }

    return p - out;
}

#endif
