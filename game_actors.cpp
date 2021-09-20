#include "splashkit.h"
#include "game_actors.h"

bitmap power_up_image(const power_up_kind &kind)
{
    switch (kind)
    {
    case SHIELD:
        return bitmap_named("shield");
    case POWER:
        return bitmap_named("power");
    case POTION:
        return bitmap_named("potion");
    case DROPS:
        return bitmap_named("drops");
    case DIAMOND:
        return bitmap_named("diamond");
    case STAR:
        return bitmap_named("star");
    case CASH:
        return bitmap_named("cash");
    case LEVEL:
        return bitmap_named("level");
    case BULLET:
        return bitmap_named("bullet");
    case COIN:
        return bitmap_named("coin");
    case HEART:
        return bitmap_named("heart");
    case MUSCLE:
        return bitmap_named("muscle");
    case TIME:
        return bitmap_named("time");
    default:
        return bitmap_named("star");
        write_line("!!!power up image wrong!!!");
    }
}

bitmap garbage_image(const garbage_kind &kind)
{
    switch (kind)
    {
    case ASTEROID:
        return bitmap_named("garbage_asteroid");
    case BULB:
        return bitmap_named("garbage_bulb");
    case TIN:
        return bitmap_named("garbage_tin");
    case TV:
        return bitmap_named("garbage_tv");
    default:
        return bitmap_named("garbage_asteroid");
        write_line("!!!garbage image wrong!!!");
    }
}

bitmap fuel_image(const fuel_kind &kind)
{
    switch (kind)
    {
    case FUEL:
        return bitmap_named("fuel");
    case BATTERY:
        return bitmap_named("battery");
    case NOS:
        return bitmap_named("nos");
    default:
        return bitmap_named("fuel");
        write_line("!!!fuel image wrong!!!");
    }
}

point_2d scr_rnd_loc()
{
    point_2d screen_rand_loc;

    screen_rand_loc.x = rnd(screen_width()) + camera_x();
    screen_rand_loc.y = rnd(screen_height()) + camera_y();

    return screen_rand_loc;
}

power_up_data new_power_up(double x, double y, const power_up_kind &kind)
{
    power_up_data result;

    result.kind = kind;
    //result.been_hit = false;
    result.power_up_sprite = create_sprite(power_up_image(result.kind));

    sprite_set_x(result.power_up_sprite, x);
    sprite_set_y(result.power_up_sprite, y);

    sprite_set_dx(result.power_up_sprite, rnd() * 4 - 2);
    sprite_set_dy(result.power_up_sprite, rnd() * 4 - 2);

    return result;
}

void draw_game_power_ups(const vector<power_up_data> &power_ups_to_draw)
{
    for (int i = 0; i < power_ups_to_draw.size(); i++)
    {
        draw_sprite(power_ups_to_draw[i].power_up_sprite);
    }
}

void update_power_up(power_up_data &power_up_to_update)
{
    //Move power-up sprite according to sprite x and y velocity set in new power-up function
    update_sprite(power_up_to_update.power_up_sprite);

    double left_bound = camera_x() - 25 * SCREEN_BORDER;
    double right_bound = camera_x() + screen_width() + 25 * SCREEN_BORDER;
    double top_bound = camera_y() - 25 * SCREEN_BORDER;
    double bottom_bound = camera_y() + screen_height() + 25 * SCREEN_BORDER;

    point_2d sprite_center = center_point(power_up_to_update.power_up_sprite);

    if (sprite_center.y < top_bound || sprite_center.y < -1 * screen_height())
    {
        sprite_set_dy(power_up_to_update.power_up_sprite, rnd(0, 2));
    }
    else if (sprite_center.y > bottom_bound || sprite_center.y > 2 * screen_height())
    {
        sprite_set_dy(power_up_to_update.power_up_sprite, (-1) * rnd(0, 2));
    }

    if (sprite_center.x < left_bound || sprite_center.x < -1 * screen_width())
    {
        sprite_set_dx(power_up_to_update.power_up_sprite, rnd(0, 2));
    }
    else if (sprite_center.x > right_bound || sprite_center.x < 2 * screen_width())
    {
        sprite_set_dx(power_up_to_update.power_up_sprite, (-1) * rnd(0, 2));
    }
}

