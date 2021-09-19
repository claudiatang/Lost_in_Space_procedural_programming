#ifndef LOST_IN_SPACE_GAME
#define LOST_IN_SPACE_GAME

//#include <vector>
#include "splashkit.h"
//#include "player.h"
//#include "power_up.h"
#include "user_interface.h"

using std::string;
using std::vector;

/**
 * Enumerate data for different game levels
 * 
 */
enum level_data
{
    LEVEL_1,
    LEVEL_2,
    LEVEL_3
};

/**
 * data for timer and seconds
 * 
 */
struct time_data
{
    timer game_timer;
    int seconds_allowed;
    int seconds_elapsed;
    int seconds_remained;
};

/**
 * Game data keeps track of all of the information related to the game.
 * 
 * @field   level             level of the game
 * @field   time              store time allowed, time passed and time remaining of the game
 * @field   player            player data in the game
 * @field   power up kinds    all the power up kind the game has
 * @field   power ups         all the power ups data the game has
 */
struct game_data
{
    level_data level;
    time_data time;
    player_data player;
    vector<power_up_kind> power_up_kinds;
    vector<power_up_data> power_ups;
    vector<fuel_kind> fuel_kinds;
    vector<fuel_data> fuels;
    bool game_finished;
    bool game_won;
    bool game_exit;
};

/**
 * Add a power up of a certain kind to the player 
 * and increment player score accordingly
 * 
 * @param player  the player to whom the power up is to be added 
 * @param kind    the kind of the power up to be added to the player
 */
void add_player_power_up(player_data &player, power_up_kind &kind);

/**
 * Add a fuel of a certain kind to the player's fuel pct variable
 * 
 * @param player   the player to whom the fuel is to be added 
 * @param kind     the kind of fuel to be added to the player
 */
void add_player_fuel(player_data &player, fuel_kind &kind);

/**
 * Delete a power up from the game
 * according to passed in index
 * 
 * @param game    the game to delete the power up from
 * @param index   index of the power up to delete
 */
void delete_game_power_up(game_data &game, int indx);

/**
 * Delete a fuel from the game
 * according to passed in index
 * 
 * @param game    the game to delete fuel from
 * @param indx    index of fuel to delete
 */
void delete_game_fuel(game_data &game, int indx);

void update_game_status(game_data &game);

/**
 * update the game 
 * 
 * @param game  the game to update
 */
void update_game(game_data &game);

/**
 * Return a bitmap background image
 * according to game level
 * 
 * @param level     input game level data
 * @return bitmap   return a bitmap background for current game
 */
bitmap get_bgd_image(const level_data &level);

/**
 * Draw the in-game background of a game
 * 
 * @param game   the game that the background to be drawn to
 */
void draw_game_bgd(const game_data &game);

/**
 * Draw player, power ups and icons on the screen
 * 
 * @param game  the game to draw
 */
void draw_game(const game_data &game);

/**
 * Return a dynamic array of power up kinds that 
 * will appear in the game 
 * according to different game levels
 * 
 * @param level  game level
 * @return       vector<power_up_kind> 
 */
vector<power_up_kind> game_power_up_kinds(level_data &level);

/**
 * Add power up of the kinds that will appear in the game
 * to the dynamic array of game power ups 
 * 
 * @param game    the game that will be added power ups
 */
void add_game_power_ups(game_data &game);

/**
 * Return a dynamic array of fuel kinds that
 * will appear in the game
 * according to different game levels
 * 
 * @param level  game level
 * @return       vector<fuel_kind> 
 */
vector<fuel_kind> game_fuel_kinds(level_data &level);

/**
 * Add fuels of the kinds that will appear in the game
 * to the dynamic array of game fuels
 * 
 * @param game   the game that will be added fuels
 */
void add_game_fuels(game_data &game);

/**
 * Create a new game
 * 
 * @return a game_data struct as the new game 
 */
game_data create_new_game(level_data &level);

#endif