#include <eval.h>

#include <stdio.h>
#include <string.h>

#include <array.h>

struct time_assignment *generate_schedule(struct jsp *job_order) {
    /* mapping of machine ids to point in time until they are blocked */
    unsigned machine_times[job_order->n_machines];
    memset(machine_times, 0, sizeof machine_times);

    /* mapping of job ids to point in time until they are blocked */
    unsigned job_times[job_order->n_jobs];
    memset(job_times, 0, sizeof job_times);

    /* array to throw all the time assignments (one for each operation) into */
    array(struct time_assignment, schedule, 0);
    aforeach(op, job_order->operations) {
        unsigned m_id = job_order->operations[op].machine;
        unsigned j_id = job_order->operations[op].job;
        unsigned earliest_start = machine_times[m_id] > job_times[j_id]
                                    ? machine_times[m_id]
                                    : job_times[j_id];
        struct time_assignment ta = {
            .machine = m_id,
            .job = j_id,
            .start = earliest_start,
            .end = earliest_start + job_order->operations[op].duration,
        };
        apush(schedule, ta);
        machine_times[m_id] = ta.end;
        job_times[j_id] = ta.end;
    }
    return schedule;
}

unsigned eval(struct time_assignment *schedule) {
    (void) schedule;
    return 0;
}

void print_schedule(struct time_assignment *schedule) {
    printf("Schedule generated:\n");
    aforeach(i, schedule) {
        printf("\tJob %3u on machine %3u from %6u to %6u\n", schedule[i].machine,
               schedule[i].job, schedule[i].start, schedule[i].end);
    }
}
