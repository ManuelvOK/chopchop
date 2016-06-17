#include <jobs.h>

#include <assert.h>
#include <stdlib.h>

#include <array/array.h>

struct job *init_job(unsigned id, unsigned n_ops) {
    struct job *j = malloc(sizeof *j);
    assert(j != NULL);
    j->id = id;
    array(struct operation, ops, n_ops);
    j->ops = ops;
    return j;
}

struct operation *init_operation(unsigned machine, unsigned duration) {
    struct operation *op = malloc(sizeof *op);
    assert(op != NULL);
    op->machine = machine;
    op->duration = duration;
    return op;
}
