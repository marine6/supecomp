#ifndef LINEAR_LIVENESS_H
#define LINEAR_LIVENESS_H

void free_liveness(list* map);
list* liveness_linear_prog(linear_prog* p);

#endif
