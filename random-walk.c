#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define DEFAULT_AGENTS 5
#define WIDTH 500
#define HEIGHT 500

typedef struct {

    int x;
    int y;
    Uint32 color;

}Agent;

void draw_agents(Agent *agents, int num_agents, SDL_Surface *surface) {

    int dist = (rand() % (20 - 10 + 1) + 10);
    double dir_calc = ((double) rand() / (double) RAND_MAX);
    int dir = 0;
   
    if (dir_calc > .5)
        dir = 1;
    else
        dir = 0;

    SDL_Rect rect;
    for (int i = 0; i < num_agents; i++) {
        
        if (dir) {
            rect = (SDL_Rect) {agents[i].x, agents[i].y, dist, 5};
            agents[i].x = agents[i].x + dist;
        } else {
            rect = (SDL_Rect) {agents[i].x, agents[i].y, 5, dist};
            agents[i].y = agents[i].y + dist;
        }
        SDL_FillRect (surface, &rect, agents[i].color); 
        SDL_Log("Drawing at %d, %d to (%d, %d))", rect.x, rect.y, agents[i].x, agents[i].y);
    }

}


int main(int argc, const char *argv[]) {
    
    int num_agents;    


    if (argc == 1) {
        num_agents = DEFAULT_AGENTS;
    }

    if (argc == 2) {
        num_agents = atoi(argv[1]);
        printf("Running with %d\n", num_agents);
    } else {
        printf("Usage: %s <num-of-agents>\n", argv[0]);
    }
    
    SDL_Window *pwindow = SDL_CreateWindow("Random Walk", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);

    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
        
    int app_running = 1;
    SDL_Event event; 

    Agent agents[1];
    agents[0] = (Agent) {100, 100, 0xFFFFFFFF};
    
    struct timespec start, end;
    
    timespec_get(&start, TIME_UTC);
    float delta_time;
    while (app_running) {
        
        timespec_get(&end, TIME_UTC);
        delta_time = (end.tv_nsec - start.tv_nsec) / 1000000.0f;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                app_running = 0;
            }
        }
       


       SDL_Log("Delta (ms) : %f", delta_time);
        if (delta_time >= 16.66f) {
            SDL_UpdateWindowSurface(pwindow);

            draw_agents(agents, 1, psurface);
            timespec_get(&start, TIME_UTC);
        }
    }

    return 0;
}
