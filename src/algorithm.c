#include <algorithm.h>

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include <eval.h>
#include <hood.h>

enum {T_MAX = 1024, TEMP_INITIAL = 20, TEMP_COOL = 2, SA_SCALE = 128};

static bool accept_anyways(unsigned cur_eval, unsigned neigh_eval,
                           unsigned temperature);

static unsigned update_temperature(unsigned t);

struct jsp optimise(struct jsp schedule, enum algorithm alg) {
    unsigned temperature = TEMP_INITIAL;
    for (unsigned t = 0; t < T_MAX; ++t) {
        unsigned cur_eval = eval(&schedule);
        struct jsp neigh_schedule = get_neighbour(schedule);
        unsigned neigh_eval = eval(&neigh_schedule);
        if (neigh_eval < cur_eval) {
            /* memory leak incoming */
            schedule = neigh_schedule;
        } else if ((alg == A_STOCHASTIC_HILLCLIMBING
                   || alg == A_SIMULATED_ANNEALING)
                   && accept_anyways(cur_eval, neigh_eval, temperature)) {
            /* memory leak incoming */
            schedule = neigh_schedule;
        }
        if (alg == A_SIMULATED_ANNEALING && t % SA_SCALE == 0) {
            temperature = update_temperature(t / SA_SCALE);
        }
    }
    return schedule;
}

static bool accept_anyways(unsigned cur_eval, unsigned neigh_eval,
                           unsigned temperature) {
    double rval = rand() / (1.0 * RAND_MAX);
    return rval < exp((cur_eval - neigh_eval) / temperature);
}

static unsigned update_temperature(unsigned t) {
    return TEMP_INITIAL * exp(-t * TEMP_COOL);
}
