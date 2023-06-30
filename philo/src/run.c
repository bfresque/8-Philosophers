/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:47:03 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/30 13:51:35 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
int	run_start(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_create(&data->akademia[i].pthread, NULL, philo_start, \
					(void *)&data->akademia[i]))
			return (11);
		i += 2;
	}
	usleep(50);
	i = 1;
	while (i < data->nb_of_philo)
	{
		if (pthread_create(&data->akademia[i].pthread, NULL, philo_start, \
					(void *)&data->akademia[i]))
			return (11);
		i += 2;
	}
	run_trial(data);
	return (0);
}

void	run_trial(t_data *data)
{
	int			i;
	long int	hungry;

	i = 0;
	while (clock_running(data))
	{
		pthread_mutex_lock(&data->akademia[i].mutex_last_meal);
		hungry = clock_timestamp(data) - data->akademia[i].last_meal;
		pthread_mutex_unlock(&data->akademia[i].mutex_last_meal);
		if (hungry > (long int) data->time_to_die)
		{
			philo_dying(&data->akademia[i]);
			break ;
		}
		i = (i + 1) % data->nb_of_philo;
	}
}

void	run_join(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_of_philo)
		pthread_join(data->akademia[i].pthread, NULL);
}
