#include <random>
#include <iostream>
#include <time.h>
#include "settings.h"
#include "organism.h"

using std::cout;

//public function to create an orgnaism
void Organism::create_organism() {
    start_position();
    return;
}

//Randomly selects start position along edge of surface
void Organism::start_position() {
    switch (rand() % 4)
    {
    case 0:
        y_pos = rand() % surfaceWidth;
        x_pos = 0;
        start = 'L';
        break;
    case 1:
        y_pos = rand() % surfaceWidth;
        x_pos = surfaceHeight - 1;
        start = 'R';
        break;
    case 2:
        y_pos = 0;
        x_pos = rand() % surfaceHeight;
        start = 'T';
        break;
    case 3:
        y_pos = surfaceWidth - 1;
        x_pos = rand() % surfaceHeight;
        start = 'B';
        break;
    default:
        cout << "Error: rand() % 4 value outside expected range";
        break;
    }
    return;
}

/*Moves organism randomly Till organism gets food
with food organism moves to closest side*/
void Organism::move() {
    if (!nourished && !nour_and_return) {
        switch (rand() % 5)
        {
        case 0:
            primary_direction();
            break;
        case 1:
            if (x_pos == surfaceHeight - 1) {
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
            if (y_pos == surfaceWidth - 1) {
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
    else if (nourished && !nour_and_return) {
        switch (side) {
        case 'L':
            if (x_pos == 0) {
                nour_and_return = true;
                break;
            }
            x_pos -= 1;
            break;
        case 'R':
            if (x_pos == surfaceHeight - 1) {
                nour_and_return = true;
                break;
            }
            x_pos += 1;
            break;
        case 'T':
            if (y_pos == 0) {
                nour_and_return = true;
                break;
            }
            y_pos -= 1;
            break;
        case 'B':
            if (y_pos == surfaceWidth - 1) {
                nour_and_return = true;
                break;
            }
            y_pos += 1;
            break;
        default:
            cout << "Error: non-inilizted side chracter";
            break;
        }   
    }
    else if (nourished && nour_and_return){
        ;
    }
    return;
}

//Increased chance in moving towards opposite wall they started L->R, T->B ...
void Organism::primary_direction() {
    switch (start)
    {
    case 'L':
        if (x_pos == surfaceHeight - 1) {
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
        if (y_pos == surfaceWidth - 1) {
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
    return;
}

//Checks choosen move spot for food
void Organism::food_check(char** surface) {
    if (!nourished) {
        if (surface[x_pos][y_pos] == '*') {
            nourished = true;
            return_side();
        }
    }
    return;
}

//Chooses shortest return after getting food
void Organism::return_side() {
    int shortest_x, shortest_y;
    char side_x, side_y;
    if ((surfaceHeight - 1 - x_pos) > (x_pos - 0)) {
        shortest_x = x_pos;
        side_x = 'L';
    }
    else {
        shortest_x = surfaceHeight - 1 - x_pos;
        side_x = 'R';
    }
    if ((surfaceWidth - 1 - y_pos) > (y_pos - 0)) {
        shortest_y = y_pos;
        side_y = 'T';
    }
    else {
        shortest_y = surfaceWidth - 1 - y_pos;
        side_y = 'B';
    }
    if (shortest_x > shortest_y)
        side = side_y;
    else
        side = side_x;
    return;
}
