#include <cmath>
#include "splashkit.h"
#include "lost_in_space.h"

//the number of corresponding player power up kind incremented by 1
//player score incremented by 100
void add_player_power_up(player_data &player, power_up_kind &kind)
{
    bool kind_exist = false;

    //when player already has this power up kind in its list
    for (int i = 0; i < player.player_power_ups.size(); i++)
    {
        if (player.player_power_ups[i].kind == kind)
        {
            player.player_power_ups[i].number += 1;
            kind_exist = true;

            player.score += 100;
        }
    }

    //when player has not got this power up kind
    if (kind_exist == false)
    {
        player_power_up new_player_power_up;
        new_player_power_up.kind = kind;
        new_player_power_up.number = 1;
        player.player_power_ups.push_back(new_player_power_up);

        player.score += 100;
    }
}

void add_player_fuel(player_data &player, fuel_kind &kind)
{
    switch (kind)
    {
    case FUEL:
        player.fuel_pct = min(player.fuel_pct + 0.1, 1.0);
        break;
    case BATTERY:
        player.fuel_pct = min(player.fuel_pct + 0.2, 1.0);
        break;
    case NOS:
        player.fuel_pct = min(player.fuel_pct + 0.5, 1.0);
        break;
    default:
        break;
    }
}

void reduce_player_fuel(player_data &player, garbage_kind &kind)
{
    if (kind == ASTEROID)
    {
        player.fuel_pct = max(player.fuel_pct - 0.002, 0.0);
    }
    else
    {
        player.fuel_pct = max(player.fuel_pct - 0.001, 0.0);
    }
}

void delete_game_power_up(game_data &game, int indx)
{
    for (int k = indx; k < game.power_ups.size() - 1; k++)
    {
        game.power_ups[k] = game.power_ups[k + 1];
    }

    game.power_ups.pop_back();
}

void delete_game_fuel(game_data &game, int indx)
{
    write_line("pass in indx [" + to_string(indx) + "]");
    for (int j = indx; j < game.fuels.size() - 1; j++)
    {
        write_line("j " + to_string(j));
        game.fuels[j] = game.fuels[j + 1];
    }

    game.fuels.pop_back();
}

void update_game_status(game_data &game)
{
    if (game.time.seconds_remained <= 0 || game.player.fuel_pct <= 0 || game.power_ups.size() <= 0)
    {
        game.game_finished = true;
    }

    if (game.game_finished && game.time.seconds_remained > 0 && game.player.fuel_pct > 0)
    {
        game.game_won = true;
    }

    if (!game.game_exit && timer_ticks(game.time.game_timer) / 1000 - game.time.seconds_elapsed > 3)
    {
        game.game_exit = true;
        if (has_timer("Game Timer"))
        {
            free_timer(game.time.game_timer);
        }
    }
}

void update_game(game_data &game)
{

    //update game time
    if (!game.game_finished && !game.game_won && !game.game_exit)
    {
        game.time.seconds_elapsed = timer_ticks(game.time.game_timer) / 1000;
        game.time.seconds_remained = game.time.seconds_allowed - game.time.seconds_elapsed;

        //update player
        update_player(game.player);

        //update player collision with power ups
        for (int i = 0; i < game.power_ups.size(); i++)
        {
            //write_line("power up index [" + to_string(i) + "]");
            update_power_up(game.power_ups[i]);

            if (sprite_collision(game.power_ups[i].power_up_sprite, game.player.player_sprite))
            {
                add_player_power_up(game.player, game.power_ups[i].kind);
                //write_line("added player power up.");
                delete_game_power_up(game, i);
            }
        }

        //update player collision with fuels
        for (int i = 0; i < game.fuels.size(); i++)
        {
            update_actor_sprite(game.fuels[i].fuel_sprite);

            if (sprite_collision(game.fuels[i].fuel_sprite, game.player.player_sprite))
            {
                add_player_fuel(game.player, game.fuels[i].kind);
                delete_game_fuel(game, i);
            }
        }

        //update player collision with garbages
        for (int i = 0; i < game.garbages.size(); i++)
        {
            update_actor_sprite(game.garbages[i].garbage_sprite);

            if (sprite_collision(game.garbages[i].garbage_sprite, game.player.player_sprite))
            {
                reduce_player_fuel(game.player, game.garbages[i].kind);
            }
        }
    }

    //update game status
    update_game_status(game);
}

bitmap get_bgd_image(const game_level &level)
{
    switch (level)
    {
    case LEVEL_1:
        return bitmap_named("space_background_1");
        break;
    case LEVEL_2:
        return bitmap_named("space_background_2");
        break;
    case LEVEL_3:
        return bitmap_named("space_background_3");
        break;
    default:
        return bitmap_named("space_background_1");
        write_line("!!!background image wrong!!!");
        break;
    }
}

