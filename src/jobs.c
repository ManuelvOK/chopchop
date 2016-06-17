#include <jobs.h>

#include <assert.h>
#include <stdlib.h>

#include <array.h>

struct job init_job(unsigned id, unsigned n_ops) {
    struct job j;
    j.id = id;
    array(struct operation, ops, n_ops);
    j.ops = ops;
    return j;
}

struct operation init_operation(unsigned machine, unsigned duration) {
    struct operation op = {.machine = machine, .duration = duration};
    return op;
}

struct jsp init_jsp_data(void) {
    struct jsp js;
    js.n_machines = 0;
    array(struct job, j, 0);
    js.jobs = j;
    return js;
}
