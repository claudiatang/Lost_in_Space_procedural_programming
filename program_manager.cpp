#include "splashkit.h"
#include "program_manager.h"

bool if_level_unlocked(const program_manager &manager, const level_data &level)
{
    bool if_unlocked = false;

    for (int i = 0; i < manager.level_unlocked.size(); i++)
    {
        if (level == manager.level_unlocked[i])
        {
            if_unlocked = true;
        }
    }

    return if_unlocked;
}

void add_unlocked_level(program_manager &manager, const game_data game_accomplished)
{
    bool add_new_unlocked = true;

    for (int i = 0; i < manager.level_unlocked.size(); i++)
    {
        if (static_cast<int>(game_accomplished.level) + 1 == static_cast<int>(manager.level_unlocked[i]))
        {
            add_new_unlocked = false;
        }
    }

    if (add_new_unlocked == true)
    {
        manager.level_unlocked.push_back(static_cast<level_data>(static_cast<int>(game_accomplished.level) + 1));
    }
}

void handle_select_level(const button &button_to_check, program_manager &manager, bool &selected)
{
    selected = false;

    if (mouse_clicked(LEFT_BUTTON) && loc_within_button(button_to_check, mouse_position()) && button_to_check.active)
    {
        if (button_to_check.name == "level_one")
        {
            manager.new_game_level = LEVEL_1;
            selected = true;
        }
        else if (button_to_check.name == "level_two")
        {
            manager.new_game_level = LEVEL_2;
            selected = true;
        }
        else if (button_to_check.name == "level_three")
        {
            manager.new_game_level = LEVEL_3;
            selected = true;
        }
    }
}

void set_initial_unlocked_level(program_manager &manager)
{
    for (int i = 0; i < manager.level_unlocked.size(); i++)
    {
        manager.level_unlocked.pop_back();
    };

    manager.level_unlocked.push_back(LEVEL_1);
}

program_manager create_new_manager()
{
    program_manager manager;

    set_initial_unlocked_level(manager);

    return manager;
}

void run_title_screen()
{
    //int title_seconds;
    timer title_timer = create_timer("Title Timer");
    bitmap title_bgd = bitmap_named("title_screen_bgd");
    bitmap title_font = bitmap_named("title_font");

    start_timer("Title Timer");

    while (!quit_requested() && timer_ticks(title_timer) < 3000)
    {
        clear_screen(COLOR_BLACK);

        draw_bitmap(title_bgd, 0, 0);
        draw_bitmap(title_font, screen_width() / 2 - bitmap_width(title_font) / 2, screen_height() / 2 - bitmap_height(title_font) / 2);

        refresh_screen(60);
    }

    free_timer(title_timer);
}

void run_level_selection(program_manager &manager)
{
    write_line("step into level selection");
    bool level_selected = false;

    button level_one = create_new_button("level", "_1", 90, 185, if_level_unlocked(manager, LEVEL_1), "level_one");
    button level_two = create_new_button("level", "_2", 495, 185, if_level_unlocked(manager, LEVEL_2), "level_two");
    button level_three = create_new_button("level", "_3", 900, 185, if_level_unlocked(manager, LEVEL_3), "level_three");

    while (!quit_requested() && !level_selected)
    {

        process_events();
        handle_select_level(level_one, manager, level_selected);
        if (!level_selected)
        {
            handle_select_level(level_two, manager, level_selected);
        }
        if (!level_selected)
        {
            handle_select_level(level_three, manager, level_selected);
        }

        clear_screen(COLOR_BLACK);
        draw_bitmap("title_screen_bgd", 0, 0);
        draw_button(level_one);
        draw_button(level_two);
        draw_button(level_three);
        refresh_screen(60);
    }
}

void run_game_play(program_manager &manager)
{
    game_data new_game = create_new_game(manager.new_game_level);

    new_game.player = new_player(screen_width(), screen_height());

    //set all initial numbers of player power ups to be 0
    for (int i = 0; i < new_game.player.player_power_ups.size(); i++)
    {
        new_game.player.player_power_ups[i].number = 0;
    }

    while (!quit_requested() && !new_game.game_exit)
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

    if (new_game.game_won)
    {
        add_unlocked_level(manager, new_game);
    }

    for (int i = 0; i < manager.level_unlocked.size(); i++)
    {
        write_line("conquered level index [" + to_string(manager.level_unlocked[i]) + "]");
    }
}

void run_post_game(program_manager &manager)
{
    ;
}