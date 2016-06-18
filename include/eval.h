#ifndef EVAL_H
#define EVAL_H value

#include <jobs.h>

/* time_assignment:
 * a <job> runs on <machine> from <start> to <end>
 */
struct time_assignment {
    unsigned machine;
    unsigned job;
    unsigned start;
    unsigned end;
};

/* generate_schedule:
 * get an array of time_assignments - one for each operation in <job_order>
 * TODO verify that <job_order> is feasible
 * TODO this function calculates the evaluation on the fly, use it
 */
struct time_assignment *generate_schedule(struct jsp *job_order);

/* eval:
 * evaluate a <schedule> (array of time_assignments, one for each operation)
 */
unsigned eval(struct time_assignment *schedule);

/* print_schedule:
 * print a <schedule> to stdout
 */
void print_schedule(struct time_assignment *schedule);

#endif /* ifndef EVAL_H */
