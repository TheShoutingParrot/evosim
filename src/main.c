#include <evosim.h>

SDL_Window *window;
SDL_Renderer *renderer;

int main(int argv, char *argc[]) {
	size_t capTime, frameTicks, cycle, gen, frame;
	uint8_t i, gSpeed;
	bool singleStep;

	SDL_Rect logicalRect, area1, area2;
	SDL_Event event;

	// organism population 1 is p1 and population 2 is p2
	// struct organism is a list of organisms
	struct organism *p1, *p2;

	logicalRect.x = logicalRect.y = 0;
	logicalRect.w = WINDOW_LOGICAL_WIDTH;
	logicalRect.h = WINDOW_LOGICAL_HEIGHT;

	// The area1 is the area of the screen taken up by population 1
	// in the two population mode the area1 is half of the screen and
	// the other half is area2
	area1 = logicalRect;

	p1 = p2 = NULL;

	cycle = 1;
	frame = 0;

	// The higher this value is the faster the game's speed is
	gSpeed = DEFAULT_SIM_SPEED;

	// By default single step mode is off, in it the organisms breed only manually
	// (by clicking the space bar)
	singleStep = false;
	gen = 1;

	srand((unsigned) time(NULL));

	// The following for-loop creates the first (by default 6) organisms
	for(i = 0; i < N_OF_ORGANISMS_AT_START; i++) {
		newOrganism(randomGenes(BASIC_GENES), randomGenes(BASIC_GENES), randomPoint(area1), &p1);
	}

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
							if(gSpeed >= 75);
							else
								gSpeed++;
							break;

						case SDLK_MINUS:
							if(gSpeed <= 1);
							else
								gSpeed--;
							break;

						case SDLK_RETURN:
							gSpeed = DEFAULT_SIM_SPEED;
							break;

						// Toggle single step mode
						case SDLK_s:
							singleStep = !singleStep;
							if(singleStep)
								puts("single step mode on");
							else
								puts("single step mode off");

							break;

						case SDLK_SPACE:
							if(!singleStep)
								break;

							breedOrganisms(&p1, area1);
							makeOrganismsSingle(p1);

							gen++;

							if(gen % 10 == 0)
								growOrganisms(&p1);

							SDL_Delay(1);

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

		updateOrganismDirection(p1, gSpeed);
		moveOrganisms(area1, p1, gSpeed);

		if(!singleStep) {
			if((cycle % (150/gSpeed)) == 0) {
				breedOrganisms(&p1, area1);
				gen++;
			}

			if(cycle % (450/gSpeed) == 0)
				makeOrganismsSingle(p1);

			if(cycle % (1500/gSpeed) == 0) {
				growOrganisms(&p1);

				cycle = 0;
			}

			cycle++;
		}

		drawOrganisms(p1);
		SDL_RenderPresent(renderer);

		frameTicks = (SDL_GetTicks() - capTime);
		if(frameTicks < TICKS_PER_FRAME)
			SDL_Delay(TICKS_PER_FRAME - frameTicks);

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
							if(gSpeed >= 75);
							else
								gSpeed++;
							break;

						case SDLK_MINUS:
							if(gSpeed <= 1);
							else
								gSpeed--;
							break;

						case SDLK_RETURN:
							gSpeed = DEFAULT_SIM_SPEED;
							break;

						// Toggle single step mode
						case SDLK_s:
							singleStep = !singleStep;
							if(singleStep)
								puts("single step mode on");
							else
								puts("single step mode off");

							break;

						case SDLK_SPACE:
							if(!singleStep)
								break;

							breedOrganisms(&p1, area1);
							breedOrganisms(&p2, area2);

							makeOrganismsSingle(p1);
							makeOrganismsSingle(p2);

							gen++;

							if(gen % 10 == 0) {
								growOrganisms(&p1);
								growOrganisms(&p2);
							}

							SDL_Delay(1);

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

		updateOrganismDirection(p1, gSpeed);
		updateOrganismDirection(p2, gSpeed);

		moveOrganisms(area1, p1, gSpeed);
		moveOrganisms(area2, p2, gSpeed);

		drawOrganisms(p1);
		drawOrganisms(p2);

		if(!singleStep) {
			if((cycle % (150/gSpeed)) == 0) {
				breedOrganisms(&p1, area1);
				breedOrganisms(&p2, area2);
				gen++;
			}

			if(cycle % (450/gSpeed) == 0) {
				makeOrganismsSingle(p1);
				makeOrganismsSingle(p2);
			}

			if(cycle % (1500/gSpeed) == 0) {
				growOrganisms(&p1);
				growOrganisms(&p2);

				cycle = 0;
			}

			cycle++;
		}

		SDL_RenderPresent(renderer);

		frameTicks = (SDL_GetTicks() - capTime);
		if(frameTicks < TICKS_PER_FRAME)
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
	}

	
exit:
	closeSdl();

	return EXIT_SUCCESS;
}
