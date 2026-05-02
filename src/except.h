#ifndef EXCEPT_H
#define EXCEPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cw_returns.h"

/*
    Core exception/logging function
*/
void cw_except_raise(CW_Return code, const char *file, int line, const char *fmt, ...);

/*
    Macros for easy usage
*/

#define CW_THROW(code, fmt, ...) cw_except_raise(code, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define CW_ASSERT(cond, code, fmt, ...)                                                            \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            cw_except_raise(code, __FILE__, __LINE__, fmt, ##__VA_ARGS__);                         \
        }                                                                                          \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif /* EXCEPT_H */