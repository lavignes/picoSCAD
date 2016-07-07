#ifndef PS_MATH_SIMD_4D_H_
#define PS_MATH_SIMD_4D_H_

#include <immintrin.h>

#include <picoscad/math/simd/4f.h>

PS_EXTERN_BEGIN

typedef __m256d Ps4d;

typedef union {
    Ps4d v4d;
    double arr[4];
    struct {
        double x, y, z, w;
    };
} _Ps4dSIMDUnion;

PS_INLINE Ps4d ps_4d(double x, double y, double z, double w) {
    return _mm256_setr_pd(x, y, z, w);
}

PS_INLINE Ps4d ps_4d_zero() {
    return _mm256_setzero_pd();
}

PS_INLINE bool ps_4d_eq(Ps4d lhs, Ps4d rhs) {
    return 0x0F == _mm256_movemask_pd(_mm256_cmp_pd(lhs, rhs, _CMP_EQ_OQ));
}

PS_INLINE bool ps_4d_lt(Ps4d lhs, Ps4d rhs) {
    return 0x0F == _mm256_movemask_pd(_mm256_cmp_pd(lhs, rhs, _CMP_LT_OQ));
}

PS_INLINE bool ps_4d_gt(Ps4d lhs, Ps4d rhs) {
    return 0x0F == _mm256_movemask_pd(_mm256_cmp_pd(lhs, rhs, _CMP_GT_OQ));
}

PS_INLINE Ps4d ps_4d_map(Ps4d v4d, double(*fn)(double)) {
    _Ps4dSIMDUnion u = {v4d};
    return ps_4d(fn(u.x), fn(u.y), fn(u.z), fn(u.w));
}

PS_INLINE Ps4d ps_4d_load(const double* arr) {
    return _mm256_load_pd(arr);
}

PS_INLINE void ps_4d_store(Ps4d v4d, double* arr) {
    return _mm256_storeu_pd(arr, v4d);
}

PS_INLINE double ps_4d_x(Ps4d v4d) {
    _Ps4dSIMDUnion u = {v4d};
    return u.x;
}

PS_INLINE double ps_4d_y(Ps4d v4d) {
    _Ps4dSIMDUnion u = {v4d};
    return u.y;
}

PS_INLINE double ps_4d_z(Ps4d v4d) {
    _Ps4dSIMDUnion u = {v4d};
    return u.z;
}

PS_INLINE double ps_4d_w(Ps4d v4d) {
    _Ps4dSIMDUnion u = {v4d};
    return u.w;
}

#define ps_4d_swizzle(v4d, swizzle) (_mm256_shuffle_pd((v4d), (v4d), (swizzle)))

PS_INLINE Ps4d ps_4d_splat(double f) {
    return _mm256_set1_pd(f);
}

PS_INLINE Ps4d ps_4d_splat_x(Ps4d v4d) {
    return ps_4d_swizzle(v4d, PS_SWIZZLE_XXXX);
}

PS_INLINE Ps4d ps_4d_splat_y(Ps4d v4d) {
    return ps_4d_swizzle(v4d, PS_SWIZZLE_YYYY);
}

PS_INLINE Ps4d ps_4d_splat_z(Ps4d v4d) {
    return ps_4d_swizzle(v4d, PS_SWIZZLE_ZZZZ);
}

PS_INLINE Ps4d ps_4d_splat_w(Ps4d v4d) {
    return ps_4d_swizzle(v4d, PS_SWIZZLE_WWWW);
}

PS_INLINE Ps4d ps_4d_add(Ps4d lhs, Ps4d rhs) {
    return _mm256_add_pd(lhs, rhs);
}

PS_INLINE Ps4d ps_4d_sub(Ps4d lhs, Ps4d rhs) {
    return _mm256_sub_pd(lhs, rhs);
}

PS_INLINE Ps4d ps_4d_mul(Ps4d lhs, Ps4d rhs) {
    return _mm256_mul_pd(lhs, rhs);
}

PS_INLINE Ps4d ps_4d_div(Ps4d lhs, Ps4d rhs) {
    return _mm256_div_pd(lhs, rhs);
}

PS_INLINE Ps4d ps_4d_recip(Ps4d v4d) {
    return _mm256_div_pd(ps_4d_splat(1.0), v4d);
}

PS_INLINE Ps4d ps_4d_recip_fast(Ps4d v4d) {
    // TODO: AVX-512?
    return ps_4d_recip(v4d);
}

PS_INLINE Ps4d ps_4d_sqrt(Ps4d v4d) {
    _Ps4dSIMDUnion u = {v4d};
    return ps_4d(sqrtf(u.x), sqrtf(u.y), sqrtf(u.z), sqrtf(u.w));
}

PS_INLINE Ps4d ps_4d_sqrt_fast(Ps4d v4d) {
    // TODO: AVX-512?
    return ps_4d_sqrt(v4d);
}

PS_INLINE Ps4d ps_4d_rsqrt(Ps4d v4d) {
    return ps_4d_recip(ps_4d_sqrt(v4d));
}

PS_INLINE Ps4d ps_4d_rsqrt_fast(Ps4d v4d) {
    // TODO: AVX-512?
    return ps_4d_rsqrt(v4d);
}

PS_INLINE Ps4d ps_4d_cross(Ps4d lhs, Ps4d rhs) {
    return ps_4d_sub(ps_4d_mul(ps_4d_swizzle(lhs, PS_SWIZZLE_WXZY),
                               ps_4d_swizzle(rhs, PS_SWIZZLE_WYXZ)),
                     ps_4d_mul(ps_4d_swizzle(lhs, PS_SWIZZLE_WYXZ),
                               ps_4d_swizzle(rhs, PS_SWIZZLE_WXZY)));
}

PS_INLINE Ps4d ps_4d_min(Ps4d lhs, Ps4d rhs) {
    return _mm256_min_pd(lhs, rhs);
}

PS_INLINE Ps4d ps_4d_max(Ps4d lhs, Ps4d rhs) {
    return _mm256_max_pd(lhs, rhs);
}

PS_INLINE Ps4d ps_4d_abs(Ps4d v4d) {
    // removes sign bit
    return _mm256_andnot_pd(_mm256_castsi256_pd(_mm256_set1_epi64x(0x8000000000000000)), v4d);
}

PS_INLINE Ps4d ps_4d_neg(Ps4d v4d) {
    // flips sign bit
    return _mm256_xor_pd(_mm256_castsi256_pd(_mm256_set1_epi64x(0x8000000000000000)), v4d);
}

PS_EXTERN_END

#endif // PS_MATH_SIMD_4D_H_