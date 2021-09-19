#ifndef USER_INTERFACE
#define USER_INTERFACE

#include <vector>
#include "splashkit.h"
#include "player.h"
#include "power_up.h"

using std::string;
using std::vector;

struct button
{
    sprite button_sprite;
    bool active;
};

button create_new_button(string str_stem, string str_num, float x, float y);

void draw_button(button &button_to_draw);

void update_button(button &button_to_update);

string format_time(int seconds);

void draw_time_remained(int seconds_remained, double x, double y);

/**
 * Draw fuel bar and related text display.
 * 
 * @param player 
 * @param x        the top left corner x location of pct bar  
 * @param y        the top left corner y location of pct bar
 */
void draw_pct_bar(const player_data &player, double x, double y);

/**
 * Draw the icon for indicating the kind of ship being selected.
 * Icon displayed in colours when the correspondent ship kind is selected
 * Icon displayed in grey when the correspondent ship kind is not selected
 * 
 * @param player           the player data    
 * @param icon_ship_kind   The ship kind drawn on the icon
 * @param x                the top left corner x location of ship icon
 * @param y                the top left corner y location of ship icon
 */
void draw_ship_icon(const player_data &player, ship_kind icon_ship_kind, double x, double y);

/**
 * Takes a sprite and mini map width and height information
 * return a point 2D sprite coordinate on the mini map 
 * 
 * @param actor        sprites whose coordinate to be converted
 * @param map_width    mini map width
 * @param map_height   mini map height
 * @return point_2d    the converted coordinate on the mini map
 */
point_2d mini_map_coordinate(const sprite &actor, int map_width, int map_height);

/**
 * Draw minimap and print location data.
 * 
 * @param power_ups    power ups to be drawn on the mini map
 * @param fuels        fuels to be drawn on the mini map
 * @param player       the player to be drawn on the mini map
 * @param x            the top left corner x location of minimap
 * @param y            the top left corner y location of minimap
 * @param map_width    the width of minimap
 * @param map_height   the height of minimap
 */
void draw_minimap(const vector<power_up_data> &power_ups, const vector<fuel_data> &fuels, const player_data &player, double x, double y, int map_width, int map_height);

/**
 * Draw a specified power up icon and display the collected number. 
 * 
 * @param power_up_kind   The kind of the power up
 * @param power_up_num    the number of the power up that the player has
 * @param x               
 * @param y 
 */
void draw_power_up_icon(const power_up_kind &power_up_kind, int power_up_num, double x, double y);

/**
 * Draw player score on the screen
 * 
 * @param player game player
 */
void draw_score(const player_data &player);

/**
 * This function will take a player_data struct
 * and a queried power up kind
 * return the number of corresponding power up kind
 * belongs to the player
 * 
 * @param player 
 * @param kind 
 * @return the number of a power up kind the player has 
 */
int player_power_up_number(const player_data &player, const power_up_kind &kind);

/**
 * Draw the background of HUD, and lay other UI components 
 * on top of the background. 
 * 
 * @param game_player 
 * @param game_power_ups 
 * @param game_fuels 
 * @param game_power_up_kinds 
 */
void draw_hud(const player_data &game_player, const vector<power_up_data> &game_power_ups, const vector<fuel_data> &game_fuels, const vector<power_up_kind> &game_power_up_kinds);

void draw_game_play_finish(bool finished, bool win);

#endif