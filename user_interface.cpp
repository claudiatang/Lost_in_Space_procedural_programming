#include "splashkit.h"
#include "user_interface.h"

button create_new_button(string str_stem, string str_num, float x, float y)
{
    button new_button;
    bitmap button_image = bitmap_named(str_stem + str_num + "_active");

    new_button.button_sprite = create_sprite(button_image);

    sprite_add_layer(new_button.button_sprite, bitmap_named(str_stem + "_inactive"), "inactive");

    sprite_hide_layer(new_button.button_sprite, "inactive");

    sprite_set_x(new_button.button_sprite, x);
    sprite_set_y(new_button.button_sprite, y);

    return new_button;
}

void draw_button(button &button)
{
    draw_sprite(button.button_sprite);
}

void update_button(button &button)
{
    update_sprite(button.button_sprite);

    if (button.active)
    {
        sprite_show_layer(button.button_sprite, "active");
        sprite_hide_layer(button.button_sprite, "inactive");
    }
    else if (!button.active)
    {
        sprite_show_layer(button.button_sprite, "inactive");
        sprite_hide_layer(button.button_sprite, "active");
    }
}

string format_time(int seconds)
{
    string result;

    if (seconds % 60 < 10 && seconds >= 0)
    {
        result = to_string(seconds / 60) + ":0" + to_string(seconds % 60);
    }
    else if (seconds % 60 < 60 && seconds >= 10)
    {
        result = to_string(seconds / 60) + ":" + to_string(seconds % 60);
    }

    return result;
}

void draw_pct_bar(const player_data &player, double x, double y)
{
    bitmap empty_fuel = bitmap_named("empty");
    bitmap green_bar_bubbles = bitmap_named("green_bar_bubbles");

    draw_text("FUEL:", COLOR_ORANGE, "hackbotfont", 20, x, y, option_to_screen());
    draw_bitmap(empty_fuel, x + 60, y - 5, option_to_screen());
    draw_bitmap(green_bar_bubbles, x + 60, y - 5, option_part_bmp(0, 0, player.fuel_pct * bitmap_width(green_bar_bubbles), bitmap_height(green_bar_bubbles), option_to_screen()));
}

void draw_ship_icon(const player_data &player, ship_kind ship_kin, double x, double y)
{
    //decide whether to render colourful icon or greyed icon
    bitmap ship_icon;
    if (player.kind == ship_kin)
    {
        ship_icon = bitmap_named(ship_icon_string(ship_kin) + "color");
    }
    else
    {
        ship_icon = bitmap_named(ship_icon_string(ship_kin) + "grey");
    }

    draw_bitmap(ship_icon, x, y, option_to_screen());
    //indicate keyboard input for the icon and give a black shadow effect
    draw_text(std::to_string(static_cast<int>(ship_kin) + 1), COLOR_BLACK, "hackbotfont", 25, x + 5, y + 5, option_to_screen()); //the shadow of the following line
    draw_text(std::to_string(static_cast<int>(ship_kin) + 1), COLOR_WHITE_SMOKE, "hackbotfont", 25, x + 2, y + 2, option_to_screen());
}

point_2d mini_map_coordinate(const sprite &actor, int map_width, int map_height)
{
    point_2d actor_map_loc;
    actor_map_loc.x = (center_point(actor).x + screen_width()) / 18;
    actor_map_loc.y = (center_point(actor).y + screen_height()) / 18;
    return actor_map_loc;
}

void draw_minimap(const vector<power_up_data> &power_ups, const vector<fuel_data> &fuels, const player_data &player, double x, double y, int map_width, int map_height)
{
    //get the interger part of player location x y;
    int player_x = (int)center_point(player.player_sprite).x;
    int player_y = (int)center_point(player.player_sprite).y;

    //draw rectangle minimap;
    fill_rectangle(COLOR_BLACK, x, y, map_width, map_height, option_to_screen());

    //draw power up dots
    for (int i = 0; i < power_ups.size(); i++)
    {
        fill_circle(COLOR_WHITE_SMOKE, mini_map_coordinate(power_ups[i].power_up_sprite, map_width, map_height).x + x - 1, mini_map_coordinate(power_ups[i].power_up_sprite, map_width, map_height).y + y - 1, 1, option_to_screen());
    }

    //draw fuels dots
    for (int i = 0; i < fuels.size(); i++)
    {
        fill_circle(COLOR_GREEN, mini_map_coordinate(fuels[i].fuel_sprite, map_width, map_height).x + x - 1, mini_map_coordinate(fuels[i].fuel_sprite, map_width, map_height).y + y - 1, 1, option_to_screen());
    }

    //draw player dot
    fill_circle(COLOR_ORANGE_RED, mini_map_coordinate(player.player_sprite, map_width, map_height).x + x - 1, mini_map_coordinate(player.player_sprite, map_width, map_height).y + y - 1, 1, option_to_screen());

    //print the integer part of player location x y
    draw_text("LOCATION:  " + std::to_string(player_x) + "  " + std::to_string(player_y), COLOR_ORANGE, "hackbotfont", 20, x, screen_height() / 6 + y + 5, option_to_screen());
}

