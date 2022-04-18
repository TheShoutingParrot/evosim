#ifndef _EVOSIM_H
#define _EVOSIM_H

// header files
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>

// constants
#define	WINDOW_NAME		"evosim"

#define	WINDOW_LOGICAL_WIDTH 	1680
#define WINDOW_LOGICAL_HEIGHT	1050

#define TICKS_PER_FRAME		1000 / 30

#define LOG_V			SDL_LOG_CATEGORY_VIDEO
#define LOG_A			SDL_LOG_CATEGORY_APPLICATION

#define POS(x)			(((x) < 0) ? -(x) : (x))

#define BASIC_GENES		0x75469c00			// The basic genes are the genes that are used as the base of the first individuals

#define MUTATION_CHANCE		10000				// Chance of mutating (1 / MUTATION_CHANCE)
#define BIODIVERSITY		10				// Chance of the basic gene mutating at the start (1 / BIODIVERSITY)

#define N_OF_ORGANISMS_AT_START	6				// The amount of organisms that are born with the BASIC_GENES (+ mutations) at the start

#define ORGANISM_LIFESPAN	2				// The lifespan of the organism by default (1000 * (LIFESPAN + 1))

#define DEFAULT_SIM_SPEED	3				// The speed of the simulation, minimum is 1 and max is 75
#define SPEED_INCREASE_PER_GENE	0				// The amount of "increase" of the organisms speed per speed gene that is equals to 1

// variable and structure definitions

// Basic organism structure
struct organism {
	SDL_Rect body;

	SDL_Point direction;
	uint8_t cycles;						// The internal clock of the organism, only used in movement functions

	uint8_t growth;						// The "age" of the organism (dies naturally at ORGANISM_LIFESPAN)

	/* genes:
	 * 	bit 1-8: 	speed
	 * 	bit 9-10:	speed/size (affect speed and size)
	 * 	bit 11-16:	size
	 * 	bit 17-31:	color
	 * 	bit 32:		breeding/immobility
	 * */
	uint32_t aGenes;					// Genes that are "active" in the organism
	uint32_t cGenes;					// Genes that the organism is carrying

	uint32_t speed;
	SDL_Color color;

	bool single;						// True when the organism has already mated

	struct organism *next;
};

extern SDL_Window	*window;
extern SDL_Renderer	*renderer;

// Function prototypes

// src/init.c
bool init(void);
void closeSdl(void);
void drawOrganisms(struct organism *firstOrganism);

// src/life_cycle.c
void killOrganism(int x, int y, struct organism **firstOrganism, struct organism **p2);
void growOrganisms(struct organism **firstOrganism);
void killHalf(struct organism *firstOrganism);

// src/list.c 
void newOrganism(uint32_t genes1, uint32_t genes2, SDL_Point pos, struct organism **firstOrganism);
void addToOrganismList(struct organism *New, struct organism **firstOrganism);
void printOrganismInfo(struct organism organism);
void printOrganismList(struct organism *firstOrganism);

// src/movement.c
void updateOrganismDirection(struct organism *firstOrganism, uint8_t speed);
void moveOrganisms(SDL_Rect area, struct organism *firstOrganism, uint8_t speedFactor);
SDL_Point randomPoint(SDL_Rect area);
void reallocatePopulation(struct organism *firstOrganism, SDL_Rect area);
void migrateOrganism(int x, int y, struct organism **p1, struct organism **p2, SDL_Rect area1, SDL_Rect area2);

// src/reproduction.c
void breedOrganisms(struct organism **firstOrganism, SDL_Rect area);
void makeOrganismsSingle(struct organism *firstOrganism);
uint32_t randomGenes(uint32_t basicIndividual);
void newGenes(struct organism *organism, uint32_t g1, uint32_t g2);
int determineSize(uint32_t genes);
uint32_t determineSpeed(uint32_t genes);
SDL_Color determineColor(uint32_t genes);

#endif /* #ifndef _EVOSIM_H */
