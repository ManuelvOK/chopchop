#include <stdlib.h>
#include <array.h>
#include <input.h>

#ifndef DEBUG
#define DEBUG 1
#endif /* DEBUG */

struct jsp eval_input(FILE* input_file) {
    /* extract first line from file */
    char line[256] = {0};
    fgets(line, 255, input_file);
    printf("%s\n", line);

    /* scan job- and operation count from first line */
    unsigned n_jobs;
    unsigned n_machines;
    sscanf(line, "%u %u", &n_jobs, &n_machines);

    /* init job array */
    struct operation *opsofchops[n_jobs];
    for (unsigned i = 0; i < n_jobs; ++i) {
        array(struct operation, op, 0);
        opsofchops[i] = op;
    }

    /* iterate through file lines */
    unsigned machine;
    unsigned duration;
    unsigned n_operations = 0;

#if DEBUG
    printf("%u Jobs Found.\n", n_jobs);
#endif /* DEBUG */

    for (unsigned job = 0; job < n_jobs; ++job) {

#if DEBUG
        printf("\tJob %3u:\t", job);
#endif /* DEBUG */

        fgets(line, 255, input_file);

        /* iterate through operations */
        char *nptr = line;
        char *endptr = NULL;
        for (unsigned nth = 0; ;++nth) {
            machine = strtol(nptr, &endptr, 0);
            nptr = endptr;
            duration = strtol(nptr, &endptr, 0);
            /* check if 2 numbers exists */
            if (nptr == endptr)
                break;
            nptr = endptr;

#if DEBUG
            printf("(%3u | %3u) ", machine, duration);
#endif /* DEBUG */

            /* add operation */
            struct operation op = {.machine  = machine,
                                   .duration = duration,
                                   .job      = job,
                                   .nth      = nth};
            apush(opsofchops[job], op);
            ++n_operations;
        }

#if DEBUG
        printf("\n");
#endif /* DEBUG */

    }
#if DEBUG
    printf("\nBeginning to create initial order.\n");
#endif /* DEBUG */

    /* Get an initial order for the operations */
    array(struct operation, operations, n_operations);
    unsigned row = 0;
    unsigned col = 0;
    for (unsigned i = 0; i < n_operations; ++i) {
        /* fast forward until a job is found that has an operation left */
        for(;;) {
            if (col < alength(opsofchops[row])) {
                break;
            }
            if (++row >= n_jobs) {
                ++col;
                row = 0;
            }
        }

#if DEBUG
        printf("\tInserted %3u. operation from job %3u.\n", row, col);
#endif /* DEBUG */

        /* add operation to ordered operation array */
        operations[i] = opsofchops[row][col];
        if (++row >= n_jobs) {
            ++col;
            row = 0;
        }
    }

    struct jsp jsp = {.n_machines = n_machines,
                      .operations = operations,
                      .n_jobs     = n_jobs};
    return jsp;
}
