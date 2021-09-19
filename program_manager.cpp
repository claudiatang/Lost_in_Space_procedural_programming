#include "splashkit.h"
#include "program_manager.h"

void set_game_level(program_manager &manager, const level_data &level)
{
    manager.new_game_level = level;
}

program_manager create_new_manager()
{
    program_manager manager;

    return manager;
}

void run_title_screen()
{
    int title_seconds;
    timer title_timer = create_timer("Title Timer");
    bitmap title_bgd = bitmap_named("title_screen_bgd");
    bitmap title_font = bitmap_named("title_font");

    start_timer("Title Timer");

    while (not quit_requested() && title_seconds < 3)
    {
        title_seconds = timer_ticks(title_timer) / 1000;

        clear_screen(COLOR_BLACK);

        draw_bitmap(title_bgd, 0, 0);
        draw_bitmap(title_font, screen_width() / 2 - bitmap_width(title_font) / 2, screen_height() / 2 - (2 * bitmap_height(title_font) / 3));

        refresh_screen(60);
    }

    free_timer(title_timer);
}

void run_level_selection(program_manager &manager)
{
    button level_one = create_new_button("level", "_1", 90, 185);
    button level_two = create_new_button("level", "_2", 495, 185);
    button level_three = create_new_button("level", "_3", 900, 185);
    bitmap selection_bgd = bitmap_named("title_screen_bgd");

    draw_bitmap(selection_bgd, 0, 0);
    draw_button(level_one);
    draw_button(level_two);
    draw_button(level_three);
}

void run_game_play(program_manager &manager)
{
    game_data new_game = create_new_game();

    new_game.player = new_player(screen_width(), screen_height());

    //set all initial numbers of player power ups to be 0
    for (int i = 0; i < new_game.player.player_power_ups.size(); i++)
    {
        new_game.player.player_power_ups[i].number = 0;
    }

    while (not quit_requested())
    {
        // Handle input to adjust player movement
        process_events();
        handle_input(new_game.player);

        update_game(new_game);

        // Redraw everything
        clear_screen(COLOR_BLACK);

        draw_game(new_game);

        refresh_screen(60);
    }


}

void run_modules()
{
    ;
}