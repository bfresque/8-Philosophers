/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:32 by bfresque          #+#    #+#             */
/*   Updated: 2023/08/09 09:13:51 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	routine_one(t_init *init, t_philo *philo)
{
	int	i;

	i = 1;
	while (i <= init->number_must_eat)
	{
		take_fork(init, philo);
		if (i == init->number_must_eat)
			break ;
		action_sleep(init, philo);
		action_think(init, philo);
		i++;
	}
}

void	routine_two(t_init*init, t_philo *philo)
{
	int	i;

	i = 1;
	while (i && (check_flag_died(init) == 0))
	{
		take_fork(init, philo);
		action_sleep(init, philo);
		action_think(init, philo);
		i++;
	}
}

void	*philo_life(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->init->nb_of_philo == 1)
	{
		while (check_flag_died(data->init) == 0)
			check_all_deaths(data->init, data->philo);
		return (NULL);
	}
	if (data->init->number_must_eat > 0)
		routine_one(data->init, data->philo);
	else if (data->init->number_must_eat < 0)
		routine_two(data->init, data->philo);
	return (NULL);
}

void	wait_threads(t_init *init)
{
	int	i;

	i = 0;
	while (i < init->nb_of_philo)
	{
		pthread_join(init->philo[i].thread_id, NULL);
		free(init->philo[i].data);
		i++;
	}
}

void	start_threads(t_init *init)
{
	int		i;
	int		j;
	t_data	*data;

	i = 0;
	j = 0;
	data = NULL;
	while (i < init->nb_of_philo)
	{
		data = malloc(sizeof(t_data));
		if (!data)
		{
			cleanup_data(init, j);
			return ;
		}
		data->init = init;
		data->philo = &init->philo[i];
		data->philo->start_time = ft_get_time();
		data->philo->time_last_eat = ft_get_time();
		init->philo[i].data = data;
		pthread_create(&init->philo[i].thread_id, NULL, philo_life, data);
		usleep(50);
		i++;
	}
	wait_threads(init);
}
