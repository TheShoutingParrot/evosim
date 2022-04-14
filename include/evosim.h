#ifndef _EVOSIM_H
#define _EVOSIM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>

#define	WINDOW_NAME		"evosim"

#define	WINDOW_LOGICAL_WIDTH 	1680
#define WINDOW_LOGICAL_HEIGHT	1050

#define TICKS_PER_FRAME		1000 / 45

#define LOG_V			SDL_LOG_CATEGORY_VIDEO
#define LOG_A			SDL_LOG_CATEGORY_APPLICATION

#define POS(x)			(((x) < 0) ? -(x) : (x))

#define BASIC_GENES		0x75469c01			// The basic genes are the genes that are used as the base of the first individuals
								// in binary the number is: 

#define MUTATION_CHANCE		10000				// Chance of mutating (1 / MUTATION_CHANCE)
#define BIODIVERSITY		10				// Chance of the basic gene mutating at the start (1 / BIODIVERSITY)

#define N_OF_ORGANISMS_AT_START	6				// The amount of organisms that are born with the BASIC_GENES (+ mutations) at the start

struct organism {
	SDL_Rect body;

	SDL_Point direction;
	uint8_t cycles;

	uint8_t growth;

	/* genes:
	 * 	bit 1-8: 	speed
	 * 	bit 9-10:	speed/size (affect speed and size)
	 * 	bit 11-16:	size
	 * 	bit 17-31:	color
	 * 	bit 32:		breeding/immobility
	 * */
	uint32_t aGenes;
	uint32_t cGenes;

	uint32_t speed;
	SDL_Color color;

	bool single;

	struct organism *next;
};

extern SDL_Window	*window;
extern SDL_Renderer	*renderer;

bool init(void);
void closeSdl(void);

void newOrganism(uint32_t genes1, uint32_t genes2, SDL_Point pos, struct organism **firstOrganism);
void addToOrganismList(struct organism *New, struct organism **firstOrganism);
void printOrganismInfo(struct organism organism);
void printOrganismList(struct organism *firstOrganism);
void drawOrganisms(struct organism *firstOrganism);
void updateOrganismDirection(struct organism *firstOrganism);
void moveOrganisms(SDL_Rect area, struct organism *firstOrganism);
void killOrganism(int x, int y, struct organism **firstOrganism, struct organism **p2);
void growOrganisms(struct organism **firstOrganism);

void breedOrganisms(struct organism **firstOrganism, SDL_Rect area);
void makeOrganismsSingle(struct organism *firstOrganism);

uint32_t randomGenes(uint32_t basicIndividual);
void newGenes(struct organism *organism, uint32_t g1, uint32_t g2);
int determineSize(uint32_t genes);
uint32_t determineSpeed(uint32_t genes);
SDL_Color determineColor(uint32_t genes);

SDL_Point randomPoint(SDL_Rect area);

void killHalf(struct organism *firstOrganism);

void reallocatePopulation(struct organism *firstOrganism, SDL_Rect area);

void migrateOrganism(int x, int y, struct organism **p1, struct organism **p2, SDL_Rect area);

#endif /* #ifndef _EVOSIM_H */
