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
void ps_ghpolygon_free(PsGHPolygon *poly);

size_t ps_ghpolygon_get_size(PsGHPolygon *poly);

void ps_ghpolygon_add(PsGHPolygon *poly, Ps4f point);

bool ps_ghpolygon_foreach(PsGHPolygon *poly, bool (*foreach)(Ps4f *point, void *userdata), void *userdata);

// TODO: just expose union diff intersect etc.
PsArray OF(PsGHPolygon *) *ps_ghpolygon_clip(PsGHPolygon *poly, PsGHPolygon *clip, bool entry, bool clip_entry);

PS_EXTERN_END

#endif // PS_CG_GHCLIPPING_H_