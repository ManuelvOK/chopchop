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

struct jsp {
    unsigned n_machines;
    struct job *jobs; /* dynamic array */
};

/* init_job:
 * initialise a job named <id> <n_nops> operations
 */
struct job init_job(unsigned id, unsigned n_ops);

/* init_operation:
 * initialise an operation on <machine> taking <duration> time
 */
struct operation init_operation(unsigned machine, unsigned duration);

/* init_jsp_data:
 * initialise the problem specification with an empty job list and 0 machines
 */
struct jsp init_jsp_data(void);

#endif /* ifndef JOBS_H */
