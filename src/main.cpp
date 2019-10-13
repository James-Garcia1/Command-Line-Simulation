#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <random>
#include <map>
#include "settings.h"
#include "organism.h"

using std::cout;
using std::cin;
using std::vector;

//Creates a pointer vector to objects of class Organism that are on the heap
vector<Organism*> instance_organisms(const int numOrganisms, const vector<char> IDlist) {
    vector <Organism*> organisms;
    
    for (unsigned int i = 0; i < numOrganisms; ++i) {
        organisms.push_back(new Organism);
        organisms[i]->ID = IDlist[i];
    }

    return organisms;
}

//Creates 2D array on heap of the surface that will be outputed
void create_surface(char **surface, Settings s) {
    for (unsigned int i = 0; i < s.width; ++i) {
        surface[i] = new char[s.height];
        for (unsigned int j = 0; j < s.height; ++j){
            surface[i][j] = '-';
        }
    }
}

//Clears surface 2D array
void clear_surface(char **surface, Settings s) {
    for (unsigned int i = 0; i < s.width; ++i) {
        for (unsigned int j = 0; j < s.height; ++j){
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
    int food_height = s.height - 1;
    int food_width = s.width - 1;

    for(unsigned int i = 1; i < food_width; ++i) {
        for (unsigned int j = 1; j < food_height; ++j) {
            if (rand_food(s)) {
                surface[i][j] = '*';
            }
        }
    }   
}

//Output after generation
void generation_output(vector<char> IDlist) {
    int modeID;
    std::map<char,int> output_modes;
    for(auto& x : IDlist) {
        modeID = std::count(IDlist.begin(), IDlist.end(), x);
        output_modes[x] = modeID;
    }
    for(auto& [key, value]: output_modes) {
        cout << key << ": " << value << '\n';
    }
}

main() {
    //random seed so movement is random
    srand((unsigned)time(NULL));

    Settings s;
    int check = 1;
    int numOrganisms;
    vector<int> old_x_pos;
    vector<int> old_y_pos;
    vector<char> IDlist;
    char** surface = new char*[s.width];
    
    create_surface(surface, s);
    
    cout << "Enter initial number of organisms: ";
    cin >> numOrganisms;
    for (unsigned int i = 0; i < numOrganisms; ++ i){
        IDlist.push_back('A' + i);
    }
    auto listOrganisms = instance_organisms(numOrganisms, IDlist);

    //Till user exits
    for (unsigned int genCounter = 0; genCounter < s.numGenerations; ++genCounter) {
        
        create_food(surface, s);

        for (unsigned int i = 0; i < numOrganisms; ++i) {
            Organism* current = listOrganisms[i];
            current->create_organism();
            surface[current->x_pos][current->y_pos] = current->ID;
            old_x_pos.push_back (current->x_pos);
            old_y_pos.push_back (current->y_pos);
        }
        
        for (unsigned int dayCounter = 0; dayCounter < s.numDays; ++dayCounter) {
            //Outputs surface
            for (int i = 0; i < s.width; ++i) {
                for (int j = 0; j < s.height; ++j){
                    cout << surface[i][j];
                }
                cout << '\n';
            }
            
            //Moves Organism Objects, checks for food and replaces pre-movement position with '-'
        
            for (unsigned int i = 0; i < numOrganisms; ++i) {
                Organism* current = listOrganisms[i];
                current->move();
                current->food_check(surface);
                surface[current->x_pos][current->y_pos] = current->ID;
                surface[old_x_pos[i]][old_y_pos[i]] = '-';
                old_x_pos[i] = current->x_pos;
                old_y_pos[i] = current->y_pos;
            }
            cout << "continue? ";
            
            cin >> check;
        }
        
        IDlist.clear();
        old_x_pos.clear();
        old_y_pos.clear();

        for(int i = 0; i < numOrganisms; ++i) {
            Organism* current = listOrganisms[i];
            if (current->nour_and_return) {
                IDlist.push_back(current->ID);
                IDlist.push_back(current->ID);
            }
        }

        for (int i = 0; i < numOrganisms; ++i) {
            delete listOrganisms[i];
        }
        numOrganisms = IDlist.size();
        listOrganisms.clear();
        if (numOrganisms == 0) {
            cout << "All organisms died";
            break;
        }
        generation_output(IDlist);
        listOrganisms = instance_organisms(numOrganisms, IDlist); 
        clear_surface(surface, s);
    }

    //removes from heap
    for (int i = 0; i < s.width; ++i) {
        delete surface[i];
    }
    delete surface;
    
    for (int i = 0; i < numOrganisms; ++i) {
        delete listOrganisms[i];
    }
    
    return 0;
}
