#ifndef USER_INTERFACE
#define USER_INTERFACE

#include <vector>
#include "splashkit.h"
#include "player.h"
#include "game_actors.h"

using std::string;
using std::vector;

/**
 * @field  button name
 * @field  button image
 * @field  button top left coordinate
 * @field  button bottom right coordinate
 * @field  button active or inactive
 * 
 */
struct button
{
    string name;
    bitmap image;
    point_2d top_left;
    point_2d bottom_right;
    bool active;
};

/**
 * Create and return a button type data for continue or exit the game
 * 
 * @param bitmap_name   image name
 * @param x             left most location of the button
 * @param y             top most location of the button
 * @param button_name   button name
 * @return button 
 */
button continue_exit_button(string bitmap_name, double x, double y, string button_name);

/**
 * Create and return a button type data for selecting levels
 * 
 * @param bitmap_name   image name
 * @param x             left most location of the button
 * @param y             top most location of the button
 * @param button_name   button name
 * @return button 
 */
button level_selection_button(string str_stem, string str_num, double x, double y, bool is_active, string btn_name);

/**
 * Draw button on the screen
 * 
 * @param button_to_draw 
 */
void draw_button(const button &button_to_draw);

/**
 * Return a boolean value whether a location is within the button
 * 
 * @param button      button to be queried
 * @param input_loc   location to be queried
 * @return true       when the location is within the botton
 * @return false      when the location is outside the button
 */
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

/**
 * Draw Win or Game Over according to game result on the screen
 * 
 * @param finished   
 * @param win 
 */
void draw_game_play_finish(bool finished, bool win);

/**
 * Update bonus score points for the player
 * 
 * @param score             player score to start with
 * @param bonus             player bonus to be added on
 * @param score_to_update   player score to be updated
 */
void update_bonus_points(const int &score, const int &bonus, int &score_to_update);

/**
 * Draw adding bonus points animation
 * 
 * @param score_to_draw   score to be drawn
 * @param font_size       font size of the score
 * @param x               location x
 * @param y               location y
 */
void draw_bonus_points(const int &score_to_draw, int font_size, double x, double y);

/**
 * Draw post game scoreboard with information of
 * power ups that have been collect
 * player score and bonus points
 * time remained for the game
 * 
 * @param score_and_bonus 
 * @param game_power_up_kinds 
 * @param player 
 * @param continue_button 
 * @param exit_button 
 * @param sec_remained 
 */
void draw_post_game_scoreboard(const int &score_and_bonus, const vector<power_up_kind> &game_power_up_kinds, const player_data &player, const button &continue_button, const button &exit_button, int &sec_remained);

/**
 * play unlock ship animation
 * 
 * @param kind   the ship kind that is being unlocked
 */
void play_unlock_ship(const ship_kind &kind);

#endif