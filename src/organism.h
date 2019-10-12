#ifndef ORGANISM_H
#define ORGANISM_H
#include "settings.h"

class Organism {
    public:
        int x_pos;
        int y_pos;
        bool nourished = false;
        bool nour_and_return = false;
        void create_organism();
        void move();
        void food_check(char** surface);
    private:
        Settings s;
        int surfaceHeight = s.height;
        int surfaceWidth = s.width;
        char side;
        char start;
        void start_position();
        void primary_direction();
        void return_side();
} ;

#endif
