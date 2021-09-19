#include "splashkit.h"
//#include "player.h"
//#include "power_up.h"
#include "program_manager.h"
#include "lost_in_space.h"

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */
int main()
{
    program_manager new_manager = create_new_manager();

    load_resources();
    open_window("Lost In Space", 1280, 720);

    write_line("before title screen");
    run_title_screen();

    run_level_selection(new_manager);

    write_line("exit level selection before game play");
    run_game_play(new_manager);

    return 0;
}