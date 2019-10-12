#ifndef ORGANISM_H
#define ORGANISM_H
#include "settings.h"

class Organism {
    public:
        int x_pos;
        int y_pos;
        void create_organism();
        void move();
    private:
        Settings s;
        int surfaceHeight = s.height;
        int surfaceWidth = s.width;
        char start;
        void start_position();
        void primary_direction();
} ;

#endif