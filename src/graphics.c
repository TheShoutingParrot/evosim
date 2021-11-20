#include <evosim.h>

bool init(void) {
	srand(time(NULL));

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(LOG_V, "Failed to initialize SDL: %s", SDL_GetError());
		return true;
	}

	window = SDL_CreateWindow(WINDOW_NAME,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WINDOW_LOGICAL_WIDTH, WINDOW_LOGICAL_HEIGHT,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if(window == NULL) {
		SDL_LogError(LOG_V, "Failed to create the window %s", SDL_GetError());
		return true;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if(renderer == NULL) {
                SDL_LogError(LOG_V, "Failed to create the renderer: %s", SDL_GetError());
                return true;
        }

        SDL_RenderSetLogicalSize(renderer, WINDOW_LOGICAL_WIDTH, WINDOW_LOGICAL_HEIGHT);
}

void closeSdl(void) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void drawOrganisms(struct organism *firstOrganism) {
	struct organism *organism;

	organism = firstOrganism;

	while(organism != NULL) {
		SDL_SetRenderDrawColor(renderer, organism->color.r, organism->color.g, organism->color.b, organism->color.a);
		SDL_RenderFillRect(renderer, &(organism->body));

		organism = organism->next;
	}
}
