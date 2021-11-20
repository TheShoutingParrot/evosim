#include <evosim.h>

SDL_Window *window;
SDL_Renderer *renderer;

int main(int argv, char *argc[]) {
	size_t capTime, frameTicks, cycle, ticksPerFrame;
	SDL_Rect logicalRect, area1, area2;
	SDL_Event event;

	struct organism *p1, *p2;

	logicalRect.x = logicalRect.y = 0;
	logicalRect.w = WINDOW_LOGICAL_WIDTH;
	logicalRect.h = WINDOW_LOGICAL_HEIGHT;

	area1 = logicalRect;

	p1 = p2 = NULL;

	ticksPerFrame = TICKS_PER_FRAME;

	cycle = 1;

	newOrganism(0xc5460af2, 0xc546341f, randomPoint(area1), &p1);
	newOrganism(0x35463450, 0x3566349f, randomPoint(area1), &p1);
	newOrganism(0x45663400, 0x45665400, randomPoint(area1), &p1);
	newOrganism(0x45665430, 0x44665413, randomPoint(area1), &p1);
	newOrganism(0x45764401, 0x44664400, randomPoint(area1), &p1);
	newOrganism(0x45664421, 0x00460a12, randomPoint(area1), &p1);

	growOrganisms(&p1);

	init();

one_population:
	area1 = logicalRect;

	for(;;) {
		capTime = SDL_GetTicks();
		while(SDL_PollEvent(&event) != 0) {
			switch(event.type) {
				case SDL_QUIT:
					goto exit;

				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == SDL_BUTTON_LEFT) {
						killOrganism(event.button.x, event.button.y, &p1, NULL);
					}
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_h:
							killHalf(p1);

							break;
							
						case SDLK_PLUS:
							if(ticksPerFrame < 4);
							else
								ticksPerFrame -= 1;
							break;

						case SDLK_MINUS:
							ticksPerFrame += 1;
							break;

						case SDLK_RETURN:
							ticksPerFrame = TICKS_PER_FRAME;
							break;

						case SDLK_2:
							goto two_populations;
					}
					break;
			}
		}


		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0xcc, 0xcc, 0xcc, 0xff);
		SDL_RenderFillRect(renderer, &logicalRect);

		updateOrganismDirection(p1);
		moveOrganisms(area1, p1);
		drawOrganisms(p1);

		if(cycle % 50 == 0) {
			breedOrganisms(&p1, area1);
		}

		if(cycle % 150 == 0) {
			makeOrganismsSingle(p1);
		}

		if(cycle == 1000) {
			growOrganisms(&p1);

			cycle = 0;
		}

		SDL_RenderPresent(renderer);

		frameTicks = (SDL_GetTicks() - capTime);
		if(frameTicks < ticksPerFrame)
			SDL_Delay(ticksPerFrame - frameTicks);

		cycle++;
	}

two_populations:
	area1 = logicalRect;
	area1.w = area1.w/2 - 2;
	
	area2.x = logicalRect.w/2 + 2;
	area2.y = 0;
	area2.w = logicalRect.w/2 - 2;
	area2.h = logicalRect.h;

	reallocatePopulation(p1, area1);

	for(;;) {
		capTime = SDL_GetTicks();
		while(SDL_PollEvent(&event) != 0) {
			switch(event.type) {
				case SDL_QUIT:
					goto exit;

				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == SDL_BUTTON_LEFT) {
						killOrganism(event.button.x, event.button.y, &p1, &p2);
					}
					else if(event.button.button == SDL_BUTTON_RIGHT) {
						migrateOrganism(event.button.x, event.button.y, &p1, &p2, area2);
					}
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_h:
							killHalf(p1);
							killHalf(p2);

							break;
							
						case SDLK_PLUS:
							if(ticksPerFrame < 4);
							else
								ticksPerFrame -= 1;
							break;

						case SDLK_MINUS:
							ticksPerFrame += 1;
							break;

						case SDLK_RETURN:
							ticksPerFrame = TICKS_PER_FRAME;
							break;

						case SDLK_1:
							goto one_population;
					}
					break;
			}
		}


		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0xcc, 0xcc, 0xcc, 0xff);
		SDL_RenderFillRect(renderer, &area1);

		SDL_SetRenderDrawColor(renderer, 0xaa, 0xaa, 0xaa, 0xff);
		SDL_RenderFillRect(renderer, &area2);

		updateOrganismDirection(p1);
		updateOrganismDirection(p2);

		moveOrganisms(area1, p1);
		moveOrganisms(area2, p2);

		drawOrganisms(p1);
		drawOrganisms(p2);

		if(cycle % 50 == 0) {
			breedOrganisms(&p1, area1);
			breedOrganisms(&p2, area2);
		}

		if(cycle % 150 == 0) {
			makeOrganismsSingle(p1);
			makeOrganismsSingle(p2);
		}

		if(cycle == 1000) {
			growOrganisms(&p1);
			growOrganisms(&p2);

			cycle = 0;
		}

		SDL_RenderPresent(renderer);

		frameTicks = (SDL_GetTicks() - capTime);
		if(frameTicks < ticksPerFrame)
			SDL_Delay(ticksPerFrame - frameTicks);

		cycle++;
	}

	
exit:
	closeSdl();

	return EXIT_SUCCESS;
}
