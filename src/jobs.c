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
    array(struct operation, ops, n_ops);
    js.operations = ops;
    return js;
}
