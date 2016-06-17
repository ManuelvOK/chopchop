#ifndef JOBS_H
#define JOBS_H value

/* operation:
 * a job takes <duration> time on <machine>
 */
struct operation {
    unsigned machine;
    unsigned duration;
};

/* job:
 * a job named <id> with operations <ops>
 */
struct job {
    unsigned id;
    struct operation *ops; /* dynamic array */
};

/* init_job:
 * initialise a job named <id> <n_nops> operations
 */
struct job init_job(unsigned id, unsigned n_ops);

/* init_operation:
 * initialise an operation on <machine> taking <duration> time
 */
struct operation init_operation(unsigned machine, unsigned duration);

#endif /* ifndef JOBS_H */
