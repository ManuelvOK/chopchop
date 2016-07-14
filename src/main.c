#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <algorithm.h>
#include <array.h>
#include <eval.h>
#include <input.h>
#include <vision.h>
#include <pthread.h>

static void evaluate_input_parameters(int argc, char *argv[]);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

char in[255] = "input";
int T_MAX = 0;
int TEMP_INI = 0;
int C_RATE = 0;
int ALGORITHM = 0;
int VISUALISATION = 0;

int main(int argc, char *argv[]) {


    evaluate_input_parameters(argc, argv);
    /* initialise RNG */
    srand(time(NULL));

    /* read input file */
    FILE* input = fopen(in, "r");
    struct jsp jsp = eval_input(input);
    fclose(input);

    /* this is for visualisation */
    struct jsp *model = &jsp;

    /* start visualisation */
    pthread_t visualisation;

    if (VISUALISATION) {
        if (pthread_create(&visualisation, NULL, visualise, (void *) &model)) {
            perror("Error creating thread for visualisation");
            exit(EXIT_FAILURE);
        }
    }

    /* genrate solution */
    struct jsp solution = optimise(jsp, &model, ALGORITHM, T_MAX, TEMP_INI, C_RATE);

    /* print solution */
    struct time_assignment *schedule = generate_schedule(&solution);
    print_schedule(schedule);

    if (VISUALISATION) {
        /* wait for user to end visualisation */
        void *retval;
        pthread_join(visualisation, &retval);
    }

    pthread_mutex_destroy(&mutex);

    /* avoid memory leakage */
    afree(schedule);
    delete_jsp(&solution);
    return 0;
}

static void extract_int(char *src, int *dst) {
    char* endptr = NULL;
    int tmp = strtol(src, &endptr, 0);
    if (endptr != src) {
         *dst = tmp;
    }
}

static void evaluate_input_parameters(int argc, char *argv[]) {
    if (argc <= 1) return;

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0]  != '-' || argc < i) {
            continue;
        }
        if (!strcmp(argv[i] + 1, "i")) {
            strcpy(in, argv[++i]);
        } else if (!strcmp(argv[i] + 1, "t")) {
            extract_int(argv[++i], &T_MAX);
        } else if (!strcmp(argv[i] + 1, "T")) {
            extract_int(argv[++i], &TEMP_INI);
        } else if (!strcmp(argv[i] + 1, "c")) {
            extract_int(argv[++i], &C_RATE);
        } else if (!strcmp(argv[i] + 1, "a")) {
            extract_int(argv[++i], &ALGORITHM);
        } else if (!strcmp(argv[i] + 1, "v")) {
            extract_int(argv[++i], &VISUALISATION);
        }
    }
}
