#include <evosim.h>

void killOrganism(int x, int y, struct organism **firstOrganism, struct organism **p2) {
        struct organism *organism, *prevOrganism;

        prevOrganism = *firstOrganism;
        organism = *firstOrganism;

        while(organism != NULL) {
                if(x >= organism->body.x && x <= (organism->body.x + organism->body.w)
                                && y >= organism->body.y && y <= (organism->body.y + organism->body.h)) {
                        if(organism == *firstOrganism) {
                                *firstOrganism = organism->next;
                        }
                        else {
                                prevOrganism->next = organism->next;
                        }

                        free(organism);

                        return;
                }

                prevOrganism = organism;

                organism = organism->next;
        }

        if(p2 == NULL)
                return;

        prevOrganism = *p2;
        organism = *p2;

        while(organism != NULL) {
                if(x >= organism->body.x && x <= (organism->body.x + organism->body.w)
				 && y >= organism->body.y && y <= (organism->body.y + organism->body.h)) {
                        if(organism == *p2) {
                                *p2 = organism->next;
                        }
                        else {
                                prevOrganism->next = organism->next;
                        }

                        free(organism);

                        return;
                }

                prevOrganism = organism;

                organism = organism->next;
        }
}

void growOrganisms(struct organism **firstOrganism) {
        struct organism *organism, *prevOrganism;

        prevOrganism = *firstOrganism;
        organism = *firstOrganism;

        while(organism != NULL) {
                organism->growth++;

                if(organism->growth == ORGANISM_LIFESPAN) {
                        if(organism == *firstOrganism) {
                                *firstOrganism = organism->next;
                        }
                        else {
                                prevOrganism->next = organism->next;
                        }

                        free(organism);

                        organism = prevOrganism->next;
                }

                else {
                        prevOrganism = organism;

                        organism = organism->next;
                }

        }
}

void killHalf(struct organism *firstOrganism) {
        struct organism *prevOrganism, *organism;

        prevOrganism = firstOrganism;
        organism = firstOrganism->next;

        while(organism != NULL) {
                prevOrganism->next = organism->next;

                free(organism);

                if(prevOrganism->next == NULL)
                        break;

                prevOrganism = prevOrganism->next;
                organism = prevOrganism->next;
        }
}
