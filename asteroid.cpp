#include "asteroid.h"

bool asteroids_overlaps(std::vector<Asteroid>& asteroids, int lastIndex, sprite new_sprite)
{
    for (int i = 0; i < lastIndex; i++)
    {
        if ( sprite_collision( asteroids[i].a_sprite,new_sprite ) )
        {
            return true;
        }
    }
    return false;
}

std::vector<Asteroid> make_asteroids(int nAsteroids)
{
    std::vector<Asteroid> asteroids(nAsteroids);
    bitmap asteroid_bm = bitmap_named("asteroid");

    // Create the sprite with 3 layers - we can turn on and off based
    // on the ship kind selected
    for( int i = 0; i < nAsteroids; i++ )
    {
        asteroids[i].vel_x = (rnd(10)/100.0f - 0.05f) * 1.10f;
        asteroids[i].vel_y = (rnd(10)/100.0f - 0.05f)*1.10f;
        asteroids[i].deltaRotation = rnd(10)/10.0f - 0.5f;
        asteroids[i].a_sprite = create_sprite(asteroid_bm);
        point_2d pos;
  		const int scale = 5;
        do
        {
            pos.x = screen_center().x + double(rnd(800)-400)*scale;
            pos.y = screen_center().y + double(rnd(600)-300)*scale;
            sprite_set_position( asteroids[i].a_sprite,pos );
        } while ( asteroids_overlaps( asteroids, i, asteroids[i].a_sprite ) );
        
        sprite_set_velocity( asteroids[i].a_sprite, { asteroids[i].vel_x,asteroids[i].vel_y } );
    }
    // Position in the centre of the initial screen
    return asteroids;
}

void update_asteroids(std::vector<Asteroid>& asteroids)
{

    // Get the center of the 
    for( Asteroid& a: asteroids )
    {
        float rotation = sprite_rotation(a.a_sprite);
        // point_2d center = center_point(a.a_sprite);
        sprite_set_rotation(a.a_sprite, rotation+a.deltaRotation );
        update_sprite(a.a_sprite);
    }
}

void draw_asteroids(std::vector<Asteroid>& asteroids)
{
    for( Asteroid& a: asteroids )
    {
        draw_sprite(a.a_sprite);
    }
}