#ifndef PS_MATH_4D_H_
#define PS_MATH_4D_H_

#ifdef __AVX__
#include <picoscad/math/simd/4d.h>
#else
#include <picoscad/math/scalar/4d.h>
#endif

PS_EXTERN_BEGIN

PS_INLINE Ps4d ps_4d_dot2(Ps4d lhs, Ps4d rhs) {
    const Ps4d mul = ps_4d_mul(lhs, rhs);
    return ps_4d_add(ps_4d_splat_x(mul), ps_4d_splat_y(mul));
}

PS_INLINE Ps4d ps_4d_dot3(Ps4d lhs, Ps4d rhs) {
    const Ps4d mul = ps_4d_mul(lhs, rhs);
    return ps_4d_add(ps_4d_add(ps_4d_splat_x(mul), ps_4d_splat_y(mul)),
                     ps_4d_splat_z(mul));
}

PS_INLINE Ps4d ps_4d_dot(Ps4d lhs, Ps4d rhs) {
    const Ps4d mul = ps_4d_mul(lhs, rhs);
    return ps_4d_add(ps_4d_add(ps_4d_add(ps_4d_splat_x(mul),
                                         ps_4d_splat_y(mul)),
                               ps_4d_splat_z(mul)),
                     ps_4d_splat_w(mul));
}

PS_INLINE Ps4d ps_4d_length2(Ps4d v4d) {
    return ps_4d_sqrt(ps_4d_dot2(v4d, v4d));
}

PS_INLINE Ps4d ps_4d_length3(Ps4d v4d) {
    return ps_4d_sqrt(ps_4d_dot3(v4d, v4d));
}

PS_INLINE Ps4d ps_4d_length(Ps4d v4d) {
    return ps_4d_sqrt(ps_4d_dot(v4d, v4d));
}

PS_INLINE Ps4d ps_4d_length2_fast(Ps4d v4d) {
    return ps_4d_sqrt_fast(ps_4d_dot2(v4d, v4d));
}

PS_INLINE Ps4d ps_4d_length3_fast(Ps4d v4d) {
    return ps_4d_sqrt_fast(ps_4d_dot3(v4d, v4d));
}

PS_INLINE Ps4d ps_4d_length_fast(Ps4d v4d) {
    return ps_4d_sqrt_fast(ps_4d_dot(v4d, v4d));
}

PS_INLINE Ps4d ps_4d_square_length2(Ps4d v4d) {
    return ps_4d_dot2(v4d, v4d);
}

PS_INLINE Ps4d ps_4d_square_length3(Ps4d v4d) {
    return ps_4d_dot3(v4d, v4d);
}

PS_INLINE Ps4d ps_4d_square_length(Ps4d v4d) {
    return ps_4d_dot(v4d, v4d);
}

PS_INLINE Ps4d ps_4d_normalize2(Ps4d v4d) {
    return ps_4d_mul(v4d, ps_4d_rsqrt(ps_4d_dot2(v4d, v4d)));
}

PS_INLINE Ps4d ps_4d_normalize3(Ps4d v4d) {
    return ps_4d_mul(v4d, ps_4d_rsqrt(ps_4d_dot3(v4d, v4d)));
}

PS_INLINE Ps4d ps_4d_normalize(Ps4d v4d) {
    return ps_4d_mul(v4d, ps_4d_rsqrt(ps_4d_dot(v4d, v4d)));
}

PS_INLINE Ps4d ps_4d_normalize2_fast(Ps4d v4d) {
    return ps_4d_mul(v4d, ps_4d_rsqrt_fast(ps_4d_dot2(v4d, v4d)));
}

PS_INLINE Ps4d ps_4d_normalize3_fast(Ps4d v4d) {
    return ps_4d_mul(v4d, ps_4d_rsqrt_fast(ps_4d_dot3(v4d, v4d)));
}

PS_INLINE Ps4d ps_4d_normalize_fast(Ps4d v4d) {
    return ps_4d_mul(v4d, ps_4d_rsqrt_fast(ps_4d_dot(v4d, v4d)));
}

PS_EXTERN_END

#endif // PS_MATH_4D_H_