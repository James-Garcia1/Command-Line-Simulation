# Command-Line-Simulation

A small simulation where a user-inputted number of "organisms" have a certain number of days to get food and return to the edge of the map. These organisms spawn on the outer edge of the map and have random movement that favors the opposite edge that they spawned on; L->R, T->B. etc. After retriving food organisms moves toward the closest edge and "exit" the map. Once the day counter is reached the next generation starts and new food is spawned as well as each organism that retrieved food and exited duplicating and each organism that did not "dying". Lastly, the population size is outputed. Once every generation has run program exits.

Change settings in settings.h.

Run with any c++ compiler with the command: g++ -std=c++17 main.cpp organism.cpp manage.cpp
