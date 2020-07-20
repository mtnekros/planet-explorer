#include "planet.h"
#include "splashkit.h"

#include "player.h"
#include <string>

using namespace std;

/**
 * The ship bitmap function converts a ship kind into a 
 * bitmap that can be used.
 * 
 * Not exposed by the header.
 * 
 * @param kind  The kind of ship you want the bitmap of
 * @return      The bitmap matching this ship kind
 */
bitmap planet_bitmap(planet_kind kind)
{
    switch (kind)
    {
    case MERCURY:
        return bitmap_named("mercury");
    case VENUS:
        return bitmap_named("venus");
    case EARTH:
        return bitmap_named("earth");
    case MARS:
        return bitmap_named("mars");
    case JUPITER:
        return bitmap_named("jupiter");
    case URANUS:
        return bitmap_named("uranus");
    case SATURN:
        return bitmap_named("saturn");
    case NEPTUNE:
        return bitmap_named("neptune");
    default:
        return bitmap_named("pluto");
    }
}

planet_data new_planet(double x, double y)
{
    planet_data result;
    result.planet_visited = false;
    bitmap default_bitmap = planet_bitmap(static_cast<planet_kind>(rnd(9)));

    result.planet_sprite = create_sprite(default_bitmap);

    // Position in the centre of the initial screen
    sprite_set_x(result.planet_sprite,x);
    sprite_set_y(result.planet_sprite,y);
    
    return result;
}

bool planets_overlap(std::vector<planet_data>& planets, int lastIndex, sprite new_sprite)
{
    for (int i = 0; i < lastIndex; i++)
    {
        if ( sprite_collision( planets[i].planet_sprite,new_sprite ) )
        {
            return true;
        }
    }
    return false;
}

std::vector<planet_data> make_planets( int nPlanets )
{
    std::vector<planet_data> planets( nPlanets );
    for ( int i = 0; i < nPlanets; i++ )
    {
        planets[i].planet_visited = false;
        bitmap default_bitmap = planet_bitmap(static_cast<planet_kind>(rnd(9)));

        planets[i].planet_sprite = create_sprite(default_bitmap);
        const int scale = 5;
        point_2d pos;
        do
        {
            pos.x = screen_center().x + double(rnd(800)-400)*scale;
            pos.y = screen_center().y + double(rnd(600)-300)*scale;
            sprite_set_position( planets[i].planet_sprite,pos );
        } while ( planets_overlap( planets, i, planets[i].planet_sprite ) );
    }
    return planets;
}

void draw_planet( const planet_data &planet)
{
    float rotation = sprite_rotation(planet.planet_sprite);
    sprite_set_rotation(planet.planet_sprite, rotation + PLANET_ROTATE_SPEED);
    sprite_set_dx(planet.planet_sprite, PLANET_SPEED);
    draw_sprite(planet.planet_sprite);
}

void draw_planets( const std::vector<planet_data>& planets )
{
    for ( const planet_data& planet : planets )
    {
        draw_planet( planet );
        if ( planet.planet_visited )
        {
            const point_2d pos = sprite_position( planet.planet_sprite );
            draw_text("Visited!", color_light_cyan(),pos.x,pos.y );
        }
    }
}

void update_planet(planet_data &planet_to_update)
{
    // Apply movement based on rotation and velocity in the sprite
    update_sprite(planet_to_update.planet_sprite);
}

void update_planets( std::vector<planet_data>& planets )
{
    for ( planet_data& planet : planets )
    {
        update_planet( planet );
    }
}

