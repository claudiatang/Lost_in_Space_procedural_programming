#ifndef PROGRAM_MANAGER
#define PROGRAM_MANAGER

#include "splashkit.h"
#include "lost_in_space.h"
#include "user_interface.h"

/**
 * program manager data to store
 * information of game progress
 * 
 * @field  level 
 * @field  levels unlocked
 * @field  ship kinds unlocked
 * @field  game data
 * @field  continue next game
 * 
 */
struct program_manager
{
    game_level level;
    vector<game_level> levels_unlocked;
    vector<ship_kind> ships_unlocked;
    game_data game;
    bool continue_next_game;
};

/**
 * Retur a boolean value whether a queried level is unlocked
 * 
 * @param manager   program manager to store unlocked level array
 * @param level     level to be queried
 * @return true     returned value if level is unlocked
 * @return false    returned value if level is still locked 
 */
bool if_level_unlocked(const program_manager &manager, const game_level &level);

/**
 * Add a new unlocked value to the array of unlocked levels in program manager
 * 
 * @param manager   program manager to store unlocked level array 
 */
void add_unlocked_level(program_manager &manager);

/**
 * Add a new ship kind to the array of unlocked ship kinds in program manager
 * 
 * @param manager             program manager to store unlocked ship kinds array 
 * @param play_unlock_anim    boolean value whether to play unlock ship kind animation
 */
void add_unlocked_ship(program_manager &manager, bool &play_unlock_anim);

/**
 * Handle user clicking on level selection button 
 * 
 * @param manager 
 * @param button_to_check 
 * @param selected 
 */
void handle_select_level(program_manager &manager, const button &button_to_check, bool &selected);

/**
 * Set the initial unlocked level 
 *  
 * @param manager    program manager to store unlocked level array 
 */
void set_initial_unlocked_level(program_manager &manager);

/**
 * @brief Set the initial unlocked ship object
 * 
 * @param manager   program manager to store unlocked ship kind array
 */
void set_initial_unlocked_ship(program_manager &manager);

/**
 * Implement game music logic
 * 
 * @param game           the game to play the music
 * @param bgm            background music data for the game
 * @param finish_play    whether the game-play has finished
 */
void play_game_music(const game_data &game, const music bgm, bool &finish_play);

/**
 * Return a newly created program manager data
 * 
 * @return the program manager data to be returned 
 */
program_manager create_new_manager();

/**
 * Display game title screen
 * 
 */
void run_title_screen();

/**
 * Execute level selection stage
 * 
 * @param manager  program manager 
 */
void run_level_selection(program_manager &manager);

/**
 * Execute game play stage
 * 
 * @param manager  program manager
 */
void run_game_play(program_manager &manager);

/**
 * Execute post game scoreboard display stage
 * 
 * @param manager  program manager
 */
void run_post_game(program_manager &manager);

/**
 * Execute program manager
 * 
 * @param manager  program manager
 */
void run_program_manager(program_manager &manager);

#endif