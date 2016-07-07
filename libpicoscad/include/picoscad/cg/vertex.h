#ifndef PS_CG_VERTEX_H_
#define PS_CG_VERTEX_H_

#include <picoscad/math/4f.h>

PS_EXTERN_BEGIN

typedef struct PsVertex PsVertex;
typedef struct PsPolygon PsPolygon;

struct PsPolygon {
    PsVertex *first;
};

struct PsVertex {
    Ps4f v4f;

    PsVertex *next;
    PsVertex *prev;
    PsVertex *neighbor;
    bool entry;
    float alpha;
    bool intersect;
    bool checked;
};



PS_EXTERN_END

#endif // PS_CG_VERTEX_H_