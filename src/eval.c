#include <eval.h>

#include <stdio.h>
#include <string.h>

#include <array.h>

struct time_assignment *generate_schedule(struct jsp *job_order) {
    unsigned machine_times[job_order->n_machines];
    memset(machine_times, 0, sizeof machine_times);
    unsigned job_times[alength(job_order->jobs)];
    memset(job_times, 0, sizeof job_times);
    array(struct time_assignment, schedule, 0);
    aforeach(j, job_order->jobs) {
        aforeach(o, job_order->jobs[j].ops) {
            unsigned m_id = job_order->jobs[j].ops[o].machine;
            unsigned j_id = job_order->jobs[j].id;
            unsigned earliest_start = machine_times[m_id] < job_times[j_id]
                                      ? machine_times[m_id]
                                      : job_times[j_id];
            struct time_assignment ta = {
                .machine = m_id,
                .job = j_id,
                .start = earliest_start,
                .end = earliest_start + job_order->jobs[j].ops[o].duration,
            };
            apush(schedule, ta);
            machine_times[m_id] = ta.end;
            job_times[j_id] = ta.end;
        }
    }
    return schedule;
}

unsigned eval(struct time_assignment *schedule) {
    (void) schedule;
    return 0;
}

void print_schedule(struct time_assignment *schedule) {
    aforeach(i, schedule) {
        printf("J%u on M%u from %u to %u\n", schedule[i].machine,
               schedule[i].job, schedule[i].start, schedule[i].end);
    }
}
