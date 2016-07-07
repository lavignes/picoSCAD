#ifndef PS_MATH_MAT4F_H_
#define PS_MATH_MAT4F_H_

#include <picoscad/math/4f.h>

PS_EXTERN_BEGIN

typedef struct PsMat4f {
    Ps4f x, y, z, w;
} PsMat4f;

PS_INLINE PsMat4f ps_mat4f(Ps4f x, Ps4f y, Ps4f z, Ps4f w) {
    return (PsMat4f) {x, y, z, w};
}

PS_INLINE void ps_mat4f_identity(PsMat4f *m4f) {
    *m4f = (PsMat4f) {
            ps_4f(1.0f, 0.0f, 0.0f, 0.0f),
            ps_4f(0.0f, 1.0f, 0.0f, 0.0f),
            ps_4f(0.0f, 0.0f, 1.0f, 0.0f),
            ps_4f(0.0f, 0.0f, 0.0f, 1.0f)
    };
}

PS_INLINE void ps_mat4f_4f_mul(const PsMat4f *lhs, const Ps4f *rhs, Ps4f *out) {
    *out = ps_4f_add(ps_4f_mul(lhs->x, ps_4f_splat_x(*rhs)),
                     ps_4f_add(ps_4f_mul(lhs->y, ps_4f_splat_y(*rhs)),
                               ps_4f_add(ps_4f_mul(lhs->z, ps_4f_splat_z(*rhs)),
                                         ps_4f_mul(lhs->w, ps_4f_splat_w(*rhs)))));
}

PS_INLINE void ps_mat4f_add(const PsMat4f *lhs, const PsMat4f *rhs, PsMat4f *out) {
    *out = (PsMat4f) {
            ps_4f_add(lhs->x, rhs->x),
            ps_4f_add(lhs->y, rhs->y),
            ps_4f_add(lhs->z, rhs->z),
            ps_4f_add(lhs->w, rhs->w)
    };
}

PS_INLINE void ps_mat4f_sub(const PsMat4f *lhs, const PsMat4f *rhs, PsMat4f *out) {
    *out = (PsMat4f) {
            ps_4f_sub(lhs->x, rhs->x),
            ps_4f_sub(lhs->y, rhs->y),
            ps_4f_sub(lhs->z, rhs->z),
            ps_4f_sub(lhs->w, rhs->w)
    };
}

PS_INLINE void ps_mat4f_mul(const PsMat4f *lhs, const PsMat4f *rhs, PsMat4f *out) {
    *out = (PsMat4f) {
            ps_4f_mul(lhs->x, rhs->x),
            ps_4f_mul(lhs->y, rhs->y),
            ps_4f_mul(lhs->z, rhs->z),
            ps_4f_mul(lhs->w, rhs->w)
    };
}

PS_INLINE void ps_mat4f_div(const PsMat4f *lhs, const PsMat4f *rhs, PsMat4f *out) {
    *out = (PsMat4f) {
            ps_4f_div(lhs->x, rhs->x),
            ps_4f_div(lhs->y, rhs->y),
            ps_4f_div(lhs->z, rhs->z),
            ps_4f_div(lhs->w, rhs->w)
    };
}

PS_INLINE void ps_mat4f_perspective(PsMat4f *m4f, float fovy, float aspect, float znear, float zfar) {
    const float dz = zfar - znear;
    const float cot = tanf(PS_MATH_TAU - fovy * 0.5f);
    *m4f = (PsMat4f) {
            ps_4f(cot / aspect, 0.0f, 0.0f, 0.0f),
            ps_4f(0.0f, cot, 0.0f, 0.0f),
            ps_4f(0.0f, 0.0f, -(zfar + znear) / dz, -1.0f),
            ps_4f(0.0f, 0.0f, -2.0f * znear * zfar / dz, 0.0f)
    };
}

