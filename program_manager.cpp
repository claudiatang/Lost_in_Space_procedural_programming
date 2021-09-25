#include "splashkit.h"
#include "program_manager.h"

bool if_level_unlocked(const program_manager &manager, const game_level &level)
{
    bool if_unlocked = false;

    for (int i = 0; i < manager.levels_unlocked.size(); i++)
    {
        if (level == manager.levels_unlocked[i])
        {
            if_unlocked = true;
        }
    }

    return if_unlocked;
}

void add_unlocked_level(program_manager &manager)
{
    bool add_new_unlocked = true;

    for (int i = 0; i < manager.levels_unlocked.size(); i++)
    {
        if (static_cast<int>(manager.game.level) + 1 == static_cast<int>(manager.levels_unlocked[i]) || static_cast<int>(manager.game.level) > 1)
        {
            add_new_unlocked = false;
        }
    }

    if (add_new_unlocked == true)
    {
        manager.levels_unlocked.push_back(static_cast<game_level>(static_cast<int>(manager.game.level) + 1));
    }
}

void add_unlocked_ship(program_manager &manager, bool &play_unlock_anim)
{
    bool add_new_unlocked = true;

    for (int i = 0; i < manager.ships_unlocked.size(); i++)
    {
        if (static_cast<int>(manager.game.level) + 1 == static_cast<int>(manager.ships_unlocked[i]) || static_cast<int>(manager.game.level) > 1)
        {
            add_new_unlocked = false;
        }
    }

    if (add_new_unlocked == true)
    {
        manager.ships_unlocked.push_back(static_cast<ship_kind>(static_cast<int>(manager.game.level) + 1));
        play_unlock_anim = true;
    }
}

void handle_select_level(program_manager &manager, const button &button_to_check, bool &selected)
{

    if (mouse_clicked(LEFT_BUTTON) && loc_within_button(button_to_check, mouse_position()) && button_to_check.active)
    {
        if (button_to_check.name == "level_one")
        {
            manager.level = LEVEL_1;
            selected = true;
        }
        else if (button_to_check.name == "level_two")
        {
            manager.level = LEVEL_2;
            selected = true;
        }
        else if (button_to_check.name == "level_three")
        {
            manager.level = LEVEL_3;
            selected = true;
        }
    }
}

void handle_continue_exit(program_manager &manager, const button &button_to_check, bool &selected)
{
    if (mouse_clicked(LEFT_BUTTON) && loc_within_button(button_to_check, mouse_position()))
    {
        if (button_to_check.name == "continue game")
        {
            manager.continue_next_game = true;
            selected = true;
            write_line("continue set to true, selected set to true");
        }
        else if (button_to_check.name == "exit game")
        {
            manager.continue_next_game = false;
            selected = true;
            write_line("continue set to false, selected set to true");
        }
    }
}

void set_initial_unlocked_level(program_manager &manager)
{
    for (int i = 0; i < manager.levels_unlocked.size(); i++)
    {
        manager.levels_unlocked.pop_back();
    }

    manager.levels_unlocked.push_back(LEVEL_1);
}

void set_initial_unlocked_ship(program_manager &manager)
{
    for (int i = 0; i < manager.ships_unlocked.size(); i++)
    {
        manager.ships_unlocked.pop_back();
    }

    manager.ships_unlocked.push_back(AQUARII);
}

program_manager create_new_manager()
{
    program_manager manager;

    set_initial_unlocked_level(manager);

    set_initial_unlocked_ship(manager);

    manager.continue_next_game = true;

    return manager;
}

void run_title_screen()
{
    write_line("step into title");
    //int title_seconds;
    timer title_timer = create_timer("Title Timer");
    bitmap title_bgd = bitmap_named("title_screen_bgd");
    bitmap title_font = bitmap_named("title_font");

    start_timer("Title Timer");

    play_music("title_music");

    while (!quit_requested() && timer_ticks(title_timer) < 7500 && !key_typed(RETURN_KEY))
    {
        process_events();
        clear_screen(COLOR_BLACK);
        //write_line("step into title while loop");

        draw_bitmap(title_bgd, 0, 0);
        draw_bitmap(title_font, screen_width() / 2 - bitmap_width(title_font) / 2, screen_height() / 2 - bitmap_height(title_font) / 2);
        draw_text("Press 'Enter' to Skip", COLOR_BLACK, "hackbotfont", 25, 450, 650);
        draw_text("Press 'Enter' to Skip", COLOR_ALICE_BLUE, "hackbotfont", 25, 453, 653);

        refresh_screen(60);
    }

    free_timer(title_timer);
}

