#include <string.h>

#include <picoscad/data/array.h>

struct PsArray {
    size_t size;
    size_t length;
    size_t highLoad;
    void **elements;
};

static void array_double(PsArray *array) {
    void *old_elements = array->elements;
    size_t old_size = array->size;
    void *elements = realloc(old_elements, sizeof(void *) * old_size * 2);
    array->elements = elements;
    array->size = old_size * 2;
    array->highLoad = (array->size >> 2) * 3;
}

PsArray *ps_array_new(size_t size) {
    PsArray *array = malloc(sizeof(PsArray));
    if (size < 8) {
        size = 8;
    }
    void *elements = malloc(sizeof(void *) * size);
    array->size = size;
    array->length = 0;
    array->elements = elements;
    array->highLoad = (size >> 2) * 3;
    return array;
}

void ps_array_free(PsArray *array) {
    free(array->elements);
    free(array);
}

size_t ps_array_add(PsArray *array, void *element) {
    array->elements[array->length] = element;
    array->length++;
    if (array->length >= array->highLoad) {
        array_double(array);
    }
    return array->length - 1;
}

void *ps_array_remove(PsArray *array, size_t index) {
    void *element = array->elements[index];
    memmove(array->elements + index, array->elements + index + 1,
            sizeof(void *) * (array->length - index - 1));
    array->length--;
    return element;
}

void *ps_array_get(PsArray *array, size_t index) {
    return array->elements[index];
}

size_t ps_array_get_length(PsArray *array) {
    return array->length;
}

bool ps_array_foreach(PsArray *array, bool (*foreach)(void *element, size_t index, void *userdata), void *userdata) {
    for (size_t i = 0; i < array->length; ++i) {
        if (foreach(array->elements[i], i, userdata)) {
            return true;
        }
    }
    return false;
}
