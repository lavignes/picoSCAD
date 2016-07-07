#ifndef PS_MATH_SCALAR_4F_H_
#define PS_MATH_SCALAR_4F_H_

#include <string.h>

#include <picoscad/math/math.h>

#define _PS_4F_SHUFFLE(x, y, z, w) (((x) << 6) | ((y) << 4) | ((z) << 2) | (w))

typedef enum PsSwizzle {
    PS_SWIZZLE_XXXX = _PS_4F_SHUFFLE(0, 0, 0, 0),
    PS_4F_SWIZZLE_XXXY = _PS_4F_SHUFFLE(0, 0, 0, 1),
    PS_4F_SWIZZLE_XXXZ = _PS_4F_SHUFFLE(0, 0, 0, 2),
    PS_4F_SWIZZLE_XXXW = _PS_4F_SHUFFLE(0, 0, 0, 3),
    PS_4F_SWIZZLE_XXYX = _PS_4F_SHUFFLE(0, 0, 1, 0),
    PS_4F_SWIZZLE_XXYY = _PS_4F_SHUFFLE(0, 0, 1, 1),
    PS_4F_SWIZZLE_XXYZ = _PS_4F_SHUFFLE(0, 0, 1, 2),
    PS_4F_SWIZZLE_XXYW = _PS_4F_SHUFFLE(0, 0, 1, 3),
    PS_4F_SWIZZLE_XXZX = _PS_4F_SHUFFLE(0, 0, 2, 0),
    PS_4F_SWIZZLE_XXZY = _PS_4F_SHUFFLE(0, 0, 2, 1),
    PS_4F_SWIZZLE_XXZZ = _PS_4F_SHUFFLE(0, 0, 2, 2),
    PS_4F_SWIZZLE_XXZW = _PS_4F_SHUFFLE(0, 0, 2, 3),
    PS_4F_SWIZZLE_XXWX = _PS_4F_SHUFFLE(0, 0, 3, 0),
    PS_4F_SWIZZLE_XXWY = _PS_4F_SHUFFLE(0, 0, 3, 1),
    PS_4F_SWIZZLE_XXWZ = _PS_4F_SHUFFLE(0, 0, 3, 2),
    PS_4F_SWIZZLE_XXWW = _PS_4F_SHUFFLE(0, 0, 3, 3),
    PS_4F_SWIZZLE_XYXX = _PS_4F_SHUFFLE(0, 1, 0, 0),
    PS_4F_SWIZZLE_XYXY = _PS_4F_SHUFFLE(0, 1, 0, 1),
    PS_4F_SWIZZLE_XYXZ = _PS_4F_SHUFFLE(0, 1, 0, 2),
    PS_4F_SWIZZLE_XYXW = _PS_4F_SHUFFLE(0, 1, 0, 3),
    PS_4F_SWIZZLE_XYYX = _PS_4F_SHUFFLE(0, 1, 1, 0),
    PS_4F_SWIZZLE_XYYY = _PS_4F_SHUFFLE(0, 1, 1, 1),
    PS_4F_SWIZZLE_XYYZ = _PS_4F_SHUFFLE(0, 1, 1, 2),
    PS_4F_SWIZZLE_XYYW = _PS_4F_SHUFFLE(0, 1, 1, 3),
    PS_4F_SWIZZLE_XYZX = _PS_4F_SHUFFLE(0, 1, 2, 0),
    PS_4F_SWIZZLE_XYZY = _PS_4F_SHUFFLE(0, 1, 2, 1),
    PS_4F_SWIZZLE_XYZZ = _PS_4F_SHUFFLE(0, 1, 2, 2),
    PS_4F_SWIZZLE_XYZW = _PS_4F_SHUFFLE(0, 1, 2, 3),
    PS_4F_SWIZZLE_XYWX = _PS_4F_SHUFFLE(0, 1, 3, 0),
    PS_4F_SWIZZLE_XYWY = _PS_4F_SHUFFLE(0, 1, 3, 1),
    PS_4F_SWIZZLE_XYWZ = _PS_4F_SHUFFLE(0, 1, 3, 2),
    PS_4F_SWIZZLE_XYWW = _PS_4F_SHUFFLE(0, 1, 3, 3),
    PS_4F_SWIZZLE_XZXX = _PS_4F_SHUFFLE(0, 2, 0, 0),
    PS_4F_SWIZZLE_XZXY = _PS_4F_SHUFFLE(0, 2, 0, 1),
    PS_4F_SWIZZLE_XZXZ = _PS_4F_SHUFFLE(0, 2, 0, 2),
    PS_4F_SWIZZLE_XZXW = _PS_4F_SHUFFLE(0, 2, 0, 3),
    PS_4F_SWIZZLE_XZYX = _PS_4F_SHUFFLE(0, 2, 1, 0),
    PS_4F_SWIZZLE_XZYY = _PS_4F_SHUFFLE(0, 2, 1, 1),
    PS_4F_SWIZZLE_XZYZ = _PS_4F_SHUFFLE(0, 2, 1, 2),
    PS_4F_SWIZZLE_XZYW = _PS_4F_SHUFFLE(0, 2, 1, 3),
    PS_4F_SWIZZLE_XZZX = _PS_4F_SHUFFLE(0, 2, 2, 0),
    PS_4F_SWIZZLE_XZZY = _PS_4F_SHUFFLE(0, 2, 2, 1),
    PS_4F_SWIZZLE_XZZZ = _PS_4F_SHUFFLE(0, 2, 2, 2),
    PS_4F_SWIZZLE_XZZW = _PS_4F_SHUFFLE(0, 2, 2, 3),
    PS_4F_SWIZZLE_XZWX = _PS_4F_SHUFFLE(0, 2, 3, 0),
    PS_4F_SWIZZLE_XZWY = _PS_4F_SHUFFLE(0, 2, 3, 1),
    PS_4F_SWIZZLE_XZWZ = _PS_4F_SHUFFLE(0, 2, 3, 2),
    PS_4F_SWIZZLE_XZWW = _PS_4F_SHUFFLE(0, 2, 3, 3),
    PS_4F_SWIZZLE_XWXX = _PS_4F_SHUFFLE(0, 3, 0, 0),
    PS_4F_SWIZZLE_XWXY = _PS_4F_SHUFFLE(0, 3, 0, 1),
    PS_4F_SWIZZLE_XWXZ = _PS_4F_SHUFFLE(0, 3, 0, 2),
    PS_4F_SWIZZLE_XWXW = _PS_4F_SHUFFLE(0, 3, 0, 3),
    PS_4F_SWIZZLE_XWYX = _PS_4F_SHUFFLE(0, 3, 1, 0),
    PS_4F_SWIZZLE_XWYY = _PS_4F_SHUFFLE(0, 3, 1, 1),
    PS_4F_SWIZZLE_XWYZ = _PS_4F_SHUFFLE(0, 3, 1, 2),
    PS_4F_SWIZZLE_XWYW = _PS_4F_SHUFFLE(0, 3, 1, 3),
    PS_4F_SWIZZLE_XWZX = _PS_4F_SHUFFLE(0, 3, 2, 0),
    PS_4F_SWIZZLE_XWZY = _PS_4F_SHUFFLE(0, 3, 2, 1),
    PS_4F_SWIZZLE_XWZZ = _PS_4F_SHUFFLE(0, 3, 2, 2),
    PS_4F_SWIZZLE_XWZW = _PS_4F_SHUFFLE(0, 3, 2, 3),
    PS_4F_SWIZZLE_XWWX = _PS_4F_SHUFFLE(0, 3, 3, 0),
    PS_4F_SWIZZLE_XWWY = _PS_4F_SHUFFLE(0, 3, 3, 1),
    PS_4F_SWIZZLE_XWWZ = _PS_4F_SHUFFLE(0, 3, 3, 2),
    PS_4F_SWIZZLE_XWWW = _PS_4F_SHUFFLE(0, 3, 3, 3),
    PS_4F_SWIZZLE_YXXX = _PS_4F_SHUFFLE(1, 0, 0, 0),
    PS_4F_SWIZZLE_YXXY = _PS_4F_SHUFFLE(1, 0, 0, 1),
    PS_4F_SWIZZLE_YXXZ = _PS_4F_SHUFFLE(1, 0, 0, 2),
    PS_4F_SWIZZLE_YXXW = _PS_4F_SHUFFLE(1, 0, 0, 3),
    PS_4F_SWIZZLE_YXYX = _PS_4F_SHUFFLE(1, 0, 1, 0),
    PS_4F_SWIZZLE_YXYY = _PS_4F_SHUFFLE(1, 0, 1, 1),
    PS_4F_SWIZZLE_YXYZ = _PS_4F_SHUFFLE(1, 0, 1, 2),
    PS_4F_SWIZZLE_YXYW = _PS_4F_SHUFFLE(1, 0, 1, 3),
    PS_4F_SWIZZLE_YXZX = _PS_4F_SHUFFLE(1, 0, 2, 0),
    PS_4F_SWIZZLE_YXZY = _PS_4F_SHUFFLE(1, 0, 2, 1),
    PS_4F_SWIZZLE_YXZZ = _PS_4F_SHUFFLE(1, 0, 2, 2),
    PS_4F_SWIZZLE_YXZW = _PS_4F_SHUFFLE(1, 0, 2, 3),
    PS_4F_SWIZZLE_YXWX = _PS_4F_SHUFFLE(1, 0, 3, 0),
    PS_4F_SWIZZLE_YXWY = _PS_4F_SHUFFLE(1, 0, 3, 1),
    PS_4F_SWIZZLE_YXWZ = _PS_4F_SHUFFLE(1, 0, 3, 2),
    PS_4F_SWIZZLE_YXWW = _PS_4F_SHUFFLE(1, 0, 3, 3),
    PS_4F_SWIZZLE_YYXX = _PS_4F_SHUFFLE(1, 1, 0, 0),
    PS_4F_SWIZZLE_YYXY = _PS_4F_SHUFFLE(1, 1, 0, 1),
    PS_4F_SWIZZLE_YYXZ = _PS_4F_SHUFFLE(1, 1, 0, 2),
    PS_4F_SWIZZLE_YYXW = _PS_4F_SHUFFLE(1, 1, 0, 3),
    PS_4F_SWIZZLE_YYYX = _PS_4F_SHUFFLE(1, 1, 1, 0),
    PS_SWIZZLE_YYYY = _PS_4F_SHUFFLE(1, 1, 1, 1),
    PS_4F_SWIZZLE_YYYZ = _PS_4F_SHUFFLE(1, 1, 1, 2),
    PS_4F_SWIZZLE_YYYW = _PS_4F_SHUFFLE(1, 1, 1, 3),
    PS_4F_SWIZZLE_YYZX = _PS_4F_SHUFFLE(1, 1, 2, 0),
    PS_4F_SWIZZLE_YYZY = _PS_4F_SHUFFLE(1, 1, 2, 1),
    PS_4F_SWIZZLE_YYZZ = _PS_4F_SHUFFLE(1, 1, 2, 2),
    PS_4F_SWIZZLE_YYZW = _PS_4F_SHUFFLE(1, 1, 2, 3),
    PS_4F_SWIZZLE_YYWX = _PS_4F_SHUFFLE(1, 1, 3, 0),
    PS_4F_SWIZZLE_YYWY = _PS_4F_SHUFFLE(1, 1, 3, 1),
    PS_4F_SWIZZLE_YYWZ = _PS_4F_SHUFFLE(1, 1, 3, 2),
    PS_4F_SWIZZLE_YYWW = _PS_4F_SHUFFLE(1, 1, 3, 3),
    PS_4F_SWIZZLE_YZXX = _PS_4F_SHUFFLE(1, 2, 0, 0),
    PS_4F_SWIZZLE_YZXY = _PS_4F_SHUFFLE(1, 2, 0, 1),
    PS_4F_SWIZZLE_YZXZ = _PS_4F_SHUFFLE(1, 2, 0, 2),
    PS_4F_SWIZZLE_YZXW = _PS_4F_SHUFFLE(1, 2, 0, 3),
    PS_4F_SWIZZLE_YZYX = _PS_4F_SHUFFLE(1, 2, 1, 0),
    PS_4F_SWIZZLE_YZYY = _PS_4F_SHUFFLE(1, 2, 1, 1),
    PS_4F_SWIZZLE_YZYZ = _PS_4F_SHUFFLE(1, 2, 1, 2),
    PS_4F_SWIZZLE_YZYW = _PS_4F_SHUFFLE(1, 2, 1, 3),
    PS_4F_SWIZZLE_YZZX = _PS_4F_SHUFFLE(1, 2, 2, 0),
    PS_4F_SWIZZLE_YZZY = _PS_4F_SHUFFLE(1, 2, 2, 1),
    PS_4F_SWIZZLE_YZZZ = _PS_4F_SHUFFLE(1, 2, 2, 2),
    PS_4F_SWIZZLE_YZZW = _PS_4F_SHUFFLE(1, 2, 2, 3),
    PS_4F_SWIZZLE_YZWX = _PS_4F_SHUFFLE(1, 2, 3, 0),
    PS_4F_SWIZZLE_YZWY = _PS_4F_SHUFFLE(1, 2, 3, 1),
    PS_4F_SWIZZLE_YZWZ = _PS_4F_SHUFFLE(1, 2, 3, 2),
    PS_4F_SWIZZLE_YZWW = _PS_4F_SHUFFLE(1, 2, 3, 3),
    PS_4F_SWIZZLE_YWXX = _PS_4F_SHUFFLE(1, 3, 0, 0),
    PS_4F_SWIZZLE_YWXY = _PS_4F_SHUFFLE(1, 3, 0, 1),
    PS_4F_SWIZZLE_YWXZ = _PS_4F_SHUFFLE(1, 3, 0, 2),
    PS_4F_SWIZZLE_YWXW = _PS_4F_SHUFFLE(1, 3, 0, 3),
    PS_4F_SWIZZLE_YWYX = _PS_4F_SHUFFLE(1, 3, 1, 0),
    PS_4F_SWIZZLE_YWYY = _PS_4F_SHUFFLE(1, 3, 1, 1),
    PS_4F_SWIZZLE_YWYZ = _PS_4F_SHUFFLE(1, 3, 1, 2),
    PS_4F_SWIZZLE_YWYW = _PS_4F_SHUFFLE(1, 3, 1, 3),
    PS_4F_SWIZZLE_YWZX = _PS_4F_SHUFFLE(1, 3, 2, 0),
    PS_4F_SWIZZLE_YWZY = _PS_4F_SHUFFLE(1, 3, 2, 1),
    PS_4F_SWIZZLE_YWZZ = _PS_4F_SHUFFLE(1, 3, 2, 2),
    PS_4F_SWIZZLE_YWZW = _PS_4F_SHUFFLE(1, 3, 2, 3),
    PS_4F_SWIZZLE_YWWX = _PS_4F_SHUFFLE(1, 3, 3, 0),
    PS_4F_SWIZZLE_YWWY = _PS_4F_SHUFFLE(1, 3, 3, 1),
    PS_4F_SWIZZLE_YWWZ = _PS_4F_SHUFFLE(1, 3, 3, 2),
    PS_4F_SWIZZLE_YWWW = _PS_4F_SHUFFLE(1, 3, 3, 3),
    PS_4F_SWIZZLE_ZXXX = _PS_4F_SHUFFLE(2, 0, 0, 0),
    PS_4F_SWIZZLE_ZXXY = _PS_4F_SHUFFLE(2, 0, 0, 1),
    PS_4F_SWIZZLE_ZXXZ = _PS_4F_SHUFFLE(2, 0, 0, 2),
    PS_4F_SWIZZLE_ZXXW = _PS_4F_SHUFFLE(2, 0, 0, 3),
    PS_4F_SWIZZLE_ZXYX = _PS_4F_SHUFFLE(2, 0, 1, 0),
    PS_4F_SWIZZLE_ZXYY = _PS_4F_SHUFFLE(2, 0, 1, 1),
    PS_4F_SWIZZLE_ZXYZ = _PS_4F_SHUFFLE(2, 0, 1, 2),
    PS_4F_SWIZZLE_ZXYW = _PS_4F_SHUFFLE(2, 0, 1, 3),
    PS_4F_SWIZZLE_ZXZX = _PS_4F_SHUFFLE(2, 0, 2, 0),
    PS_4F_SWIZZLE_ZXZY = _PS_4F_SHUFFLE(2, 0, 2, 1),
    PS_4F_SWIZZLE_ZXZZ = _PS_4F_SHUFFLE(2, 0, 2, 2),
    PS_4F_SWIZZLE_ZXZW = _PS_4F_SHUFFLE(2, 0, 2, 3),
    PS_4F_SWIZZLE_ZXWX = _PS_4F_SHUFFLE(2, 0, 3, 0),
    PS_4F_SWIZZLE_ZXWY = _PS_4F_SHUFFLE(2, 0, 3, 1),
    PS_4F_SWIZZLE_ZXWZ = _PS_4F_SHUFFLE(2, 0, 3, 2),
    PS_4F_SWIZZLE_ZXWW = _PS_4F_SHUFFLE(2, 0, 3, 3),
    PS_4F_SWIZZLE_ZYXX = _PS_4F_SHUFFLE(2, 1, 0, 0),
    PS_4F_SWIZZLE_ZYXY = _PS_4F_SHUFFLE(2, 1, 0, 1),
    PS_4F_SWIZZLE_ZYXZ = _PS_4F_SHUFFLE(2, 1, 0, 2),
    PS_4F_SWIZZLE_ZYXW = _PS_4F_SHUFFLE(2, 1, 0, 3),
    PS_4F_SWIZZLE_ZYYX = _PS_4F_SHUFFLE(2, 1, 1, 0),
    PS_4F_SWIZZLE_ZYYY = _PS_4F_SHUFFLE(2, 1, 1, 1),
    PS_4F_SWIZZLE_ZYYZ = _PS_4F_SHUFFLE(2, 1, 1, 2),
    PS_4F_SWIZZLE_ZYYW = _PS_4F_SHUFFLE(2, 1, 1, 3),
    PS_4F_SWIZZLE_ZYZX = _PS_4F_SHUFFLE(2, 1, 2, 0),
    PS_4F_SWIZZLE_ZYZY = _PS_4F_SHUFFLE(2, 1, 2, 1),
    PS_4F_SWIZZLE_ZYZZ = _PS_4F_SHUFFLE(2, 1, 2, 2),
    PS_4F_SWIZZLE_ZYZW = _PS_4F_SHUFFLE(2, 1, 2, 3),
    PS_4F_SWIZZLE_ZYWX = _PS_4F_SHUFFLE(2, 1, 3, 0),
    PS_4F_SWIZZLE_ZYWY = _PS_4F_SHUFFLE(2, 1, 3, 1),
    PS_4F_SWIZZLE_ZYWZ = _PS_4F_SHUFFLE(2, 1, 3, 2),
    PS_4F_SWIZZLE_ZYWW = _PS_4F_SHUFFLE(2, 1, 3, 3),
    PS_4F_SWIZZLE_ZZXX = _PS_4F_SHUFFLE(2, 2, 0, 0),
    PS_4F_SWIZZLE_ZZXY = _PS_4F_SHUFFLE(2, 2, 0, 1),
    PS_4F_SWIZZLE_ZZXZ = _PS_4F_SHUFFLE(2, 2, 0, 2),
    PS_4F_SWIZZLE_ZZXW = _PS_4F_SHUFFLE(2, 2, 0, 3),
    PS_4F_SWIZZLE_ZZYX = _PS_4F_SHUFFLE(2, 2, 1, 0),
    PS_4F_SWIZZLE_ZZYY = _PS_4F_SHUFFLE(2, 2, 1, 1),
    PS_4F_SWIZZLE_ZZYZ = _PS_4F_SHUFFLE(2, 2, 1, 2),
    PS_4F_SWIZZLE_ZZYW = _PS_4F_SHUFFLE(2, 2, 1, 3),
    PS_4F_SWIZZLE_ZZZX = _PS_4F_SHUFFLE(2, 2, 2, 0),
    PS_4F_SWIZZLE_ZZZY = _PS_4F_SHUFFLE(2, 2, 2, 1),
    PS_SWIZZLE_ZZZZ = _PS_4F_SHUFFLE(2, 2, 2, 2),
    PS_4F_SWIZZLE_ZZZW = _PS_4F_SHUFFLE(2, 2, 2, 3),
    PS_4F_SWIZZLE_ZZWX = _PS_4F_SHUFFLE(2, 2, 3, 0),
    PS_4F_SWIZZLE_ZZWY = _PS_4F_SHUFFLE(2, 2, 3, 1),
    PS_4F_SWIZZLE_ZZWZ = _PS_4F_SHUFFLE(2, 2, 3, 2),
    PS_4F_SWIZZLE_ZZWW = _PS_4F_SHUFFLE(2, 2, 3, 3),
    PS_4F_SWIZZLE_ZWXX = _PS_4F_SHUFFLE(2, 3, 0, 0),
    PS_4F_SWIZZLE_ZWXY = _PS_4F_SHUFFLE(2, 3, 0, 1),
    PS_4F_SWIZZLE_ZWXZ = _PS_4F_SHUFFLE(2, 3, 0, 2),
    PS_4F_SWIZZLE_ZWXW = _PS_4F_SHUFFLE(2, 3, 0, 3),
    PS_4F_SWIZZLE_ZWYX = _PS_4F_SHUFFLE(2, 3, 1, 0),
    PS_4F_SWIZZLE_ZWYY = _PS_4F_SHUFFLE(2, 3, 1, 1),
    PS_4F_SWIZZLE_ZWYZ = _PS_4F_SHUFFLE(2, 3, 1, 2),
    PS_4F_SWIZZLE_ZWYW = _PS_4F_SHUFFLE(2, 3, 1, 3),
    PS_4F_SWIZZLE_ZWZX = _PS_4F_SHUFFLE(2, 3, 2, 0),
    PS_4F_SWIZZLE_ZWZY = _PS_4F_SHUFFLE(2, 3, 2, 1),
    PS_4F_SWIZZLE_ZWZZ = _PS_4F_SHUFFLE(2, 3, 2, 2),
    PS_4F_SWIZZLE_ZWZW = _PS_4F_SHUFFLE(2, 3, 2, 3),
    PS_4F_SWIZZLE_ZWWX = _PS_4F_SHUFFLE(2, 3, 3, 0),
    PS_4F_SWIZZLE_ZWWY = _PS_4F_SHUFFLE(2, 3, 3, 1),
    PS_4F_SWIZZLE_ZWWZ = _PS_4F_SHUFFLE(2, 3, 3, 2),
    PS_4F_SWIZZLE_ZWWW = _PS_4F_SHUFFLE(2, 3, 3, 3),
    PS_4F_SWIZZLE_WXXX = _PS_4F_SHUFFLE(3, 0, 0, 0),
    PS_4F_SWIZZLE_WXXY = _PS_4F_SHUFFLE(3, 0, 0, 1),
    PS_4F_SWIZZLE_WXXZ = _PS_4F_SHUFFLE(3, 0, 0, 2),
    PS_4F_SWIZZLE_WXXW = _PS_4F_SHUFFLE(3, 0, 0, 3),
    PS_4F_SWIZZLE_WXYX = _PS_4F_SHUFFLE(3, 0, 1, 0),
    PS_4F_SWIZZLE_WXYY = _PS_4F_SHUFFLE(3, 0, 1, 1),
    PS_4F_SWIZZLE_WXYZ = _PS_4F_SHUFFLE(3, 0, 1, 2),
    PS_4F_SWIZZLE_WXYW = _PS_4F_SHUFFLE(3, 0, 1, 3),
    PS_4F_SWIZZLE_WXZX = _PS_4F_SHUFFLE(3, 0, 2, 0),
    PS_SWIZZLE_WXZY = _PS_4F_SHUFFLE(3, 0, 2, 1),
    PS_4F_SWIZZLE_WXZZ = _PS_4F_SHUFFLE(3, 0, 2, 2),
    PS_4F_SWIZZLE_WXZW = _PS_4F_SHUFFLE(3, 0, 2, 3),
    PS_4F_SWIZZLE_WXWX = _PS_4F_SHUFFLE(3, 0, 3, 0),
    PS_4F_SWIZZLE_WXWY = _PS_4F_SHUFFLE(3, 0, 3, 1),
    PS_4F_SWIZZLE_WXWZ = _PS_4F_SHUFFLE(3, 0, 3, 2),
    PS_4F_SWIZZLE_WXWW = _PS_4F_SHUFFLE(3, 0, 3, 3),
    PS_4F_SWIZZLE_WYXX = _PS_4F_SHUFFLE(3, 1, 0, 0),
    PS_4F_SWIZZLE_WYXY = _PS_4F_SHUFFLE(3, 1, 0, 1),
    PS_SWIZZLE_WYXZ = _PS_4F_SHUFFLE(3, 1, 0, 2),
    PS_4F_SWIZZLE_WYXW = _PS_4F_SHUFFLE(3, 1, 0, 3),
    PS_4F_SWIZZLE_WYYX = _PS_4F_SHUFFLE(3, 1, 1, 0),
    PS_4F_SWIZZLE_WYYY = _PS_4F_SHUFFLE(3, 1, 1, 1),
    PS_4F_SWIZZLE_WYYZ = _PS_4F_SHUFFLE(3, 1, 1, 2),
    PS_4F_SWIZZLE_WYYW = _PS_4F_SHUFFLE(3, 1, 1, 3),
    PS_4F_SWIZZLE_WYZX = _PS_4F_SHUFFLE(3, 1, 2, 0),
    PS_4F_SWIZZLE_WYZY = _PS_4F_SHUFFLE(3, 1, 2, 1),
    PS_4F_SWIZZLE_WYZZ = _PS_4F_SHUFFLE(3, 1, 2, 2),
    PS_4F_SWIZZLE_WYZW = _PS_4F_SHUFFLE(3, 1, 2, 3),
    PS_4F_SWIZZLE_WYWX = _PS_4F_SHUFFLE(3, 1, 3, 0),
    PS_4F_SWIZZLE_WYWY = _PS_4F_SHUFFLE(3, 1, 3, 1),
    PS_4F_SWIZZLE_WYWZ = _PS_4F_SHUFFLE(3, 1, 3, 2),
    PS_4F_SWIZZLE_WYWW = _PS_4F_SHUFFLE(3, 1, 3, 3),
    PS_4F_SWIZZLE_WZXX = _PS_4F_SHUFFLE(3, 2, 0, 0),
    PS_4F_SWIZZLE_WZXY = _PS_4F_SHUFFLE(3, 2, 0, 1),
    PS_4F_SWIZZLE_WZXZ = _PS_4F_SHUFFLE(3, 2, 0, 2),
    PS_4F_SWIZZLE_WZXW = _PS_4F_SHUFFLE(3, 2, 0, 3),
    PS_4F_SWIZZLE_WZYX = _PS_4F_SHUFFLE(3, 2, 1, 0),
    PS_4F_SWIZZLE_WZYY = _PS_4F_SHUFFLE(3, 2, 1, 1),
    PS_4F_SWIZZLE_WZYZ = _PS_4F_SHUFFLE(3, 2, 1, 2),
    PS_4F_SWIZZLE_WZYW = _PS_4F_SHUFFLE(3, 2, 1, 3),
    PS_4F_SWIZZLE_WZZX = _PS_4F_SHUFFLE(3, 2, 2, 0),
    PS_4F_SWIZZLE_WZZY = _PS_4F_SHUFFLE(3, 2, 2, 1),
    PS_4F_SWIZZLE_WZZZ = _PS_4F_SHUFFLE(3, 2, 2, 2),
    PS_4F_SWIZZLE_WZZW = _PS_4F_SHUFFLE(3, 2, 2, 3),
    PS_4F_SWIZZLE_WZWX = _PS_4F_SHUFFLE(3, 2, 3, 0),
    PS_4F_SWIZZLE_WZWY = _PS_4F_SHUFFLE(3, 2, 3, 1),
    PS_4F_SWIZZLE_WZWZ = _PS_4F_SHUFFLE(3, 2, 3, 2),
    PS_4F_SWIZZLE_WZWW = _PS_4F_SHUFFLE(3, 2, 3, 3),
    PS_4F_SWIZZLE_WWXX = _PS_4F_SHUFFLE(3, 3, 0, 0),
    PS_4F_SWIZZLE_WWXY = _PS_4F_SHUFFLE(3, 3, 0, 1),
    PS_4F_SWIZZLE_WWXZ = _PS_4F_SHUFFLE(3, 3, 0, 2),
    PS_4F_SWIZZLE_WWXW = _PS_4F_SHUFFLE(3, 3, 0, 3),
    PS_4F_SWIZZLE_WWYX = _PS_4F_SHUFFLE(3, 3, 1, 0),
    PS_4F_SWIZZLE_WWYY = _PS_4F_SHUFFLE(3, 3, 1, 1),
    PS_4F_SWIZZLE_WWYZ = _PS_4F_SHUFFLE(3, 3, 1, 2),
    PS_4F_SWIZZLE_WWYW = _PS_4F_SHUFFLE(3, 3, 1, 3),
    PS_4F_SWIZZLE_WWZX = _PS_4F_SHUFFLE(3, 3, 2, 0),
    PS_4F_SWIZZLE_WWZY = _PS_4F_SHUFFLE(3, 3, 2, 1),
    PS_4F_SWIZZLE_WWZZ = _PS_4F_SHUFFLE(3, 3, 2, 2),
    PS_4F_SWIZZLE_WWZW = _PS_4F_SHUFFLE(3, 3, 2, 3),
    PS_4F_SWIZZLE_WWWX = _PS_4F_SHUFFLE(3, 3, 3, 0),
    PS_4F_SWIZZLE_WWWY = _PS_4F_SHUFFLE(3, 3, 3, 1),
    PS_4F_SWIZZLE_WWWZ = _PS_4F_SHUFFLE(3, 3, 3, 2),
    PS_SWIZZLE_WWWW = _PS_4F_SHUFFLE(3, 3, 3, 3),
} PsSwizzle;

