#include <evosim.h>

void newOrganism(uint32_t genes1, uint32_t genes2, SDL_Point pos, struct organism **firstOrganism) {
        struct organism *New;

        New = (struct organism *)calloc(sizeof(struct organism), 1);

        newGenes(New, genes1, genes2);

        New->body.x = pos.x;
        New->body.y = pos.y;

        New->body.w = determineSize(New->aGenes);
        New->body.h = New->body.w;

        New->speed = determineSpeed(New->aGenes);

        New->color = determineColor(New->aGenes);

        New->growth = 0;

        New->single = true;

        New->next = NULL;

        addToOrganismList(New, firstOrganism);
}

void addToOrganismList(struct organism *New, struct organism **firstOrganism) {
        struct organism *organism;

        if(*firstOrganism == NULL) {
                *firstOrganism = New;
                return;
        }

        organism = *firstOrganism;

        while(organism->next != NULL) {
                organism = organism->next;
        }

        organism->next = New;
}

void printOrganismInfo(struct organism organism) {
        printf("genes: %x + %x\nsize %d x %d\npos %d %d\ndirection %d %d\nspeed %d\ncolor %d %d %d\nnext %p\n",
                        organism.aGenes, organism.cGenes, organism.body.w, organism.body.h, organism.body.x, organism.body.y,
                        organism.direction.x, organism.direction.y, organism.speed, organism.color.r, organism.color.g, organism.color.b,
                        organism.next);
}

void printOrganismList(struct organism *firstOrganism) {
        struct organism *organism;
        uint32_t i;

        i = 0;

        organism = firstOrganism;

        while(organism != NULL) {
                printf("organism %d:\n", i++);
                printOrganismInfo(*organism);

                organism = organism->next;
        }
}
