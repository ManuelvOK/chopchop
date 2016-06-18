#include <stdlib.h>
#include <array.h>
#include <input.h>

struct jsp eval_input(FILE* input_file) {
    /* extract first line from file */
    char line[256] = {0};
    fgets(line, 255, input_file);
    printf("%s\n", line);

    /* scan job- and operation count from first line */
    int n_jobs;
    int n_machines;
    sscanf(line, "%d %d", &n_jobs, &n_machines);

    /* init job array */
    struct operation *opsofchops[n_jobs];
    for (int i = 0; i < n_jobs; ++i) {
        array(struct operation, op, 0);
        opsofchops[i] = op;
    }

    /* iterate through file lines */
    int machine;
    int duration;
    int n_operations = 0;

    for (int job = 0; job < n_jobs; ++job) {
        fgets(line, 255, input_file);

        /* iterate through operations */
        char *nptr = line;
        char *endptr = NULL;
        for (;;) {
            machine = strtol(nptr, &endptr, 0);
            nptr = endptr;
            duration = strtol(nptr, &endptr, 0);
            if (nptr == endptr)
                break;
            nptr = endptr;
            printf("(%d | %d) ", machine, duration);
            struct operation op = {.machine  = machine,
                                   .duration = duration,
                                   .job      = job};
            apush(opsofchops[job], op);
            ++n_operations;
        }
        printf("\n");
    }

    array(struct operation, operations, n_operations);
    int row = 0;
    int col = 0;
    for (int i = 0; i < n_operations; ++i) {
        for(;;) {
            if (alength(opsofchops[row]) <= col + 1) {
                break;
            }
            if (++row >= n_jobs) {
                ++col;
                row = 0;
            }
        }
        operations[i] = opsofchops[row][col];
        if (++row >= n_jobs) {
            ++col;
            row = 0;
        }
    }
    aforeach(i, operations) {
        printf("%d\n", operations[i].job);
    }

    struct jsp jsp = {.n_machines = n_machines, .operations = operations};
    return jsp;
}
