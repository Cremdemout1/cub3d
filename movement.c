#include "includes/main.h"

#define DEBUG 1 // Set to 0 to disable debug logs
#define debug_printf(...) if (DEBUG) printf(__VA_ARGS__)

int keybrd_hook(int key, t_game **game)
{
    double new_x = (*game)->map.x_player;
    double new_y = (*game)->map.y_player;

    // Movement calculations
    if (key == XK_W) // Move forward
    {
        new_x += cos(deg_to_rad((*game)->map.facing)) * PLAYER_SPEED;
        new_y += sin(deg_to_rad((*game)->map.facing)) * PLAYER_SPEED;
        debug_printf("Move Forward: new_x = %f, new_y = %f\n", new_x, new_y);
    }
    else if (key == XK_S) // Move backward
    {
        new_x -= cos(deg_to_rad((*game)->map.facing)) * PLAYER_SPEED;
        new_y -= sin(deg_to_rad((*game)->map.facing)) * PLAYER_SPEED;
        debug_printf("Move Backward: new_x = %f, new_y = %f\n", new_x, new_y);
    }
    else if (key == XK_A) // Strafe left
    {
        new_x -= cos(deg_to_rad((*game)->map.facing + 90)) * PLAYER_SPEED;
        new_y -= sin(deg_to_rad((*game)->map.facing + 90)) * PLAYER_SPEED;
        debug_printf("Strafe Left: new_x = %f, new_y = %f\n", new_x, new_y);
    }
    else if (key == XK_D) // Strafe right
    {
        new_x += cos(deg_to_rad((*game)->map.facing - 90)) * PLAYER_SPEED;
        new_y += sin(deg_to_rad((*game)->map.facing - 90)) * PLAYER_SPEED;
        debug_printf("Strafe Right: new_x = %f, new_y = %f\n", new_x, new_y);
    }
    else if (key == XK_KP_RIGHT) // Rotate right
    {
        (*game)->map.facing += ROT_SPEED;
        if ((*game)->map.facing >= 360)
            (*game)->map.facing -= 360;
        debug_printf("Rotate Right: facing = %d\n", (*game)->map.facing);
    }
    else if (key == XK_KP_LEFT) // Rotate left
    {
        (*game)->map.facing -= ROT_SPEED;
        if ((*game)->map.facing < 0)
            (*game)->map.facing += 360;
        debug_printf("Rotate Left: facing = %d\n", (*game)->map.facing);
    }
    else if (key == XK_ESCAPE) // Exit game
    {
        exit_t(*game);
    }

    // Map boundaries and collision detection
    int grid_x = (int)(new_x / XPM_X);
    int grid_y = (int)(new_y / XPM_Y);

    debug_printf("Collision Check: grid_x = %d, grid_y = %d\n", grid_x, grid_y);

    if (grid_x >= 0 && grid_x < (*game)->map.biggest_width &&
        grid_y >= 0 && grid_y < (*game)->map.length &&
        (*game)->map.map[grid_y][grid_x] != '1') // Check if new position is walkable
    {
        (*game)->map.x_player = new_x;
        (*game)->map.y_player = new_y;
        cast_all_rays(*game); // Only update the view if movement is valid
    }

    return (key);
}

// #include "includes/main.h"

// int keybrd_hook(int key, t_game **game)
// {
//     double new_x = (*game)->map.x_player;
//     double new_y = (*game)->map.y_player;

//     // Movement calculations
//     if (key == XK_W) // Move forward
//     {
//         if ((*game)->map.map[(int)])
//     }
//     else if (key == XK_S) // Move backward
//     {
    
//     }
//     else if (key == XK_A) // Strafe left
//     {

//     }
//     else if (key == XK_D) // Strafe right
//     {
      
//     else if (key == XK_KP_RIGHT) // Rotate right
//     {
      
//     }
//     else if (key == XK_KP_LEFT) // Rotate left
//     {
     
//     }
//     else if (key == XK_ESCAPE) // Exit game
//         exit_t(*game);

//     int grid_x = (int)(new_x / XPM_X);
//     int grid_y = (int)(new_y / XPM_Y);

//     return (key);
// }
