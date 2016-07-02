#include <vision.h>
#include <jobs.h>
#include <eval.h>

#include <array.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <pthread.h>
#include <stdio.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
enum {
    WIDTH = 800,
    HEIGHT = 500,
    MARGIN = 20,
};

static unsigned *colors = NULL;

static int init_SDL();
static void draw_model(struct jsp *model);
static void init_colors(int n_jobs);
static void set_color(int job);
static void HSV_to_RGB(float h, float s, float v,
                       float *r, float *g, float *b);

void *visualise(void *shedule) {
    struct jsp **model = shedule;

    if (init_SDL())
        pthread_exit(NULL);

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        draw_model(*model);
    }

    if (colors) {
        afree(colors);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    pthread_exit(NULL);
}

int init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("chopchop", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED
                                    | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    return 0;
}

static void draw_model(struct jsp *model) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    /* draw coordinate system */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, MARGIN, MARGIN, MARGIN, HEIGHT - MARGIN);
    SDL_RenderDrawLine(renderer, MARGIN, HEIGHT - MARGIN, WIDTH - MARGIN,
                       HEIGHT - MARGIN);

    struct time_assignment *schedule = generate_schedule(model);
    init_colors(model->n_jobs);
    int job_height = (HEIGHT - 2 * MARGIN) / (model->n_machines - 1) - 10;
    aforeach(i, schedule) {
        SDL_Rect r = {schedule[i].start / 4 + MARGIN + 1,
                      schedule[i].machine * (job_height + 5) + MARGIN + 1,
                      schedule[i].end - schedule[i].start,
                      job_height};
        set_color(schedule[i].job);
        SDL_RenderFillRect(renderer, &r);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &r);
    }
    afree(schedule);
    SDL_RenderPresent(renderer);
    (void) model;
}

static void init_colors(int n_jobs) {
    array(unsigned, c, n_jobs);
    colors = c;

    aforeach(i, colors) {
        colors[i] = (360 / (n_jobs)) * i;
    }
}

static void set_color(int job) {
    float r = 0;
    float g = 0;
    float b = 0;

    HSV_to_RGB((float)colors[job], 1.0f, 1.0f, &r, &g, &b);
    SDL_SetRenderDrawColor(renderer, r * 255, g * 255, b * 255, 255);
}

static void HSV_to_RGB(float h, float s, float v,
        float *r, float *g, float *b) {

    int i;
	float f, p, q, t;
	if( s == 0 ) {
		// achromatic (grey)
		*r = *g = *b = v;
		return;
	}
	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );
	switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}
}