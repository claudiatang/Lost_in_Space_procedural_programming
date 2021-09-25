#ifndef USER_INTERFACE
#define USER_INTERFACE

#include <vector>
#include "splashkit.h"
#include "player.h"
#include "game_actors.h"

using std::string;
using std::vector;

struct button
{
    string name;
    bitmap image;
    point_2d top_left;
    point_2d bottom_right;
    bool active;
};

button continue_exit_button(string bitmap_name, double x, double y, string button_name);

button level_selection_button(string str_stem, string str_num, double x, double y, bool is_active, string btn_name);

void draw_button(const button &button_to_draw);

bool loc_within_button(const button &button, point_2d input_loc);

string format_time(int &seconds);

/**
 * Draw fuel bar and related text display.
 * 
 * @param player 
 * @param x        the top left corner x location of pct bar  
 * @param y        the top left corner y location of pct bar
 */
void draw_pct_bar(const double &fuel_pct, double x, double y);

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
void draw_ship_icon(const player_data &player, const ship_kind &kind, bool ship_unlocked, double x, double y);

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
void draw_minimap(const vector<power_up_data> &power_ups, const vector<fuel_data> &fuels, const vector<garbage_data> &garbages, const player_data &player, double x, double y, int map_width, int map_height);

/**
 * Draw a specified power up icon and display the collected number. 
 * 
 * @param power_up_kind   The kind of the power up
 * @param power_up_num    the number of the power up that the player has
 * @param x               
 * @param y 
 */
void draw_power_up_summary(const power_up_kind &power_up_kind, int power_up_num, double x, double y);

/**
 * Draw player score on the screen
 * 
 * @param player game player
 */
void draw_score(const int &player_score, double x, double y);

void draw_time_remained(int &seconds_remained, int font_size, double x, double y);

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
void draw_hud(const player_data &player, const vector<power_up_data> &game_power_ups, const vector<fuel_data> &game_fuels, const vector<garbage_data> &game_garbages, const vector<power_up_kind> &game_power_up_kinds, int seconds_remained);

void draw_game_play_finish(bool finished, bool win);

void update_bonus_points(const int &score, const int &bonus, int &score_to_update);

void draw_bonus_points(const int &score_to_draw, int font_size, double x, double y);

void draw_post_game_scoreboard(const int &score_and_bonus, const vector<power_up_kind> &game_power_up_kinds, const player_data &player, const button &continue_button, const button &exit_button, int &sec_remained);

void play_unlock_ship(const ship_kind &kind, int &count);

#endif