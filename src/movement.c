#include <evosim.h>

void updateOrganismDirection(struct organism *firstOrganism, uint8_t speed) {
	if(speed == 0)
		return;

        struct organism *organism;
        SDL_Point newDir;

        organism = firstOrganism;

        while(organism != NULL) {
                if(organism->cycles == 0) {
                        if(rand() % 2 == 0)
                                newDir.x = -1;
                        else
                                newDir.x = 1;

                        if(rand() % 2 == 0)
                                newDir.y = -1;
                        else
                                newDir.y = 1;

                        if(rand() % 25 == 6)
                                newDir.x = 0;
                        if(rand() % 25 == 8)
                                newDir.y = 0;

                        if(organism->direction.x == newDir.x && organism->direction.y == newDir.y && (rand() % 2 == 1)) {
                                if(rand() % 2)
                                        newDir.x = -newDir.x;
                                else
                                        newDir.y = -newDir.y;
                        }

                        organism->direction = newDir;

                        organism->cycles = (rand() % (100/speed) + 1);
                }

                organism->cycles--;

                organism = organism->next;
        }
}

void moveOrganisms(SDL_Rect area, struct organism *firstOrganism, uint8_t speedFactor) {
        struct organism *organism;
	uint32_t speed;

        organism = firstOrganism;

        if(area.x == 0) {
                while(organism != NULL) {
			speed = organism->speed * (uint32_t)speedFactor;

                        if(((organism->body.x + organism->body.w) + organism->direction.x * speed > area.w
                                        || (organism->body.y + organism->body.h) + organism->direction.y * speed > area.h
                                        || organism->body.x + organism->direction.x * speed < area.x
                                        || organism->body.y + organism->direction.y * speed < 0)) {
                                organism->direction.x = -organism->direction.x;
                                organism->direction.y = -organism->direction.y;
                        }

                        organism->body.x += organism->direction.x * speed;
                        organism->body.y += organism->direction.y * speed;

                        organism = organism->next;
                }
        }

        else {
                while(organism != NULL) {
			speed = organism->speed * (uint32_t)speedFactor;

                        if(((organism->body.x + organism->body.w) + organism->direction.x * speed > (area.w + area.x)
                                        || (organism->body.y + organism->body.h) + organism->direction.y * speed > area.h
                                        || organism->body.x + organism->direction.x * speed < area.x
                                        || organism->body.y + organism->direction.y * speed < 0)) {
                                organism->direction.x = -organism->direction.x;
                                organism->direction.y = -organism->direction.y;
                        }

                        organism->body.x += organism->direction.x * speed;
                        organism->body.y += organism->direction.y * speed;

                        organism = organism->next;
                }
        }
}

SDL_Point randomPoint(SDL_Rect area) {
        SDL_Point p;

        p.x = rand() % (area.w - 100) + area.x;

        p.y = rand() % (area.h - 100);

        return p;
}

void reallocatePopulation(struct organism *firstOrganism, SDL_Rect area) {
        struct organism *organism;
        SDL_Point newLoc;

        organism = firstOrganism;

        while(organism != NULL) {
                if(area.w < organism->body.x) {
                        newLoc = randomPoint(area);
                        organism->body.x = newLoc.x;
                        organism->body.y = newLoc.y;
                }

                organism = organism->next;
        }
}

void migrateOrganism(int x, int y, struct organism **p1, struct organism **p2, SDL_Rect area1, SDL_Rect area2) {
        struct organism *organism, *prevOrganism, **originP, **targetP;
	SDL_Rect targetA;

	if(x >= area1.x && x <= (area1.x + area1.w) && y >= area1.y && y <= (area1.y + area1.w)) {
        	prevOrganism = *p1;
	        organism = *p1;

		originP = p1;
		targetP = p2;

		targetA = area2;
	} 
	else if(x >= area2.x && x <= (area2.x + area2.w) && y >= area2.y && y <= (area2.y + area2.w)) {
        	prevOrganism = *p2;
	        organism = *p2;

		originP = p2;
		targetP = p1;

		targetA = area1;
	}
	else
		return;

        while(organism != NULL) {
                if(x >= organism->body.x && x <= (organism->body.x + organism->body.w)
                                && y >= organism->body.y && y <= (organism->body.y + organism->body.h)) {
                        newOrganism(organism->aGenes, organism->cGenes, randomPoint(targetA), targetP);

                        if(organism == *originP)
                                *originP = organism->next;
                        else
                                prevOrganism->next = organism->next;

                        free(organism);

                        break;
                }

                prevOrganism = organism;

                organism = organism->next;
        }
}
