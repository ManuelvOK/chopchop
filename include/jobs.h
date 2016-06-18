#ifndef JOBS_H
#define JOBS_H value

/* operation:
 * the <nth> operation of a job named <job_id> takes <duration> time on
 * <machine>
 */
struct operation {
    unsigned job;
    unsigned nth;
    unsigned machine;
    unsigned duration;
};

/* job shop scheduling problem:
 * <operations> must be scheduled on <n_machines> machines in total
 */
struct jsp {
    unsigned n_machines;
    struct operation *operations; /* dynamic array */
};

/* init_operation:
 * initialise the <nth> operation of <job> on <machine> taking <duration> time
 */
struct operation init_operation(unsigned job, unsigned nth,
                                unsigned machine, unsigned duration);

/* init_jsp_data:
 * initialise the jsp specification with an empty operation list of length
 * <n_ops> and a machine counter of 0
 */
struct jsp init_jsp_data(unsigned n_ops);

#endif /* ifndef JOBS_H */
