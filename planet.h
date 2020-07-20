#ifndef PLANET
#define PLANET

#include "splashkit.h"
#include <vector>

using namespace std;

#define PLANET_SPEED 0.001
#define PLANET_ROTATE_SPEED 0.1
#define PLANET_X 200
#define PLANET_Y 200


enum planet_kind
{
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE,
    PLUTO
};

struct planet_data
{
    sprite          planet_sprite;
    bool            planet_visited;
    planet_kind     p_kind;
};


planet_data new_planet(double x, double y);

std::vector<planet_data> make_planets( int nPlanets );

void draw_planet(const planet_data &planet_to_draw);

void draw_planets( const std::vector<planet_data>& planets );

void update_planet(planet_data &planet_to_update);

void update_planets( std::vector<planet_data>& planets );

#endif 