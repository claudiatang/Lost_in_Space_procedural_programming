#ifndef PROGRAM_MANAGER
#define PROGRAM_MANAGER

#include "splashkit.h"
#include "lost_in_space.h"
#include "user_interface.h"

// enum program_module
// {
//     TITLE_SCREEN,
//     LEVEL_SELECTION,
//     GAME_PLAY,
//     POST_GAME
// };

struct program_manager
{
    //program_module module;
    level_data new_game_level;
    vector<level_data> level_conquered;
};

void set_game_level(program_manager &manager, const level_data &level);

program_manager create_new_manager();

void run_title_screen();

void run_level_selection(program_manager &manager);

void run_game_play(program_manager &manager);

void run_modules();

#endif