#ifndef LOST_IN_SPACE_PLAYER
#define LOST_IN_SPACE_PLAYER

#include "splashkit.h"
#include "planet.h"
#include "asteroid.h"
#include <vector>

using namespace std;

#define PLAYER_SPEED 0.5
#define PLAYER_ROTATE_SPEED 3
#define SCREEN_BORDER 100
#define MAX_HEALTH 10

/**
 * Different options for the kind of ship.
 * Adjusts the image used.
 */
enum ship_kind
{
    AQUARII,
    GLIESE,
    PEGASI
};

/**
 * The player data keeps track of all of the information related to the player.
 * 
 * @field   player_sprite   The player's sprite - used to track position and movement
 * @field   score           The current score for the player
 * @field   kind            Current kind of player ship
 */
struct player_data
{
    sprite      player_sprite;
    int         score;
    ship_kind   kind;
    float         health = MAX_HEALTH;
};

/**
 * Creates a new player in the centre of the screen with the default ship.
 * 
 * @returns     The new player data
 */
player_data new_player();

/**
 * Draws the player to the screen. 
 * 
 * @param player_to_draw    The player to draw to the screen
 */
void draw_player(const player_data &player_to_draw);

/**
 * Actions a step update of the player - moving them and adjusting the camera.
 * 
 * @param player_to_update      The player being updated
 */
void update_player(player_data &player_to_update);

/**
 * Read user input and update the player based on this interaction.
 * 
 * @param player    The player to update
 */
void handle_input(player_data &player);

bool player_is_alive( player_data& player );

bool handle_planet_discovery( player_data& player, std::vector<planet_data>& planets );

void handle_asteroid_collision( player_data& player, std::vector<Asteroid>& planets );

#endif 