#undef _PS_4F_SHUFFLE

typedef struct Ps4f {
    union {
        struct {
            float _x, _y, _z, _w;
        };
        float _arr[4];
    };
} Ps4f;

PS_INLINE Ps4f ps_4f(float x, float y, float z, float w) {
    return (Ps4f) { ._x = x, ._y = y, ._z = z, ._w = w };
}

PS_INLINE Ps4f ps_4f_zero() {
    return ps_4f(0.0f, 0.0f, 0.0f, 0.0f);
}

PS_INLINE bool ps_4f_eq(Ps4f lhs, Ps4f rhs) {
    return lhs._x == rhs._x && lhs._y == rhs._y && lhs._z == rhs._z && lhs._w == rhs._w;
}

PS_INLINE bool ps_4f_lt(Ps4f lhs, Ps4f rhs) {
    return lhs._x < rhs._x && lhs._y < rhs._y && lhs._z < rhs._z && lhs._w < rhs._w;
}

PS_INLINE bool ps_4f_gt(Ps4f lhs, Ps4f rhs) {
    return lhs._x > rhs._x && lhs._y > rhs._y && lhs._z > rhs._z && lhs._w > rhs._w;
}

PS_INLINE Ps4f ps_4f_map(Ps4f v4f, float(*fn)(float)) {
    return ps_4f(fn(v4f._x), fn(v4f._y), fn(v4f._z), fn(v4f._w));
}

