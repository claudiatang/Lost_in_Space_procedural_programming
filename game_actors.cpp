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

void draw_garbages(const vector<garbage_data> &garbages_to_draw)
{
    for (int i = 0; i < garbages_to_draw.size(); i++)
    {
        draw_sprite(garbages_to_draw[i].garbage_sprite);
    }
}

void update_actor_sprite(sprite &sprite_to_update)
{
    update_sprite(sprite_to_update);

    point_2d sprite_center = center_point(sprite_to_update);

    if (sprite_center.y < -1 * screen_height())
    {
        sprite_set_dy(sprite_to_update, rnd(0, 2));
    }
    else if (sprite_center.y > 2 * screen_height())
    {
        sprite_set_dy(sprite_to_update, -1 * rnd(0, 2));
    }

    if (sprite_center.x < -1 * screen_width())
    {
        sprite_set_dx(sprite_to_update, rnd(0, 2));
    }
    else if (sprite_center.x > 2 * screen_width())
    {
        sprite_set_dx(sprite_to_update, -1 * rnd(0, 2));
    }
}

void delete_game_power_up(vector<power_up_data> &game_power_ups, int indx)
{
    for (int k = indx; k < game_power_ups.size() - 1; k++)
    {
        game_power_ups[k] = game_power_ups[k + 1];
    }

    game_power_ups.pop_back();
}

void delete_game_fuel(vector<fuel_data> &game_fuels, int indx)
{
    //write_line("pass in indx [" + to_string(indx) + "]");
    for (int j = indx; j < game_fuels.size() - 1; j++)
    {
        //write_line("j " + to_string(j));
        game_fuels[j] = game_fuels[j + 1];
    }

    game_fuels.pop_back();
}