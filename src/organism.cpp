#include <random>
#include <iostream>
#include <time.h>
#include "settings.h"
#include "organism.h"

using std::cout;

//public function to create an orgnaism
void Organism::create_organism() {
    start_position();
}

//Randomly selects start position along edge of surface
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

//Moves organism. If on wall and moves toward wall will move opposite direction
void Organism::move() {
    switch (rand() % 5)
    {
    case 0:
        primary_direction();
        break;
    case 1:
        if (x_pos == surfaceWidth - 1) {
            x_pos -= 1;
            break;
        }
        x_pos += 1;
        break;
    case 2:
        if (x_pos == 0) {
            x_pos += 1;
            break;
        }
        x_pos -= 1;
        break;
    case 3:
        if (y_pos == surfaceHeight - 1) {
            y_pos -= 1;
            break;
        }
        y_pos +=1;
        break;
    case 4:
        if (y_pos == 0) {
            y_pos += 1;
            break;
        }
        y_pos -= 1;
        break;
    default:
        cout << "Error: rand() % 5 value outside expected range";
        break;
    }
}

//Increased chance in moving towards opposite wall they started L->R, T->B ...
void Organism::primary_direction() {
    switch (start)
    {
    case 'L':
        if (x_pos == surfaceWidth - 1) {
            x_pos -= 1;
            break;
        }
        x_pos += 1;
        break;
    case 'R':
        if (x_pos == 0) {
            x_pos += 1;
            break;
        }
        x_pos -= 1;
        break;
    case 'T':
        if (y_pos == surfaceHeight - 1) {
            y_pos -= 1;
            break;
        }
        y_pos += 1;
        break;
    case 'B':
        if (y_pos == 0) {
            y_pos += 1;
            break;
        }
        y_pos -= 1;
        break;
    default:
        cout << "Error: non-inilizted start chracter";
        break;
    }
}