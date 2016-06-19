#include <algorithm.h>

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include <array.h>
#include <eval.h>
#include <hood.h>

//enum {T_MAX = 8000000, TEMP_INITIAL = 22};
//static const double cooling_rate = 10;

static bool accept_anyways(unsigned cur_eval, unsigned neigh_eval,
                           double temperature);

static unsigned update_temperature(unsigned t, unsigned TEMP_INITIAL,
                                   unsigned T_MAX, unsigned COOLING_RATE);

struct jsp optimise(struct jsp schedule, enum algorithm alg, unsigned T_MAX,
                    unsigned TEMP_INITIAL, unsigned COOLING_RATE) {
    double temperature = TEMP_INITIAL;
    struct jsp optimum = copy_jsp_data(schedule);
    unsigned opt_eval = eval(&optimum);
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
        if (cur_eval < opt_eval) {
            delete_jsp(&optimum);
            optimum = copy_jsp_data(schedule);
            opt_eval = cur_eval;
        }
        if (alg == A_SIMULATED_ANNEALING) {
            temperature = update_temperature(t, TEMP_INITIAL, T_MAX,
                                             COOLING_RATE);
        }
    }
    /* if the last tested solution was the optimal one, this has already been
     * deleted
     */
    if (schedule.operations != NULL) {
        delete_jsp(&schedule);
    }
    return optimum;
}

static bool accept_anyways(unsigned cur_eval, unsigned neigh_eval,
                           double temperature) {
    double rval = rand() / (1.0 * RAND_MAX);
    double diff = 1.0 * cur_eval - neigh_eval;
    return rval < exp((diff) / temperature);
}

static unsigned update_temperature(unsigned t, unsigned TEMP_INITIAL,
                                   unsigned T_MAX, unsigned COOLING_RATE) {
    double new_temp = TEMP_INITIAL * exp(-1.0 * COOLING_RATE * t / T_MAX);
    return new_temp;
}
