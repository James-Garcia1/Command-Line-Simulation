#include <iostream>
#include <math.h>
#include <vector>
#include "class.cpp"

using std::cout;
using std::cin;
using std::vector;

vector<Organism*> instance_organisms(int numOrganisms) {
    vector <Organism*> organisms;

    for (unsigned int i = 0; i < numOrganisms; ++i) {
        organisms.push_back(new Organism);
    }

    return organisms;
}

void create_surface(char **surface, int height, int width) {
    for (int i = 0; i < height; ++i) {
        surface[i] = new char[width];
        for (int j = 0; j < width; ++j){
            surface[i][j] = '-';
        }
    }
}

main() {
    srand((unsigned)time(NULL));

    const int width = 10;
    const int height = 10;
    int check = 1;
    int numOrganisms;
    vector<int> old_x_pos;
    vector<int> old_y_pos;
    char** surface = new char*[height];
    
    create_surface(surface, height, width);

    cout << "Enter initial number of organisms: ";
    cin >> numOrganisms;
    vector<Organism*> listOrganisms = instance_organisms(numOrganisms);
    
    for (unsigned int i = 0; i < numOrganisms; ++i) {
        Organism* current = listOrganisms[i];
        current->create_organism(height, width);
        surface[current->x_pos][current->y_pos] = 'A' + i;
        old_x_pos.push_back (current->x_pos);
        old_y_pos.push_back (current->y_pos);    
    }
    
    while (check != 0) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j){
                cout << surface[i][j];
            }
            cout << '\n';
        }
        for (unsigned int i = 0; i < numOrganisms; ++i) {
            Organism* current = listOrganisms[i];
            current->move();
            surface[old_x_pos[i]][old_y_pos[i]] = '-';
            surface[current->x_pos][current->y_pos] = 'A' + i;
            old_x_pos[i] = current->x_pos;
            old_y_pos[i] = current->y_pos;
        }
        cout << "continue? ";
        cin >> check;
    } 
    
    for (int i = 0; i < height; ++i) {
        delete surface[i];
    }
    delete surface;

    for (int i = 0; i < numOrganisms; ++i) {
        delete listOrganisms[i];
    }
   
    return 0;
}
