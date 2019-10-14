#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <random>
#include <map>
#include "settings.h"
#include "organism.h"
#include "manage.h"

using std::cout;
using std::cin;
using std::vector;

main() {
    //random seed so movement is random
    srand((unsigned)time(NULL));

    Settings s;
    int check = 1;
    int numOrganisms;
    vector<int> old_x_pos;
    vector<int> old_y_pos;
    vector<char> IDlist;
    char** surface = new char*[s.height];
    
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
        
        for (unsigned int dayCounter = 0; dayCounter < s.numDays && check != 0; ++dayCounter) {
            //Outputs surface
            for (int i = 0; i < s.height; ++i) {
                for (int j = 0; j < s.width; ++j){
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
            cout << "Nonzero int continue, 0 quit, Nonint auto-run: ";
            
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
    for (int i = 0; i < s.height; ++i) {
        delete surface[i];
    }
    delete surface;
    
    for (int i = 0; i < numOrganisms; ++i) {
        delete listOrganisms[i];
    }
    
    return 0;
}