void draw_power_up_icon(const power_up_kind &power_up_kind, int power_up_num, double x, double y)
{
    bitmap power_up_icon = power_up_image(power_up_kind);
    draw_bitmap(power_up_icon, x, y, option_to_screen());
    draw_text("X " + std::to_string(power_up_num), COLOR_BLACK, "hackbotfont", 40, bitmap_width(power_up_icon) / 2 + x + 3, bitmap_width(power_up_icon) * 2 / 3 + y + 3, option_to_screen()); //shadow of the following line
    draw_text("X " + std::to_string(power_up_num), COLOR_WHITE_SMOKE, "hackbotfont", 40, bitmap_width(power_up_icon) / 2 + x, bitmap_width(power_up_icon) * 2 / 3 + y, option_to_screen());
}

void draw_score(const player_data &player)
{
    draw_text("SCORE: " + to_string(player.score), COLOR_ORANGE, "hackbotfont", 25, 450, 30, option_to_screen());
}

void draw_time_remained(int seconds_remained, double x, double y)
{
    draw_text(format_time(seconds_remained), COLOR_ORANGE, "hackbotfont", 25, x, y, option_to_screen());
}

//return the number of each power up kind the player collected
int player_power_up_number(const player_data &player, const power_up_kind &kind)
{
    int number;
    bool kind_exist = false;

    for (int i = 0; i < player.player_power_ups.size(); i++)
    {
        if (player.player_power_ups[i].kind == kind)
        {
            number = player.player_power_ups[i].number;
            kind_exist = true;
        }
    }

    if (kind_exist == true)
    {
        return number;
    }
    else
    {
        return 0;
    }
}

void draw_hud(const player_data &player, const vector<power_up_data> &game_power_ups, const vector<fuel_data> &game_fuels, const vector<power_up_kind> &game_power_up_kinds)
{
    bitmap hud_top = bitmap_named("hud_bgd");
    bitmap hud_bottom = bitmap_named("hud_bgd_btm");

    int hud_bgd_top_width = bitmap_width(hud_top);
    int hub_bgd_btm_width = bitmap_width(hud_bottom);
    int hub_bgd_btm_height = bitmap_height(hud_bottom);

    draw_bitmap(hud_top, (screen_width() - hud_bgd_top_width) / 2, 10, option_to_screen());
    draw_bitmap(hud_bottom, (screen_width() - hub_bgd_btm_width) / 2, screen_height() - hub_bgd_btm_height - 15, option_to_screen());

    draw_pct_bar(player, 20, 30);

    draw_ship_icon(player, AQUARII, 20, 80);
    draw_ship_icon(player, GLIESE, 120, 80);
    draw_ship_icon(player, PEGASI, 220, 80);

    draw_score(player);

    draw_minimap(game_power_ups, game_fuels, player, 1010, 20, screen_width() / 6, screen_height() / 6);

    //Draw power up icons according to the game's power ups
    //and player's power up numbers
    for (int i = 0; i < game_power_up_kinds.size(); i++)
    {
        draw_power_up_icon(game_power_up_kinds[i], player_power_up_number(player, game_power_up_kinds[i]), 30 + i * 150, screen_height() - hub_bgd_btm_height - 50);
    }

    //draw YOU WIN when game power ups are zero
    // if (game_power_ups.size() == 0)
    // {
    //     //write_line("YOU WIN!!");
    // }
}

void draw_game_play_finish(bool finished, bool win)
{
    if (finished && win)
    {
        draw_text("YOU WIN !!", COLOR_ORANGE, "hackbotfont", 150, screen_width() / 2 - 350, screen_height() / 2 - 50, option_to_screen());
    }
    else if (finished && !win)
    {
        draw_text("GAME OVER", COLOR_ORANGE, "hackbotfont", 150, screen_width() / 2 - 350, screen_height() / 2 - 50, option_to_screen());
    }
}
