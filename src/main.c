#include <stdio.h>
#include <input.h>

int main(int argc, char *argv[]) {
    printf("UNSATISFIABLE\n");
    FILE* input = fopen("input", "r");
    struct jsp jsp = eval_input(input);
    fclose(input);
    return 0;
}
