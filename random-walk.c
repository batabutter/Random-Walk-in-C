#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define DEFAULT_AGENTS 5
#define WIDTH 500
#define HEIGHT 500

#define FRAME_TIME 100.0f

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct {

    int x;
    int y;
    Uint32 color;
    

}Agent;

void draw_agents(Agent *agents, int num_agents, SDL_Surface *surface) {

    int dist = (rand() % (20 - 10 + 1) + 10);
    double dir_calc = ((double) rand() / (double) RAND_MAX);
    Direction dir = DOWN;
 
    if (dir_calc < .25)
        dir = UP;
    else if (dir_calc >= .25 && dir_calc <= .5)
        dir = DOWN;
    else if (dir_calc >.5 && dir_calc < .75)
        dir = LEFT;
    else {
        dir = RIGHT;
    }


    SDL_Rect rect;
    for (int i = 0; i < num_agents; i++) {
        
        switch (dir) {
            case DOWN:
                rect = (SDL_Rect) {agents[i].x, agents[i].y, 5, dist};
                agents[i].y = agents[i].y + dist;
            break;
            
            case LEFT:
                rect = (SDL_Rect) {agents[i].x - dist, agents[i].y, dist, 5};
                agents[i].x = agents[i].x - dist;
            break;
            
            case RIGHT:
                rect = (SDL_Rect) {agents[i].x, agents[i].y, dist, 5};
                agents[i].x = agents[i].x + dist;
            break;
            
            case UP:
                rect = (SDL_Rect) {agents[i].x, agents[i].y - dist, 5, dist};
                agents[i].y = agents[i].y - dist;
            break; 
        }
        SDL_FillRect (surface, &rect, agents[i].color); 
        SDL_Log("Drawing at %d, %d to (%d, %d))", rect.x, rect.y, agents[i].x, agents[i].y);
    }

}


int main(int argc, const char *argv[]) {
    
    int num_agents;    
    srand(time(NULL));

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
    
    uint32_t start_time;
    float frame_time;

    start_time = SDL_GetTicks();
    while (app_running) {
        
        frame_time = SDL_GetTicks() - start_time;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                app_running = 0;
            }
        }
       
        //SDL_Log("Delta (ms) : %f", frame_time);
        if (frame_time >= FRAME_TIME) {
            SDL_UpdateWindowSurface(pwindow);
            //SDL_Log("Updating the window");
            draw_agents(agents, 1, psurface);
            start_time = SDL_GetTicks();
        }
    }

    return 0;
}
