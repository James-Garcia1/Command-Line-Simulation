#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include "organism.cpp"

using std::cout;
using std::cin;
using std::vector;

//Creates a pointer vector to objects of class Organism that are on the heap
vector<Organism*> instance_organisms(int numOrganisms) {
    vector <Organism*> organisms;

    for (unsigned int i = 0; i < numOrganisms; ++i) {
        organisms.push_back(new Organism);
    }

    return organisms;
}

//Creates 2D array on heap of the surface that will be outputed
void create_surface(char **surface, const int height, const int width) {
    for (unsigned int i = 0; i < width; ++i) {
        surface[i] = new char[height];
        for (int j = 0; j < height; ++j){
            surface[i][j] = '-';
        }
    }
}

main() {
    //random seed so movement is random
    srand((unsigned)time(NULL));
    
    //Size of surface plane
    const int width = 10;
    const int height = 7;
    
    int check = 1;
    int numOrganisms;
    vector<int> old_x_pos;
    vector<int> old_y_pos;
    char** surface = new char*[width];
    
    create_surface(surface, height, width);

    cout << "Enter initial number of organisms: ";
    cin >> numOrganisms;
    auto listOrganisms = instance_organisms(numOrganisms);
    
    //Places Organism objects on 2D surface keeps track of initial position in old_pos
    for (unsigned int i = 0; i < numOrganisms; ++i) {
        Organism* current = listOrganisms[i];
        current->create_organism(height, width);
        surface[current->x_pos][current->y_pos] = 'A' + i;
        old_x_pos.push_back (current->x_pos);
        old_y_pos.push_back (current->y_pos);
    }

    //Till user exits
    while (check != 0) {
        //Outputs surface
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j){
                cout << surface[i][j];
            }
            cout << '\n';
        }
        
        //Moves Organism Objects and replaces pre-movement position with '-'
       
        for (unsigned int i = 0; i < numOrganisms; ++i) {
            Organism* current = listOrganisms[i];
            current->move();
            surface[current->x_pos][current->y_pos] = 'A' + i;
            surface[old_x_pos[i]][old_y_pos[i]] = '-';
            old_x_pos[i] = current->x_pos;
            old_y_pos[i] = current->y_pos;
        }
        cout << "continue? ";
        
        cin >> check;
    } 
  
    //removes from heap
    for (int i = 0; i < height; ++i) {
        delete surface[i];
    }
    delete surface;

    for (int i = 0; i < numOrganisms; ++i) {
        delete listOrganisms[i];
    }
   
    return 0;
}
