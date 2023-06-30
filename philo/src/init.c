/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:09:29 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/30 13:51:35 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
int	init_data(t_data *data, int ac, char **av)
{
	memset(data, 0, sizeof(t_data));
	if (parsing_atoi(&data->nb_of_philo, av[1]))
		return (1);
	if (parsing_atoi(&data->time_to_die, av[2]))
		return (2);
	if (parsing_atoi(&data->time_to_eat, av[3]))
		return (3);
	if (parsing_atoi(&data->time_to_sleep, av[4]))
		return (4);
	if (6 == ac)
	{
		if (parsing_atoi(&data->must_eat, av[5]))
			return (5);
	}
	else
		data->must_eat = -1;
	return (init_data_etc(data));
}

int	init_data_etc(t_data *data)
{
	int	think;

	data->timeover = data->nb_of_philo;
	think = (data->time_to_die - \
			(data->time_to_eat + data->time_to_sleep)) / 2;
	if (think < 0)
		think = 0;
	if (1 == data->nb_of_philo)
		think = -1;
	data->time_to_think = think;
	if (pthread_mutex_init(&data->mutex_timeover, NULL))
		return (6);
	data->time_start = 0;
	data->time_start = clock_timestamp(data);
	if (init_akademia(data))
		return (7);
	return (init_ware(data));
}

int	init_akademia(t_data *data)
{
	int	i;

	data->akademia = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (NULL == data->akademia)
		return (1);
	i = -1;
	while (++i < data->nb_of_philo)
	{
		if (init_philo(data, i))
			return (1);
	}
	return (0);
}

int	init_philo(t_data *data, int i)
{
	data->akademia[i].number = i + 1;
	data->akademia[i].must_eat = data->must_eat;
	data->akademia[i].last_meal = clock_timestamp(data);
	if (pthread_mutex_init(&data->akademia[i].mutex_last_meal, NULL))
		return (1);
	data->akademia[i].pthread = 0;
	data->akademia[i].data = data;
	return (0);
}

int	init_ware(t_data *data)
{
	int	i;

	data->ware = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (NULL == data->ware)
		return (8);
	i = -1;
	while (++i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->ware[i], NULL))
			return (9);
	}
	return (0);
}
