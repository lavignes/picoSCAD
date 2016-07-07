#include <picoscad/cg/ghclipping.h>

typedef struct GHVertex GHVertex;

struct PsGHPolygon {
    GHVertex *head;
    size_t size;
};

struct GHVertex {
    Ps4f v4f;
    GHVertex *next;
    GHVertex *prev;
    GHVertex *neighbor;
    bool entry;
    float alpha;
    bool intersect;
    bool checked;
};

static GHVertex *ghvertex_new(Ps4f v4f, float alpha, bool intersect, bool entry) {
    GHVertex *vertex = malloc(sizeof(GHVertex));
    vertex->v4f = v4f;
    vertex->next = NULL;
    vertex->prev = NULL;
    vertex->neighbor = NULL;
    vertex->entry = entry;
    vertex->alpha = alpha;
    vertex->intersect = intersect;
    vertex->checked = false;
    return vertex;
}

static void ghvertex_free(GHVertex *vertex) {
    free(vertex);
}

static void ghpolygon_insert(PsGHPolygon *poly, GHVertex *vertex, GHVertex *start, GHVertex *end) {
    GHVertex *current = start;
    while (current != end && current->alpha < vertex->alpha) {
        current = current->next;
    }
    vertex->next = current;
    GHVertex *prev = current->prev;
    vertex->prev = prev;
    prev->next = vertex;
    current->prev = vertex;
    poly->size++;
}

static float angle3(Ps4f lhs, Ps4f rhs) {
    // arccos(a * b / |a| * |b|)?
    return acosf(ps_4f_x(ps_4f_div(ps_4f_dot3(lhs, rhs), ps_4f_length3(lhs) * ps_4f_length3(rhs))));
}

static bool ghpolygon_vertex_inside(PsGHPolygon *poly, GHVertex *vertex) {
    float angle = 0;
    GHVertex *current = poly->head;
    do {
        angle += angle3(ps_4f_sub(current->v4f, vertex->v4f), ps_4f_sub(current->next->v4f, vertex->v4f));
        current = current->next;
    } while (current != poly->head);
    if (fabsf(angle) < PS_MATH_PI) {
        return false;
    }
    return true;
}

// TODO: generalize denominator/alpha calculation to 3D :/
static bool intersection(Ps4f p1, Ps4f p2, Ps4f p3, Ps4f p4, Ps4f *point, float *alpha1, float *alpha2) {
    Ps4f diff1 = ps_4f_sub(p2, p1);
    Ps4f diff2 = ps_4f_sub(p4, p3);
    float denominator = (ps_4f_y(diff2) * ps_4f_x(diff1)) - (ps_4f_x(diff2) * ps_4f_y(diff1));
    if (denominator == 0.0f) {
        return false;
    }
    Ps4f diff3 = ps_4f_sub(p1, p3);
    float a1 = ((ps_4f_x(diff1) * ps_4f_y(diff3)) - (ps_4f_y(diff1) * ps_4f_x(diff3))) / denominator;
    float a2 = ((ps_4f_x(diff2) * ps_4f_y(diff3)) - (ps_4f_y(diff2) * ps_4f_x(diff3))) / denominator;
    // Degenerate case :(
    if (((a1 == 0.0f || a1 == 1.0f) && (a2 >= 0.0f && a2 <= 1.0f)) ||
        ((a2 == 0.0f || a2 == 1.0f) && (a1 >= 0.0f && a1 <= 1.0f))) {
        return false;
    }
    if (a1 > 0.0f && a1 < 1.0f && a2 > 0.0f && a2 < 1.0f) {
        *point = ps_4f_add(p1, ps_4f_mul(diff1, ps_4f_splat(a1)));
        *alpha1 = a1;
        *alpha2 = a2;
        return true;
    }
    return false;
}

