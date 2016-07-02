#ifndef ALGORITHM_H
#define ALGORITHM_H value

#include <jobs.h>

/* algorithm:
 * kind of algorithm to use for optimisation
 */
enum algorithm {
    A_LOCAL_SEARCH,
    A_STOCHASTIC_HILLCLIMBING,
    A_SIMULATED_ANNEALING,
};

/* optimise:
 * improve the given <schedule> until the termination condition is met using
 * the given algorithm
 * note: the given <schedule> will be altered and become invalid
 */
struct jsp optimise(struct jsp schedule,struct jsp **current,
                    enum algorithm alg, unsigned T_MAX,
                    unsigned TEMP_INITIAL, unsigned COOLING_RATE);

#endif /* ifndef ALGORITHM_H */
