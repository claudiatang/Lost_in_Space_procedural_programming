#ifndef GAME_ACTORS
#define GAME_ACTORS

#include "splashkit.h"
//#include "player.h"

#define SCREEN_BORDER 50

/**
 * Different power_up types.
 * Adjusts the image used.
 */
enum power_up_kind
{
    SHIELD,
    POWER,
    POTION,
    DROPS,
    DIAMOND,
    STAR,
    CASH,
    LEVEL,
    BULLET,
    COIN,
    HEART,
    MUSCLE,
    TIME
};

enum garbage_kind
{
    ASTEROID,
    BULB,
    TIN,
    TV
};

/**
 * Different fuel types.
 * Adjusts the image used.
 */
enum fuel_kind
{
    FUEL,
    BATTERY,
    NOS
};

/**
 * Power up data type contains all relevant information for each power up type.
 * 
 * @field   power_up_sprite   power up sprite, used to track and represent power up movement
 * @field   kind              current power up type
 */
struct power_up_data
{
    sprite power_up_sprite;
    power_up_kind kind;
};

/**
 * Space garbage data type contains all relevant information for each garbage type.
 * 
 * @field   grabage_sprite   used to track and represent garbage movement
 * @field   kind              current garbage type
 */
struct garbage_data
{
    sprite garbage_sprite;
    garbage_kind kind;
};

/**
 * Fuel data type contains all relevant information for each fuel type.
 * 
 * @field   fuel_sprite   used to track and represent fuel movement
 * @field   kind          current fuel type
 */
struct fuel_data
{
    sprite fuel_sprite;
    fuel_kind kind;
};

/**
 * The power up bitmap function converts a power up kind data into a 
 * power up bitmap that can be used.
 * 
 * @param kind  The kind of power up
 * @return bitmap  The bitmap matching this power up kind
 */
bitmap power_up_image(const power_up_kind &kind);

/**
 * takes a garbage kind data and return a corresponding 
 * garbage bitmap accordingly
 * 
 * @param kind   The kind of garbadge
 * @return bitmap  the bitmap matching the garbage kind
 */
bitmap garbage_image(const garbage_kind &kind);

/**
 * The fuel bitmap function converts a fuel kind data into
 * a fuel bitmap that can be used.
 * 
 * @param kind       the kind of fuel you
 * @return bitmap    the bitmap matching this fuel kind
 */
bitmap fuel_image(const fuel_kind &kind);

/**
 * This function return a a random location 
 * within the curent screen
 * as a point_2d data type
 * 
 * @return point_2d 
 */
point_2d scr_rnd_loc();

/**
 * Creates a new power up at the specified location.
 * 
 * @returns     The new power_up_data type
 */
power_up_data new_power_up(double x, double y, const power_up_kind &kind);

/**
 * Draw all the power ups in the game 
 * 
 * @param power_ups_to_draw 
 */
void draw_game_power_ups(const vector<power_up_data> &power_ups_to_draw);

fuel_data new_fuel(double x, double y, const fuel_kind &kind);

/**
 * draw fuels of the game
 * 
 * @param fuels_to_draw 
 */
void draw_game_fuels(const vector<fuel_data> &fuels_to_draw);

/**
 * Return a newly created barbage data type
 * 
 * @param x                garbage location x
 * @param y                garbage location y
 * @param kind             the kind of the garbage
 * @return garbage_data 
 */
garbage_data new_garbage(double x, double y, const garbage_kind &kind);

/**
 * draw garbages of the game
 * 
 * @param garbages_to_draw 
 */
void draw_garbages(const vector<garbage_data> &garbages_to_draw);

/**
 * Update actors of the game
 * 
 * @param sprite_to_update 
 */
void update_actor_sprite(sprite &sprite_to_update);

/**
 * Delete a power up from the game
 * according to passed in index
 * 
 * @param game    the game to delete the power up from
 * @param index   index of the power up to delete
 */
void delete_game_power_up(vector<power_up_data> &game_power_ups, int indx);

/**
 * Delete a fuel from the game
 * according to passed in index
 * 
 * @param game    the game to delete fuel from
 * @param indx    index of fuel to delete
 */
void delete_game_fuel(vector<fuel_data> &game_fuels, int indx);

#endif