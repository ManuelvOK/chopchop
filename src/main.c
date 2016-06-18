#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <eval.h>
#include <input.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));
    printf("UNSATISFIABLE\n");
    FILE* input = fopen("input", "r");
    struct jsp jsp = eval_input(input);
    puts("");
    print_schedule(generate_schedule(&jsp));
    fclose(input);
    return 0;
}
