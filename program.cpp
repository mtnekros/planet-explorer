#include "splashkit.h"
#include "player.h"
#include "planet.h"
#include <string>
#include "asteroid.h"
using namespace std;


/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

//function for displaying the HUD
void draw_bar(player_data &player, point_2d initial_center);
/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */

struct CoinAnimation {
    bitmap coin_bmp;
    animation_script script;
    animation coinSpin;
    drawing_options opt;
    timer animation_timer;
};

CoinAnimation make_coin_animation()
{
    CoinAnimation coin_anim;
    // adding bitmap and it's details
    coin_anim.coin_bmp = load_bitmap("CoinBmp", "gold_coin.png");
    bitmap_set_cell_details(coin_anim.coin_bmp, 26, 26, 6, 1, 6);
    // loading script
    coin_anim.script = load_animation_script("Spinning", "coin_animation.txt");
    //create the animation coinSpin 
    coin_anim.coinSpin =create_animation(coin_anim.script, "Spinning");
    //create a drawing option for coin animation
    coin_anim.opt = option_with_animation(coin_anim.coinSpin);
    // adding animationTimer
    coin_anim.animation_timer = create_timer("animate_timer");

    return coin_anim;
};

void trigger_animation_start( CoinAnimation& anim )
{
    if( !timer_started(anim.animation_timer) )
    {
        start_timer( anim.animation_timer );
    }
    else
    {
        reset_timer( anim.animation_timer );
    }
}

void draw_animation_if_started( CoinAnimation& anim )
{
    if ( timer_started(anim.animation_timer) && timer_ticks(anim.animation_timer) < 1000 )
    {
        update_animation(anim.coinSpin);
        draw_bitmap(anim.coin_bmp, screen_center().x - 26, screen_center().y, anim.opt);
        draw_bitmap(anim.coin_bmp, screen_center().x, screen_center().y, anim.opt);
        draw_bitmap(anim.coin_bmp, screen_center().x + 26, screen_center().y, anim.opt);
    }
    else
    {
        reset_timer(anim.animation_timer);
        stop_timer(anim.animation_timer);
    }
}

int main()
{
    open_window("Lost In Space", 800, 600);
    load_resources();
    const point_2d initial_center = screen_center();
    CoinAnimation coin_animation = make_coin_animation();
    std::vector<planet_data> planets = make_planets(20);
    player_data player = new_player();
    std::vector<Asteroid> asteroids = make_asteroids( 40 );

    bool gameIsWon = false;
    while ( not quit_requested()  )
    {
        process_events();
        // handle input, discovery and collision only if player is alive or game not won
        if ( player_is_alive(player) && !gameIsWon )
        {
            // Handle input to adjust player movement
            handle_input(player);
            bool newPlanetDiscovered = handle_planet_discovery( player, planets );
            if (newPlanetDiscovered)
            {
                trigger_animation_start( coin_animation );
            } 
            handle_asteroid_collision( player,asteroids );
            update_player(player);
        }
        
        
        // Perform movement and update the camera
        update_planets(planets);
        update_asteroids( asteroids );
        // check win conditions
        gameIsWon = player.score > 9;
        // Drawing section
        // Redraw everything
        clear_screen(COLOR_BLACK);
        draw_asteroids( asteroids );
        draw_planets(planets);
        draw_player(player);
        draw_bar(player, initial_center);
        //animation
        draw_animation_if_started( coin_animation );
        if ( gameIsWon )
        {
            draw_text("********** YOU WON!!! **********", color_white(), screen_center().x-108, screen_center().y );
        }
        if ( !player_is_alive(player) )
        {
            draw_text("********** YOU DIED!!! **********", color_white(), screen_center().x-115, screen_center().y );
        }
        
        refresh_screen(60);
    }
    return 0;
}

void draw_bar(player_data &player, point_2d initial_center)
{
    bitmap bar = bitmap_named("empty_bar");
    bitmap bari = bitmap_named("green_bar");

    fill_rectangle(COLOR_YELLOW, 0, 0, screen_width(), 60,option_to_screen());
    draw_text("SCORE: " + to_string(player.score) , COLOR_BLACK, bitmap_width(bar), 10, option_to_screen());
    draw_text("LOCATION: " + point_to_string(center_point(player.player_sprite)), COLOR_BLACK, bitmap_width(bar), 20, option_to_screen());
    const double distance = point_point_distance(sprite_position( player.player_sprite ), initial_center); 
    draw_text("DISTANCE FROM CENTER: " + to_string(distance)  , COLOR_BLACK, bitmap_width(bar), 30, option_to_screen());
    draw_text("ALL PLANETS ARE WITHIN 4000 PTS DISTANCE.",COLOR_BLACK, bitmap_width(bar), 40, option_to_screen());
    draw_bitmap(bar,0,0, option_to_screen());
    const float healthFractionLeft = player.health/MAX_HEALTH;

    drawing_options opn = option_part_bmp(0,0,bitmap_width(bar)*healthFractionLeft,bitmap_height(bar),option_to_screen ());
    draw_bitmap(bari,0,0, opn);
}