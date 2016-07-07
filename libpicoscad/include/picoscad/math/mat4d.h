#ifndef PS_MATH_MAT4D_H_
#define PS_MATH_MAT4D_H_

#include <picoscad/math/4d.h>

PS_EXTERN_BEGIN

typedef struct PsMat4d {
    Ps4d x, y, z, w;
} PsMat4d;

PS_INLINE PsMat4d ps_mat4d(Ps4d x, Ps4d y, Ps4d z, Ps4d w) {
return (PsMat4d) {x, y, z, w};
}

PS_INLINE void ps_mat4d_identity(PsMat4d *m4d) {
    *m4d = (PsMat4d) {
            ps_4d(1.0, 0.0, 0.0, 0.0),
            ps_4d(0.0, 1.0, 0.0, 0.0),
            ps_4d(0.0, 0.0, 1.0, 0.0),
            ps_4d(0.0, 0.0, 0.0, 1.0)
    };
}

PS_INLINE void ps_mat4d_4d_mul(const PsMat4d *lhs, const Ps4d *rhs, Ps4d *out) {
    *out = ps_4d_add(ps_4d_mul(lhs->x, ps_4d_splat_x(*rhs)),
                     ps_4d_add(ps_4d_mul(lhs->y, ps_4d_splat_y(*rhs)),
                               ps_4d_add(ps_4d_mul(lhs->z, ps_4d_splat_z(*rhs)),
                                         ps_4d_mul(lhs->w, ps_4d_splat_w(*rhs)))));
}

PS_INLINE void ps_mat4d_add(const PsMat4d *lhs, const PsMat4d *rhs, PsMat4d *out) {
    *out = (PsMat4d) {
            ps_4d_add(lhs->x, rhs->x),
            ps_4d_add(lhs->y, rhs->y),
            ps_4d_add(lhs->z, rhs->z),
            ps_4d_add(lhs->w, rhs->w)
    };
}

PS_INLINE void ps_mat4d_sub(const PsMat4d *lhs, const PsMat4d *rhs, PsMat4d *out) {
    *out = (PsMat4d) {
            ps_4d_sub(lhs->x, rhs->x),
            ps_4d_sub(lhs->y, rhs->y),
            ps_4d_sub(lhs->z, rhs->z),
            ps_4d_sub(lhs->w, rhs->w)
    };
}

PS_INLINE void ps_mat4d_mul(const PsMat4d *lhs, const PsMat4d *rhs, PsMat4d *out) {
    *out = (PsMat4d) {
            ps_4d_mul(lhs->x, rhs->x),
            ps_4d_mul(lhs->y, rhs->y),
            ps_4d_mul(lhs->z, rhs->z),
            ps_4d_mul(lhs->w, rhs->w)
    };
}

PS_INLINE void ps_mat4d_div(const PsMat4d *lhs, const PsMat4d *rhs, PsMat4d *out) {
    *out = (PsMat4d) {
            ps_4d_div(lhs->x, rhs->x),
            ps_4d_div(lhs->y, rhs->y),
            ps_4d_div(lhs->z, rhs->z),
            ps_4d_div(lhs->w, rhs->w)
    };
}

PS_INLINE void ps_mat4d_perspective(PsMat4d *m4d, double fovy, double aspect, double znear, double zfar) {
    const double dz = zfar - znear;
    const double cot = tan(PS_MATH_TAU - fovy * 0.5);
    *m4d = (PsMat4d) {
            ps_4d(cot / aspect, 0.0, 0.0, 0.0),
            ps_4d(0.0, cot, 0.0, 0.0),
            ps_4d(0.0, 0.0, -(zfar + znear) / dz, -1.0),
            ps_4d(0.0, 0.0, -2.0 * znear * zfar / dz, 0.0)
    };
}

PS_INLINE void ps_mat4d_ortho(PsMat4d *m4d, double left, double right,
                              double bottom, double top, double znear, double zfar) {
    const double dx = right - left;
    const double dy = top - bottom;
    const double dz = zfar - znear;
    *m4d = (PsMat4d) {
            ps_4d(2.0 / dx, 0.0, 0.0, 0.0),
            ps_4d(0.0, 2.0 / dy, 0.0, 0.0),
            ps_4d(0.0, 0.0, -2.0 / dz, 0.0),
            ps_4d(-(right + left) / dx, -(top + bottom) / dy,
                  -(zfar + znear) / dz, 1.0)
    };
}

PS_INLINE void ps_mat4d_translation(PsMat4d *m4d, double x, double y, double z) {
    *m4d = (PsMat4d) {
            ps_4d(1.0, 0.0, 0.0, 0.0),
            ps_4d(0.0, 1.0, 0.0, 0.0),
            ps_4d(0.0, 0.0, 1.0, 0.0),
            ps_4d(x, y, z, 1.0)
    };
}

PS_INLINE void ps_mat4d_scale(PsMat4d *m4d, double x, double y, double z) {
    *m4d = (PsMat4d) {
            ps_4d(x, 0.0, 0.0, 0.0),
            ps_4d(0.0, y, 0.0, 0.0),
            ps_4d(0.0, 0.0, z, 0.0),
            ps_4d(0.0, 0.0, 0.0, 1.0)
    };
}

PS_INLINE void ps_mat4d_rot_x(PsMat4d *m4d, double radians) {
    const double s = sin(radians);
    const double c = cos(radians);
    *m4d = (PsMat4d) {
            ps_4d(1.0, 0.0, 0.0, 0.0),
            ps_4d(0.0, c, -s, 0.0),
            ps_4d(0.0, s, c, 0.0),
            ps_4d(0.0, 0.0, 0.0, 1.0)
    };
}

PS_INLINE void ps_mat4d_rot_y(PsMat4d *m4d, double radians) {
    const double s = sin(radians);
    const double c = cos(radians);
    *m4d = (PsMat4d) {
            ps_4d(c, 0.0, s, 0.0),
            ps_4d(0.0, 1.0, 0.0, 0.0),
            ps_4d(-s, 0.0, c, 0.0),
            ps_4d(0.0, 0.0, 0.0, 1.0)
    };
}

PS_INLINE void ps_mat4d_rot_z(PsMat4d *m4d, double radians) {
    const double s = sin(radians);
    const double c = cos(radians);
    *m4d = (PsMat4d) {
            ps_4d(c, -s, 0.0, 0.0),
            ps_4d(s, c, 0.0, 0.0),
            ps_4d(0.0, 0.0, 1.0, 0.0),
            ps_4d(0.0, 0.0, 0.0, 1.0)
    };
}

PS_INLINE void ps_mat4d_transpose(PsMat4d *m4d) {
    const Ps4d dx = ps_4d(ps_4d_x(m4d->x), ps_4d_x(m4d->y),
                          ps_4d_x(m4d->z), ps_4d_x(m4d->w));
    const Ps4d dy = ps_4d(ps_4d_y(m4d->x), ps_4d_y(m4d->y),
                          ps_4d_y(m4d->z), ps_4d_y(m4d->w));
    const Ps4d dz = ps_4d(ps_4d_z(m4d->x), ps_4d_z(m4d->y),
                          ps_4d_z(m4d->z), ps_4d_z(m4d->w));
    const Ps4d dw = ps_4d(ps_4d_w(m4d->x), ps_4d_w(m4d->y),
                          ps_4d_w(m4d->z), ps_4d_w(m4d->w));
    *m4d = (PsMat4d) {dx, dy, dz, dw};
}

PS_EXTERN_END

#endif // PS_MATH_MAT4D_H_