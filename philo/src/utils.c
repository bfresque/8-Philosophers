/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:26:21 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/30 13:51:30 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	utils_printmsg(t_data *data, int nb, char *str)
{
	int	timer;

	pthread_mutex_lock(&data->mutex_timeover);
	timer = data->timeover;
	if (timer)
		printf("%ld %d %s\n", clock_timestamp(data), nb, str);
	pthread_mutex_unlock(&data->mutex_timeover);
	return (timer == 0);
}