PsArray OF(PsGHPolygon *) *ghpolygon_clip(PsGHPolygon *poly, PsGHPolygon *clip, bool entry, bool clip_entry) {
    // Phase-1 (find intersections)
    GHVertex *current = poly->head;
    do {
        if (!current->intersect) {
            GHVertex *clip_current = clip->head;
            do {
                if (!clip_current->intersect) {
                    Ps4f point;
                    float alpha, alpha_clip;
                    // Check for intersection
                    if (intersection(current->v4f, current->next->v4f, clip_current->v4f, clip_current->next->v4f,
                                     &point, &alpha, &alpha_clip)) {
                        // Create new points in each polygon representing the intersecting points
                        GHVertex *neighbor = ghvertex_new(point, alpha, true, false);
                        GHVertex *clip_neighbor = ghvertex_new(point, alpha_clip, true, false);
                        neighbor->neighbor = clip_neighbor;
                        clip_neighbor->neighbor = neighbor;
                        ghpolygon_insert(poly, neighbor, current, current->next);
                        ghpolygon_insert(clip, clip_neighbor, clip_current, clip_current->next);
                    }
                }
                clip_current = clip_current->next;
            } while (clip_current != clip->head);
        }
        current = current->next;
    } while (current != poly->head);

    // Phase-2 (entry-exit checking)
    current = poly->head;
    entry ^= ghpolygon_vertex_inside(clip, current);
    do {
        if (current->intersect) {
            current->entry = entry;
            entry = !entry;
        }
        current = current->next;
    } while (current != poly->head);
    GHVertex *clip_current = clip->head;
    clip_entry ^= ghpolygon_vertex_inside(poly, clip_current);
    do {
        if (clip_current->intersect) {
            clip_current->entry = clip_entry;
            clip_entry = !clip_entry;
        }
        clip_current = clip_current->next;
    } while (clip_current != clip->head);

    // Phase-3 (clip that shit)
    PsArray OF(PsGHPolygon *) *array = ps_array_new(1);
    size_t unchecked_count = poly->size;
    GHVertex *intersect = poly->head;
    while (unchecked_count > 0) {
        // Find next intersecting point
        do {
            if (intersect->intersect && !intersect->checked) {
                break;
            }
            intersect = intersect->next;
        } while (intersect != poly->head);
        // Create new clipped polygon
        current = intersect;
        PsGHPolygon *clipped = ps_ghpolygon_new();
        ps_ghpolygon_add(clipped, current->v4f);
        while (true) {
            current->checked = true;
            unchecked_count--;
            if (current->entry) {
                while (true) {
                    current = current->next;
                    ps_ghpolygon_add(clipped, current->v4f);
                    if (current->intersect) {
                        break;
                    }
                }
            } else {
                while (true) {
                    current = current->prev;
                    ps_ghpolygon_add(clipped, current->v4f);
                    if (current->intersect) {
                        break;
                    }
                }
            }
            current = current->neighbor;
            if (current->checked) {
                break;
            }
        }
        ps_array_add(array, clipped);
    }

    if (ps_array_get_length(array) == 0) {
        ps_array_add(array, poly);
    }
    return array;
}

PsGHPolygon *ps_ghpolygon_new() {
    PsGHPolygon *poly = malloc(sizeof(PsGHPolygon));
    poly->head = NULL;
    poly->size = 0;
    return poly;
}

PsGHPolygon *ps_ghpolygon_new_with_points(Ps4f *points, size_t length) {
    PsGHPolygon *poly = ps_ghpolygon_new();
    for (size_t i = 0; i < 4; ++i) {
        ps_ghpolygon_add(poly, points[i]);
    }
    return poly;
}

void ps_ghpolygon_free(PsGHPolygon *poly) {
    GHVertex *current = poly->head;
    do {
        GHVertex *next = current->next;
        ghvertex_free(current);
        current = next;
    } while (current != poly->head);
    free(poly);
}

size_t ps_ghpolygon_get_size(PsGHPolygon *poly) {
    return poly->size;
}

void ps_ghpolygon_add(PsGHPolygon *poly, Ps4f point) {
    GHVertex *vertex = ghvertex_new(point, 0.0f, false, true);
    if (!poly->head) {
        poly->head = vertex;
        poly->head->next = vertex;
        poly->head->prev = vertex;
    } else {
        GHVertex *next = poly->head;
        GHVertex *prev = next->prev;
        next->prev = vertex;
        vertex->next = next;
        vertex->prev = prev;
        prev->next = vertex;
    }
    poly->size++;
}

bool ps_ghpolygon_foreach(PsGHPolygon *poly, bool (*foreach)(Ps4f *point, void *userdata), void *userdata) {
    GHVertex *current = poly->head;
    do {
        if (foreach(&current->v4f, userdata)) {
            return true;
        }
        current = current->next;
    } while (current != poly->head);
    return false;
}

PsArray OF(PsGHPolygon *) *ps_ghpolygon_union(PsGHPolygon *poly, PsGHPolygon *target) {
    return ghpolygon_clip(poly, target, false, false);
}

PsArray OF(PsGHPolygon *) *ps_ghpolygon_diff(PsGHPolygon *poly, PsGHPolygon *target) {
    return ghpolygon_clip(poly, target, false, true);
}

PsArray OF(PsGHPolygon *) *ps_ghpolygon_intersect(PsGHPolygon *poly, PsGHPolygon *target) {
    return ghpolygon_clip(poly, target, true, true);
}