#include "splashkit.h"
#include "user_interface.h"

button continue_exit_button(string bitmap_name, double x, double y, string button_name)
{
    button new_button;
    new_button.image = bitmap_named(bitmap_name);
    new_button.name = button_name;

    new_button.top_left.x = x;
    new_button.top_left.y = y;
    new_button.bottom_right.x = x + bitmap_width(new_button.image);
    new_button.bottom_right.y = y + bitmap_height(new_button.image);

    return new_button;
}

button level_selection_button(string str_stem, string str_num, double x, double y, bool is_active, string btn_name)
{
    button new_button;
    new_button.active = is_active;
    new_button.name = btn_name;

    if (new_button.active)
    {
        new_button.image = bitmap_named(str_stem + str_num + "_active");
    }
    else
    {
        new_button.image = bitmap_named(str_stem + "_inactive");
    }

    new_button.top_left.x = x;
    new_button.top_left.y = y;
    new_button.bottom_right.x = x + bitmap_width(new_button.image);
    new_button.bottom_right.y = y + bitmap_height(new_button.image);

    return new_button;
}

void draw_button(const button &button_to_draw)
{
    draw_bitmap(button_to_draw.image, button_to_draw.top_left.x, button_to_draw.top_left.y);
}

bool loc_within_button(const button &button, point_2d input_loc)
{
    if (input_loc.x > button.top_left.x && input_loc.x < button.bottom_right.x && input_loc.y > button.top_left.y && input_loc.y < button.bottom_right.y)
    {
        return true;
    }

    return false;
}

string format_time(int &seconds)
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

void draw_pct_bar(const double &fuel_pct, double x, double y)
{
    bitmap empty_fuel = bitmap_named("empty");
    //bitmap green_bar_bubbles = bitmap_named("green_bar_bubbles");

    draw_text("FUEL:", COLOR_ORANGE, "hackbotfont", 20, x, y, option_to_screen());
    draw_bitmap(empty_fuel, x + 60, y - 5, option_to_screen());
    if (fuel_pct >= 0.25)
    {
        draw_bitmap("green_bar_bubbles", x + 60, y - 5, option_part_bmp(0, 0, fuel_pct * bitmap_width("green_bar_bubbles"), bitmap_height("green_bar_bubbles"), option_to_screen()));
    }
    else
    {
        draw_bitmap("red_bar", x + 60, y - 5, option_part_bmp(0, 0, fuel_pct * bitmap_width("red_bar"), bitmap_height("red_bar"), option_to_screen()));
    }
}

void draw_ship_icon(const player_data &player, const ship_kind &kind, bool ship_unlocked, double x, double y)
{
    //decide whether to render colorful icon or greyed icon
    bitmap ship_icon;
    if (player.kind == kind && ship_unlocked)
    {
        ship_icon = bitmap_named(ship_icon_string(kind) + "color");
    }
    else if (ship_unlocked)
    {
        ship_icon = bitmap_named(ship_icon_string(kind) + "grey");
    }
    else
    {
        ship_icon = bitmap_named("ship_icon_locked_02");
    }

    draw_bitmap(ship_icon, x, y, option_to_screen());

    //indicate keyboard input for the icon and give a black shadow effect
    if (ship_unlocked)
    {
        draw_text(std::to_string(static_cast<int>(kind) + 1), COLOR_BLACK, "hackbotfont", 25, x + 5, y + 5, option_to_screen()); //the shadow of the following line
        draw_text(std::to_string(static_cast<int>(kind) + 1), COLOR_WHITE_SMOKE, "hackbotfont", 25, x + 2, y + 2, option_to_screen());
    }
}

point_2d mini_map_coordinate(const sprite &actor, int map_width, int map_height)
{
    point_2d actor_map_loc;
    actor_map_loc.x = (center_point(actor).x + screen_width()) / 18;
    actor_map_loc.y = (center_point(actor).y + screen_height()) / 18;
    return actor_map_loc;
}

void draw_minimap(const vector<power_up_data> &power_ups, const vector<fuel_data> &fuels, const vector<garbage_data> &garbages, const player_data &player, double x, double y, int map_width, int map_height)
{
    //get the interger part of player location x y;
    int player_x = (int)center_point(player.player_sprite).x;
    int player_y = (int)center_point(player.player_sprite).y;

    //draw rectangle minimap;
    fill_rectangle(COLOR_BLACK, x, y, map_width, map_height, option_to_screen());

    //draw power up dots
    for (int i = 0; i < power_ups.size(); i++)
    {
        fill_circle(COLOR_YELLOW, mini_map_coordinate(power_ups[i].power_up_sprite, map_width, map_height).x + x - 1, mini_map_coordinate(power_ups[i].power_up_sprite, map_width, map_height).y + y - 1, 1, option_to_screen());
    }

    //draw fuels dots
    for (int i = 0; i < fuels.size(); i++)
    {
        fill_circle(COLOR_GREEN, mini_map_coordinate(fuels[i].fuel_sprite, map_width, map_height).x + x - 1, mini_map_coordinate(fuels[i].fuel_sprite, map_width, map_height).y + y - 1, 1, option_to_screen());
    }

    //draw garbadge dots
    for (int i = 0; i < garbages.size(); i++)
    {
        fill_circle(COLOR_GRAY, mini_map_coordinate(garbages[i].garbage_sprite, map_width, map_height).x + x - 1, mini_map_coordinate(garbages[i].garbage_sprite, map_width, map_height).y + y - 1, 1, option_to_screen());
    }

    //draw player dot
    fill_circle(COLOR_ORANGE_RED, mini_map_coordinate(player.player_sprite, map_width, map_height).x + x - 1, mini_map_coordinate(player.player_sprite, map_width, map_height).y + y - 1, 1, option_to_screen());

    //print the integer part of player location x y
    draw_text("LOCATION:  " + std::to_string(player_x) + "  " + std::to_string(player_y), COLOR_ORANGE, "hackbotfont", 20, x, screen_height() / 6 + y + 5, option_to_screen());
}

