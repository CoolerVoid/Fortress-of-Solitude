#ifndef VECTOR_H
#define VECTOR_H

#define ice_vector_LIMIT 1
#define ICE_MAX_LEN_STR_CMP 512

typedef struct vector {
    void **elements;
    int limit;
    int max;
} ice_vector;


void ice_vector_init(ice_vector *v);
int  ice_vector_max(ice_vector *v);
void ice_vector_resize(ice_vector *v, int limit);
void ice_vector_swap(ice_vector *v, int index, int index2);
void ice_vector_write(ice_vector *v, int index, void *element);
void ice_vector_add(ice_vector *v, void *element);
void *ice_vector_view(ice_vector *v, int index);
void ice_vector_free(ice_vector *v);
void ice_vector_remove(ice_vector *v, int index);
void ice_vector_pop(ice_vector *v);

// this is util to use with sort functions or binary search compare...
int ice_cmp_str(const void *a, const void *b);
int ice_cmp_int(const void *a, const void *b);
int ice_cmp_double(const void *a, const void *b);
int ice_cmp_float(const void *a, const void *b);


#endif
