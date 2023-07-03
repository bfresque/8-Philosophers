/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:19 by bfresque          #+#    #+#             */
/*   Updated: 2023/07/03 11:58:23 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

t_init *init_data(t_init *init, char **av)
{
	init->nb_of_philo = ft_atoi_philo(av[1]);
	init->time_to_die = ft_atoi_philo(av[2]);
	init->time_to_eat = ft_atoi_philo(av[3]);
	init->time_to_sleep = ft_atoi_philo(av[4]);
	init->number_must_eat = ft_atoi_philo(av[5]);
	init->all_philo_finished = 0;
	return init;
}


t_init *init_philo(t_init *init)
{
	int i;

	i = init->nb_of_philo -1;
	init->philo = malloc(sizeof(t_philo) * init->nb_of_philo);
	if (init->philo == NULL)
		return NULL;
	while (i >= 0)
	{
		init->philo[i].id_philo = i + 1;
		init->philo[i].nb_eat_time = 0;
		init->philo[i].left_fork_id = i;
		init->philo[i].right_fork_id = (i + 1) % init->nb_of_philo;
		init->philo[i].time_last_eat = 0;
		i--;
	}
	return init;
}

t_init *init_forks(t_init *init)
{
	int i;

	i = 0;
	init->forks = malloc(sizeof(pthread_mutex_t) * init->nb_of_philo);
	if (init->forks == NULL)
		return NULL;
	while (i < init->nb_of_philo)
	{
		pthread_mutex_init(&(init->forks[i]), NULL);
		i++;
	}
	return init;
}