PS_INLINE Ps4f ps_4f_load(float *arr) {
    return ps_4f(arr[0], arr[1], arr[2], arr[3]);
}

PS_INLINE void ps_4f_store(Ps4f v4f, float *arr) {
    memcpy(arr, &v4f, sizeof(Ps4f));
}

PS_INLINE float ps_4f_x(Ps4f v4f) {
    return v4f._x;
}

PS_INLINE float ps_4f_y(Ps4f v4f) {
    return v4f._y;
}

PS_INLINE float ps_4f_z(Ps4f v4f) {
    return v4f._z;
}

PS_INLINE float ps_4f_w(Ps4f v4f) {
    return v4f._w;
}

PS_INLINE Ps4f ps_4f_swizzle(Ps4f v4f, PsSwizzle swizzle) {
    return ps_4f(v4f._arr[(swizzle & 0xC0) >> 6],
                 v4f._arr[(swizzle & 0x30) >> 4],
                 v4f._arr[(swizzle & 0x0C) >> 2],
                 v4f._arr[(swizzle & 0x03)]);
}

PS_INLINE Ps4f ps_4f_splat(float f) {
    return ps_4f(f, f, f, f);
}

PS_INLINE Ps4f ps_4f_splat_x(Ps4f v4f) {
    return ps_4f_splat(v4f._x);
}