PS_INLINE void ps_mat4f_ortho(PsMat4f *m4f, float left, float right,
                              float bottom, float top, float znear, float zfar) {
    const float dx = right - left;
    const float dy = top - bottom;
    const float dz = zfar - znear;
    *m4f = (PsMat4f) {
            ps_4f(2.0f / dx, 0.0f, 0.0f, 0.0f),
            ps_4f(0.0f, 2.0f / dy, 0.0f, 0.0f),
            ps_4f(0.0f, 0.0f, -2.0f / dz, 0.0f),
            ps_4f(-(right + left) / dx, -(top + bottom) / dy,
                  -(zfar + znear) / dz, 1.0f)
    };
}

PS_INLINE void ps_mat4f_translation(PsMat4f *m4f, float x, float y, float z) {
    *m4f = (PsMat4f) {
            ps_4f(1.0f, 0.0f, 0.0f, 0.0f),
            ps_4f(0.0f, 1.0f, 0.0f, 0.0f),
            ps_4f(0.0f, 0.0f, 1.0f, 0.0f),
            ps_4f(x, y, z, 1.0f)
    };
}

PS_INLINE void ps_mat4f_scale(PsMat4f *m4f, float x, float y, float z) {
    *m4f = (PsMat4f) {
            ps_4f(x, 0.0f, 0.0f, 0.0f),
            ps_4f(0.0f, y, 0.0f, 0.0f),
            ps_4f(0.0f, 0.0f, z, 0.0f),
            ps_4f(0.0f, 0.0f, 0.0f, 1.0f)
    };
}

PS_INLINE void ps_mat4f_rot_x(PsMat4f *m4f, float radians) {
    const float s = sinf(radians);
    const float c = cosf(radians);
    *m4f = (PsMat4f) {
            ps_4f(1.0f, 0.0f, 0.0f, 0.0f),
            ps_4f(0.0f, c, -s, 0.0f),
            ps_4f(0.0f, s, c, 0.0f),
            ps_4f(0.0f, 0.0f, 0.0f, 1.0f)
    };
}

PS_INLINE void ps_mat4f_rot_y(PsMat4f *m4f, float radians) {
    const float s = sinf(radians);
    const float c = cosf(radians);
    *m4f = (PsMat4f) {
            ps_4f(c, 0.0f, s, 0.0f),
            ps_4f(0.0f, 1.0f, 0.0f, 0.0f),
            ps_4f(-s, 0.0f, c, 0.0f),
            ps_4f(0.0f, 0.0f, 0.0f, 1.0f)
    };
}

PS_INLINE void ps_mat4f_rot_z(PsMat4f *m4f, float radians) {
    const float s = sinf(radians);
    const float c = cosf(radians);
    *m4f = (PsMat4f) {
            ps_4f(c, -s, 0.0f, 0.0f),
            ps_4f(s, c, 0.0f, 0.0f),
            ps_4f(0.0f, 0.0f, 1.0f, 0.0f),
            ps_4f(0.0f, 0.0f, 0.0f, 1.0f)
    };
}

PS_INLINE void ps_mat4f_transpose(PsMat4f *m4f) {
    const Ps4f dx = ps_4f(ps_4f_x(m4f->x), ps_4f_x(m4f->y),
                          ps_4f_x(m4f->z), ps_4f_x(m4f->w));
    const Ps4f dy = ps_4f(ps_4f_y(m4f->x), ps_4f_y(m4f->y),
                          ps_4f_y(m4f->z), ps_4f_y(m4f->w));
    const Ps4f dz = ps_4f(ps_4f_z(m4f->x), ps_4f_z(m4f->y),
                          ps_4f_z(m4f->z), ps_4f_z(m4f->w));
    const Ps4f dw = ps_4f(ps_4f_w(m4f->x), ps_4f_w(m4f->y),
                          ps_4f_w(m4f->z), ps_4f_w(m4f->w));
    *m4f = (PsMat4f) {dx, dy, dz, dw};
}

PS_EXTERN_END

#endif // PS_MATH_MAT4F_H_