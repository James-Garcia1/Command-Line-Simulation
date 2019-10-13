#ifndef SETTINGS_H
#define SETTINGS_H

struct Settings {
    //vertical length of area
    const int width = 14;
    //horizontal length of area
    const int height = 10;
    //percentage of food spawn on inner spaces
    const int foodFrequency = 25;
    //number of times simulation will reset and run for numDays
    const unsigned int numGenerations = 100;
    //number of times simulation will run between generations
    const unsigned int numDays = 20;
};

#endif