fuel_data new_fuel(double x, double y, const fuel_kind &kind)
{
    fuel_data result;

    result.kind = kind;
    result.fuel_sprite = create_sprite(fuel_image(result.kind));

    sprite_set_x(result.fuel_sprite, x);
    sprite_set_y(result.fuel_sprite, y);

    sprite_set_dx(result.fuel_sprite, rnd() * 4 - 2);
    sprite_set_dy(result.fuel_sprite, rnd() * 4 - 2);

    return result;
}

void draw_game_fuels(const vector<fuel_data> &fuels_to_draw)
{
    for (int i = 0; i < fuels_to_draw.size(); i++)
    {
        draw_sprite(fuels_to_draw[i].fuel_sprite);
    }
}

// void update_fuel(fuel_data &fuel_to_update)
// {
//     //Move fuel sprite according to sprite x and y velocity set in new fuel function
//     update_sprite(fuel_to_update.fuel_sprite);

//     double left_bound = -1.5 * SCREEN_BORDER;
//     double right_bound = 1.5 * SCREEN_BORDER;
//     double top_bound = -1.5 * SCREEN_BORDER;
//     double bottom_bound = 1.5 * SCREEN_BORDER;

//     point_2d sprite_center = center_point(fuel_to_update.fuel_sprite);

//     if (sprite_center.y < top_bound || sprite_center.y < -1 * screen_height())
//     {
//         sprite_set_dy(fuel_to_update.fuel_sprite, rnd(0, 2));
//     }
//     else if (sprite_center.y > bottom_bound || sprite_center.y > 2 * screen_height())
//     {
//         sprite_set_dy(fuel_to_update.fuel_sprite, (-1) * rnd(0, 2));
//     }

//     if (sprite_center.x < left_bound || sprite_center.x < -1 * screen_width())
//     {
//         sprite_set_dx(fuel_to_update.fuel_sprite, rnd(0, 2));
//     }
//     else if (sprite_center.x > right_bound || sprite_center.x < 2 * screen_width())
//     {
//         sprite_set_dx(fuel_to_update.fuel_sprite, (-1) * rnd(0, 2));
//     }
// }

garbage_data new_garbage(double x, double y, const garbage_kind &kind)
{
    garbage_data result;

    result.kind = kind;
    result.garbage_sprite = create_sprite(garbage_image(result.kind));

    sprite_set_x(result.garbage_sprite, x);
    sprite_set_y(result.garbage_sprite, y);

    sprite_set_dx(result.garbage_sprite, rnd() * 4 - 2);
    sprite_set_dy(result.garbage_sprite, rnd() * 4 - 2);

    return result;
}

void draw_garbage(const vector<garbage_data> &garbages_to_draw)
{
    for (int i = 0; i < garbages_to_draw.size(); i++)
    {
        draw_sprite(garbages_to_draw[i].garbage_sprite);
    }
}

void update_actor_sprite(sprite &sprite_to_update)
{
    update_sprite(sprite_to_update);

    double left_bound = -1.5 * SCREEN_BORDER;
    double right_bound = 1.5 * SCREEN_BORDER;
    double top_bound = -1.5 * SCREEN_BORDER;
    double bottom_bound = 1.5 * SCREEN_BORDER;

    point_2d sprite_center = center_point(sprite_to_update);

    if (sprite_center.y < top_bound || sprite_center.y < -1 * screen_height())
    {
        sprite_set_dy(sprite_to_update, rnd(0, 2));
    }
    else if (sprite_center.y > bottom_bound || sprite_center.y > 2 * screen_height())
    {
        sprite_set_dy(sprite_to_update, (-1) * rnd(0, 2));
    }

    if (sprite_center.x < left_bound || sprite_center.x < -1 * screen_width())
    {
        sprite_set_dx(sprite_to_update, rnd(0, 2));
    }
    else if (sprite_center.x > right_bound || sprite_center.x < 2 * screen_width())
    {
        sprite_set_dx(sprite_to_update, (-1) * rnd(0, 2));
    }
}