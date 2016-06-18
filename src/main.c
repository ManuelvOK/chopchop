#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <array.h>
#include <eval.h>
#include <input.h>

int main(int argc, char *argv[]) {
    /* initialise RNG */
    srand(time(NULL));

    /* read input file */
    FILE* input = fopen("input", "r");
    struct jsp jsp = eval_input(input);
    fclose(input);

    /* genrate solution */


    /* print solution */
    puts("");
    struct time_assignment *schedule = generate_schedule(&jsp);
    print_schedule(schedule);

    /* avoid memory leakage */
    afree(schedule);
    delete_jsp(&jsp);
    return 0;
}
