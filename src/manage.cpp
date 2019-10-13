#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <random>
#include <map>
#include "organism.h"
#include "manage.h"

//Creates a pointer vector to objects of class Organism that are on the heap
std::vector<Organism*> instance_organisms(const int numOrganisms, const std::vector<char> IDlist) {
    std::vector <Organism*> organisms;
    
    for (unsigned int i = 0; i < numOrganisms; ++i) {
        organisms.push_back(new Organism);
        organisms[i]->ID = IDlist[i];
    }

    return organisms;
}

//Creates 2D array on heap of the surface that will be outputed
void create_surface(char **surface, Settings s) {
    for (unsigned int i = 0; i < s.height; ++i) {
        surface[i] = new char[s.width];
        for (unsigned int j = 0; j < s.width; ++j){
            surface[i][j] = '-';
        }
    }
}

//Clears surface 2D array
void clear_surface(char **surface, Settings s) {
    for (unsigned int i = 0; i < s.height; ++i) {
        for (unsigned int j = 0; j < s.width; ++j){
            surface[i][j] = '-';
        }
    }
}

//Determine if space starts with food based of frequency
bool rand_food(Settings s) {
    int chance = rand() % 100;
    if (chance < s.foodFrequency){
        return true;
    }
    return false;
}

//Creates Food on surface
void create_food(char **surface, Settings s) {
    int food_height = s.width - 1;
    int food_width = s.height - 1;

    for(unsigned int i = 1; i < food_width; ++i) {
        for (unsigned int j = 1; j < food_height; ++j) {
            if (rand_food(s)) {
                surface[i][j] = '*';
            }
        }
    }   
}

//Output after generation
void generation_output(std::vector<char> IDlist) {
    int modeID;
    std::map<char,int> output_modes;
    for(auto& x : IDlist) {
        modeID = std::count(IDlist.begin(), IDlist.end(), x);
        output_modes[x] = modeID;
    }
    for(auto& [key, value]: output_modes) {
        std::cout << key << ": " << value << '\n';
    }
}
