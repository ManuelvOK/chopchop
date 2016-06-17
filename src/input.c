#include <stdlib.h>
#include <array.h>
#include <input.h>

struct jsp eval_input(FILE* input_file) {
    /* extract first line from file */
    char line[256] = {0};
    fgets(line, 255, input_file);
    printf("%s\n", line);

    /* scan job- and operation count from first line */
    int job_count;
    int machine_count;
    sscanf(line, "%d %d", &job_count, &machine_count);
    /* init job array */
    array(struct job, jobs, job_count);

    int machine;
    int duration;

    /* iterate through file lines */
    for (int job = 0; job < job_count; ++job) {
        fgets(line, 255, input_file);
        jobs[job] = init_job(job, 0);

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
            struct operation op = {.machine = machine, .duration = duration};
            apush(jobs[job].ops, op);
        }
        printf("\n");
    }
    struct jsp jsp = {machine_count, jobs};
    return jsp;
}
