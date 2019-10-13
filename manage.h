
#ifndef MANAGE_H
#define MANAGE_H
#include "settings.h"

std::vector<Organism*> instance_organisms(const int numOrganisms, const std::vector<char> IDlist);
void create_surface(char **surface, Settings s);
void clear_surface(char **surface, Settings s);
bool rand_food(Settings s);
void create_food(char **surface, Settings s);
void generation_output(std::vector<char> IDlist);

#endif