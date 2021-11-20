#include <evosim.h>

void newGenes(struct organism *organism, uint32_t g1, uint32_t g2) {
        uint8_t i, j;

        organism->aGenes = 0;
        organism->cGenes = 0;

        for(i = 0; i < 32; i+=2) {
                if(g1 >> i & 1) {
                        if(rand() % MUTATION_CHANCE == 3);
                        else
                                organism->aGenes = organism->aGenes | (1 << i);

                        if(rand() % MUTATION_CHANCE == 6) {
                                organism->cGenes = organism->cGenes | (!(g2 >> i & 1) << i);
                        }
                        else
                                organism->cGenes = organism->cGenes | ((g2 >> i & 1) << i);
                }
                else if(g2 >> i & 1) {
                        if(rand() % MUTATION_CHANCE == 9);
                        else
                                organism->aGenes = organism->aGenes | (1 << i);

                        if(rand() % MUTATION_CHANCE == 12) {
                                organism->cGenes = organism->cGenes | (!(g1 >> i & 1) << i);
                        }
                        else
                                organism->cGenes = organism->cGenes | ((g1 >> i & 1) << i);
                }
        }

	for(i = 1; i < 32; i+=2) {
                if(!(g1 >> i & 1)) {
                        if(rand() % MUTATION_CHANCE == 2) {
                                organism->aGenes = organism->aGenes | 1 << i;
                        }

                        if(rand() % MUTATION_CHANCE == 4) {
                                organism->cGenes = organism->cGenes | (!(g2 >> i & 1) << i);
                        }
                        else {
                                organism->cGenes = organism->cGenes | ((g2 >> i & 1) << i);
                        }
                }
                else if(!(g2 >> i & 1)) {
                        if(rand() % MUTATION_CHANCE == 6) {
                                organism->aGenes = organism->aGenes | 1 << i;
                        }

                        if(rand() % MUTATION_CHANCE == 8) {
                                organism->cGenes = organism->cGenes | (!(g1 >> i & 1) << i);
                        }
                        else {
                                organism->cGenes = organism->cGenes | ((g1 >> i & 1) << i);
                        }
                }
                else {
                        if(rand() % MUTATION_CHANCE == 10);
                        else
                                organism->aGenes = organism->aGenes | (1 << i);

                        if(rand() % MUTATION_CHANCE == 12);
			else
                                organism->cGenes = organism->cGenes | (1 << i);
                }

        }
}

uint32_t parentGenes(uint32_t g1, uint32_t g2) {
        uint32_t result;
        uint8_t genes, i;

        result = 0;
        genes = 16;

        if(rand() % 2) {
                for(i = 0; i < 32; i++) {
                        if(rand() % genes == 0 && genes != 0) {
                                result |= g1 & (1 << i);
                                genes--;
                        }
                        else
                                result |= g2 & (1 << i);
                }
        }

        else {
                for(i = 0; i < 32; i++) {
                        if(rand() % genes == 0 && genes != 0) {
                                result |= g2 & (1 << i);
                                genes--;
                        }
                        else
                                result |= g1 & (1 << i);
                }
        }

        return result;
}

int determineSize(uint32_t genes) {
        int size;
        uint8_t i;

        size = 20;

        for(i = 0; i < 8; i++) {
                if((genes >> (i + 8)) & 1) {
                        size += 8;
                }
        }

        return size;
}

uint32_t determineSpeed(uint32_t genes) {
        uint32_t speed;
        uint8_t i;

        speed = 1;

        for(i = 0; i < 10; i++) {
                if((genes >> (i)) & 1)
                        speed += 1;
        }

        if((genes & (1 << 31)))
                speed = 0;

        return speed;
}

SDL_Color determineColor(uint32_t genes) {
        SDL_Color color;
        uint8_t i;

        color.r = 0;
        color.g = 0;
        color.b = 0;
        color.a = 0xFF;

        for(i = 0; i < 5; i++) {
                if((genes >> (i+16)) & 1)
                        color.r += 0x33;
        }

        for(i = 0; i < 5; i++) {
                if((genes >> (i+21)) & 1)
                        color.g += 0x33;
        }

        for(i = 0; i < 5; i++) {
                if((genes >> (i+26)) & 1)
                        color.b += 0x33;
        }

        return color;
}

void breedOrganisms(struct organism **firstOrganism, SDL_Rect area) {
        struct organism *organism, *fOrganism, *potentialMate;
        int closest;

        fOrganism = *firstOrganism;

        while(fOrganism != NULL) {
                if(!fOrganism->single || fOrganism->growth == 0);
                else {
                        closest = 750;
                        organism = fOrganism->next;
                        while(organism != NULL) {
                                if(organism->growth == 0 || !organism->single);
                                else {
                                        if((POS(organism->body.x - fOrganism->body.x) + POS(organism->body.y - fOrganism->body.y)) < closest) {
                                                closest = POS(organism->body.x - fOrganism->body.x) + POS(organism->body.y - fOrganism->body.y);
                                                potentialMate = organism;
                                        }
                                }

                                organism = organism->next;
                        }

                        if(closest < 750) {
                                if(rand() % 2);
                                else {
                                        fOrganism->single = false;
                                        potentialMate->single = false;

                                        if((fOrganism->aGenes & (1 << 31)) && ((fOrganism->cGenes & (1 << 31)))) {
                                                uint8_t i;

                                                for(i = 0; i < (rand() % 5); i++) {
                                                        newOrganism(parentGenes(potentialMate->aGenes, potentialMate->cGenes),
                                                                parentGenes(fOrganism->aGenes, fOrganism->cGenes), randomPoint(area), firstOrganism);
                                                }
                                        }
                                        else
                                                newOrganism(parentGenes(potentialMate->aGenes, potentialMate->cGenes),
                                                        parentGenes(fOrganism->aGenes, fOrganism->cGenes), randomPoint(area), firstOrganism);
                                }
                        }
                }

                fOrganism = fOrganism->next;
        }
}

void makeOrganismsSingle(struct organism *firstOrganism) {
        struct organism *organism;

        organism = firstOrganism;

        while(organism != NULL) {
                organism->single = true;
                organism = organism->next;
        }
}
