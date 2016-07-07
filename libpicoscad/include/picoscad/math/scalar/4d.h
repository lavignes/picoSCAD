#ifndef PS_MATH_SCALAR_4D_H_
#define PS_MATH_SCALAR_4D_H_

#include <string.h>

#include <picoscad/math/scalar/4f.h>

typedef struct Ps4d {
    union {
        struct {
            double _x, _y, _z, _w;
        };
        double _arr[4];
    };
} Ps4d;

PS_INLINE Ps4d ps_4d(double x, double y, double z, double w) {
    return (Ps4d) { ._x = x, ._y = y, ._z = z, ._w = w };
}

PS_INLINE Ps4d ps_4d_zero() {
    return ps_4d(0.0, 0.0, 0.0, 0.0);
}

PS_INLINE bool ps_4d_eq(Ps4d lhs, Ps4d rhs) {
    return lhs._x == rhs._x && lhs._y == rhs._y && lhs._z == rhs._z && lhs._w == rhs._w;
}

PS_INLINE bool ps_4d_lt(Ps4d lhs, Ps4d rhs) {
    return lhs._x < rhs._x && lhs._y < rhs._y && lhs._z < rhs._z && lhs._w < rhs._w;
}

PS_INLINE bool ps_4d_gt(Ps4d lhs, Ps4d rhs) {
    return lhs._x > rhs._x && lhs._y > rhs._y && lhs._z > rhs._z && lhs._w > rhs._w;
}

PS_INLINE Ps4d ps_4d_map(Ps4d v4d, double(*fn)(double)) {
    return ps_4d(fn(v4d._x), fn(v4d._y), fn(v4d._z), fn(v4d._w));
}

PS_INLINE Ps4d ps_4d_load(double *arr) {
    return ps_4d(arr[0], arr[1], arr[2], arr[3]);
}

PS_INLINE void ps_4d_store(Ps4d v4d, double *arr) {
    memcpy(arr, &v4d, sizeof(Ps4d));
}

PS_INLINE double ps_4d_x(Ps4d v4d) {
    return v4d._x;
}

PS_INLINE double ps_4d_y(Ps4d v4d) {
    return v4d._y;
}

PS_INLINE double ps_4d_z(Ps4d v4d) {
    return v4d._z;
}

PS_INLINE double ps_4d_w(Ps4d v4d) {
    return v4d._w;
}

PS_INLINE Ps4d ps_4d_swizzle(Ps4d v4d, Ps4fSwizzle swizzle) {
    return ps_4d(v4d._arr[(swizzle & 0xC0) >> 6],
                 v4d._arr[(swizzle & 0x30) >> 4],
                 v4d._arr[(swizzle & 0x0C) >> 2],
                 v4d._arr[(swizzle & 0x03)]);
}

PS_INLINE Ps4d ps_4d_splat(double f) {
    return ps_4d(f, f, f, f);
}

PS_INLINE Ps4d ps_4d_splat_x(Ps4d v4d) {
    return ps_4d_splat(v4d._x);
}

PS_INLINE Ps4d ps_4d_splat_y(Ps4d v4d) {
    return ps_4d_splat(v4d._y);
}

PS_INLINE Ps4d ps_4d_splat_z(Ps4d v4d) {
    return ps_4d_splat(v4d._z);
}

PS_INLINE Ps4d ps_4d_splat_w(Ps4d v4d) {
    return ps_4d_splat(v4d._w);
}

PS_INLINE Ps4d ps_4d_add(Ps4d lhs, Ps4d rhs) {
    return ps_4d(lhs._x + rhs._x, lhs._y + rhs._y, lhs._z + rhs._z, lhs._w + rhs._w);
}

PS_INLINE Ps4d ps_4d_sub(Ps4d lhs, Ps4d rhs) {
    return ps_4d(lhs._x - rhs._x, lhs._y - rhs._y, lhs._z - rhs._z, lhs._w - rhs._w);
}

PS_INLINE Ps4d ps_4d_mul(Ps4d lhs, Ps4d rhs) {
    return ps_4d(lhs._x * rhs._x, lhs._y * rhs._y, lhs._z * rhs._z, lhs._w * rhs._w);
}

PS_INLINE Ps4d ps_4d_div(Ps4d lhs, Ps4d rhs) {
    return ps_4d(lhs._x / rhs._x, lhs._y / rhs._y, lhs._z / rhs._z, lhs._w / rhs._w);
}

PS_INLINE Ps4d ps_4d_recip(Ps4d v4d) {
    return ps_4d(1.0 / v4d._x, 1.0 / v4d._y, 1.0 / v4d._z, 1.0 / v4d._w);
}

PS_INLINE Ps4d ps_4d_recip_fast(Ps4d v4d) {
    return ps_4d_recip(v4d);
}

PS_INLINE Ps4d ps_4d_sqrt(Ps4d v4d) {
    return ps_4d(sqrt(v4d._x), sqrt(v4d._y), sqrt(v4d._z), sqrt(v4d._w));
}

PS_INLINE Ps4d ps_4d_sqrt_fast(Ps4d v4d) {
    return ps_4d_sqrt(v4d);
}

PS_INLINE Ps4d ps_4d_rsqrt(Ps4d v4d) {
    return ps_4d_recip(ps_4d_sqrt(v4d));
}

PS_INLINE Ps4d ps_4d_rsqrt_fast(Ps4d v4d) {
    return ps_4d_rsqrt(v4d);
}

PS_INLINE Ps4d ps_4d_cross(Ps4d lhs, Ps4d rhs) {
    return ps_4d(lhs._y * rhs._z - lhs._z * rhs._y,
                 lhs._z * rhs._x - lhs._x * rhs._z,
                 lhs._x * rhs._y - lhs._y * rhs._x, 0.0);
}

PS_INLINE Ps4d ps_4d_min(Ps4d lhs, Ps4d rhs) {
    return ps_4d(fmin(lhs._x, rhs._x), fmin(lhs._y, rhs._y),
                 fmin(lhs._z, rhs._z), fmin(lhs._w, rhs._w));
}

PS_INLINE Ps4d ps_4d_max(Ps4d lhs, Ps4d rhs) {
    return ps_4d(fmax(lhs._x, rhs._x), fmax(lhs._y, rhs._y),
                 fmax(lhs._z, rhs._z), fmax(lhs._w, rhs._w));
}

PS_INLINE Ps4d ps_4d_abs(Ps4d v4d) {
    return ps_4d(fabs(v4d._x), fabs(v4d._y), fabs(v4d._z), fabs(v4d._w));
}

PS_INLINE Ps4d ps_4d_neg(Ps4d v4d) {
    return ps_4d(-v4d._x, -v4d._y, -v4d._z, -v4d._w);
}

#endif // PS_MATH_SCALAR_4D_H_