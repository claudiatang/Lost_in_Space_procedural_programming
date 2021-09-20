#ifndef LOST_IN_SPACE_PLAYER
#define LOST_IN_SPACE_PLAYER

#include "splashkit.h"
#include <vector>
#include "game_actors.h"

using namespace std;

#define PLAYER_SPEED 1.5
#define PLAYER_ROTATE_SPEED 3
#define SCREEN_BORDER 50

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
 * THe player power up data stores the 
 * power up kind and power up number
 * collected by the player
 * 
 * @field   kind    player's power up kind
 * @field   number  the number of this power up kind  
 * 
 */
struct player_power_up
{
    power_up_kind kind;
    int number;
};

/**
 * The player data keeps track of all of the information related to the player.
 * 
 * @field   player_sprite   The player's sprite - used to track position and movement
 * @field   score           The current score for the player
 * @field   kind            Current kind of player ship
 * @field   fuel_pct        player ship fuel status
 * @field   player_pu_nums  numbers of different power ups collected by the player
 */
struct player_data
{
    sprite player_sprite;
    int score;
    ship_kind kind;
    double fuel_pct;
    vector<player_power_up> player_power_ups;
};

/**
 * The ship bitmap function converts a ship kind into a 
 * bitmap that can be used.
 * 
 * Not exposed by the header.
 * 
 * @param kind  The kind of ship you want the bitmap of
 * @return      The bitmap matching this ship kind
 */
bitmap ship_bitmap(ship_kind kind);

/**
 * @brief 
 * 
 * @param  kind     ship kind
 * @return string   a string of the ship kind
 */
string ship_icon_string(ship_kind kind);

/**
 * Creates a new player in the centre of the screen with the default ship.
 * 
 * @returns     The new player data
 */
player_data new_player(int screen_x, int screen_y);

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
 * Switch the ship kind - will adjust which layer is hidden/shown
 */
void player_switch_ship(player_data &player, ship_kind target);

/**
 * Read user input and update the player based on this interaction.
 * 
 * @param player    The player to update
 */
void handle_input(player_data &player);

#endif