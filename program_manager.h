#ifndef PROGRAM_MANAGER
#define PROGRAM_MANAGER

#include "splashkit.h"
#include "lost_in_space.h"
#include "user_interface.h"

struct program_manager
{
    level_data new_game_level;
    vector<level_data> level_unlocked;
};

bool if_level_unlocked(const program_manager &manager, const level_data &level);

void add_unlocked_level(program_manager &manager, const game_data game_accomplished);

void handle_select_level(const button &button_to_check, program_manager &manager, bool &selected);

void set_initial_unlocked_level(program_manager &manager);

program_manager create_new_manager();

void run_title_screen();

void run_level_selection(program_manager &manager);

void run_game_play(program_manager &manager);

void run_post_game();

#endif