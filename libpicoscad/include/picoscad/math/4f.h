#ifndef PS_MATH_4F_H_
#define PS_MATH_4F_H_

#ifdef __SSE__
#include <picoscad/math/simd/4f.h>
#else
#include <picoscad/math/scalar/4f.h>
#endif

PS_EXTERN_BEGIN

PS_INLINE Ps4f ps_4f_dot2(Ps4f lhs, Ps4f rhs) {
    const Ps4f mul = ps_4f_mul(lhs, rhs);
    return ps_4f_add(ps_4f_splat_x(mul), ps_4f_splat_y(mul));
}

PS_INLINE Ps4f ps_4f_dot3(Ps4f lhs, Ps4f rhs) {
    const Ps4f mul = ps_4f_mul(lhs, rhs);
    return ps_4f_add(ps_4f_add(ps_4f_splat_x(mul), ps_4f_splat_y(mul)),
                     ps_4f_splat_z(mul));
}

PS_INLINE Ps4f ps_4f_dot(Ps4f lhs, Ps4f rhs) {
    const Ps4f mul = ps_4f_mul(lhs, rhs);
    return ps_4f_add(ps_4f_add(ps_4f_add(ps_4f_splat_x(mul),
                                         ps_4f_splat_y(mul)),
                               ps_4f_splat_z(mul)),
                     ps_4f_splat_w(mul));
}

PS_INLINE Ps4f ps_4f_length2(Ps4f v4f) {
    return ps_4f_sqrt(ps_4f_dot2(v4f, v4f));
}

PS_INLINE Ps4f ps_4f_length3(Ps4f v4f) {
    return ps_4f_sqrt(ps_4f_dot3(v4f, v4f));
}

PS_INLINE Ps4f ps_4f_length(Ps4f v4f) {
    return ps_4f_sqrt(ps_4f_dot(v4f, v4f));
}

PS_INLINE Ps4f ps_4f_length2_fast(Ps4f v4f) {
    return ps_4f_sqrt_fast(ps_4f_dot2(v4f, v4f));
}

PS_INLINE Ps4f ps_4f_length3_fast(Ps4f v4f) {
    return ps_4f_sqrt_fast(ps_4f_dot3(v4f, v4f));
}

PS_INLINE Ps4f ps_4f_length_fast(Ps4f v4f) {
    return ps_4f_sqrt_fast(ps_4f_dot(v4f, v4f));
}

PS_INLINE Ps4f ps_4f_square_length2(Ps4f v4f) {
    return ps_4f_dot2(v4f, v4f);
}

PS_INLINE Ps4f ps_4f_square_length3(Ps4f v4f) {
    return ps_4f_dot3(v4f, v4f);
}

PS_INLINE Ps4f ps_4f_square_length(Ps4f v4f) {
    return ps_4f_dot(v4f, v4f);
}

PS_INLINE Ps4f ps_4f_normalize2(Ps4f v4f) {
    return ps_4f_mul(v4f, ps_4f_rsqrt(ps_4f_dot2(v4f, v4f)));
}

PS_INLINE Ps4f ps_4f_normalize3(Ps4f v4f) {
    return ps_4f_mul(v4f, ps_4f_rsqrt(ps_4f_dot3(v4f, v4f)));
}

PS_INLINE Ps4f ps_4f_normalize(Ps4f v4f) {
    return ps_4f_mul(v4f, ps_4f_rsqrt(ps_4f_dot(v4f, v4f)));
}

PS_INLINE Ps4f ps_4f_normalize2_fast(Ps4f v4f) {
    return ps_4f_mul(v4f, ps_4f_rsqrt_fast(ps_4f_dot2(v4f, v4f)));
}

PS_INLINE Ps4f ps_4f_normalize3_fast(Ps4f v4f) {
    return ps_4f_mul(v4f, ps_4f_rsqrt_fast(ps_4f_dot3(v4f, v4f)));
}

PS_INLINE Ps4f ps_4f_normalize_fast(Ps4f v4f) {
    return ps_4f_mul(v4f, ps_4f_rsqrt_fast(ps_4f_dot(v4f, v4f)));
}

PS_INLINE Ps4f ps_4f_surfnorm(Ps4f p1, Ps4f p2, Ps4f p3) {
    return ps_4f_cross(ps_4f_sub(p2, p1), ps_4f_sub(p3, p1));
}

PS_EXTERN_END

#endif // PS_MATH_4F_H_