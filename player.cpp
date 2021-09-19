#include <cmath>
#include "splashkit.h"
#include "player.h"
#include "power_up.h"

bitmap ship_bitmap(ship_kind kind)
{
    switch (kind)
    {
    case AQUARII:
        return bitmap_named("aquarii");
    case GLIESE:
        return bitmap_named("gliese");
    case PEGASI:
        return bitmap_named("pegasi");
    default:
        return bitmap_named("aquarii");
    }
}

string ship_icon_string(ship_kind kind)
{
    switch (kind)
    {
    case AQUARII:
        return "aquarri_icon_";
    case GLIESE:
        return "gliese_icon_";
    case PEGASI:
        return "pegasi_icon_";
    default:
        return "aquarri_icon_";
    }
}

player_data new_player(int win_width, int win_height)
{
    player_data result;
    bitmap default_bitmap = ship_bitmap(AQUARII);

    // Create the sprite with 3 layers - we can turn on and off based
    // on the ship kind selected
    result.player_sprite = create_sprite(default_bitmap);

    sprite_add_layer(result.player_sprite, ship_bitmap(GLIESE), "GLIESE");
    sprite_add_layer(result.player_sprite, ship_bitmap(PEGASI), "PEGASI");

    // Default to layer 0 = Aquarii so hide others
    sprite_hide_layer(result.player_sprite, static_cast<int>(GLIESE));
    sprite_hide_layer(result.player_sprite, static_cast<int>(PEGASI));

    result.kind = AQUARII;

    // Position in the centre of the initial screen
    sprite_set_x(result.player_sprite, win_width / 2 - sprite_width(result.player_sprite) / 2);
    sprite_set_y(result.player_sprite, win_height / 2 - sprite_height(result.player_sprite) / 2);

    result.fuel_pct = 0.5;

    return result;
}

void draw_player(const player_data &player_to_draw)
{
    draw_sprite(player_to_draw.player_sprite);
}

void update_player(player_data &player_to_update)
{
    // Apply movement based on rotation and velocity in the sprite
    update_sprite(player_to_update.player_sprite);

    player_to_update.fuel_pct -= 0.0001 * sprite_dx(player_to_update.player_sprite);

    // Test edge of screen boundaries to adjust the camera
    double left_edge = camera_x() + SCREEN_BORDER;
    double right_edge = left_edge + screen_width() - 2 * SCREEN_BORDER;
    double top_edge = camera_y() + 3.6 * SCREEN_BORDER;                      //adjust top edge according to top HUD height, 1.2 is resulted from testing
    double bottom_edge = camera_y() + screen_height() - 2.5 * SCREEN_BORDER; //adjust bottom edge according to top Bottom HUD height, 1.8 is resulted from testing

    // Get the center of the player
    point_2d sprite_center = center_point(player_to_update.player_sprite);

    //confine player location within 3 times screen width and height
    if (sprite_center.x < -1 * screen_width())
    {
        sprite_set_x(player_to_update.player_sprite, sprite_x(player_to_update.player_sprite) + fabs(sprite_dx(player_to_update.player_sprite)));
        // write_line("plus");
        // write_line(sprite_x(player_to_update.player_sprite));
        // write_line(5 * fabs(sprite_dx(player_to_update.player_sprite)));
    }
    else if (sprite_center.x > 2 * screen_width())
    {
        sprite_set_x(player_to_update.player_sprite, sprite_x(player_to_update.player_sprite) - fabs(sprite_dx(player_to_update.player_sprite)));
        // write_line("minus");
        // write_line(sprite_x(player_to_update.player_sprite));
        // write_line(-5 * fabs(sprite_dx(player_to_update.player_sprite)));
    }

    if (sprite_center.y < -1 * screen_height())
    {
        sprite_set_y(player_to_update.player_sprite, sprite_y(player_to_update.player_sprite) + fabs(sprite_dx(player_to_update.player_sprite)));
        // write_line("plus");
        // write_line(sprite_y(player_to_update.player_sprite));
        // write_line(5 * fabs(sprite_dy(player_to_update.player_sprite)));
    }
    else if (sprite_center.y > 2 * screen_height())
    {
        sprite_set_y(player_to_update.player_sprite, sprite_y(player_to_update.player_sprite) - fabs(sprite_dx(player_to_update.player_sprite)));
        // write_line("minus");
        // write_line(sprite_y(player_to_update.player_sprite));
        // write_line(-5 * fabs(sprite_dy(player_to_update.player_sprite)));
    }

    // Move the camera to follow player location
    if (sprite_center.y < top_edge)
    {
        move_camera_by(0, sprite_center.y - top_edge);
    }
    else if (sprite_center.y > bottom_edge)
    {
        move_camera_by(0, sprite_center.y - bottom_edge);
    }

    if (sprite_center.x < left_edge)
    {
        move_camera_by(sprite_center.x - left_edge, 0);
    }
    else if (sprite_center.x > right_edge)
    {
        move_camera_by(sprite_center.x - right_edge, 0);
    }
}

void player_switch_ship(player_data &player, ship_kind target)
{
    // only do this if there is a change
    if (player.kind != target)
    {
        // show then hide layers
        sprite_show_layer(player.player_sprite, static_cast<int>(target));
        sprite_hide_layer(player.player_sprite, static_cast<int>(player.kind));

        // remember what is currently shown
        player.kind = target;
    }
}

void handle_input(player_data &player)
{
    // Allow the player to switch ships
    if (key_typed(NUM_1_KEY))
        player_switch_ship(player, AQUARII);
    if (key_typed(NUM_2_KEY))
        player_switch_ship(player, GLIESE);
    if (key_typed(NUM_3_KEY))
        player_switch_ship(player, PEGASI);

    // Handle movement - rotating left/right and moving forward/back
    float dx = sprite_dx(player.player_sprite);
    float rotation = sprite_rotation(player.player_sprite);

    // Allow rotation with left/right keys
    if (key_down(A_KEY))
        sprite_set_rotation(player.player_sprite, rotation - PLAYER_ROTATE_SPEED);
    if (key_down(D_KEY))
        sprite_set_rotation(player.player_sprite, rotation + PLAYER_ROTATE_SPEED);

    // Increase speed with up/down keys - typed to give step increases
    if (key_typed(S_KEY))
        sprite_set_dx(player.player_sprite, dx - PLAYER_SPEED);
    if (key_typed(W_KEY))
        sprite_set_dx(player.player_sprite, dx + PLAYER_SPEED);
}
