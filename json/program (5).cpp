#include "splashkit.h"
#include "player.h"
#include "planet.h"
#include <string>
#include "asteriod.h"
using namespace std;


/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */
int main()
{
    open_window("Lost In Space", 800, 600);
    load_resources();

    bitmap bar = bitmap_named("empty_bar");
    bitmap bari = bitmap_named("green_bar");

    planet_data planet;
    planet = new_planet(PLANET_X, PLANET_Y);
   
    player_data player;
    player = new_player();

    // **************** YO LINE THAP *********************
    std::vector<Asteroid> asteroids = make_asteroids( 4 );
    
    while ( not quit_requested() )
    {
        // Handle input to adjust player movement
        process_events();
        handle_input(player);
       
       //Gets the center coordinates of player and planet
        point_2d player_center = center_point(player.player_sprite);
        point_2d planet_center = center_point(planet.planet_sprite);

        //calcutlates the distance  between player and planet
        float distance = point_point_distance(player_center, planet_center);

        // Perform movement and update the camera
        update_player(player);

        // Redraw everything
        clear_screen(COLOR_BLACK);
        player.score = 0;
        draw_bar(player, distance, bar, bari);
        
        // including something stationary - it doesn't move
        fill_rectangle(COLOR_WHITE, 400, 300, 10, 10);


        // update and draw the asteroids // ********** YO DUI LINE PANI THAP *******************
        update_asteroids( asteroids );
        draw_asteroids( asteroids );
        // draw and update planet
        draw_planet(planet);
        update_planet(planet);
        // as well as the player who can move
        draw_player(player);


        refresh_screen(60);
    }

    return 0;
}