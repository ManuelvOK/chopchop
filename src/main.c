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

    /* this is for vsualisation */
    struct jsp *model = &jsp;

    /* start visualisation */
    pthread_t visualisation;

    if (VISUALISATION) {
        if (pthread_create(&visualisation, NULL, visualise, (void *) &model)) {
            printf("Visualisation Failed\n");
        }
    }

    /* genrate solution */
    struct jsp solution = optimise(jsp, &model, ALGORITHM, T_MAX, TEMP_INI, C_RATE);

    /* print solution */
    puts("");
    struct time_assignment *schedule = generate_schedule(&solution);
    print_schedule(schedule);

    if (VISUALISATION) {
        /* abort visualisation */
        pthread_cancel(visualisation);
    }

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
            printf("in\n");
        } else if (!strcmp(argv[i] + 1, "t")) {
            extract_int(argv[++i], &T_MAX);
            printf("t_max\n");
        } else if (!strcmp(argv[i] + 1, "T")) {
            extract_int(argv[++i], &TEMP_INI);
            printf("temp_ini\n");
        } else if (!strcmp(argv[i] + 1, "c")) {
            extract_int(argv[++i], &C_RATE);
            printf("c_rate\n");
        } else if (!strcmp(argv[i] + 1, "a")) {
            extract_int(argv[++i], &ALGORITHM);
            printf("algorithm\n");
        } else if (!strcmp(argv[i] + 1, "v")) {
            extract_int(argv[++i], &VISUALISATION);
            printf("visualisation\n");
        }
    }
}
