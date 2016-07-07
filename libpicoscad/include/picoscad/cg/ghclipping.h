#ifndef PS_CG_GHCLIPPING_H_
#define PS_CG_GHCLIPPING_H_

#include <picoscad/math/4f.h>
#include <picoscad/data/array.h>

PS_EXTERN_BEGIN

/**
 * A Greiner-Hormann Polygon
 */
typedef struct PsGHPolygon PsGHPolygon;

PsGHPolygon *ps_ghpolygon_new();
PsGHPolygon *ps_ghpolygon_new_with_points(Ps4f *points, size_t length);
void ps_ghpolygon_free(PsGHPolygon *poly);

size_t ps_ghpolygon_get_size(PsGHPolygon *poly);

void ps_ghpolygon_add(PsGHPolygon *poly, Ps4f point);

bool ps_ghpolygon_foreach(PsGHPolygon *poly, bool (*foreach)(Ps4f *point, void *userdata), void *userdata);

PsArray OF(PsGHPolygon *) *ps_ghpolygon_union(PsGHPolygon *poly, PsGHPolygon *target);

PsArray OF(PsGHPolygon *) *ps_ghpolygon_diff(PsGHPolygon *poly, PsGHPolygon *target);

PsArray OF(PsGHPolygon *) *ps_ghpolygon_intersect(PsGHPolygon *poly, PsGHPolygon *target);

PS_EXTERN_END

#endif // PS_CG_GHCLIPPING_H_