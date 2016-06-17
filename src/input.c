#include <stdlib.h>
#include <array/array.h>
#include <input.h>

struct jsp eval_input(FILE* input_file) {
    /* extract first line from file */
    char *line;
    fscanf(input_file, "%ms", &line);

    /* scan job- and operation count from first line */
    int job_count;
    int machine_count;
    sscanf(line, "%d %d", &job_count, &machine_count);
    free(line);

    /* init job array */
    array(struct job, jobs, job_count);

    int machine;
    int duration;

    /* iterate through file lines */
    for (int job = 0; job < job_count; ++job) {
        fscanf(input_file, "%ms", &line);
        jobs[job] = init_job(job, 0);

        /* iterate through operations */
        while (2 == sscanf(line, "%d, %d ", machine, duration)) {
            struct operation op = {machine, duration};
            apush(jobs[job].ops, op);
        }

        /* free memory since it is new allocated in next iteration */
        free(line);
    }
}