PS_INLINE Ps4f ps_4f_splat_y(Ps4f v4f) {
    return ps_4f_splat(v4f._y);
}

PS_INLINE Ps4f ps_4f_splat_z(Ps4f v4f) {
    return ps_4f_splat(v4f._z);
}

PS_INLINE Ps4f ps_4f_splat_w(Ps4f v4f) {
    return ps_4f_splat(v4f._w);
}

PS_INLINE Ps4f ps_4f_add(Ps4f lhs, Ps4f rhs) {
    return ps_4f(lhs._x + rhs._x, lhs._y + rhs._y, lhs._z + rhs._z, lhs._w + rhs._w);
}

PS_INLINE Ps4f ps_4f_sub(Ps4f lhs, Ps4f rhs) {
    return ps_4f(lhs._x - rhs._x, lhs._y - rhs._y, lhs._z - rhs._z, lhs._w - rhs._w);
}

PS_INLINE Ps4f ps_4f_mul(Ps4f lhs, Ps4f rhs) {
    return ps_4f(lhs._x * rhs._x, lhs._y * rhs._y, lhs._z * rhs._z, lhs._w * rhs._w);
}

PS_INLINE Ps4f ps_4f_div(Ps4f lhs, Ps4f rhs) {
    return ps_4f(lhs._x / rhs._x, lhs._y / rhs._y, lhs._z / rhs._z, lhs._w / rhs._w);
}

