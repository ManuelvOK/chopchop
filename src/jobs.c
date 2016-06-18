#include <jobs.h>

#include <assert.h>
#include <stdlib.h>

#include <array.h>

struct operation init_operation(unsigned job, unsigned nth,
                                unsigned machine, unsigned duration) {
    struct operation op = {.job = job, .nth = nth, .machine = machine,
                           .duration = duration};
    return op;
}

struct jsp init_jsp_data(unsigned n_ops) {
    struct jsp js;
    js.n_machines = 0;
    js.n_jobs = 0;
    array(struct operation, ops, n_ops);
    js.operations = ops;
    return js;
}

void delete_jsp(struct jsp *jsp) {
    afree(jsp->operations);
    jsp->n_machines = 0;
    jsp->n_jobs = 0;
    jsp->operations = NULL;
}

struct jsp copy_jsp_data(struct jsp other) {
    struct jsp new_jsp;
    new_jsp.n_machines = other.n_machines;
    new_jsp.n_jobs = other.n_jobs;
    array(struct operation, ops, alength(other.operations));
    aforeach(op, ops) {
        op[ops] = other.operations[op];
    }
    new_jsp.operations = ops;
    return new_jsp;
}
