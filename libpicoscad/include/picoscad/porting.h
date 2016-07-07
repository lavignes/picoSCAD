#ifndef PS_PORTING_H_
#define PS_PORTING_H_

// Grab the bulk of the c11 primitives
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <uchar.h>

#ifdef __cplusplus
#define PS_EXTERN_BEGIN extern "C" {
#define PS_EXTERN_END }
#else
#define PS_EXTERN_BEGIN
#define PS_EXTERN_END
#endif

#ifndef __GNUC__
#define __has_attribute(...) 0
#endif

#if __has_attribute(always_inline)
#define PS_INLINE inline __attribute__((always_inline))
#else
#define PS_INLINE inline
#endif

#define OF(types...)

#endif // PS_PORTING_H_