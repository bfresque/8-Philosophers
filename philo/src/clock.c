/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:58:47 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/30 13:51:35 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
long int	clock_timestamp(t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - data->time_start);
}

void	clock_down(t_data *data)
{
	pthread_mutex_lock(&data->mutex_timeover);
	if (data->timeover > 0)
		data->timeover--;
	pthread_mutex_unlock(&data->mutex_timeover);
}

int	clock_running(t_data *data)
{
	int	running;

	running = 0;
	pthread_mutex_lock(&data->mutex_timeover);
	if (data->timeover != 0)
		running = 1;
	pthread_mutex_unlock(&data->mutex_timeover);
	return (running);
}
