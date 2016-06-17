#ifndef EVAL_H
#define EVAL_H value

#include <jobs.h>

struct time_assignment {
    unsigned machine;
    unsigned job;
    unsigned start;
    unsigned end;
};

struct time_assignment *generate_schedule(struct jsp *job_order);
unsigned eval(struct time_assignment *schedule);
void print_schedule(struct time_assignment *schedule);

#endif /* ifndef EVAL_H */
