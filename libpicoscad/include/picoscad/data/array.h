#ifndef PS_DATA_ARRAY_H_
#define PS_DATA_ARRAY_H_

#include <picoscad/math/4f.h>

PS_EXTERN_BEGIN

typedef struct PsArray PsArray;

PsArray *ps_array_new(size_t size);
void ps_array_free(PsArray *array);

size_t ps_array_add(PsArray *array, void *element);

void *ps_array_remove(PsArray *array, size_t index);

void *ps_array_get(PsArray *array, size_t index);

size_t ps_array_get_length(PsArray *array);

bool ps_array_foreach(PsArray *array, bool (*foreach)(void *element, size_t index, void *userdata), void *userdata);

PS_EXTERN_END

#endif // PS_DATA_ARRAY_H_