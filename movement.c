#include "includes/main.h"

void    player_rotate(t_game *game)
{
    if (game->keys[97]) //rotate left
    {
        double oldDirX;
        double oldPlaneX;

        oldDirX = game->player.dirX;
        oldPlaneX = game->player.planeX;

        game->player.dirX = game->player.dirX * cos(-ROT_SPEED) - game->player.dirY * sin(-ROT_SPEED);
        game->player.dirY = oldDirX * sin(-ROT_SPEED) + game->player.dirY * cos(-ROT_SPEED);
        game->player.planeX = oldPlaneX * cos(-ROT_SPEED) - game->player.planeY * sin(-ROT_SPEED);
        game->player.planeY = oldPlaneX * sin(-ROT_SPEED) + game->player.planeY * cos(-ROT_SPEED);
        cast_all_rays(game);
    }       
    if (game->keys[100]) //rotate right
    {
        double oldDirX;
        double oldPlaneX;

        oldDirX = game->player.dirX;
        oldPlaneX = game->player.planeX;
        game->player.dirX = game->player.dirX * cos(ROT_SPEED) - game->player.dirY * sin(ROT_SPEED);
        game->player.dirY = oldDirX * sin(ROT_SPEED) + game->player.dirY * cos(ROT_SPEED);
        game->player.planeX = oldPlaneX * cos(ROT_SPEED) - game->player.planeY * sin(ROT_SPEED);
        game->player.planeY = oldPlaneX * sin(ROT_SPEED) + game->player.planeY * cos(ROT_SPEED);
        cast_all_rays(game);
    }
}

int    normalized_value(double value)
{
    int integer_val;
    double decimal;

    integer_val = (int)value;
    decimal = value - integer_val;
    if (decimal < 0.2)
        return (integer_val);
    return (integer_val + 1);
}

void player_move(t_game *game)
{
    // if (game->keys[119]) // Move forward
    // {
    //     if (game->map.map[(int)(game->player.posX + game->player.dirX * PLAYER_SPEED)]
    //         [(int)game->player.posY] != '1')
    //         game->player.posX += game->player.dirX * PLAYER_SPEED;
    //     if (game->map.map[(int)game->player.posX]
    //         [(int)(game->player.posY + game->player.dirY * PLAYER_SPEED)])
    //         game->player.posY += game->player.dirY * PLAYER_SPEED;
    //     cast_all_rays(game);
    // }
    if (game->keys[119]) // Move forward
    {
        int normalizedX = normalized_value(game->player.posX);
        int normalizedY = normalized_value(game->player.posY);

        printf("X: %d\nY: %d\n", normalizedX, normalizedY);
        printf("dirX: %f\ndirY: %f\n", game->player.dirX, game->player.dirY);
        printf("width: %d\nlength: %d\n", game->map.width[normalizedX], game->map.length);
        if (game->map.map[normalizedY][(int)(normalizedX + game->player.dirX * PLAYER_SPEED)] != '1')
            game->player.posX += game->player.dirX * PLAYER_SPEED;
        if (game->map.map[(int)(normalizedY + game->player.dirY * PLAYER_SPEED)][normalizedX])
            game->player.posY += game->player.dirY * PLAYER_SPEED;
        cast_all_rays(game);
    }

    if (game->keys[115]) // Move backward
    {
        if (game->map.map[(int)game->player.posY][(int)(game->player.posX - game->player.dirX * PLAYER_SPEED)])
            game->player.posX -= game->player.dirX * PLAYER_SPEED;
        if (game->map.map[(int)(game->player.posY - game->player.dirY * PLAYER_SPEED)][(int)game->player.posX])
            game->player.posY -= game->player.dirY * PLAYER_SPEED;
        cast_all_rays(game);
    }
}

