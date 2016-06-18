#include <algorithm.h>

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include <array.h>
#include <eval.h>
#include <hood.h>

enum {T_MAX = 8000, TEMP_INITIAL = 22};
static const double cooling_rate = 10;

static bool accept_anyways(unsigned cur_eval, unsigned neigh_eval,
                           double temperature);

static unsigned update_temperature(unsigned t);

struct jsp optimise(struct jsp schedule, enum algorithm alg) {
    double temperature = TEMP_INITIAL;
    for (unsigned t = 1; t < T_MAX; ++t) {
        unsigned cur_eval = eval(&schedule);
        struct jsp neigh_schedule = get_neighbour(schedule);
        unsigned neigh_eval = eval(&neigh_schedule);
        if (neigh_eval < cur_eval) {
            delete_jsp(&schedule);
            schedule = neigh_schedule;
        } else if ((alg == A_STOCHASTIC_HILLCLIMBING
                   || alg == A_SIMULATED_ANNEALING)
                   && accept_anyways(cur_eval, neigh_eval, temperature)) {
            delete_jsp(&schedule);
            schedule = neigh_schedule;
        } else {
            delete_jsp(&neigh_schedule);
        }
        if (alg == A_SIMULATED_ANNEALING) {
            temperature = update_temperature(t);
        }
    }
    return schedule;
}

static bool accept_anyways(unsigned cur_eval, unsigned neigh_eval,
                           double temperature) {
    double rval = rand() / (1.0 * RAND_MAX);
    double diff = 1.0 * cur_eval - neigh_eval;
    return rval < exp((diff) / temperature);
}

static unsigned update_temperature(unsigned t) {
    double new_temp = TEMP_INITIAL * exp(-cooling_rate * t / T_MAX);
    return new_temp;
}
