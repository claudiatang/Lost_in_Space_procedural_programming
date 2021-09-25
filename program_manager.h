#ifndef PROGRAM_MANAGER
#define PROGRAM_MANAGER

#include "splashkit.h"
#include "lost_in_space.h"
#include "user_interface.h"

struct program_manager
{
    game_level level;
    vector<game_level> levels_unlocked;
    vector<ship_kind> ships_unlocked;
    game_data game;
    bool continue_next_game;
};

bool if_level_unlocked(const program_manager &manager, const game_level &level);

void add_unlocked_level(program_manager &manager);

void add_unlocked_ship(program_manager &manager, bool &play_unlock_anim);

void handle_select_level(program_manager &manager, const button &button_to_check, bool &selected);

void set_initial_unlocked_level(program_manager &manager);

void set_initial_unlocked_ship(program_manager &manager);

program_manager create_new_manager();

void run_title_screen();

void run_level_selection(program_manager &manager);

void run_game_play(program_manager &manager);

void run_post_game(program_manager &manager);

void run_program_manager(program_manager &manager);

#endif