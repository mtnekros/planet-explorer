#ifndef ASTEROID
#define ASTEROID

#include "splashkit.h"
#include <vector>

struct Asteroid
{
    sprite a_sprite;
    float vel_x         = 0.0f;
    float vel_y         = 0.0f;
    float deltaRotation = 0.0f;
};

bool asteroids_overlaps(std::vector<Asteroid>& asteroids, int lastIndex, sprite new_sprite);

std::vector<Asteroid> make_asteroids(int nAsteroids);

void update_asteroids(std::vector<Asteroid>& asteroids);

void draw_asteroids(std::vector<Asteroid>& asteroids);

#endif
