#include "includes/main.h"

void    player_rotate(t_game *game)
{
    double oldDirX;
    double oldPlaneX;
    double rot_speed = ROT_SPEED * game->dt;

    if (game->keys[LEFT_ARR]) //rotate left
    {
        oldDirX = game->player.dirX;
        oldPlaneX = game->player.planeX;
        game->player.dirX = game->player.dirX * cos(-rot_speed) - game->player.dirY * sin(-rot_speed);
        game->player.dirY = oldDirX * sin(-rot_speed) + game->player.dirY * cos(-rot_speed);
        game->player.planeX = oldPlaneX * cos(-rot_speed) - game->player.planeY * sin(-rot_speed);
        game->player.planeY = oldPlaneX * sin(-rot_speed) + game->player.planeY * cos(-rot_speed);
        cast_all_rays(game);
    }       
    if (game->keys[RIGHT_ARR]) //rotate right
    {
        oldDirX = game->player.dirX;
        oldPlaneX = game->player.planeX;
        game->player.dirX = game->player.dirX * cos(rot_speed) - game->player.dirY * sin(rot_speed);
        game->player.dirY = oldDirX * sin(rot_speed) + game->player.dirY * cos(rot_speed);
        game->player.planeX = oldPlaneX * cos(rot_speed) - game->player.planeY * sin(rot_speed);
        game->player.planeY = oldPlaneX * sin(rot_speed) + game->player.planeY * cos(rot_speed);
        cast_all_rays(game);
    }
}

int    normalized_value(double value)
{
    int integer_val;
    double decimal;

    integer_val = (int)value;
    decimal = value - integer_val;
    if (decimal < 0.5)
        return (integer_val);
    return (integer_val + 1);
}

int check_collision(t_game *game, double x, double y)
{
    if (game->map.map[(int)y]
        [(int)(x + PLAYER_RADIUS)] == '1' || 
        game->map.map[(int)y]
        [(int)(x - PLAYER_RADIUS)] == '1' || 
        game->map.map[(int)(y + PLAYER_RADIUS)]
        [(int)x] == '1' || 
        game->map.map[(int)(y - PLAYER_RADIUS)]
        [(int)x] == '1')
            return (1);
    if (game->map.map[(int)(y + PLAYER_RADIUS)]
        [(int)(x + PLAYER_RADIUS)] == '1' ||
        game->map.map[(int)(y - PLAYER_RADIUS)]
        [(int)(x - PLAYER_RADIUS)] == '1' ||
        game->map.map[(int)(y + PLAYER_RADIUS)]
        [(int)(x - PLAYER_RADIUS)] == '1' ||
        game->map.map[(int)(y - PLAYER_RADIUS)]
        [(int)(x + PLAYER_RADIUS)] == '1')
            return (1);
    return (0);
}

void change_player_coords(t_game *game, double nextX, double nextY)
{
    if (!check_collision(game, nextX, nextY))
    {
        game->player.posX = nextX;
        game->player.posY = nextY;
    }
    // else // sliding very rarely gives seg fault in corners when using valgrind
    // {
    //     if (!check_collision(game, nextX, game->player.posY))
    //         game->player.posX = nextX;
    //     if (!check_collision(game, game->player.posX, nextY))
    //         game->player.posY = nextY;
    // }
}

void player_move(t_game *game)
{
    double nextX;
    double nextY;
    double strafeX;
    double strafeY;

    if (game->keys[119]) // Move forward
    {
        nextX = game->player.posX + game->player.dirX * PLAYER_SPEED * game->dt;
        nextY = game->player.posY + game->player.dirY * PLAYER_SPEED * game->dt;
        change_player_coords(game, nextX, nextY);
        cast_all_rays(game);
    }
    if (game->keys[115]) // Move backward
    {
        nextX = game->player.posX - game->player.dirX * PLAYER_SPEED * game->dt;
        nextY = game->player.posY - game->player.dirY * PLAYER_SPEED * game->dt;
        change_player_coords(game, nextX, nextY);
        cast_all_rays(game);
    }
    if (game->keys[100]) //strafe 
    {
        strafeX = -game->player.dirY;
        strafeY = game->player.dirX;
        nextX = game->player.posX + strafeX * (PLAYER_SPEED / 3 * 2) * game->dt;
        nextY = game->player.posY + strafeY * (PLAYER_SPEED / 2 * 2) * game->dt;
        change_player_coords(game, nextX, nextY);
        cast_all_rays(game);
    }
    if (game->keys[97]) // strafe
    {
        strafeX = game->player.dirY;
        strafeY = -game->player.dirX;
        nextX = game->player.posX + strafeX * (PLAYER_SPEED / 3 * 2) * game->dt;
        nextY = game->player.posY + strafeY * (PLAYER_SPEED / 3 * 2) * game->dt;
        change_player_coords(game, nextX, nextY);
        cast_all_rays(game);
    }
}
