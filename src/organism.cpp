#include <random>
#include <iostream>
#include <time.h>

using std::cout;

class Organism {
    public:
        int x_pos;
        int y_pos;
        int surfaceHeight;
        int surfaceWidth;
        char gene;
        char start;
        void create_organism(int height, int width);
        void move();
    private:
        void start_position();
        void primary_direction();
} ;

void Organism::create_organism(int height, int width) {
    surfaceHeight = height;
    surfaceWidth = width;
    start_position();
}

void Organism::start_position() {
    switch (rand() % 4)
    {
    case 0:
        y_pos = rand() % surfaceHeight;
        x_pos = 0;
        start = 'L';
        break;
    case 1:
        y_pos = rand() % surfaceHeight;
        x_pos = surfaceWidth - 1;
        start = 'R';
        break;
    case 2:
        y_pos = 0;
        x_pos = rand() % surfaceWidth;
        start = 'T';
        break;
    case 3:
        y_pos = surfaceHeight - 1;
        x_pos = rand() % surfaceWidth;
        start = 'B';
        break;
    default:
        cout << "Error: rand() % 4 value outside expected range";
        break;
    }
}

void Organism::move() {
    switch (rand() % 6)
    {
    case 0:
    case 1:
        primary_direction();
        break;
    case 2:
        if (x_pos == surfaceWidth - 1)
            break;
        x_pos += 1;
        break;
    case 3:
        if (x_pos == 0)
            break;
        x_pos -= 1;
        break;
    case 4:
        if (y_pos == surfaceHeight - 1)
            break;
        y_pos +=1;
        break;
    case 5:
        if (y_pos == 0)
            break;
        y_pos -= 1;
        break;
    default:
        cout << "Error: rand() % 6 value outside expected range";
        break;
    }
}

void Organism::primary_direction() {
    switch (start)
    {
    case 'L':
        if (x_pos == surfaceWidth - 1)
            break;
        x_pos += 1;
        break;
    case 'R':
        if (x_pos == 0)
            break;
        x_pos -= 1;
        break;
    case 'T':
        if (y_pos == surfaceHeight - 1)
            break;
        y_pos += 1;
        break;
    case 'B':
        if (y_pos == 0)
            break;
        y_pos -= 1;
        break;
    default:
        cout << "Error: non-inilizted start chracter";
        break;
    }
}