void draw_game_bgd(const game_data &game)
{
    bitmap background = get_bgd_image(game.level);
    int rows;
    int columns;

    rows = std::ceil(3 * double(screen_height()) / double(bitmap_height(background)));
    columns = std::ceil(3 * double(screen_width()) / double(bitmap_width(background)));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            draw_bitmap(background, -1 * screen_width() + j * bitmap_width(background) - 100, -1 * screen_height() + i * bitmap_height(background) - 100);
        }
    }
}

void draw_game(const game_data &game)
{
    draw_game_bgd(game);

    draw_game_power_ups(game.power_ups);

    draw_game_fuels(game.fuels);

    draw_garbage(game.garbages);

    draw_hud(game.player, game.power_ups, game.fuels, game.garbages, game.power_up_kinds, game.time.seconds_remained);

    draw_game_play_finish(game.game_finished, game.game_won);

    draw_player(game.player);
}

vector<power_up_kind> game_power_up_kinds(game_level &level)
{
    vector<power_up_kind> kinds;

    switch (level)
    {
    case LEVEL_1:
        kinds = {STAR, COIN, DIAMOND};
        break;
    case LEVEL_2:
        kinds = {STAR, COIN, DIAMOND, HEART, SHIELD};
        break;
    case LEVEL_3:
        kinds = {STAR, COIN, DIAMOND, HEART, SHIELD, POWER, TIME, MUSCLE};
        break;
    default:
        write_line("!!!power up kinds assignment wrong!!!");
        break;
    }

    return kinds;
}

void add_game_power_ups(game_data &game)
{
    game.power_up_kinds = game_power_up_kinds(game.level);
    int kinds_size = game.power_up_kinds.size();
    int power_ups_num;

    switch (game.level)
    {
    case LEVEL_1:
        power_ups_num = rnd(8, 12);
        break;
    case LEVEL_2:
        power_ups_num = rnd(15, 18);
        break;
    case LEVEL_3:
        power_ups_num = rnd(20, 24);
        break;
    default:
        power_ups_num = rnd(8, 12);
        write_line("!!!set game power up number wrong!!!");
        break;
    }

    for (int i = 0; i < power_ups_num; i++)
    {
        game.power_ups.push_back(new_power_up(scr_rnd_loc().x, scr_rnd_loc().y, game.power_up_kinds[rnd(kinds_size)]));
    }
}

vector<fuel_kind> game_fuel_kinds(game_level &level)
{
    vector<fuel_kind> kinds;

    switch (level)
    {
    case LEVEL_1:
        kinds = {FUEL};
        break;
    case LEVEL_2:
        kinds = {FUEL, BATTERY};
        break;
    case LEVEL_3:
        kinds = {FUEL, BATTERY, NOS};
        break;
    default:
        kinds = {FUEL};
        write_line("!!!fuel kinds assignment wrong!!!");
        break;
    }

    return kinds;
}

void add_game_fuels(game_data &game)
{
    game.fuel_kinds = game_fuel_kinds(game.level);
    int kinds_size = game.fuel_kinds.size();
    int fuels_num = rnd(8, 12);

    for (int i = 0; i < fuels_num; i++)
    {
        game.fuels.push_back(new_fuel(rnd(int(-1.5 * screen_width()), int(1.5 * screen_width())) + 640, rnd(int(-1.5 * screen_height()), int(1.5 * screen_height())) + 360, game.fuel_kinds[rnd(kinds_size)]));
    }
}

void add_game_garbages(game_data &game)
{
    int garbages_num;

    switch (game.level)
    {
    case LEVEL_1:
        garbages_num = rnd(6, 8);
        break;
    case LEVEL_2:
        garbages_num = rnd(9, 11);
        break;
    case LEVEL_3:
        garbages_num = rnd(12, 15);
        break;
    default:
        garbages_num = rnd(8, 12);
        write_line("!!!set game garbage number wrong!!!");
        break;
    }

    for (int i = 0; i < garbages_num; i++)
    {
        game.garbages.push_back(new_garbage(rnd(int(-1.5 * screen_width()), int(1.5 * screen_width())), rnd(int(-1.5 * screen_height()), int(1.5 * screen_height())), garbage_kind(rnd(0, 3))));
    }
}

game_data create_new_game(game_level &level)
{
    game_data game;

    game.time.game_timer = create_timer("Game Timer");
    game.time.seconds_allowed = 60;
    start_timer("Game Timer");
    game.level = level;
    add_game_power_ups(game);
    add_game_fuels(game);
    add_game_garbages(game);
    game.game_exit = false;
    game.game_finished = false;
    game.game_won = false;

    game.player = new_player();

    return game;
}