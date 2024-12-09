#include "includes/main.h"

int keybrd_hook(int key, t_game **game)
{
    double new_x = (*game)->map.x_player;
    double new_y = (*game)->map.y_player;

    // Movement calculations
    if (key == XK_W || key == XK_KP_UP) // Move forward
    {
        new_x += cos(deg_to_rad((*game)->map.facing)) * PLAYER_SPEED;
        new_y += sin(deg_to_rad((*game)->map.facing)) * PLAYER_SPEED;
    }
    else if (key == XK_S) // Move backward
    {
        new_x -= cos(deg_to_rad((*game)->map.facing)) * PLAYER_SPEED;
        new_y -= sin(deg_to_rad((*game)->map.facing)) * PLAYER_SPEED;
    }
    // else if (key == XK_A) // Strafe left
    // {
    //     new_x -= cos(deg_to_rad((*game)->map.facing + 90)) * PLAYER_SPEED;
    //     new_y -= sin(deg_to_rad((*game)->map.facing + 90)) * PLAYER_SPEED;
    //     debug_printf("Strafe Left: new_x = %f, new_y = %f\n", new_x, new_y);
    // }
    // else if (key == XK_D) // Strafe right
    // {
    //     new_x += cos(deg_to_rad((*game)->map.facing - 90)) * PLAYER_SPEED;
    //     new_y += sin(deg_to_rad((*game)->map.facing - 90)) * PLAYER_SPEED;
    //     debug_printf("Strafe Right: new_x = %f, new_y = %f\n", new_x, new_y);
    // }
    else if (key == XK_ESCAPE) // Exit game
    {
        exit_t(*game);
    }
    return (key);
}
