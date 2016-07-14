#include <hood.h>

#include <stdlib.h>
#include <stdio.h>

#include <array.h>

#ifndef DEBUG
#define DEBUG 0
#endif

struct jsp get_neighbour(const struct jsp schedule) {
    /* get a random index to swap */
    unsigned start;
    do {
        start = (rand() / (RAND_MAX * 1.0))
                    * (alength(schedule.operations) - 1);
    } while (schedule.operations[start].job
             == schedule.operations[start + 1].job);

    /* get the longest sequence of distinct jobs */
    char punchmap[schedule.n_jobs];
    for (unsigned i = 0; i < schedule.n_jobs; ++i) {
        punchmap[i] = 0;
    }

    unsigned end = start;
    punchmap[schedule.operations[start].job] = 1;
    while (punchmap[schedule.operations[end + 1].job] == 0
            && end < alength(schedule.operations)) {
        punchmap[schedule.operations[end + 1].job] = 1;
        ++end;
    }

#if DEBUG
    aforeach(i, schedule.operations) {
        printf("%2u ", schedule.operations[i].job);
    }
#endif

    unsigned swap_size = (rand() / (RAND_MAX * 1.0)) * (end - start - 1) + 1;

#if DEBUG
    printf("\n");
    aforeach(i, schedule.operations) {
        if (i == start) {
            printf(" ^-");
        } else if(i == start + swap_size) {
            printf("-^ ");
        } else if (i > start && i < start + swap_size) {
            printf("---");
        } else {
            printf("   ");
        }
    }
    printf("\n");
    printf("start: %3u\tend: %3u\toperations: %3u\tjobs: %3u\tswap %3u operations\n",
            start, end, alength(schedule.operations),schedule.n_jobs, swap_size);
#endif
    /* create new jsp */
    struct jsp new_jsp = init_jsp_data(alength(schedule.operations));
    new_jsp.n_jobs = schedule.n_jobs;
    new_jsp.n_machines = schedule.n_machines;

    /* copy operation data and swap two of them */
    aforeach (i, schedule.operations) {
        if (i >= start && i <= start + swap_size) {
            new_jsp.operations[i] = schedule.operations[start + swap_size - (i - start)];
        } else {
            new_jsp.operations[i] = schedule.operations[i];
        }
    }

    return new_jsp;
}