void draw_power_up_summary(const power_up_kind &power_up_kind, int power_up_num, double x, double y)
{
    bitmap power_up_icon = power_up_image(power_up_kind);
    draw_bitmap(power_up_icon, x, y, option_scale_bmp(0.75, 0.75, option_to_screen()));
    draw_text("X " + std::to_string(power_up_num), COLOR_BLACK, "hackbotfont", 40, x + 505, y + 40, option_to_screen()); //shadow of the following line
    draw_text("X " + std::to_string(power_up_num), COLOR_WHITE_SMOKE, "hackbotfont", 40, x + 500, y + 35, option_to_screen());
}

void draw_score(const int &player_score, double x, double y)
{
    draw_text("SCORE: " + to_string(player_score), COLOR_ORANGE, "hackbotfont", 25, x, y, option_to_screen());
}

void draw_time_remained(int &seconds_remained, int font_size, double x, double y)
{
    draw_text(format_time(seconds_remained), COLOR_ORANGE, "hackbotfont", font_size, x, y, option_to_screen());
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

void draw_hud(const player_data &player, const vector<power_up_data> &game_power_ups, const vector<fuel_data> &game_fuels, const vector<garbage_data> &game_garbages, const vector<power_up_kind> &game_power_up_kinds, int seconds_remained)
{
    bitmap hud_top = bitmap_named("hud_bgd");

    int hud_bgd_top_width = bitmap_width(hud_top);

    draw_bitmap(hud_top, (screen_width() - hud_bgd_top_width) / 2, 10, option_to_screen());

    draw_pct_bar(player.fuel_pct, 20, 30);

    draw_ship_icon(player, AQUARII, if_ship_unlocked(player, AQUARII), 20, 80);
    draw_ship_icon(player, GLIESE, if_ship_unlocked(player, GLIESE), 120, 80);
    draw_ship_icon(player, PEGASI, if_ship_unlocked(player, PEGASI), 220, 80);

    draw_score(player.score, 450, 30);
    draw_time_remained(seconds_remained, 25, 760, 30);

    draw_minimap(game_power_ups, game_fuels, game_garbages, player, 1010, 20, screen_width() / 6, screen_height() / 6);
}

void draw_game_play_finish(bool finished, bool win)
{
    if (finished && win)
    {
        draw_text("YOU WIN !!", COLOR_ORANGE, "hackbotfont", 150, screen_width() / 2 - 350, screen_height() / 2 - 50, option_to_screen());
    }
    else if (finished && !win)
    {
        draw_text("GAME OVER", COLOR_ORANGE, "hackbotfont", 150, screen_width() / 2 - 400, screen_height() / 2 - 50, option_to_screen());
    }
}

void update_bonus_points(const int &score, const int &bonus, int &score_to_update)
{

    if (score_to_update < score + bonus)
    {
        score_to_update += 5;
        if (!sound_effect_playing("add_bonus_points"))
        {
            play_sound_effect("add_bonus_points");
        }
    }
}

void draw_bonus_points(const int &score_to_draw, int font_size, double x, double y)
{
    draw_text("SCORE ", COLOR_ORANGE, "hackbotfont", font_size, x, y);
    draw_text(to_string(score_to_draw), COLOR_ORANGE, "hackbotfont", font_size, x + 500, y);
}

void draw_post_game_scoreboard(const int &score_and_bonus, const vector<power_up_kind> &game_power_up_kinds, const player_data &player, const button &continue_button, const button &exit_button, int &sec_remained)
{
    int power_up_line_space = 400 / game_power_up_kinds.size();

    draw_bitmap("title_screen_bgd", 0, 0);
    draw_bitmap("scoreboard_bgd", 240, 60, option_to_screen());

    for (int i = 0; i < game_power_up_kinds.size(); i++)
    {
        draw_power_up_summary(game_power_up_kinds[i], player_power_up_number(player, game_power_up_kinds[i]), 350, 55 + i * power_up_line_space);
    }

    draw_text("TIME REMAINED ", COLOR_ORANGE, "hackbotfont", 30, 350, 500);
    draw_time_remained(sec_remained, 30, 850, 490);
    draw_bonus_points(score_and_bonus, 30, 350, 535);

    draw_button(continue_button);
    draw_button(exit_button);
}

void play_unlock_ship(const ship_kind &kind)
{
    bitmap unlocked_ship = bitmap_named(ship_icon_string(kind) + "unlock");
    draw_bitmap(unlocked_ship, 640 - bitmap_width(unlocked_ship) / 2, 360 - bitmap_height(unlocked_ship) / 2);
}