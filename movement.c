#include "includes/main.h"

// int player_move(t_game *game, int key)
// {
//     return (key);
// }

// int player_rotate(t_game *game, int key)
// {

//     return (key);
// }

int keybrd_hook(int key, t_game **game)
{
    // Movement calculations
    if (key == XK_ESCAPE) // Exit game
        exit_t(*game);
    // else if (key = XK_W || key == XK_S)
    //     player_move(game, key);
    // else if (key == XK_A || key == XK_D)
    //     player_rotate(game, key);
    return (key);
}
