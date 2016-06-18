#include <hood.h>
#include <stdlib.h>

#include <array.h>

struct jsp get_neighbour(const struct jsp schedule) {
    /* get a random index to swap */
    unsigned index;
    do {
        index = (rand() / (RAND_MAX * 1.0))
                    * (alength(schedule.operations) - 1);
    } while (schedule.operations[index].job
             == schedule.operations[index + 1].job);

    /* create new jsp */
    struct jsp new_jsp = init_jsp_data(alength(schedule.operations));
    new_jsp.n_jobs = schedule.n_jobs;
    new_jsp.n_machines = schedule.n_machines;

    /* copy operation data and swap two of them */
    aforeach (i, schedule.operations) {
        if (i == index) {
            new_jsp.operations[i] = schedule.operations[i + 1];
        } else if (i == index + 1) {
            new_jsp.operations[i] = schedule.operations[i - 1];
        } else {
            new_jsp.operations[i] = schedule.operations[i];
        }
    }

    return new_jsp;
}