void run_level_selection(program_manager &manager)
{
    write_line("step into level selection");
    bool level_selected = false;

    button level_one = level_selection_button("level", "_1", 90, 185, if_level_unlocked(manager, LEVEL_1), "level_one");
    button level_two = level_selection_button("level", "_2", 495, 185, if_level_unlocked(manager, LEVEL_2), "level_two");
    button level_three = level_selection_button("level", "_3", 900, 185, if_level_unlocked(manager, LEVEL_3), "level_three");

    while (!quit_requested() && !level_selected)
    {

        process_events();
        handle_select_level(manager, level_one, level_selected);
        if (!level_selected)
        {
            handle_select_level(manager, level_two, level_selected);
        }
        if (!level_selected)
        {
            handle_select_level(manager, level_three, level_selected);
        }

        clear_screen(COLOR_BLACK);
        draw_bitmap("title_screen_bgd", 0, 0);
        draw_button(level_one);
        draw_button(level_two);
        draw_button(level_three);
        refresh_screen(60);
    }

    write_line("selected level " + to_string(manager.level));
}

void run_game_play(program_manager &manager)
{
    manager.game = create_new_game(manager.level, manager.ships_unlocked);
    music game_bgm = music_named("macross_bgm");
    bool finish_sound_played = false;

    //set all initial numbers of player power ups to be 0
    for (int i = 0; i < manager.game.player.player_power_ups.size(); i++)
    {
        manager.game.player.player_power_ups[i].number = 0;
    }

    while (!quit_requested() && !manager.game.game_exit)
    {
        if (!music_playing() && !manager.game.game_finished)
        {
            play_music(game_bgm, 1, 0.9);
        }
        else if (manager.game.game_finished)
        {
            fade_music_out(manager.game.time.seconds_elapsed * 1000 + 1000 - timer_ticks(manager.game.time.game_timer));
            if (manager.game.game_won && !sound_effect_playing("win_1") && !finish_sound_played)
            {
                finish_sound_played = true;
                play_sound_effect("win_1");
            }
            else if (!sound_effect_playing("lose") && !finish_sound_played)
            {
                finish_sound_played = true;
                play_sound_effect("lose");
            }
        }

        if (sound_effect_playing("be_hit") || sound_effect_playing("collect_1") || sound_effect_playing("collect_2"))
        {
            set_music_volume(0.1);
        }
        else
        {
            set_music_volume(0.9);
        }

        //manage_game_play_audio(manager, game_bgm, finish_sound_played);
        // Handle input to adjust player movement
        process_events();
        handle_input(manager.game.player);

        update_game(manager.game);

        // Redraw everything
        clear_screen(COLOR_BLACK);

        draw_game(manager.game);

        refresh_screen(60);
    }

    if (manager.game.game_won)
    {
        add_unlocked_level(manager);
    }

    for (int i = 0; i < manager.levels_unlocked.size(); i++)
    {
        write_line("unlocked level index [" + to_string(manager.levels_unlocked[i]) + "]");
    }
}

void run_post_game(program_manager &manager)
{
    bool continue_exit_selected = false;
    bool if_play_unlock_ship = false;
    int anim_tick_count = 0;

    button continue_game = continue_exit_button("continue_button", 250, 600, "continue game");
    button exit_game = continue_exit_button("exit_button", 840, 600, "exit game");
    int score_to_draw = manager.game.player.score;
    add_bonus_points(manager.game);
    move_camera_to(0, 0);

    if (manager.game.game_won)
    {
        add_unlocked_ship(manager, if_play_unlock_ship);
    }

    while (!quit_requested() && !continue_exit_selected)
    {
        process_events();
        handle_continue_exit(manager, continue_game, continue_exit_selected);
        if (!continue_exit_selected)
        {
            handle_continue_exit(manager, exit_game, continue_exit_selected);
        }

        clear_screen(COLOR_BLACK);

        update_bonus_points(manager.game.player.score, manager.game.player.bonus, score_to_draw);
        draw_post_game_scoreboard(score_to_draw, manager.game.power_up_kinds, manager.game.player, continue_game, exit_game, manager.game.time.seconds_remained);

        if (if_play_unlock_ship)
        {
            play_unlock_ship(static_cast<ship_kind>(static_cast<int>(manager.game.level) + 1), anim_tick_count);
        }

        refresh_screen(60);
    }
}

void run_program_manager(program_manager &manager)
{
    run_title_screen();

    while (!quit_requested() && manager.continue_next_game)
    {
        run_level_selection(manager);

        run_game_play(manager);

        run_post_game(manager);
    }
}