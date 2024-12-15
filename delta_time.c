/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:23:11 by ycantin           #+#    #+#             */
/*   Updated: 2024/12/15 13:39:19 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/main.h"


void update_dt(t_game *game)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    game->dt = (current_time.tv_sec - game->last_time.tv_sec) +
                       (current_time.tv_usec - game->last_time.tv_usec) / 1e6;
    game->last_time = current_time;
}