PS_INLINE Ps4f ps_4f_recip(Ps4f v4f) {
    return ps_4f(1.0f / v4f._x, 1.0f / v4f._y, 1.0f / v4f._z, 1.0f / v4f._w);
}

PS_INLINE Ps4f ps_4f_recip_fast(Ps4f v4f) {
    return ps_4f_recip(v4f);
}

PS_INLINE Ps4f ps_4f_sqrt(Ps4f v4f) {
    return ps_4f(sqrtf(v4f._x), sqrtf(v4f._y), sqrtf(v4f._z), sqrtf(v4f._w));
}

PS_INLINE Ps4f ps_4f_sqrt_fast(Ps4f v4f) {
    return ps_4f_sqrt(v4f);
}

PS_INLINE Ps4f ps_4f_rsqrt(Ps4f v4f) {
    return ps_4f_recip(ps_4f_sqrt(v4f));
}

PS_INLINE Ps4f ps_4f_rsqrt_fast(Ps4f v4f) {
    return ps_4f_rsqrt(v4f);
}

PS_INLINE Ps4f ps_4f_cross(Ps4f lhs, Ps4f rhs) {
    return ps_4f(lhs._y * rhs._z - lhs._z * rhs._y,
                 lhs._z * rhs._x - lhs._x * rhs._z,
                 lhs._x * rhs._y - lhs._y * rhs._x, 0.0f);
}

PS_INLINE Ps4f ps_4f_min(Ps4f lhs, Ps4f rhs) {
    return ps_4f(fminf(lhs._x, rhs._x), fminf(lhs._y, rhs._y),
                 fminf(lhs._z, rhs._z), fminf(lhs._w, rhs._w));
}

PS_INLINE Ps4f ps_4f_max(Ps4f lhs, Ps4f rhs) {
    return ps_4f(fmaxf(lhs._x, rhs._x), fmaxf(lhs._y, rhs._y),
                 fmaxf(lhs._z, rhs._z), fmaxf(lhs._w, rhs._w));
}

PS_INLINE Ps4f ps_4f_abs(Ps4f v4f) {
    return ps_4f(fabsf(v4f._x), fabsf(v4f._y), fabsf(v4f._z), fabsf(v4f._w));
}

PS_INLINE Ps4f ps_4f_neg(Ps4f v4f) {
    return ps_4f(-v4f._x, -v4f._y, -v4f._z, -v4f._w);
}

#endif // PS_MATH_SCALAR_4F_H_