/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:19 by bfresque          #+#    #+#             */
/*   Updated: 2023/06/30 15:01:24 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

t_init *init_data(t_init *data, char **av)
{
	data->nb_of_philo = ft_atoi_philo(av[1]);
	data->time_to_die = ft_atoi_philo(av[2]);
	data->time_to_eat = ft_atoi_philo(av[3]);
	data->time_to_sleep = ft_atoi_philo(av[4]);
	data->number_must_eat = ft_atoi_philo(av[5]);
	pthread_mutex_init(&data->is_eat, NULL);
	return data;
}


t_init *init_philo(t_init *data)
{
	int i;

	i = data->nb_of_philo -1;
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (data->philo == NULL)
		return NULL;
	while (i >= 0)
	{
		data->philo[i].id_philo = i + 1;
		data->philo[i].nb_eat_time = 0;
		data->philo[i].left_fork_id = i;
		data->philo[i].right_fork_id = (i + 1) % data->nb_of_philo;
		data->philo[i].time_last_eat = 0;
		i--;
	}
	return data;
}

t_init *init_forks(t_init *data)
{
	int i;

	i = data->nb_of_philo - 1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (data->forks == NULL)
		return NULL;
	while (i >= 0)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		i--;
	}
	return data;
}
